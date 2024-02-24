
# Answer Document

##### Andrew ID: adrianwa

## Part 1: Practice Problems (15%)
### Question 1


Given a pointer to struct D called “d”, what expression will access “data”, the member of struct A? You may assume that all pointers are initialized and are valid.

```cpp
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
```

#### Answer
d->c.b->a.data

### Question 2


Given the following structs, predict the memory layout of a struct A named “stack”. You may assume that it is a 32-bit machine.


```cpp
struct A{
    float a, b, c;
    B* ptr;
    B mem;
};

struct B {
    float d, e;
};

A stack;
```


#### Answer


| Address | Expressions
|---------|--------------------|
| A+0x00  | stack, stack.a     |
| A+0x04  | stack, stack.b     |
| A+0x08  | stack, stack.c     |
| A+0x0C  | stack, stack.ptr   |
| A+0x14  | stack, stack.mem.d |
| A+0x20  | stack, stack.mem.e |


### Question 3

Given the functions below, what is the value stored  in the points a and b after calling foo?

```cpp
struct point {
    float x, y;
};

void foo(point& p1, point p2) {
    point p3;
    p3.x = p1.x + p2.x;
    p3.y = p1.y + p2.y;
    bar(p3);
    p1.x -= p3.x;
    p1.y -= p3.y;
}

void bar(point p3) {
    p3.x *= .5f;
    p3.y *= .5f;
}

point a, b;
a.x = b.y = 1;
a.y = b.x = 0;
foo(a, b);
```

#### Answer

First the `point` variables `a` and `b` are defined and then their members `x` and `y` are assigned.
At this point `a` is of the form `x = 1` and `y = 0`, while `b` is of the form `x = 0` and `y = 1`.
When these variables are passed into `foo`, `a` is passed by reference, while `b` is passed by value. Then a new `point` variable, `p3` is created.
The members of `p3` are then assigned the sum of the matching members of the variables `a` and `b`. making `p3.x = p3.y = 1`. `p3` is then passed to `bar` by value, making the multiplication have no effect on `p3`.
Lastly, the matching members of `p3` are deducted from the members of `a`, which results in the modification of the variable `a`'s members, to `a.x = 0` and `a.y = -1`. Therefore, the values stored in point `a` are `a.x = 0` and `a.y = -1` and the values stored in `b` are `b.x = 0` and `b.y = 1`.


## Part 2: Coding Questions

### Question 1


Write an overview of how your AI works, including how it detects where projectiles will fall and how it chooses where to go.

#### Answer

My AI uses basic physics (projectile motion) to calculate the positions that all the projectiles will land and super-imposes them onto a boolean vector map of the same width as the map. Additionally, the projectiles are artificially widened in this prediction to account for the impact explosion radius. Next the active explosions are super imposed on this map. The AI then finds the direction that the nearest safe-space is in and begins moving in that direction. This is repeated for every player tick.

### Question 2

What challenges did you face when writing an AI?

#### Answer

The biggest issue I faced was over complicating the solution. Rather than using a single map, I implemented a system where a set number of times-steps was predicted and these were then mapped to a map of boolean vectors. This proved troublesome to navigate.

### Question 3

How well does your AI work on a Hard scenario? If it doesn’t work, why? If it does, try harder scenarios and see when it does fail and explain why?


#### Answer

My AI is capable of surviving on a Hard Scenario for a short time. I believe this is because of the simplified boolean map allowing the AI to get backed into a corner that it cannot move out of fast enough. With the more complicated map I had originally tried to implement, I may have been able to find a path through the time-steps and dangers.

### Question 4

What did you think of the assignment and did it meet its goals? Why or why not?


#### Answer

I enjoyed this assignment very much. It provided a fun learning experience that was challenging and rewarding.