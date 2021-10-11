#include "Foo.hpp"

Foo::Foo() : constant_(-1)
{
    allocated_ = new int(-1);
}

Foo::Foo(int constant, int allocated) : constant_(constant)
{
    allocated_ = new int(allocated);
}

Foo::~Foo()
{
    delete allocated_;
}

Foo::Foo(const Foo &other) : constant_(other.constant_)
{
    allocated_ = new int(*other.allocated_);
}

Foo &Foo::operator=(const Foo &other)
{
    if (this != &other)
    {
        *allocated_ = *other.allocated_;
    }
    return *this;
}

bool Foo::operator==(const Foo &rhs) const
{
    return constant_ == rhs.constant_ && *allocated_ == *rhs.allocated_;
}
bool Foo::operator!=(const Foo &rhs) const
{
    return !operator==(rhs);
}
bool Foo::operator<(const Foo &rhs) const
{
    return *allocated_ < *rhs.allocated_;
}
bool Foo::operator>(const Foo &rhs) const
{
    return *allocated_ > *rhs.allocated_;
}
bool Foo::operator<=(const Foo &rhs) const
{
    return *allocated_ <= *rhs.allocated_;
}
bool Foo::operator>=(const Foo &rhs) const
{
    return *allocated_ >= *rhs.allocated_;
}

int Foo::getConstant() const
{
    return constant_;
}
int Foo::getAllocated() const
{
    return *allocated_;
}
void Foo::setAllocated(int n)
{
    *allocated_ = n;
}

std::ostream &operator<<(std::ostream &os, Foo const &foo)
{
    os << foo.getConstant() << ":" << foo.getAllocated();
    return os;
}
