#include <iostream>
#include <string>
#include "Expression.h"

using namespace std;

void parseExpressions(string &input, Expression &exp) {
	size_t pos = 0;
	while ((pos = input.find(';')) != string::npos) {
		if (pos == 0) {
			input.erase(0, 1);
			continue;
		}

		// TODO: ExpressionSequence class to handle multiple expressions
		exp.set(input.substr(0, pos));
		input.erase(0, pos + 1);
	}
}

int main() {
	string input;
	string cmd;
	Expression exp;

	cout << "input: ";
	getline(cin, input);

	parseExpressions(input, exp);

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
		else if (cmd == "=")
			cout << "Not implemented" << endl;
		else
			cout << "Invalid action" << endl << "Valid commands: =, <, >, f, c, s, q" << endl;
	}

	return 0;
}