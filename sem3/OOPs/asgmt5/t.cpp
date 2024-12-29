#include <iostream>
using namespace std;

class A
{
public:
    virtual void f1(void)
    {
        cout << "inside f1(void) parent\n";
    }

    virtual void f2(void)
    {
        cout << "inside f2(void) parent\n";
    }
};

class B : public A
{
public:
    void f1(int)
    {
        cout << "inside f1(int) child\n";
    }
    void f2(void)
    {
        cout << "inside f2(void) child\n";
    }
};

int main()
{
    A *p;
    B b;
    p = &b;

    p->f2();
    p->f1(10);
    b.f1();
}