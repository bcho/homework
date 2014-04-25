using System.Xml;
using System.Xml.Serialization;


namespace SortAlgorithm
{
    // 预定义颜色常量.
    public static class ColorConstants
    {
        public const string Blue = "#2980b9";
        public const string Red = "#e74c3c";
        public const string Grey = "#bdc3c7";
    }

    // 指针颜色定义
    public class Color
    {
        [XmlAttribute("name")]
        public string Name;
        [XmlAttribute("index")]
        public int Index;
        [XmlAttribute("color")]
        public string Value;

        public Color(string name, int index, string value_)
        {
            Name = name;
            Index = index;
            Value = value_;
        }

        internal Color() {}
    }
}
