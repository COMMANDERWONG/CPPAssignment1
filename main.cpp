#include <iostream>
#include "FlexArray.h"
using namespace std;

int main()
{
    int arr[]{1, 2, 3, 4, 5, 6};
    FlexArray a{arr, 6};
    bool b;
    for (int i = 0; i < 3; i++)
    {
        b = a.pop_back();
    }
     cout << a.printAll()<< endl;
    string s = a.printAll();
    for (int i = 0; i < 3; i++)
        a.pop_back(); // now empty
    b = a.pop_back();
    cout << a.printAll()<< endl;
}
