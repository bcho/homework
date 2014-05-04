====================
树 数据结构 ADT 定义
====================


数据对象及关系定义
==================

数据对象: ``D``

``D`` 是具有相同特性的数据元素的集合。


数据关系: ``R``

- 若 :math:`D=\emptyset`，则称 :math:`D` 为空树

- 若 :math:`D` 中仅含有一个数据元素，则 :math:`R` 为空集，
  否则 :math:`R=\{H\}`， :math:`H` 是如下二元关系:

    (1) 在 :math:`D` 中存在唯一的称为根的数据元素 :math:`root`，
    它在关系 :math:`H` 下无前驱;

    (2) 若 :math:`D - \{root\} \neq \emptyset`，则存在 :math:`D - \{root\}` 的
    一个划分 :math:`D_{1}, D_{2}, ..., D_{m} \, (m > 0)`，
    对任意 :math:`j \neq k \, (1 \leq j, \, k \leq m)` 
    有 :math:`D_{j} \cap D_{k} = \emptyset`，
    且对任意的 :math:`i \, (1 \leq i \leq m)`, 
    唯一存在数据元素 :math:`x_{i} \subset D_{i}`，
    有 :math:`<root, \, x_{i}> \in H`;

    (3) 对应于 :math:`D - \{root\}` 的划分，
    :math:`H - \{<root, x_{i}>, \, ..., \, <root, x_{m}>\}`
    有唯一的一个划分 :math:`H_{1}, \, H_{2}, \, ..., \, H_{m} \, (m > 0)`,
    对任意 :math:`j \neq k \, (1 \leq j, k \leq m)`
    有 :math:`D_{j} \cap D_{k} = \emptyset`，且对任意 :math:`i \m (1 \leq i \leq m)`,
    :math:`H_{i}` 是 :math:`D_{i}` 上的二元关系，
    :math:`(D_{i}, \, {H_{i}})` 是一颗符合本定义的树，称为根 :math:`root` 的子树。
