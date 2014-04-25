using System;
using System.Collections;
using System.Collections.Generic;


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

        // 获取当前状态快照.
        SortAlgorithmSnapShot GetSnapShot();

        // 获取所有快照.
        IEnumerable<SortAlgorithmSnapShot> GetSnapShots();

        // 设置状态快照信息.
        void SetSnapShot(SortAlgorithmSnapShot sort);

        // 记录一个状态快照.
        void TakeSnapShot();
    }
}
