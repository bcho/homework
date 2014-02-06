
public class PercolationStats {
    private double[] xt;
    private int times;
    private int size;

    public PercolationStats(int N, int T) {
        if (N <= 0 || T <= 0) {
            throw new IllegalArgumentException();
        }

        size = N;
        times = T;
        xt = new double[times];

        int count;
        Percolation site;
        for (int run = 0; run < times; run++) {
            site = new Percolation(size);
            count = 0;
            while (!site.percolates()) {
                int i = 1 + StdRandom.uniform(size);
                int j = 1 + StdRandom.uniform(size);
                if (!site.isOpen(i, j)) {
                    site.open(i, j);
                    count = count + 1;
                }
            }
            xt[run] = (double) count / (size * size);
        }
    }

    public double mean() {
        return StdStats.mean(xt);
    }

    public double stddev() {
        return StdStats.stddev(xt);
    }

    public double confidenceLo() {
        double miu = mean();
        double sig = stddev();

        return miu - 1.96 * sig / Math.sqrt(times);
    }

    public double confidenceHi() {
        double miu = mean();
        double sig = stddev();

        return miu + 1.96 * sig / Math.sqrt(times);
    }

    private int fromRange(int lo, int hi) {
        return lo + (int) (Math.random() * (hi - lo + 1));
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int T = Integer.parseInt(args[1]);

        PercolationStats stats = new PercolationStats(N, T);

        StdOut.println("mean                    = " + stats.mean());
        StdOut.println("stddev                  = " + stats.stddev());
        StdOut.println("95% confidence interval = " + stats.confidenceLo() + ", "
                + stats.confidenceHi());
    }
}
