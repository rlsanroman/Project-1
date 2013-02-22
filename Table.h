#ifndef TABLE_H_
#define TABLE_H_

#include <map>
#include "Record.h"
#include "Attribute.h"

class __declspec(dllexport) Table
{
private:
	vector<Attribute> attributes;
	vector<Record> records;
	
	class improperSyntax: public exception
	{
		virtual const char* what() const throw()
		{
			return "Improper Query Syntax";
		}
	};
	
	class noEntryTable: public exception
	{
		virtual const char* what() const throw()
		{
			return "Entry does not exist in Table";
		}
	};
	
	struct boolTree {
	public:
		string value;
		bool isBoolean, negated;
		boolTree *left, *right;
		
		boolTree(): negated(false) {}
		boolTree(bool isB): isBoolean(isB), negated(false) {}
		boolTree(string value): value(value), isBoolean(false), negated(false) {}
		boolTree(string value, boolTree* l, boolTree* r): value(value), isBoolean(false), left(l), right(r), negated(false) {}
	};
	
	string getToken(string& str);
	boolTree* makeTree(string& cond);
	bool checkEntry(boolTree* conditions, Record* r);
	unsigned long getIndex(const string& ref);
	
public:

	Table();
	Table(vector<Attribute> a);

	void addColumn(Attribute att);
	void deleteColumn(string name);
	void insertRecord(Record r);

	vector<Attribute> getAttributes() const { return attributes; }
	unsigned long getSize() const { return records.size(); }
	Record getRecord(int index) const { return records[index]; } // added this function to get record


	void renameAttribute(string oldname, string newname);
	Table static crossJoin(const Table& t1, const Table& t2);
	int sum(string name);
	unsigned int count(string name);
	int min (string name);
	int max (string name);
	
	vector<Record*> checkAgainst(string cond);
	friend class Database;
};

#endif