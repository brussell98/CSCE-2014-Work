#include <iostream>
#include <string>
#include "Sequence.cpp"

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
	Sequence seq;

	cout << "input: ";
	getline(cin, input);

	seq = input;

	while (true) {
		cout << endl << "action: ";
		getline(cin, cmd);

		if (cmd == "debug") {
			for (int i = 0; i < seq.size(); i++)
				seq[i].display();
		} else if (cmd == "q")
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