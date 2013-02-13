#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <string>

using namespace std;

class __declspec(dllexport) Attribute
{
private:
	string name;
	char type;
public:
	Attribute() {}
	Attribute(string n, char t) : name(n), type(t) {}
	
	string getName() { return name; }
	char getType() { return type; }
	
	void setName(string n) { name = n; }
	void setType(char t) { type = t; }
};

#endif
