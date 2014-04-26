using System;
using System.Xml;
using System.Xml.Serialization;
using System.IO;


namespace SortAlgorithm
{
    public class Application
    {
        private static string TemplateBeginName = "index.html.tmpl.begin";
        private static string TemplateEndName = "index.html.tmpl.end";
        private static string OutputName = "index.html";
        private static string OutputDirectory = "site";
        private static int DefaultScale = 70;

        public static void Main(string[] args)
        {
            int scale;

            if (args.Length > 0)
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
                scale = DefaultScale;
            }

            Generate(scale);

            string path = BuildPath(OutputName);
            System.Diagnostics.Process.Start(path);
            System.Console.WriteLine("Please view output in {0}.", path);
        }

        private static void Generate(int scale)
        {
            QuickSort qs = new QuickSort(scale);

            qs.SetComparator((double a, double b) => a < b);
            qs.Seed();
            qs.Sort();

            XmlSerializer serializer = new XmlSerializer(typeof(QuickSortSnapShotsXML));
            TextWriter data = new StringWriter();
            serializer.Serialize(data, qs.GetSnapShotsXML());
            data.Close();

            TextWriter writer = new StreamWriter(BuildPath(OutputName));
            writer.Write("{0}{1}{2}", ReadTemplate(TemplateBeginName), data, ReadTemplate(TemplateEndName));
            writer.Close();
        }

        private static string BuildPath(string name)
        {
            string current = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            return System.IO.Path.Combine(current, name);
        }

        private static string ReadTemplate(string name)
        {
            string path = BuildPath(name);

            return System.IO.File.ReadAllText(path);
        }
    }
}
