/*
 * CSCE 2014 HW #5
 * Author: Brandon Russell
 *
 * Parses an expression into a series of tokens
*/

#include <iostream>
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
}

void Expression::display() const {
	cout << "original = " << original << endl;

	cout << "tokenized = ";
	for (int i = 0; i < (int)tokenized.size(); i++)
		cout << tokenized.at(i).get_token() << ";";

	cout << "\npostfix = ";
	for (int i = 0; i < (int)postfix.size(); i++)
		cout << postfix.at(i).get_token() << ";";

	cout << "\nvalid = " << valid << endl;
	cout << "type = " << typeToString(type) << endl;
}
