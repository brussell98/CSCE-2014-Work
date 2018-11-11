/*
 * CSCE 2014 HW #5
 * Author: Brandon Russell
 *
 * Stores a token that is part of an expression, along with its properties
*/

#include <iostream>
#include <cstdlib>
#include "Token.h"

string typeToString(Token_type t) {
	switch (t) {
		case ID:
			return "ID";
		case INT:
			return "INT";
		case OP:
			return "OP";
		case EQ:
			return "EQ";
		case OpenBrace:
			return "OpenBrace";
		case CloseBrace:
			return "CloseBrace";
		default:
			return "INVALID";
	}
}

Token::Token() {
	type = INVALID;
	token = string();
	priority = -1;
}

Token::Token(string s) {
	set(s);
}

void Token::set(string s) {
	token = s;
	priority = -1;

	if (s == "=")
		type = EQ;
	else if (s == "(")
		type = OpenBrace;
	else if (s == ")")
		type = CloseBrace;
	else if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%")
		type = OP;
	else {
		// First, check if any characters are not alphanumeric. If so, it is invalid
		// Also check if the token contains only numbers
		bool invalid = false;
		bool onlyNum = true;
		for (int i = 0; i < (int)s.size(); i++) {
			if (!isalnum(s[i])) {
				type = INVALID;
				invalid = true;
				break;
			}

			if (!isdigit(s[i]))
				onlyNum = false;
		}

		// If the token is not invalid and starts with an alphabetical character, it's an ID
		if (!invalid) {
			if (isalpha(s[0]))
				type = ID;
			// If the token contains only numbers and is positive, it's an INT
			else if (onlyNum && atoi(s.c_str()) > -1 && (s.length() == 1 || s[0] != '0'))
				type = INT;
			else
				type = INVALID;
		}
	}
}

int Token::value() const {
	switch (type) {
		case ID:
			return -1;
		case INT:
			return atoi(token.c_str());
		default:
			return -2;
	}
}

void Token::display() const {
	cout << "type = " << typeToString(type) << endl;
	cout << "token = " << token << endl;
	cout << "priority = " << priority << endl;
}
