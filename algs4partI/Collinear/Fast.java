import java.util.Arrays;
import java.util.HashMap;
import java.util.ArrayList;

public class Fast {
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

        int begin, end;
        Point origin, last;
        double currentSlope;

        HashMap<Double, ArrayList<Point>> foundSlopes = new HashMap<Double, ArrayList<Point>>();
        boolean isFound;

        for (int i = 0; i < count; i++) {
            origin = points[i];

            // Sort points by their slope to the origin.
            Arrays.sort(points, i + 1, count, origin.SLOPE_ORDER);
            last = points[count - 1];

            // Find subgroups with the same slope to the origin.
            for (begin = i + 1, end = i + 2; end < count; end++) {
                Point b = points[begin];
                Point e = points[end];

                if (origin.slopeTo(b) != origin.slopeTo(e) || end == count - 1) {
                    currentSlope = origin.slopeTo(b);

                    // Reach to the end, make a force check.
                    if (end == count - 1 && currentSlope == origin.slopeTo(last)) {
                        end = count;
                    }

                    // Also make sure it's not been found yet.
                    isFound = false;
                    if (foundSlopes.containsKey(currentSlope)) {
                        ArrayList<Point> selected = foundSlopes.get(currentSlope);
                        for (int j = 0; j < selected.size(); j++) {
                            if (selected.get(j).slopeTo(origin) == currentSlope) {
                                isFound = true;
                                break;
                            }
                        }
                    }

                    // Subgroups size > 4, print it.
                    if (end - begin >= 3 && !isFound) {
                        // Sort the subgroup by coordination.
                        Arrays.sort(points, begin, end);

                        StdOut.print(origin.toString());
                        for (int j = begin; j < end; j++) {
                            StdOut.print(" -> ");
                            StdOut.print(points[j].toString());
                        }
                        StdOut.println();

                        origin.drawTo(points[end - 1]);

                        if (foundSlopes.containsKey(currentSlope)) {
                            foundSlopes.get(currentSlope).add(origin);
                        } else {
                            ArrayList<Point> selected;
                            selected = new ArrayList<Point>();
                            selected.add(origin);
                            foundSlopes.put(currentSlope, selected);
                        }
                    }
                    // Find next subgroup.
                    begin = end;
                }
            }

            // Restore position, ordered by point's coordination.
            Arrays.sort(points, i + 1, count);
        }
    }
}
