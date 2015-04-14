using System;
using System.Collections;

using CSharp.Utils;

namespace CSharp.Lab1
{
    // 二叉树节点
    public class Node
    {
        public int Data { get; set; }

        public Node Left { get; set; }
        public Node Right { get; set; }

        public int Height {
            get {
                var subTreeHeight = 0;
                if (Left != null)
                {
                    subTreeHeight = Left.Height;
                }
                if (Right != null)
                {
                    var r = Right.Height;
                    subTreeHeight = subTreeHeight > r ? subTreeHeight : r;
                }
                return 1 + subTreeHeight;
            }
        }

        public int Leafs {
            get {
                if (Left == null && Right == null)
                {
                    return 1;
                }
                var leafs = 0;
                if (Left != null)
                {
                    leafs += Left.Leafs;
                }
                if (Right != null)
                {
                    leafs += Right.Leafs;
                }
                return leafs;
            }
        }

        public Node(int data)
        {
            Setup(data, null, null);
        }

        public Node(int data, Node left, Node right)
        {
            Setup(data, left, right);
        }

        public int CompareTo(Node other)
        {
            if (other.Data < Data)
            {
                return 1;
            }
            else if (other.Data > Data)
            {
                return -1;
            }

            return 0;
        }

        protected void Setup(int data, Node left, Node right)
        {
            Data = data;
            Left = left;
            Right = right;
        }
    }

    // 二叉树子节点添加器
    public abstract class AbstractChildNodeAdder
    {
        // 添加一个子节点
        abstract public AbstractChildNodeAdder AddChildNode(Node child);
        
        // 添加一个子节点
        public AbstractChildNodeAdder AddChildNode(int data)
        {
            return AddChildNode(new Node(data));
        }
    }

    // 二叉排序树子节点添加器
    public class SortTreeChildNodeAdder : AbstractChildNodeAdder
    {
        protected Node Root;

        public SortTreeChildNodeAdder(Node root)
        {
            Root = root;
        }

        public override AbstractChildNodeAdder AddChildNode(Node child)
        {
            Add(Root, child);

            return this;
        }

        protected void Add(Node root, Node child)
        {
            var cmp = root.CompareTo(child);

            // 放到左子树
            if (cmp >= 0)
            {
                if (root.Left == null)
                {
                    root.Left = child;
                }
                else
                {
                    Add(root.Left, child);
                }
            }
            // 放到右子树
            else
            {
                if (root.Right == null)
                {
                    root.Right = child;
                }
                else
                {
                    Add(root.Right, child);
                }
            }
        }
    }

    // 完全二叉树子节点添加器
    public class CompleteTreeChildNodeAdder : AbstractChildNodeAdder
    {
        protected Node Root;
        protected int Nodes;

        public CompleteTreeChildNodeAdder(Node root)
        {
            Root = root;
            Nodes = 1;
        }

        public override AbstractChildNodeAdder AddChildNode(Node child)
        {
            Nodes += 1;
            var parent = ParentNode(Nodes);
            if (parent.Left == null)
            {
                parent.Left = child;
            }
            else if (parent.Right == null)
            {
                parent.Right = child;
            }

            return this;
        }

        protected Node ParentNode(int now)
        {
            int parentNo = now / 2;

            return FindNodeAt(Root, parentNo);
        }

        protected Node FindNodeAt(Node n, int targetNo)
        {
            return FindNodeAt(n, targetNo, 1);
        }

        protected Node FindNodeAt(Node n, int targetNo, int currentNo)
        {
            if (n == null)
            {
                return null;
            }

            if (targetNo == currentNo)
            {
                return n;
            }

            Node target;

            target = FindNodeAt(n.Left, targetNo, currentNo * 2);
            if (target == null)
            {
                target = FindNodeAt(n.Right, targetNo, currentNo * 2 + 1);
            }
            return target;
        }
    }

    // 二叉树中序遍历器
    public class InOrderTraversalIterator : IEnumerable
    {
        private Node root;

        public InOrderTraversalIterator(Node _root)
        {
            root = _root;
        }

        public IEnumerable Traversal(Node node)
        {
            if (node == null)
            {
                yield break;
            }

            if (node.Left != null)
            {
                foreach (var n in Traversal(node.Left))
                {
                    yield return n;
                }
            }
            yield return node;
            if (node.Right != null)
            {
                foreach (var n in Traversal(node.Right))
                {
                    yield return n;
                }
            }
        }

        public IEnumerator GetEnumerator()
        {
            foreach (var n in Traversal(root))
            {
                yield return n;
            }
        }
    }

    // 测试用例
    public class Test
    {
        delegate void TestCase();

        public void TestInstaceNode()
        {
            int data = 5;
            var node = new Node(data);

            Assert.Test(data == node.Data);
            Assert.Test(null == node.Left);
            Assert.Test(null == node.Right);

            var left = new Node(data - 1);
            var right = new Node(data + 1);
            node = new Node(data, left, right);

            Assert.Test(data == node.Data);
            Assert.Test(left == node.Left);
            Assert.Test(right == node.Right);
        }

        public void TestInOrderTraversalIterator()
        {
            var root = new Node(5);
            var adder = new SortTreeChildNodeAdder(root);
            adder.AddChildNode(4)
                .AddChildNode(6)
                .AddChildNode(3)
                .AddChildNode(7);

            Node previous = null;
            foreach (Node n in new InOrderTraversalIterator(root))
            {
                if (previous != null)
                {
                    Assert.Test(previous.Data <= n.Data);
                }
                previous = n;
            }
        }

        public void TestHeight()
        {
            var root = new Node(3);
            var adder = new SortTreeChildNodeAdder(root);
            Assert.Test(root.Height == 1);

            adder.AddChildNode(2);
            Assert.Test(root.Height == 2);

            adder.AddChildNode(4);
            Assert.Test(root.Height == 2);

            adder.AddChildNode(5);
            Assert.Test(root.Height == 3);
        }

        public void TestLeafs()
        {
            var root = new Node(3);
            var adder = new SortTreeChildNodeAdder(root);
            Assert.Test(root.Leafs == 1);

            adder.AddChildNode(2);
            Assert.Test(root.Leafs == 1);

            adder.AddChildNode(4);
            Assert.Test(root.Leafs == 2);

            adder.AddChildNode(5);
            Assert.Test(root.Leafs == 2);
        }

        public void TestSortTreeChildNodeAdder()
        {
            var root = new Node(4);
            var adder = new SortTreeChildNodeAdder(root);

            adder.AddChildNode(5);
            Assert.Test(root.Right.Data == 5);

            adder.AddChildNode(3);
            Assert.Test(root.Left.Data == 3);

            adder.AddChildNode(2);
            Assert.Test(root.Left.Left.Data == 2);

            adder.AddChildNode(6);
            Assert.Test(root.Right.Right.Data == 6);

            adder.AddChildNode(4);
            Assert.Test(root.Left.Right.Data == 4);
        }

        public void TestCompleteTreeChildNodeAdder()
        {
            var root = new Node(1);
            var adder = new CompleteTreeChildNodeAdder(root);

            adder.AddChildNode(2);
            Assert.Test(root.Left.Data == 2);

            adder.AddChildNode(3);
            Assert.Test(root.Right.Data == 3);

            adder.AddChildNode(4);
            Assert.Test(root.Left.Left.Data == 4);

            adder.AddChildNode(5);
            Assert.Test(root.Left.Right.Data == 5);

            adder.AddChildNode(6);
            Assert.Test(root.Right.Left.Data == 6);

            adder.AddChildNode(7);
            Assert.Test(root.Right.Right.Data == 7);
        }

        public void Run()
        {
            (
                new TestCase(TestInstaceNode) +
                new TestCase(TestInOrderTraversalIterator) +
                new TestCase(TestHeight) +
                new TestCase(TestLeafs) +
                new TestCase(TestSortTreeChildNodeAdder) +
                new TestCase(TestCompleteTreeChildNodeAdder)
            )();

            Console.WriteLine("所有测试通过...");
        }
    }

    // 演示用例
    public class Demo
    {
        protected const int Count = 100;
        protected const int Lower = 1;
        protected const int Upper = 100;

        public void Run()
        {
            // (1) 使用随机数生成一定数量数据
            var seq = MakeSequence();

            // (2) 生成完全二叉树
            var completeTree = MakeCompleteTree(seq);
            Console.WriteLine("完全二叉树层数： {0}", completeTree.Height);

            // (3) 生成二叉排序树
            var binarySortTree = MakeBinarySortTree(seq);

            // (5) 输出中序遍历结果
            Console.WriteLine("中序遍历排序二叉树");
            PrintTree(binarySortTree);

            // (6) 计算叶子节点数
            Console.WriteLine("排序二叉树叶子节点数：{0}", binarySortTree.Leafs);

            // (7) 计算二叉树深度
            Console.WriteLine("排序二叉树深度：{0}", binarySortTree.Height);
        }

        protected int[] MakeSequence(int size = Count,
                int lo = Lower, int hi = Upper)
        {
            var seq = new int[size];
            var random = new Random();
            for (var i = 0; i < size; i++)
            {
                seq[i] = random.Next(lo, hi);
            }

            return seq;
        }

        protected Node MakeBinarySortTree(int[] seq)
        {
            if (seq.Length < 1)
            {
                return null;
            }

            var root = new Node(seq[0]);
            var adder = new SortTreeChildNodeAdder(root);
            for (var i = 1; i < seq.Length; i++)
            {
                adder.AddChildNode(seq[i]);
            }

            return root;
        }

        protected Node MakeCompleteTree(int[] seq)
        {
            if (seq.Length < 1)
            {
                return null;
            }

            var root = new Node(seq[0]);
            var adder = new CompleteTreeChildNodeAdder(root);
            for (var i = 1; i < seq.Length; i++)
            {
                adder.AddChildNode(seq[i]);
            }

            return root;
        }

        protected void PrintTree(Node root)
        {
            var iter = new InOrderTraversalIterator(root);
            foreach (Node node in iter)
            {
                Console.Write("{0} ", node.Data);
            }
            Console.WriteLine();
        }
    }

    // 命令行入口
    public class CLI
    {
        public static void Main(string[] args)
        {
            var type = "demo";
            if (args.Length > 0)
            {
                type = args[args.Length - 1];
            }

            if (type == "test")
            {
                (new Test()).Run();
            }
            else
            {
                (new Demo()).Run();
            }
        }
    }
}
