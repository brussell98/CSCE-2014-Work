/*
 * CSCE 2014 HW #5
 * Author: Brandon Russell
 *
 * Parses an expression into a series of tokens
 * Generates postfix and prefix notations, and evaluates the result
*/

#pragma once
#include <string>
#include <vector>
#include <map>
#include "Token.h"

using namespace std;

enum Exp_type { assignment, arithmetic, illegal };

class Expression {
public:
	Expression();
	Expression(const string &s);
	void set(const string &s);
	void display() const;
	string get_original() const {
		return original;
	}
	vector<Token> get_tokenized() const {
		return tokenized;
	}
	bool isValid();
	Exp_type getType();
	int evaluate(map<string, int> &vars);
	void printPostfix();
	void printPrefix();
	void printParenthesized();
private:
	string original;
	vector<Token> tokenized;
	vector<Token> postfix;
	vector<Token> prefix;
	bool valid;
	Exp_type type;
	void validate();
	void generatePostfix();
	void generatePrefix();
};
