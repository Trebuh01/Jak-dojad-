template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue() : heapSize(0), capacity(10) {
        heap = new T[capacity];
    }

    PriorityQueue(int hsize, int cap)
    {
        heapSize = hsize;
        capacity = cap;
        heap = new T[capacity];
    }

    bool empty() const { return heapSize == 0; }
    int size() const { return heapSize; }

    void push(const T& value) {
        if (heapSize == capacity) {
            resize(capacity * 2);
        }

        heap[heapSize] = value;
        heapifyUp(heapSize);
        ++heapSize;
    }

    void pop() {
        if (heapSize > 0) {
            heap[0] = heap[heapSize - 1];
            --heapSize;
            heapifyDown(0);
        }
    }

    const T& top() const {
        return heap[0];
    }

private:
    void resize(int newCapacity) {
        T* newHeap = new T[newCapacity]();
        for (int i = 0; i < heapSize; ++i) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && compare(heap[index], heap[parent])) {
            std::swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int minIndex = index;
        if (leftChild < heapSize && compare(heap[leftChild], heap[minIndex])) {
            minIndex = leftChild;
        }
        if (rightChild < heapSize && compare(heap[rightChild], heap[minIndex])) {
            minIndex = rightChild;
        }
        if (minIndex != index) {
            std::swap(heap[index], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

    T* heap = nullptr;
    int heapSize = 0;
    int capacity = 0;
    Compare compare;
};