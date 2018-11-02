#include "Linkedlist.h";

Linkedlist::Linkedlist() {
	// Nothing?
}

Linkedlist::~Linkedlist() {
	clear();
	delete head;
	delete tail;
}

bool Linkedlist::empty() const {
	return !head->next;
}

void Linkedlist::clear() {
	if (!tail)
		return;

	Node* tmp = tail->prev;
	while (tail) {
		delete tail;
		tail = tmp;
		tmp = tail->prev;
	}
}
