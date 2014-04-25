using System.Collections;


namespace SortAlgorithm
{
    // 排序算法状态的接口定义.
    public interface ISortAlgorithmSnapShot
    {
        // 数据.
        double[] Data { get; }

        // 指针信息.
        Hashtable Pointers { get; }

        // 设置数据.
        // TODO use generic.
        void SetData(double[] data);

        // 设置指针值
        void SetPointer(string name, int index);
    }
}
