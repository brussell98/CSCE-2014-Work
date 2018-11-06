/*
 * Author: Brandon Russell
 * Assignment: Homework #4
 * Due Date: Novermber 6, 2018
 *
 * Implements a linked list similar to the std::list
*/

#pragma once

class Linkedlist {
public:
	typedef int &reference;
	typedef const int &const_reference;
	Linkedlist(); //default constructor for empty list
	~Linkedlist(); //destructor to free nodes dynamically created to support the linklist
	bool empty() const;
	void clear();
	reference back();
	const_reference back() const;
	reference front();
	const_reference front() const;
	Linkedlist& operator=(const Linkedlist& l);
	void pop_back();
	void pop_front();
	void push_back(const int &x);
	void push_front(const int &x);
	void sort();
	// constructor that initializes the linked list with n nodes,
	// with elem value from 0 to n-1
	explicit Linkedlist(unsigned int n);
	// print the linked list in the forward direction,
	// similar to the show function of lab6
	void check() const;
	// print the linked list in the backward direction,
	// similar to the reverse_show function of lab7
	void rcheck() const;
	// insert a node with value specified by x after the node
	// specified by pos. The first node has position 0.
	// if the number of nodes in the linked list is less than
	// pos, the node is inserted at the end.
	void insert(unsigned int pos, const int &x);
	// remove the node specified by pos.
	// if the number of nodes in the linked list is less than
	// pos, the node at the end if any is removed.
	void erase(unsigned int pos);

private:
	struct Node {
		int value;
		Node* prev;
		Node* next;
	};
	Node* head;
	Node* tail;
};
