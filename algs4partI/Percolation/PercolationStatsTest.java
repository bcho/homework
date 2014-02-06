public class PercolationStatsTest {

    public static void main(String[] args) {
        int N = StdIn.readInt();
        Percolation site = new Percolation(N);

        while (!StdIn.isEmpty()) {
            int i = StdIn.readInt();
            int j = StdIn.readInt();
            site.open(i, j);
            StdOut.println(site.percolates());
            if (site.percolates()) {
                break;
            }
        }
    }
}
