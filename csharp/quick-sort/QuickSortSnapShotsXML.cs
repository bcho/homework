using System.Xml;
using System.Xml.Serialization;
using System.Collections;
using System.Collections.Generic;
using System.Linq;


namespace SortAlgorithm
{
    // 排序算法状态 XML 序列化的接口定义.
    [XmlRootAttribute("sort")]
    public class QuickSortSnapShotsXML : ISortAlgorithmSnapShotsXML
    {
        [XmlArrayAttribute("snapshots")]
        [XmlArrayItem("snapshot")]
        public QuickSortSnapShotXML[] SnapShots { get; private set; }

        public QuickSortSnapShotsXML(IEnumerable<SortAlgorithmSnapShot> shots)
        {
            int i = 0;
            SnapShots = new QuickSortSnapShotXML[shots.Count()];
            foreach (SortAlgorithmSnapShot shot in shots)
            {
                SnapShots[i] = new QuickSortSnapShotXML(shot);
                i = i + 1;
            }
        }

        internal QuickSortSnapShotsXML() {}
    }
}
