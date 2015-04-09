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

        public CompleteTreeChildNodeAdder(Node root)
        {
            Root = root;
        }

        public override AbstractChildNodeAdder AddChildNode(Node child)
        {
            AddToFirstAvailableNode(Root, child);

            return this;
        }

        protected Node AddToFirstAvailableNode(Node current, Node child)
        {
            if (current == null)
            {
                return null;
            }

            if (current.Left == null)
            {
                current.Left = child;
                return current;
            }
            if (current.Right == null)
            {
                current.Right = child;
                return current;
            }

            Node addedTo;
            
            addedTo = AddToFirstAvailableNode(current.Left, child);
            if (addedTo == null)
            {
                addedTo = AddToFirstAvailableNode(current.Right, child);
            }

            return addedTo;
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
        }

        public static void Run()
        {
            var test = new Test();

            (
                new TestCase(test.TestInstaceNode) +
                new TestCase(test.TestInOrderTraversalIterator) +
                new TestCase(test.TestHeight) +
                new TestCase(test.TestLeafs) +
                new TestCase(test.TestSortTreeChildNodeAdder) +
                new TestCase(test.TestCompleteTreeChildNodeAdder)
            )();

            Console.WriteLine("所有测试通过...");
        }
    }

    // 演示用例
    public class Demo
    {
        public  static void Run()
        {
            var root = new Node(4);
            var adder = new SortTreeChildNodeAdder(root);
            adder.AddChildNode(2)
                .AddChildNode(1)
                .AddChildNode(3)
                .AddChildNode(5)
                .AddChildNode(6)
                .AddChildNode(7);

            foreach (Node n in new InOrderTraversalIterator(root))
            {
                Console.WriteLine(n.Data);
            }
        }
    }

    // 命令行入口
    public class CLI
    {
        public static void Main(string[] args)
        {
            var runner = "demo";
            if (args.Length > 0)
            {
                runner = args[args.Length - 1];
            }

            if (runner == "test")
            {
                Test.Run();
            }
            else
            {
                Demo.Run();
            }
        }
    }
}
