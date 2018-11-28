/*
 * CSCE 2014 HW #5
 * Author: Brandon Russell
 *
 * An expression evaulation console application
 * Supports 5 left-associative operators and simple variables
*/

#include <iostream>
#include <string>
#include "Sequence.cpp"

using namespace std;

int main() {
	string input;
	string cmd;
	Sequence seq;

	cout << "input: ";
	getline(cin, input);

	seq = input;

	while (true) {
		cout << endl << "action: ";
		getline(cin, cmd);

		if (cmd == "q")
			return 0;
		else if (cmd == "c") {
			cout << "input: ";
			getline(cin, input);

			if (!input.empty())
				seq.append(input);
		} else if (cmd == "s") {
			cout << "input: ";
			getline(cin, input);

			seq = input;
		} else if (cmd == "<")
			for (int i = 0; i < seq.size(); i++)
				seq[i].printPostfix();
		else if (cmd == ">")
			for (int i = 0; i < seq.size(); i++)
				seq[i].printPrefix();
		else if (cmd == "f")
			for (int i = 0; i < seq.size(); i++)
				seq[i].printParenthesized();
		else if (cmd == "=")
			seq.evaluate();
		else
			cout << "Invalid action" << endl << "Valid commands: =, <, >, f, c, s, q" << endl;
	}

	return 0;
}