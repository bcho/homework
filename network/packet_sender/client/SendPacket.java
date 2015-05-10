import java.util.Arrays;
import java.lang.StringBuilder;
import java.nio.charset.Charset;

import java.io.DataOutputStream;

import java.net.InetAddress;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Socket;


public class SendPacket {

    protected static int localPort = 3000;
    
    protected abstract class Client {

        abstract void send(byte[] content) throws Exception;

    }

    protected class UDPClient extends Client {

        private int destPort = 2000;
        private InetAddress destIP;

        public UDPClient(InetAddress destIP_) {
            destIP = destIP_;
        }

        @Override
        public void send(byte[] content) throws Exception {
            DatagramSocket socket = new DatagramSocket(localPort);
            DatagramPacket packet = new DatagramPacket(
                    content,
                    content.length,
                    destIP,
                    destPort
            );
            socket.send(packet);
        }
    
    }

    protected class TCPClient extends Client {

        private InetAddress localIP;
        private int destPort = 1000;
        private InetAddress destIP;

        public TCPClient(InetAddress destIP_) {
            destIP = destIP_;

        }
    
        @Override
        public void send(byte[] content) throws Exception {
            Socket socket = new Socket(destIP, destPort, localIP, localPort);
            DataOutputStream writer = new DataOutputStream(socket.getOutputStream());
            writer.write(content, 0, content.length);
            socket.close();
        }
    
    }

    protected static class Utils {
    
        public static String join(String delimiter, String[] strs) {
            StringBuilder builder = new StringBuilder();
            for (int i = 0, il = strs.length; i < il; i++) {
                if (i > 0) {
                    builder.append(delimiter);
                }
                builder.append(strs[i]);
            }
            return builder.toString();
        }

    }

    public void showUsage() {
        System.err.println("SendPacket [TCP|UDP] [dest ip] [string ...]");
        System.exit(1);
    }

    public void reportSucceed() {
        System.exit(0);
    }

    public void reportFailed(Exception e) {
        System.err.println("Send failed:");
        System.err.println(e.getMessage());
        System.exit(1);
    }

    public void send(String protocol, String destIPStr, String content) {
        InetAddress destIP;
        try {
            destIP = InetAddress.getByName(destIPStr);
        } catch (Exception e) {
            reportFailed(e);
            return;
        }

        Client client;
        switch (protocol) {
            case "TCP":
                client = new TCPClient(destIP);
                break;
            case "UDP":
                client = new UDPClient(destIP);
                break;
            default:
                showUsage();
                return;
        }

        try {
            client.send(content.getBytes(Charset.forName("UTF-8")));
            reportSucceed();
        } catch (Exception e) {
            reportFailed(e);
        }
    }

    public static void main(String[] args) {
        SendPacket sender = new SendPacket();

        if (args.length < 3) {
            sender.showUsage();
        }

        String protocol = args[0].toUpperCase();
        String destIP = args[1];
        String content = Utils.join(
                " ",
                Arrays.copyOfRange(args, 2, args.length)
        );

        sender.send(protocol, destIP, content);
    }

}
