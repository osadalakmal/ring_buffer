#include <vector>
#include <iostream>

template <typename T>
class RingBuffer
{
    inline size_t diff(size_t a, size_t b, size_t c) {
        return a > b ? a - b : c - (b - a);
    }
public:
    RingBuffer() = delete;
    RingBuffer(size_t capacity) : d_data(capacity+1), d_capacity(capacity+1), d_head(0), d_tail(0), d_full(false), d_empty(true) {
    }
    RingBuffer(const RingBuffer&) = delete;
    RingBuffer(const RingBuffer&&) = delete;
    RingBuffer operator=(const RingBuffer&) = delete;
    RingBuffer operator=(const RingBuffer&&) = delete;

    template <typename ...Args>
    void emplace(Args&&... args) {
        if (d_full) return;
        new (&(d_data[d_tail++])) T(std::forward<Args>(args)...);
        if (d_tail == d_capacity) d_tail = 0;
        d_full = ((diff(d_head, d_tail, d_capacity) == 1));
        d_empty = (d_head == d_tail);
        //std::cout << "push head:" << d_head << " tail:" << d_tail << " full:" << d_full << " empty:" << d_empty << std::endl;
    }

    T pop() {
        auto temp = d_head++;
        if (d_head == d_capacity) d_head = 0;
        d_full = (diff(d_head, d_tail, d_capacity) == 1);
        d_empty = (d_head == d_tail);
        //std::cout << "pop head:" << d_head << " tail:" << d_tail << " full:" << d_full << " empty:" << d_empty << std::endl;
        return d_data[temp];
    }

    bool isFull() const { return d_full; }
    bool isEmpty() const { return d_empty; }
private:
    std::vector<T> d_data;
    const size_t d_capacity;
    size_t d_head;
    size_t d_tail;
    size_t d_full;
    size_t d_empty;
};