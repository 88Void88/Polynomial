#include <iostream>
#include <stdlib.h>
#include <string>
#include "list.h"

using namespace std;

int main() {
	expression ex1 = expression();
	expression ex2 = expression();
	string test1 = "2x7";
	string test2 = "x5+2x2+3x-2";

	ex1.toList(test1);
	ex1.printList();

	ex2.toList(test2);
	ex2.printList();

	expression sum = ex1 + ex2;
	sum.printList();

	cout << endl;
	system("pause");
	return 0;
}