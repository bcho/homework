using System.Xml;
using System.Xml.Serialization;


namespace SortAlgorithm
{
    // 排序算法状态 XML 序列化的接口定义.
    [XmlRootAttribute("shot")]
    public interface ISortAlgorithmSnapShotXML
    {
        // TODO use generic.
        [XmlArrayAttribute("data")]
        [XmlArrayItemAttribute("value")]
        double[] Data { get; set; }

        [XmlArrayAttribute("colors")]
        [XmlArrayItemAttribute("value")]
        Color[] Colors { get; set; }
    }
}
