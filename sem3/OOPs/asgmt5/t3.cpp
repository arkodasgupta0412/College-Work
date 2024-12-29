#include <iostream>
using namespace std;

class A
{
protected:
    void f2(void)
    {
        cout << "inside protected base\n";
    }

public:
    void f1(void)
    {
        cout << "inside public base\n";
    }
    friend void foo(void);
};

class B : public A
{
protected:
    void f2(void)
    {
        cout << "inside protected derived\n";
    }

public:
    void f1(int)
    {
        cout << "inside public derived\n";
    }
};

void foo(void)
{
    B b;
    b.f2();
}

int main()
{
    foo();
}