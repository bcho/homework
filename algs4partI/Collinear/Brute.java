import java.util.Arrays;

public class Brute {
    public static void main(String[] args) {
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);

        Point[] points;

        In file = new In(args[0]);
        int count = file.readInt();
        points = new Point[count];

        for (int i = 0; i < count && !file.isEmpty(); i++) {
            int x = file.readInt();
            int y = file.readInt();
            points[i] = new Point(x, y);
            points[i].draw();
        }

        Arrays.sort(points);

        for (int a = 0; a < count; a++) {
            for (int b = a + 1; b < count; b++) {
                double slopeBA = points[b].slopeTo(points[a]);
                for (int c = b + 1; c < count; c++) {
                    double slopeCA = points[c].slopeTo(points[a]);
                    if (slopeCA != slopeBA) {
                        continue;
                    }

                    for (int d = c + 1; d < count; d++) {
                        double slopeDA = points[d].slopeTo(points[a]);
                        if (slopeCA == slopeDA) {
                            StdOut.print(points[a].toString());
                            StdOut.print(" -> ");
                            StdOut.print(points[b].toString());
                            StdOut.print(" -> ");
                            StdOut.print(points[c].toString());
                            StdOut.print(" -> ");
                            StdOut.println(points[d].toString());

                            points[a].drawTo(points[d]);
                        }
                    }
                }
            }
        }
    }
}
