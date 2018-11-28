#include <vector>
#include <string>
#include <iostream>
#include "Expression.h"

using namespace std;

class Sequence {
public:
	Sequence() {
		exps = vector<Expression>();
	}

	Sequence(string input) {
		exps = vector<Expression>();
		append(input);
	}

	void append(string input) {
		size_t pos = 0;
		while ((pos = input.find(';')) != string::npos) {
			if (pos == 0) {
				input.erase(0, 1);
				continue;
			}

			exps.push_back(Expression(input.substr(0, pos)));
			input.erase(0, pos + 1);
		}
	}

	void evaluate() {
		map<string, int> vars;
		for (int i = 0; i < exps.size(); i++) {
			if (!exps[i].isValid())
				cout << exps[i].get_original() << " is not a valid expression" << endl;
			else if (exps[i].getType() == assignment) {
				int val = exps[i].evaluate(vars);
				cout << "Variable \"" << exps[i].get_tokenized()[0].get_token() << "\" set to " << val << endl;
			} else {
				try {
					int val = exps[i].evaluate(vars);
					cout << exps[i].get_original() << " = " << val << endl;
				} catch (exception &e) {
					if ((string)e.what() == "Undefined variable referenced in expression")
					 	cout << exps[i].get_original() << " = undefined (referenced undefined variable)" << endl;
					else
						throw e;
				}
			}
		}
	}

	Expression at(int pos) {
		return exps[pos];
	}

	Expression operator[](int pos) {
		return exps[pos];
	}

	size_t size() {
		return exps.size();
	}

private:
	vector<Expression> exps;
};
