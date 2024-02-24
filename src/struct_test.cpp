//
// Created by awalker on 2/20/24.
//

#include <iostream>

struct A {
    float data;
};

struct B {
    A a;
};

struct C {
    B* b;
};

struct D {
    C c;
};

int main() {
    D* d = new D(); // Allocating memory for struct D
    // Now d is a pointer that points to the struct D instance

    // Accessing struct D members through pointer d
    d->c.b = new B(); // Allocating memory for struct B
    d->c.b->a.data = 10.5f; // Accessing data member of struct A through struct B pointer

    // Printing out the value of data
    std::cout << "Value of data: " << d->c.b->a.data << std::endl;

    // Cleanup
    delete d->c.b;
    delete d;

    return 0;
}