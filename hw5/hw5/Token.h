#pragma once
#include <string>

using namespace std;

enum Token_type { ID, INT, OP, EQ, OpenBrace, CloseBrace, INVALID };

class Token {
public:
	Token();
	Token(string s);
	void set(string s);
	int value() const;
	void display() const;
	Token_type get_type() const {
		return type;
	}
	string get_token() const {
		return token;
	}
	int get_priority() const {
		return priority;
	}
private:
	int priority;
	Token_type type;
	string token;
};
