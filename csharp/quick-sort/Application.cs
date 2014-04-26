using System;
using System.Xml;
using System.Xml.Serialization;
using System.IO;


namespace SortAlgorithm
{
    public class Application
    {
        private static string outputName = "data.xml";
        private static int defaultScale = 100;

        public static void Main(string[] args)
        {
            int scale;

            if (args.Length > 1)
            {
                bool result = Int32.TryParse(args[0], out scale);
                if (!result)
                {
                    System.Console.WriteLine("Please input a decimal number.");
                    return;
                }
            }
            else
            {
                scale = defaultScale;
            }

            Generate(scale);
        }

        private static void Generate(int scale)
        {
            QuickSort qs = new QuickSort(scale);

            qs.SetComparator((double a, double b) => a < b);
            qs.Seed();
            qs.Sort();

            XmlSerializer serializer = new XmlSerializer(typeof(QuickSortSnapShotsXML));
            TextWriter writer = new StreamWriter(outputName);
            serializer.Serialize(writer, qs.GetSnapShotsXML());
            writer.Close();
        }
    }
}
