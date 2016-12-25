#pragma once
#include <iostream>
#include <string>

using namespace std;

struct node {
	int exp;
	int c;
	node* next;
};

class expression
{
public:
	expression();
	void add(int exp, int c);
	node* getHead();
	void setHead(node* head);
	~expression();
	void toList(string exp);
	void printList();
	expression operator+(const expression& ex);
private:
	node *head = NULL, *tail = NULL;
};

expression::expression()
{

}

inline void expression::add(int exp, int c)
{
	node *temp = new node();
	temp->exp = exp;
	temp->c = c;
	if (head == NULL) {
		head = temp;
		tail = head;
		head->next = tail;
		tail->next = NULL;
	}
	else {
		tail->next = temp;
		tail = tail->next;
		tail->next = NULL;
	}
}

inline node * expression::getHead()
{
	return head;
}

inline void expression::setHead(node * head)
{
	expression::head = head;
}

expression::~expression()
{
}

inline void expression::toList(string exp)
{
	int counter = 1;
	//if first number not negative, push plus
	if (exp[0] != '-') {
		exp.insert(0, "+");
	}

	if (exp.empty()) {
		add(0, 0);
	}
	//while expression string is not empty, loop
	while (counter >= 0) {
		int index = 0;
		string cString;
		int c;
		string exponentString;
		int exponent;
		string sub;

		//takes the operator character
		sub.push_back(exp[0]);
		exp.erase(0, 1);

		//takes one part of the equation
		while (exp[0] != '+' && exp[0] != '-' && !exp.empty()) {
			sub.push_back(exp[0]);
			exp.erase(0, 1);
		}
		index = 0;

		//takes constant
		while (sub[0] != 'x' && !sub.empty()) { //loops until x
			cString.push_back(sub[0]);
			sub.erase(0, 1);
		}
		if (cString[0] == '+') { //if const is positive
			cString.erase(0, 1);
			if (cString.empty()) {
				c = 1;
			}
			else {
				c = stoi(cString);
			}
		}
		else if(cString[0] == '-'){ //if const negative
			cString.erase(0, 1);
			if (cString.empty()) {
				c = -1;
			}
			else {
				c = stoi(cString) * -1;
			}
		}
		else {//if no const
			c = 0;
		}

		if (sub[0] == 'x' || sub[0] == 'X') {
			sub.erase(0, 1);
			exponentString = sub;
			if (exponentString.empty()) {
				exponent = 1;
			}
			else {
				exponent = stoi(exponentString);
			}
		}
		else {
			exponent = 0;
		}
		
		//adding to linked list
		if (head == NULL) {
			//if first element on list
			counter = exponent;
			add(exponent, c);
		}
		else {
			while (exponent != counter) {
				add(counter, 0);
				counter--;
			}
			add(exponent, c);
		}

		counter--;
	}
}

inline void expression::printList()
{
	node *temp = head;
	if (temp == NULL) {
		cout << 0;
		return;
	}
	while (temp != NULL)
	{
		if (temp->c == 0) {
			temp = temp->next;
			continue;
		}

		if (temp->c >= 0) {
			cout << '+';
		}
		if (temp->exp == 0) {
			cout << temp->c;
		}
		else {
			cout << temp->c << "x^" << temp->exp;
		}
		temp = temp->next;
	}
	cout << endl;
}

inline expression expression::operator+(const expression & ex)
{
	node* expression1;
	node* expression2;
	node* temp1;
	node* temp2;
	expression sum;
	//the one with larger exponent becomes refference
	if (expression::head->exp > ex.head->exp) {
		temp1 = expression1 = expression::head;
		temp2 = expression2 = ex.head;
	}
	else {
		temp2 = expression2 = expression::head;
		temp1 = expression1 = ex.head;
	}
	
	int i = expression1->exp;

	while (temp1->exp != temp2->exp) {
		temp1 = temp1->next;
		i--;
	}

	for (i; i >= 0; i--) {
		temp1->c = temp1->c + temp2->c;
		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	sum.head = expression1;
	return sum;
}
