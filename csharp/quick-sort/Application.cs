namespace SortAlgorithm
{
    public class Application
    {
        public static void Main()
        {
            QuickSort qs = new QuickSort(5);

            qs.SetComparator((double a, double b) => a < b);
            qs.Seed();
            qs.Sort();

            foreach (SortAlgorithmSnapShot shot in qs.GetSnapShots())
            {
                foreach (double d in shot.Data)
                {
                    System.Console.Write("{0} ", d);
                }
                System.Console.WriteLine();

                foreach (string key in shot.Pointers.Keys)
                {
                    System.Console.Write("{0} {1} ", key, shot.Pointers[key]);
                }
                System.Console.WriteLine();
            }

            System.Console.WriteLine();
        }
    }
}
