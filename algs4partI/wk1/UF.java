public class UF {
    private int[] id;
    private int count;

    void union(int p, int q) {
        int parent_p = parent(p);
        int parent_q = parent(q);
        if (parent_p != parent_q) {
            count = count - 1;
        }
        id[parent_p] = parent_q;
    }

    private int parent(int i) {
        int _parent =  id[i];
        if (_parent != i) {
            id[i] = parent(_parent);
        }
        return id[i];
    }

    boolean connected(int p, int q) {
        return (parent(p) == parent(q));
    }

    int find(int p) {
        return id[p];
    }

    int count() {
        return count;
    }

    void show_id() {
        for (int i = 0;i < id.length;i++) {
            StdOut.print(id[i] + " ");
        }
        StdOut.println("");
    }

    public UF(int N) {
        count = N;
        id = new int[N];
        for (int i = 0;i < N;i++) {
            id[i] = i; 
        }
    }

    public static void main(String[] args) {
        int N = StdIn.readInt();
        UF uf = new UF(N);

        while (!StdIn.isEmpty()) {
            int p = StdIn.readInt();
            int q = StdIn.readInt();
            if (!uf.connected(p, q)) {
                uf.union(p, q);
                StdOut.println(p + " " + q);
            }
        }
        StdOut.println(uf.count() + " components");
        uf.show_id();
    }
}
