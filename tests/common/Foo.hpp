#ifndef FOO_HPP
#define FOO_HPP

#include <ostream>

class Foo
{
private:
    const int constant_;
    int *allocated_;

public:
    Foo();
    Foo(int constant, int allocated);
    ~Foo();
    Foo(const Foo &other);
    Foo &operator=(const Foo &other);

    bool operator==(const Foo &rhs) const;
    bool operator!=(const Foo &rhs) const;
    bool operator<(const Foo &rhs) const;
    bool operator>(const Foo &rhs) const;
    bool operator<=(const Foo &rhs) const;
    bool operator>=(const Foo &rhs) const;

    int getConstant() const;
    int getAllocated() const;
    void setAllocated(int n);
};

std::ostream &operator<<(std::ostream &os, Foo const &foo);

#endif /* FOO_HPP */
