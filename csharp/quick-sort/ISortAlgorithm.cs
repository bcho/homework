using System;
using System.Collections;


namespace SortAlgorithm
{
    // 排序算法的接口定义.
    public interface ISortAlgorithm
    {
        // 数据规模.
        int Scale { get; }

        // 设置比较函数.
        // TODO Use generic type.
        // TODO Use another class?
        void SetComparator(Func<double, double, bool> cmp);

        // 初始化排序算法.
        void Seed();

        // 进行排序.
        void Sort();

        // 获取当前数据排列情况.
        IEnumerable Current();
    }
}
