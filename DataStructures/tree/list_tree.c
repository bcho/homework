/* list_tree.c: 树的双亲表示法实现 */

/* 结构体定义 */
struct tree {
    char *data;
    
    struct tree *left_child;
    struct tree *parent;
    struct tree *right_sibling;
};

/* ADT 清单 */

/* 
 * 创建并初始化一棵空树
 *
 * :rtype: struct tree *
 */
struct tree *tree_init();

/* 
 * 销毁一棵树及其所有子结点
 *
 * :param t: 被销毁的树
 */
void tree_destory(struct tree *t);

/*
 * 将一棵树置为空树
 *
 * .. warning:: 不释放子树节点
 *
 * :param t: 被置空的树
 */
void tree_clear(struct tree *t);

/*
 * 检测树是否为空
 *
 * .. note:: 时间复杂度为 O(1)
 *
 * :param t: 被检测的树
 * :rtype:  0 为非空，否则为空
 */
int tree_is_empty(struct tree *t);

/*
 * 获取结点的值
 *
 * :param t: 传入的结点
 * :rtype: 返回的是结点值的头地址
 */
char *tree_value(struct tree *t);

/*
 * 对结点进行赋值
 *
 * .. note:: 会复制传入的值到结点上
 *
 * :param t: 传入的结点
 * :param data: 传入的值
 */
void tree_assign(struct tree *t, const char *data);

/*
 * 向树插入新结点到第 i 位
 *
 * .. note:: 时间复杂度为 O(n)
 * .. note:: 子结点从 0 开始编号，如果插入位置小于 0 则插入到最开始，
 *           如果插入位置大于子结点总数，插入到最末端
 *
 * :param t: 传入的树
 * :param child: 传入的新结点
 * :param i: 插入的位置
 */
void tree_insert_child(struct tree *t, struct tree *child, int i);

/*
 * 从树中删除并返回第 i 个结点
 *
 * .. note:: 时间复杂度为 O(n)
 * .. note:: 子结点从 0 开始编号，如果删除位置不存在则返回 NULL
 *
 * :param t: 传入的树
 * :param i: 删除结点的位置
 * :rtype: struct tree *
 */
struct tree *tree_delete_child(struct tree *t, int i);

/*
 * 计算树的深度
 *
 * :param t: 被计算的树
 * :rtype: 树的深度
 */
int tree_depth(struct tree *t);

/*
 * 获取树的根
 *
 * .. note:: 如果传入的结点不是树根，
 *           则返回它的父结点的树根
 *
 * :param t: 传入的树
 * :rtype: 树根结点
 */
struct tree *tree_root(struct tree *t);

/*
 * 获取结点的父结点
 *
 * .. note:: 若当前结点没有父节点，返回它本身
 *
 * :param t: 传入的结点
 * :rtype: struct tree *
 */
struct tree *tree_parent(struct tree *t);

/*
 * 获取结点的左儿子
 *
 * .. note:: 若当前结点没有左儿子，返回 NULL
 *
 * :param t: 传入的结点
 * :rtype: struct tree *
 */
struct tree *tree_left_child(struct tree *t);

/*
 * 获取结点的右兄弟
 *
 * .. note:: 若当前结点没有右儿子，返回 NULL
 *
 * :param t: 传入的结点
 * :rtype: struct tree *
 */
struct tree *tree_right_sibling(struct tree *t);

/*
 * 对树执行先根遍历
 *
 * :param t: 被遍历的树
 * :param visitor: 遍历函数指针
 */
void tree_traverse_pre_root(struct tree *t,
                            void (*visitor)(const struct tree *));

/*
 * 对树执行后根遍历
 *
 * :param t: 被遍历的树
 * :param visitor: 遍历函数指针
 */
void tree_traverse_post_root(struct tree *t,
                             void (*visitor)(const struct tree *));

/*
 * 从字符串定义创建一棵树
 *
 * .. seealso:: TODO 字符串定义
 *
 * :param s: 字符串定义
 * :rtype: struct tree *
 */
struct tree *tree_from_string(char *s);

/*
 * 生成树的字符串形式 
 *
 * .. warning:: 返回的字符串是从堆分配的内存，
 *              使用后需要手动 free 回收
 *
 * :param t: 传入的树
 * :rtype: char *
 */
char *tree_stringify(struct tree *t);

/*
 * 将树转换成二叉树
 *
 * .. note:: 返回的是新树的指针
 *
 * :param t: 传入的树
 * :rtype: struct tree *
 */
struct tree *tree_to_binary(struct tree *t);


/* 测试程序 */
int main()
{
    return 0;
}
