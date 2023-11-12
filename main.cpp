#include <iostream>
#include "FlexArray.h"
using namespace std;

int main()
{
    FlexArray a;
    for (int i = 0; i < 10; i++)
        a.push_back(i);
    cout << a.printAll() << endl;
    // x x x x x x 0 1 2 3 4 5 6 7 8 9 x x

    for (int i = 10; i < 20; i++)
        a.push_front(i);
    cout << a.printAll() << endl;
    // x x x x x x x x x x x x 19 18 17 16 15 14 13 12 11 10 0 1 2 3 4 5 6 7 8 9 x x x x x x x x x x x x x x x x

    FlexArray b;
    for (int i = 0; i < 10; i++)
        b.insert(i, i);
    cout << b.printAll() << endl;
    // x x x x x 0 1 2 3 4 5 6 7 8 9

    b = a;

    for (int i = 0; i < 13; i++)
        b.pop_front();
    cout << b.printAll() << endl;
    // x x x x x x x x x x x x x x x x x x x x x x x x x 3 4 5 6 7 8 9 x x x x x x x x x x x x x x x x

    b.erase(6);
    cout << b.printAll() << endl;
    // x x x x x x 3 4 5 6 7 8 x x x x x x

    a = b;

    for (int i = 0; i < 4; i++)
        a.pop_back();

    cout << a.printAll() << endl;
    // x x 3 4 x x
}

