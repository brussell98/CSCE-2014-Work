#include <vector>
#include <string>
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
