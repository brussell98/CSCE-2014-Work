/*
 * CSCE 2014 HW #5
 * Author: Brandon Russell
 *
 * Parses an expression into a series of tokens
*/

#include <iostream>
#include <stack>
#include "Expression.h"

string typeToString(Exp_type t) {
	switch (t) {
		case assignment:
			return "assignment";
		case arithmetic:
			return "arithmetic";
		default:
			return "illegal";
	}
}

Expression::Expression() {
	original = string();
	tokenized = vector<Token>();
	valid = false;
	type = illegal;
}

Expression::Expression(const string &s) {
	set(s);
}

void Expression::validate() {
	if (tokenized.size() == 0) {
		valid = false;
		return;
	}

	valid = true;
	enum States { operand, func, done };
	bool isAssignment = false; // Expression contains an =
	States state = operand;
	int level = 0; // Current parenthesis level
	vector<Token>::iterator token = tokenized.begin();

	do {
		switch (state) {
			case operand:
				if ((*token).get_type() == OpenBrace)
					level++;
				else if ((*token).get_type() == INT || (*token).get_type() == ID)
					state = func; // If token is an int or variable, expect an operator next
				else {
					valid = false;
					state = done;
				}
				break;

			case func:
				if ((*token).get_type() == CloseBrace) {
					level--;
					if (level < 0) {
						valid = false;
						state = done;
					}
				} else if ((*token).get_type() == EQ) {
					isAssignment = true;
					state = operand;
				} else if ((*token).get_type() == OP)
					state = operand; // If token is an operator, expect an operand next
				else {
					valid = false;
					state = done;
				}
				break;

			default:
				break;
		}
	} while (state != done && ++token != tokenized.end());

	if (level != 0) // Un-balanced parenthesis
		valid = false;
	if (state = operand) // Ended with an operator
		valid = false;

	if (valid) {
		if (isAssignment) {
			if (tokenized.size() == 3 && tokenized[0].get_type() == ID && tokenized[2].get_type() == INT)
				type = assignment;
			else
				valid = false;
		} else
			type = arithmetic;
	}
}

void Expression::generatePostfix() {
	stack<Token> opStack;

	for (int i = 0; i < tokenized.size(); i++) {
		Token t = tokenized[i];
		if (t.get_type() == INT || t.get_type() == ID)
			postfix.push_back(t);
		else if (t.get_type() == OpenBrace)
			opStack.push(t);
		else if (t.get_type() == CloseBrace) {
			while (opStack.top().get_type() != OpenBrace) {
				postfix.push_back(opStack.top());
				opStack.pop();
			}

			opStack.pop(); // Remove open parenthesis
		} else {
			while (opStack.size() != 0 && opStack.top().get_priority() >= t.get_priority()) {
				postfix.push_back(opStack.top());
				opStack.pop();
			}

			opStack.push(t);
		}
	}

	while (opStack.size() != 0) {
		postfix.push_back(opStack.top());
		opStack.pop();
	}
}

void Expression::set(const string &s) {
	original = s;
	tokenized.clear(); // Remove old tokens
	valid = false;
	type = illegal;

	string delims = "+-*/%()=";
	int i = 0;
	while (i < s.length()) {
		// For every character in the string,
		// If it's alphanumeric, extract that sequence into a token
		// If it's a delimeter, create a token from it
		// Otherwise, move on to the next character (spaces)
		if (isalnum(s[i])) {
			int p = i + 1;
			while (delims.find(s[p]) == string::npos && !isspace(s[p]) && p < s.length()) // Find end of sequence
				p++;

			tokenized.push_back(Token(s.substr(i, p - i)));
			i = p;
			continue;
		} else if (delims.find(s[i]) != string::npos)
			tokenized.push_back(Token(s.substr(i, 1)));

		i++;
	}

	validate();
	if (valid)
		generatePostfix();
}

void Expression::display() const {
	cout << "original = " << original << endl;

	cout << "tokenized = ";
	for (int i = 0; i < (int)tokenized.size(); i++)
		cout << tokenized.at(i).get_token() << ' ';

	cout << endl << "postfix = ";
	for (int i = 0; i < (int)postfix.size(); i++)
		cout << postfix.at(i).get_token() << ' ';

	cout << endl << "valid = " << valid << endl;
	cout << "type = " << typeToString(type) << endl;
}

bool Expression::isValid() {
	return valid;
}

Exp_type Expression::getType() {
	return type;
}

int Expression::evaluate(map<string, int> &vars) {
	if (type == assignment) {
		vars[tokenized[0].get_token()] = tokenized[2].value();
		return tokenized[2].value();
	}

	stack<int> operands;
	for (int i = 0; i < postfix.size(); i++) {
		Token token = postfix[i];
		if (token.get_type() == INT)
			operands.push(token.value());
		else if (token.get_type() == ID)
			operands.push(vars[token.get_token()]);
		else {
			int val1 = operands.top();
			operands.pop();
			int val2 = operands.top();
			operands.pop();

			string op = postfix[i].get_token();
			if (op == "+")
				operands.push(val1 + val2);
			else if (op == "-")
				operands.push(val1 - val2);
			else if (op == "*")
				operands.push(val1 * val2);
			else if (op == "/")
				operands.push(val1 / val2);
			else if (op == "%")
				operands.push(val1 % val2);
		}
	}

	return operands.top();
}

void Expression::printPostfix() {
	if (!valid) {
		cout << "No postfix version of " << original << " because it is not a valid expression." << endl;
		return;
	}

	if (type == assignment) {
		cout << "No postfix of " << original << " because it is an assignment expression." << endl;
		return; // Hide postfix for assignment expressions for some reason
	}

	cout << "Postfix of " << original << ':';
	for (int i = 0; i < postfix.size(); i++)
		cout << ' ' << postfix.at(i).get_token();

	cout << endl;
}

void Expression::printParenthesized() {
	if (!valid) {
		cout << "No parenthesized version of " << original << " because it is not a valid expression." << endl;
		return;
	}

	if (type == assignment) {
		cout << "No parenthesized version of " << original << " because it is an assignment expression." << endl;
		return; // Hide for assignment expressions for some reason
	}

	stack<string> st;

	for (int i = 0; i < postfix.size(); i++) {
		if (postfix[i].get_type() == INT || postfix[i].get_type() == ID)
			st.push(postfix[i].get_token());
		else {
			string op1 = st.top();
			st.pop();
			string op2 = st.top();
			st.pop();
			st.push('(' + op2 + postfix[i].get_token() + op1 + ')');
		}
	}

	cout << "Fully parenthesized version of " << original << " is: " << st.top();
}
