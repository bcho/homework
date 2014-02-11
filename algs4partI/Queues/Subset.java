public class Subset {
    public static void main(String[] args) {
        int k = Integer.parseInt(args[0]);
        String[] candidates = StdIn.readStrings();

        RandomizedQueue<String> q = new RandomizedQueue<String>();
        for (int i = 0; i < candidates.length; i++) {
            q.enqueue(candidates[i]);
        }

        for (int i = 0; !q.isEmpty() && i < k; i++) {
            StdOut.println(q.dequeue());
        }
    }
}
