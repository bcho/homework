import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private int used;
    private Item[] items;

    public RandomizedQueue() {
        items = (Item[]) new Object[1];
        used = 0;
    }

    public boolean isEmpty() {
        return used == 0;
    }

    public int size() {
        return used;
    }

    public void enqueue(Item item) {
        if (item == null) {
            throw new NullPointerException();
        }

        if (used >= items.length) {
            resize(2 * items.length);
        }

        items[used] = item;
        used = used + 1;
    }

    public Item dequeue() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        int pos = getPos();
        Item item = items[pos];
        items[pos] = items[used - 1];
        items[used - 1] = null;
        used = used - 1;

        if (used > 0 && used == items.length / 4) {
            resize(items.length / 2);
        }

        return item;
    }

    public Item sample() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        return items[getPos()];
    }

    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator<Item>(items, used);
    }

    private void resize(int newCapacity) {
        assert used <= newCapacity;

        Item[] temp = (Item[]) new Object[newCapacity];
        for (int i = 0; i < used; i++) {
            temp[i] = items[i];
        }
        items = temp;
    }

    private int getPos() {
        return StdRandom.uniform(used);
    }

    private class RandomizedQueueIterator<Item> implements Iterator<Item> {
        private Item[] items;
        private int current, capacity;

        public RandomizedQueueIterator(Item[] originItems, int used) {
            items = (Item[]) new Object[used];
            capacity = 0;
            for (int i = 0; i < originItems.length; i++) {
                if (originItems[i] != null) {
                    items[capacity] = originItems[i];
                    capacity = capacity + 1;
                }
            }
            StdRandom.shuffle(items);

            current = 0;
            capacity = used;
        }

        public boolean hasNext() {
            return current < capacity;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }

            return items[current++];
        }
    }

    public static void main(String[] args) {
        RandomizedQueue<String> q = new RandomizedQueue<String>();

        assert q.isEmpty();

        q.enqueue("a");
        assert !q.isEmpty();
        assert q.size() == 1;
        assert q.dequeue().compareTo("a") == 0;

        q.enqueue("a");
        assert q.sample().compareTo("a") == 0;
        assert q.size() == 1;
        assert !q.isEmpty();
        assert q.dequeue().compareTo("a") == 0;

        try {
            q.dequeue();
            assert false;
        } catch (NoSuchElementException e) {
            assert true;
        }
        
        try {
            q.sample();
            assert false;
        } catch (NoSuchElementException e) {
            assert true;
        }

        q = new RandomizedQueue<String>();
        q.enqueue("1");
        q.enqueue("2");
        q.enqueue("2");
        q.enqueue("2");
        q.dequeue();

        int n = 10;
        boolean[] appeared = new boolean[n];
        RandomizedQueue<Integer> p = new RandomizedQueue<Integer>();
        for (int i = 0; i < n; i++) {
            appeared[i] = false;
            p.enqueue(i);
        }
        assert p.size() == n;
        for (int i : p) {
            assert !appeared[i];
            appeared[i] = true;
            StdOut.print(i + " ");
        }
        StdOut.println("");
        for (int i : p) {
            appeared[i] = true;
            StdOut.print(i + " ");
        }
    }
}
