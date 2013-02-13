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
public:

	class noEntry: public exception
	{
		virtual const char* what() const throw()
		{
		return "Entry does not exist in Table";
		}
	};

	Table();
	Table(vector<Attribute> a);

	void addColumn(Attribute att);
	void deleteColumn(string name);
	void insertRecord(Record r);

	vector<Attribute> getAttributes() const { return attributes; }
	int getSize() const { return records.size(); }
	Record getRecord(int index) const { return records[index]; } // added this function to get record


	void renameAttribute(string oldname, string newname);
	void crossJoin(const Table& t1, const Table& t2);
	int sum(string name);
	unsigned int count(string name);
	int min (string name);
	int max (string name);

};

#endif