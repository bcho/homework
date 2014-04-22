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

            foreach (double i in qs.Current())
            {
                System.Console.Write("{0} ", i);
            }
            System.Console.WriteLine();
        }
    }
}
