#include <iostream>
#include "FlexArray.h"
using namespace std;

int main() {

	int arr[]{10,20};
	FlexArray b{arr,2};
	b.insert(0,80);
	cout << b.printAll();
	b.insert(0,90); 
	cout << b.printAll();// [90 80 10 20 X X]
	b.insert(1,99);
	cout << b.printAll();
}
