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
	//if first number not negative, push plus
	if (exp[0] != '-') {
		exp.insert(0, "+");
	}

	if (exp.empty()) {
		add(0, 0);
	}
	//while expression string is not empty, loop
	while (exp.empty() == false) {
		int index = 0;
		string cString;
		int c;
		string exponentString;
		int exponent;
		string sub;

		//takes the operator character
		sub.push_back(exp[0]);
		exp.erase(0, 1);

		while (exp[0] != '+' && exp[0] != '-' && !exp.empty()) {
			sub.push_back(exp[0]);
			exp.erase(0, 1);
		}
		index = 0;
		while (sub[0] != 'x' && !sub.empty()) {
			cString.push_back(sub[0]);
			sub.erase(0, 1);
		}
		if (cString[0] == '+') {
			cString.erase(0, 1);
			if (cString.empty()) {
				c = 1;
			}
			else {
				c = stoi(cString);
			}
		}
		else {
			cString.erase(0);
			if (cString.empty()) {
				c = -1;
			}
			else {
				c = stoi(cString) * -1;
			}
		}
		if (sub.empty()) {
			add(0, c);
			continue;
		}
		sub.erase(0, 1);
		exponentString = sub;
		if (exponentString.empty()) {
			exponent = 1;
		}
		else {
			exponent = stoi(exponentString);
		}

		add(exponent, c);
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
		if (temp->c == 0) continue;
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
	expression sum;
	node* temp1 = expression::head;
	node* temp2 = ex.head;

	while (temp2 != NULL) {
		while (temp2->exp < temp1->exp && temp1 != NULL) {
			temp1 = temp1->next;
		}
		if (temp1 == NULL) {
			sum.add(temp2->exp, temp2->c);
			temp2 = temp2->next;
			continue;
		}
		if (temp2->exp == temp1->exp) {
			temp1->c += temp2->c;
			temp2 = temp2->next;
			continue;
		}
		node *temp3 = temp2;
		temp3->next = temp1->next;
		temp1->next = temp3;
		temp2 = temp2->next;
	}
	sum.head = head;
	return sum;
}
