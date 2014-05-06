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



ADT 基本操作
============

创建并初始化一棵空树。

.. code:: C

    struct tree *tree_init();


销毁一棵树及其所有子节点。

.. code:: C
    
    void tree_destory(struct tree *t);


将一棵树置为空树

.. code:: C
    
    void tree_clear(struct tree *t);


检测树是否为空

.. code:: C

    int tree_is_empty(struct tree *t);


获取结点的值

.. code:: C
    
    char *tree_value(struct tree *t);


对结点进行赋值

.. code:: C

    void tree_assign(struct tree *t, char *data);


向树插入新结点到第 i 位

.. code:: C

    void tree_insert_child(struct tree *t, struct tree *child, int i);


从树中删除并返回第 i 个结点

.. code:: C
    
    struct tree *tree_delete_child(struct tree *t, int i);

    
计算树的深度

.. code:: C

    int tree_depth(struct tree *t);


获取树的根

.. code:: C

    struct tree *tree_root(struct tree *t);


获取结点的父结点

.. code:: C

    struct tree *tree_parent(struct tree *t);


获取结点的左儿子

.. code:: C

    struct tree *tree_left_child(struct tree *t);


获取结点的右兄弟

.. code:: C

    struct tree *tree_right_sibling(struct tree *t);


对树执行先根遍历

.. code:: C

    void tree_traverse_pre_root(struct tree *t, void (*visitor)(struct tree *));


对树执行后根遍历

.. code:: C

    void tree_traverse_post_root(struct tree *t, void (*visitor)(struct tree *));


从字符串定义创建一棵树

参见： 树的字符串形式_

.. code:: C

    struct tree *tree_from_string(char *s);


生成树的字符串形式

参见： 树的字符串形式_

.. code:: C

    char *tree_stringify(struct tree *t);



树的字符串形式
=============

为了更好地输入、输出树的结构定义，程序采取了用类似 S 表达式[#]_ 的助记符来进行描述。
在本定义中，每个结点的值作为一个``原子``，而一棵树则使用一个**多元**的
``广义表``进行描述。

例如 `(tree)` 表示的是一棵结点个数为 1，根结点值为 ``tree`` 的树。

又如：

.. code:: lisp

    ((A), (B), ((C), (D)), ((E), (F)))


表示的是一棵三层深的树，其中根结点为 ``A``，拥有 3 个子结点。其中 ``B`` 为第一个
儿子结点（左结点），``C``、``E`` 为另外两个结点。``D``、``F`` 则分别是 ``C`` 和
``F`` 结点的第一个儿子结点。


通过这种结构化的形式我们可以很好地把图形化的树状结构输入到程序中，为测试、调试提供了极大的方便。

.. [#] 此处将 S 表达式拓展成拥有多个原子结点的广义表。
