#ifndef MYALLOCATOR_HPP
#define MYALLOCATOR_HPP

#include <memory>

template <class T>
class MyAllocator : public std::allocator<T>
{
private:
    size_t num;

public:
    MyAllocator() : std::allocator<T>()
    {
        num = sizeof(T);
    }
    template <class U>
    MyAllocator(const MyAllocator<U> &other) : std::allocator<T>(other)
    {
        num = sizeof(T);
    }

    template <class U>
    struct rebind
    {
        typedef MyAllocator<U> other;
    };

    size_t getNum() const { return num; }
};

#endif /* MYALLOCATOR_HPP */
