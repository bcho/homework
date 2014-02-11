import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
    private int currentSize;
    private Node<Item> first;
    private Node<Item> last;

    public Deque() {
        currentSize = 0;
        first = new Node<Item>();
        last = new Node<Item>();
        first.next = last;
        first.prev = null;
        last.prev = first;
        last.next = null;
    }

    public boolean isEmpty() {
        return first.next == last;
    }

    public int size() {
        return currentSize;
    }

    public void addFirst(Item item) {
        if (item == null) {
            throw new NullPointerException();
        }

        Node<Item> node = new Node<Item>();
        node.item = item;
        node.next = first.next;
        node.next.prev = node;
        node.prev = first;
        first.next = node;
        currentSize = currentSize + 1;
    }

    public void addLast(Item item) {
        if (item == null) {
            throw new NullPointerException();
        }

        Node<Item> node = new Node<Item>();
        node.item = item;
        node.next = last;
        node.prev = last.prev;
        last.prev.next = node;
        last.prev = node;
        currentSize = currentSize + 1;
    }

    public Item removeFirst() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        Node<Item> oldfirst = first.next;
        first.next = oldfirst.next;
        first.next.prev = first;
        assert currentSize >= 1;
        currentSize = currentSize - 1;
        assert currentSize >= 0;
        return oldfirst.item;
    }

    public Item removeLast() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        Node<Item> oldlast = last.prev;
        last.prev = oldlast.prev;
        oldlast.prev.next = last;
        assert currentSize >= 1;
        currentSize = currentSize - 1;
        assert currentSize >= 0;
        return oldlast.item;
    }

    public Iterator<Item> iterator() {
        return new DequeIterator<Item>(first.next);
    }

    private static class Node<Item> {
        private Item item;
        private Node<Item> next;
        private Node<Item> prev;
    }

    private class DequeIterator<Item> implements Iterator<Item> {
        private Node<Item> current;

        public DequeIterator(Node<Item> first) {
            current = first;
        }

        public boolean hasNext() {
            return current != last;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            Item item = current.item;
            current = current.next;

            return item;
        }
    }
    
    public static void main(String[] args) {
        Deque<String> q = new Deque<String>();

        assert q.size() == 0;
        assert q.isEmpty();

        q.addFirst("a");
        assert q.size() == 1;
        
        q.addLast("b");
        assert q.size() == 2;

        assert q.removeFirst().equals("a");
        assert q.size() == 1;
        assert q.removeLast().equals("b");
        assert q.size() == 0;
        assert q.isEmpty();

        try {
            q.removeFirst();
            assert false;
        } catch (NoSuchElementException e) {
            assert true;
        }
        
        try {
            q.removeLast();
            assert false;
        } catch (NoSuchElementException e) {
            assert true;
        }

        try {
            q.addFirst(null);
            assert false;
        } catch (NullPointerException e) {
            assert true;
        }
        
        try {
            q.addLast(null);
            assert false;
        } catch (NullPointerException e) {
            assert true;
        }

        StringBuilder s;

        q.addFirst("h");
        q.addFirst("b");
        q.addFirst("c");
        s = new StringBuilder();
        for (String item : q) {
            s.append(item);
        }
        assert s.toString().compareTo("cbh") == 0;
        
        q = new Deque<String>();
        q.addLast("h");
        q.addLast("b");
        q.addLast("c");
        s = new StringBuilder();
        for (String item : q) {
            s.append(item);
        }
        assert s.toString().compareTo("hbc") == 0;
    }
}
