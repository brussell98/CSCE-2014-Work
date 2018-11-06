/*
 * Author: Brandon Russell
 * Assignment: Homework #4
 * Due Date: Novermber 6, 2018
 *
 * Tests the Linkedlist class
*/

#include <iostream>
#include "Linkedlist.h"

using namespace std;

int main() {
	Linkedlist empty;
	Linkedlist nonEmpty(3);
	Linkedlist list(10);

	cout << "Testing if an empty list is empty: " << (empty.empty() ? "true" : "false") << endl;
	cout << "Testing if a non-empty list is empty: " << (nonEmpty.empty() ? "true" : "false") << endl;
	nonEmpty.clear();
	nonEmpty.check();
	cout << "Testing if it's empty after calling clear(): " << (nonEmpty.empty() ? "true" : "false") << endl;
	cout << endl;

	cout << "Creating a list of 10 elements:" << endl;
	list.check();
	list.rcheck();
	cout << endl;

	cout << "Front of list: " << list.front() << endl;
	cout << "Back of list: " << list.back() << endl;
	cout << endl;

	cout << "Assigning list to the value of a new list of 5 elements:" << endl;
	Linkedlist newList(5);
	list = newList;
	list.check();
	list.rcheck();
	cout << endl;

	cout << "Testing pop back:" << endl;
	list.pop_back();
	list.check();
	cout << "Testing pop front:" << endl;
	list.pop_front();
	list.check();
	cout << endl;

	cout << "Testing push back (-10):" << endl;
	list.push_back(-10);
	list.check();
	cout << "Testing push front (7):" << endl;
	list.push_front(7);
	list.check();
	cout << endl;

	cout << "Testing insert (6 at 2):" << endl;
	list.insert(2, 6);
	list.check();
	cout << endl;

	cout << "Testing erase (at 3):" << endl;
	list.erase(3);
	list.check();
	cout << endl;

	cout << "Testing sort:" << endl;
	list.sort();
	list.check();
	list.rcheck();
	cout << endl;

	cout << endl << "# Special cases:" << endl;

	cout << "## Insert" << endl;
	cout << "Insert past end:" << endl;
	list.insert(6, 99);
	list.check();
	cout << "Insert at tail:" << endl;
	list.insert(5, 98);
	list.check();
	cout << endl;


	cout << "## Manipulating an empty list:" << endl;
	list.clear();

	cout << "Testing push back:" << endl;
	list.push_back(-10);
	list.check();
	list.clear();
	cout << "Testing push front:" << endl;
	list.push_front(7);
	list.check();
	list.clear();
	cout << "Testing insert:" << endl;
	list.insert(1, 6);
	list.check();
	list.clear();
	cout << "Testing erase (no output)" << endl;
	list.erase(0);
	cout << "Testing sort (no output)" << endl;
	list.sort();
	cout << endl;

	cout << "## Using a list with one element:" << endl;
	list.push_front(1);

	cout << "Sorting it:" << endl;
	list.sort();
	list.check();

	cout << "Testing erase on the element (no output)" << endl;
	list.erase(0);
	cout << endl;

	return 0;
}