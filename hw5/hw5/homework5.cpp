#include <iostream>
#include <string>
#include "Expression.h"

using namespace std;

int main() {
	string input;
	string cmd;
	Expression exp;

	cout << "input: ";
	getline(cin, input);

	exp.set(input);

	while (true) {
		cout << endl << "action: ";
		getline(cin, cmd);

		if (cmd == "debug")
			exp.display();
		else if (cmd == "q")
			return 0;
		else if (cmd == "c") {
			cout << "input: ";
			getline(cin, input);

			if (!input.empty()) {
				cout << "Not implemented" << endl;
				// TODO: Create Sequence class to handle multiple expressions
			}
		} else if (cmd == "s") {
			cout << "input: ";
			getline(cin, input);

			exp.set(input);
		} else if (cmd == "<")
			cout << "Not implemented" << endl;
		else if (cmd == ">")
			cout << "Not implemented" << endl;
		else if (cmd == "f")
			cout << "Not implemented" << endl;
		else
			cout << "Invalid action" << endl;
	}

	return 0;
}