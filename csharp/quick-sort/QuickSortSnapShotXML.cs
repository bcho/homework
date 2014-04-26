using System.Xml;
using System.Xml.Serialization;

namespace SortAlgorithm
{
    [XmlRootAttribute("shot")]
    public class QuickSortSnapShotXML : ISortAlgorithmSnapShotXML
    {
        // TODO use generic.
        [XmlArrayAttribute("data")]
        [XmlArrayItemAttribute("value")]
        public double[] Data { get; set; }

        [XmlArrayAttribute("colors")]
        [XmlArrayItemAttribute("value")]
        public Color[] Colors { get; set; }

        public QuickSortSnapShotXML(SortAlgorithmSnapShot shot)
        {
            Data = new double[shot.Data.Length];
            shot.Data.CopyTo(Data, 0);

            Colors = new Color[3];
            Colors[0] = new Color("p", (int) shot.Pointers["p"], ColorConstants.Red);
            Colors[1] = new Color("l", (int) shot.Pointers["l"], ColorConstants.Blue);
            Colors[2] = new Color("r", (int) shot.Pointers["r"], ColorConstants.Blue);
        }
        
        internal QuickSortSnapShotXML() {}
    }
}
