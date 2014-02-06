public class PercolationTest {

    public static void main(String[] args) {
        Percolation p;

        p = new Percolation(3);
        p.open(3, 3);
        p.open(1, 3);
        p.open(2, 3);
        p.open(3, 1);
        StdOut.println(p.percolates() == true);
        StdOut.println(p.isFull(3, 1) == false);
        StdOut.println(p.isFull(3, 3) == true);

        p = new Percolation(1);
        p.open(1, 1);
        StdOut.println(p.percolates() == true);
        StdOut.println(p.isFull(1, 1) == true);
    }

}
