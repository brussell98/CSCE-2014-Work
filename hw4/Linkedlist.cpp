/*
 * Author: Brandon Russell
 * Assignment: Homework #4
 * Due Date: Novermber 6, 2018
 *
 * Implements a linked list similar to the std::list
*/

#include <stdio.h>
#include <iostream>
#include "Linkedlist.h"

Linkedlist::Linkedlist() { }

Linkedlist::~Linkedlist() {
	clear();
}

bool Linkedlist::empty() const {
	return !head;
}

void Linkedlist::clear() {
	if (!tail)
		return;

	// Delete all nodes in reverse order
	Node* tmp = tail->prev;
	while (tail) {
		delete tail;
		tail = tmp;

		if (tail)
			tmp = tail->prev;
	}

	head = NULL;
}

// Could return null for non-const methods but nothing requires it, so don't for consitency with const methods
int& Linkedlist::back() {
	return tail->value;
}

const int& Linkedlist::back() const {
	return tail->value;
}

int& Linkedlist::front() {
	return head->value;
}

const int& Linkedlist::front() const {
	return head->value;
}

Linkedlist& Linkedlist::operator=(const Linkedlist &list) {
	clear();

	if (!list.head)
		return *this;

	// Copy list's nodes to this list (deep copy)
	head = new Node();
	head->value = list.head->value;

	Node* curr = list.head->next;
	Node* prev = head;
	while (curr) {
		Node* n = new Node();
		n->value = curr->value;
		n->prev = prev;
		prev->next = n;

		curr = curr->next;
		prev = n;
	}

	tail = prev;

	return *this;
}

void Linkedlist::pop_back() {
	if (!tail)
		return;

	Node* tmp = tail;
	tail = tail->prev;
	tail->next = NULL;
	delete tmp;
}

void Linkedlist::pop_front() {
	if (!head)
		return;

	Node* tmp = head;
	head = head->next;
	head->prev = NULL;
	delete tmp;
}

void Linkedlist::push_back(const int &x) {
	Node *n = new Node();
	n->value = x;
	n->prev = tail;

	if (tail)
		tail->next = n;
	tail = n;

	if (!head)
		head = n;
}

void Linkedlist::push_front(const int &x) {
	Node *n = new Node();
	n->value = x;
	n->next = head;

	if (head)
		head->prev = n;
	head = n;

	if (!tail)
		tail = n;
}

void Linkedlist::sort() {
	if (!head)
		return;

	/*
	 * Method: Check each element from left to right.
	 * If the element is smaller than the previous then
	 * move it left until it isn't.
	*/
	Node* curr = head->next;
	while (curr) {
		// Start with the second node, so curr->prev will always exist in the while loop
		Node* next = curr->next;

		// While the node before has a smaller value
		while (curr->prev && curr->value < curr->prev->value) {
			Node* left = curr->prev->prev;
			if (left) // If node 2 pos before then set its next to current
				left->next = curr;

			// Ensure head and tail and still correct after modifications
			if (curr->prev == head)
				head = curr;
			if (curr == tail)
				tail = curr->prev;

			// Swap positions with previous element
			curr->prev->next = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			curr->prev->prev = curr;
			curr->next = curr->prev;
			curr->prev = left;
		}

		curr = next;
	}
}

// Create with n nodes
Linkedlist::Linkedlist(unsigned int n) {
	if (n <= 0)
		return;

	tail = new Node();
	tail->value = --n;

	Node* curr = tail;
	for (n; n > 0; n) {
		curr->prev = new Node();
		curr->prev->next = curr;
		curr = curr->prev;
		curr->value = --n;
	}

	head = curr;
}

// Output all nodes
// Node:	2	Value:   2	Address:	0x7ff098c02a00	Next Address:	0x7ff098c02a20	Prev Address:	0x7ff098c029e0
void Linkedlist::check() const {
	if (!head)
		return;

	Node* curr = head;
	int i = 0;
	while (curr) {
		std::cout << "Node:\t" << i++
			<< "\tValue:\t" << curr->value
			<< "\tAddress:\t0x" << curr
			<< "\tNext Address:\t0x" << curr->next
			<< "\tPrev Address:\t0x" << curr->prev
			<< std::endl;

		curr = curr->next;
	}

	std::cout << "--------------------------------------------------" << std::endl;
}

// Output all nodes from the right
void Linkedlist::rcheck() const {
	if (!tail)
		return;

	Node* curr = tail;
	int i = 0;
	while (curr) {
		std::cout << "Node:\t" << i++
			<< "\tValue:\t" << curr->value
			<< "\tAddress:\t0x" << curr
			<< "\tNext Address:\t0x" << curr->next
			<< "\tPrev Address:\t0x" << curr->prev
			<< std::endl;

		curr = curr->prev;
	}

	std::cout << "--------------------------------------------------" << std::endl;
}

void Linkedlist::insert(unsigned int pos, const int &x) {
	if (!head) {
		head = new Node();
		head->value = x;
		tail = head;
		return;
	}

	// Find the current element at that position
	Node* currentOccupant = head;
	unsigned int i = 0;
	while (i++ < pos && currentOccupant->next)
		currentOccupant = currentOccupant->next;

	if (i - 1 < pos) { // If inserting past the end
		Node* n = new Node();
		n->value = x;
		n->prev = currentOccupant;
		currentOccupant->next = n;
		tail = n;
	} else if (currentOccupant == head) {
		Node* n = new Node();
		n->value = x;
		n->next = currentOccupant;
		currentOccupant->prev = n;
		head = n;
	} else { // Inserting at non-edge location
		Node* n = new Node();
		n->value = x;
		n->prev = currentOccupant->prev;
		n->prev->next = n;
		n->next = currentOccupant;
		currentOccupant->prev = n;
	}
}

void Linkedlist::erase(unsigned int pos) {
	if (!head)
		return;

	if (head == tail) {
		delete head;
		head = tail = NULL;
		return;
	}

	// Find node at pos
	Node* elem = head;
	unsigned int i = 0;
	while (i++ < pos && elem->next)
		elem = elem->next;

	if (elem == tail) { // If pos is past end, use tail
		tail = elem->prev;
		tail->next = NULL;
	} else if (elem == head) {
		head = elem->next;
		head->prev = NULL;
	} else { // If node is at non-edge location
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}

	delete elem;
}
