#include <iostream>
using namespace std;

class Parent
{
public:
    void doA() { cout << "doA in Parent" << endl; }
    virtual void doB() { cout << "doB in Parent" << endl; }
};

class Child : public Parent
{
public:
    void doA(int x) { cout << "doA in Child" << endl; }
    void doB() { cout << "doB in Child" << endl; }
};

Parent *p1 = new Parent();
Parent *p2 = new Child();
Child *cp = new Child();

void testStuff()
{
    p1->doA();
    p2->doA(10);

    p1->doB();
    p2->doB();
}

int main()
{
    testStuff();
}