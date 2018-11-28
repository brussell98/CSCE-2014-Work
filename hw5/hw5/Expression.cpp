/*
 * CSCE 2014 HW #5
 * Author: Brandon Russell
 *
 * Parses an expression into a series of tokens
 * Generates postfix and prefix notations, and evaluates the result
*/

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdexcept>
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
	postfix = vector<Token>();
	prefix = vector<Token>();
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
	enum States { operand, func };
	bool isAssignment = false; // Expression contains an =
	States state = operand;
	int level = 0; // Current parenthesis level
	vector<Token>::iterator token = tokenized.begin();

	do { // Expect to alternate between operators and operands
		switch (state) {
			case operand:
				if ((*token).get_type() == OpenBrace)
					level++;
				else if ((*token).get_type() == INT || (*token).get_type() == ID)
					state = func; // If token is an int or variable, expect an operator next
				else // Unexpected token
					valid = false;
				break;

			case func:
				if ((*token).get_type() == CloseBrace) {
					level--;
					if (level < 0) // If unmatched close parenthesis
						valid = false;
				} else if ((*token).get_type() == EQ) {
					isAssignment = true;
					state = operand;
				} else if ((*token).get_type() == OP)
					state = operand; // If token is an operator, expect an operand next
				else
					valid = false;
				break;

			default:
				break;
		}
	} while (valid && ++token != tokenized.end());

	if (level != 0) // Un-balanced parenthesis
		valid = false;
	if (state = operand) // Ended with an operator
		valid = false;

	if (valid) { // Set expression type
		if (isAssignment) { // Assignment can not evaluate, so it must have 3 tokens
			if (tokenized.size() == 3 && tokenized[0].get_type() == ID && tokenized[2].get_type() == INT)
				type = assignment;
			else
				valid = false;
		} else
			type = arithmetic;
	}
}

// Helper classes to make pop() return the removed value
template<class T>
T popStack(stack<T> &st) {
	T val = st.top();
	st.pop();
	return val;
}

template<class T>
T popQueue(queue<T> &q) {
	T val = q.front();
	q.pop();
	return val;
}

void Expression::generatePostfix() {
	stack<Token> opStack;

	// Using a shunting-yard algorithm
	for (int i = 0; i < tokenized.size(); i++) {
		Token t = tokenized[i];
		if (t.get_type() == INT || t.get_type() == ID)
			postfix.push_back(t);
		else if (t.get_type() == OpenBrace)
			opStack.push(t);
		else if (t.get_type() == CloseBrace) {
			// Push all of the operators in the stack until the open paren is found
			while (!opStack.empty() && opStack.top().get_type() != OpenBrace)
				postfix.push_back(popStack(opStack));

			opStack.pop(); // Remove open parenthesis
		} else { // Operator
			// Push all operators from the stack with equal or higher precedence until an open paren is found
			while (!opStack.empty() && opStack.top().get_type() != OpenBrace && opStack.top().get_priority() >= t.get_priority())
				postfix.push_back(popStack(opStack));

			opStack.push(t);
		}
	}

	while (!opStack.empty()) // Push remaining operators
		postfix.push_back(popStack(opStack));
}

void Expression::generatePrefix() {
	queue<Token> q;
	stack<Token> ops;

	// Using a reverse shunting-yard algorithm
	for (int i = (int)tokenized.size() - 1; i >= 0; i--) {
		Token t = tokenized[i];
		if (t.get_type() == INT || t.get_type() == ID)
			q.push(t);
		else if (t.get_type() == OP) {
			// Push all operators with equal or higher precedence until a close paren is found
			while (!ops.empty() && ops.top().get_priority() >= t.get_priority() && ops.top().get_type() != CloseBrace)
				q.push(popStack(ops));
			ops.push(t);
		} else if (t.get_type() == CloseBrace)
			ops.push(t);
		else if (t.get_type() == OpenBrace) {
			// Push all operators until a close paren is found
			while (ops.top().get_type() != CloseBrace)
				q.push(popStack(ops));
			ops.pop(); // Remove the right bracket
		}
	}

	while (!ops.empty()) // Push remaining operators
		q.push(popStack(ops));

	while (!q.empty()) // Push the queue to the prefix vector
		prefix.push_back(popQueue(q));

	reverse(prefix.begin(), prefix.end()); // Queue needed to become a stack, so we reverse the vector
}

void Expression::set(const string &s) {
	original = s;
	tokenized.clear(); // Remove old tokens
	postfix.clear();
	prefix.clear();
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
	if (valid) {
		generatePostfix();
		generatePrefix();
	}
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
	if (type == assignment) { // Set the variable to the given value, return that value
		vars[tokenized[0].get_token()] = tokenized[2].value();
		return tokenized[2].value();
	}

	stack<int> operands;
	// Evaluate using the postfix vector
	// When an operator is found, get the top two operands from the stack and evaulate
	for (int i = 0; i < postfix.size(); i++) {
		Token token = postfix[i];
		if (token.get_type() == INT)
			operands.push(token.value());
		else if (token.get_type() == ID) {
			if (vars.count(token.get_token()) == 0)
				throw runtime_error("Undefined variable referenced in expression");

			operands.push(vars[token.get_token()]);
		} else { // Right operand is at the top, so get it first
			int val2 = popStack(operands);
			int val1 = popStack(operands);

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

	return operands.top(); // Top is the result
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

void Expression::printPrefix() {
	if (!valid) {
		cout << "No prefix version of " << original << " because it is not a valid expression." << endl;
		return;
	}

	if (type == assignment) {
		cout << "No prefix of " << original << " because it is an assignment expression." << endl;
		return; // Hide postfix for assignment expressions for some reason
	}

	cout << "Prefix of " << original << ':';
	for (int i = 0; i < prefix.size(); i++)
		cout << ' ' << prefix.at(i).get_token();

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
	// Rebuild from postfix notation, similar logic to evaluate()
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
