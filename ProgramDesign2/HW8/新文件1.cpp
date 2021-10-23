#include<iostream>
#include"Deque - 1083315 - hw8.h"
using namespace std;

int main() {
	
	deque<int> a;

	a.push_back(1);
	a.push_back(1);
	a.push_front(2);
	cout << a[0] << endl;
	
	return 0;
}
