public class Percolation {
    private WeightedQuickUnionUF uf;
    private WeightedQuickUnionUF fullUf;
    private int size;
    private boolean[] sites;

    public Percolation(int N) {
        size = N;
        sites = new boolean[N * N + 2];
        // Include two virtual site at the top (0) and bottom (N^2 + 1).
        uf = new WeightedQuickUnionUF(N * N + 2);
        // Include top virtual site.
        fullUf = new WeightedQuickUnionUF(N * N + 1);

        for (int i = 0; i < N * N + 2; i++) {
            // Block all the sites at the begining.
            sites[i] = false;
        }
    }

    public void open(int i, int j) {
        if (i < 1 || i > size || j < 1 || j > size) {
            throw new IndexOutOfBoundsException();
        }

        if (isOpen(i, j)) {
            return;
        }

        int pos = project(i, j);
        sites[pos] = true;

        // Connect to all opened neighbours in NEWS.
        int[] dx = {1, 0, -1, 0};
        int[] dy = {0, 1, 0, -1};
        for (int a = 0; a < 4; a++) {
            int nx = dx[a] + i;
            int ny = dy[a] + j;
            int npos = project(nx, ny);
            if (nx >= 1 && nx <= size && ny >= 1 && ny <= size && isOpen(nx, ny)) {
                uf.union(npos, pos);
                fullUf.union(npos, pos);
            }
        }
        if (i == 1) {
            uf.union(0, pos);
            fullUf.union(0, pos);
        }
        if (i == size) {
            uf.union(size * size + 1, pos);
        }
    }

    public boolean isOpen(int i, int j) {
        if (i < 1 || i > size || j < 1 || j > size) {
            throw new IndexOutOfBoundsException();
        }

        return sites[project(i, j)];
    }

    public boolean isFull(int i, int j) {
        if (i < 1 || i > size || j < 1 || j > size) {
            throw new IndexOutOfBoundsException();
        }

        return fullUf.connected(0, project(i, j));
    }

    public boolean percolates() {
        return uf.connected(0, size * size + 1);
    }

    private int project(int i, int j) {
        return (i - 1) * size + j;
    }
}
