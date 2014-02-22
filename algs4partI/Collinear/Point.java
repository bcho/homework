/*************************************************************************
 * Name:
 * Email:
 *
 * Compilation:  javac Point.java
 * Execution:
 * Dependencies: StdDraw.java
 *
 * Description: An immutable data type for points in the plane.
 *
 *************************************************************************/

import java.util.Comparator;

public class Point implements Comparable<Point> {

    // compare points by slope
    public final Comparator<Point> SLOPE_ORDER = new SlopeCompareator();

    private final int x;                              // x coordinate
    private final int y;                              // y coordinate

    // create the point (x, y)
    public Point(int x, int y) {
        /* DO NOT MODIFY */
        this.x = x;
        this.y = y;
    }

    // plot this point to standard drawing
    public void draw() {
        /* DO NOT MODIFY */
        StdDraw.point(x, y);
    }

    // draw line between this point and that point to standard drawing
    public void drawTo(Point that) {
        /* DO NOT MODIFY */
        StdDraw.line(this.x, this.y, that.x, that.y);
    }

    // slope between this point and that point
    public double slopeTo(Point that) {
        if (this.compareTo(that) == 0) {
            return Double.NEGATIVE_INFINITY;
        }

        double dy = that.y - this.y;
        double dx = that.x - this.x;

        if (dy == 0) {
            return +0;
        }
        if (dx == 0) {
            return Double.POSITIVE_INFINITY;
        }
        return dy / dx;
    }

    // is this point lexicographically smaller than that one?
    // comparing y-coordinates and breaking ties by x-coordinates
    public int compareTo(Point that) {
        if (this.y == that.y) {
            return this.x - that.x;
        }
        return this.y - that.y;
    }

    // return string representation of this point
    public String toString() {
        /* DO NOT MODIFY */
        return "(" + x + ", " + y + ")";
    }

    private class SlopeCompareator implements Comparator<Point> {
        public int compare(Point v1, Point v2) {
            double slope1 = slopeTo(v1);
            double slope2 = slopeTo(v2);

            if (slope1 > slope2) {
                return 1;
            }
            if (slope1 < slope2) {
                return -1;
            }
            return 0;
        }
    }

    // unit test
    public static void main(String[] args) {
        Point a, b;

        // compareTo
        a = new Point(3, 4);
        b = new Point(3, 5);
        assert a.compareTo(b) < 0;
        assert b.compareTo(a) > 0;
        b = new Point(2, 4);
        assert a.compareTo(b) > 0;
        assert b.compareTo(a) < 0;
        assert b.compareTo(b) == 0;

        // slopeTo
        a = new Point(3, 4);
        b = new Point(1, 4);
        assert a.slopeTo(b) == 0.0;
        a = new Point(1, 3);
        b = new Point(1, 5);
        assert a.slopeTo(b) == Double.POSITIVE_INFINITY;
        assert b.slopeTo(a) == Double.POSITIVE_INFINITY;
        assert b.slopeTo(b) == Double.NEGATIVE_INFINITY;
        a = new Point(1, 4);
        b = new Point(2, 8);
        assert a.slopeTo(b) == 4;
        assert b.slopeTo(a) == a.slopeTo(b);

        // SLOPE_ORDER
        a = new Point(3, 4);
        b = new Point(3, 5);
        Point c = new Point(0, 0);
        assert c.SLOPE_ORDER.compare(a, b) < 0; 
        assert c.SLOPE_ORDER.compare(b, a) > 0; 
        assert c.SLOPE_ORDER.compare(b, b) == 0; 
    }
}
