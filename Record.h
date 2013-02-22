#ifndef RECORD_H_
#define RECORD_H_

#include <vector>
#include <string>

using namespace std;

class __declspec(dllexport) Record
{
private:
	vector<string> tuples;
public:
	Record() {}
	Record(vector<string> data) : tuples(data) {}
	
	void setTuple(int index, string newdata);
	string operator[](const unsigned long index);
	
	friend class Table;
};

#endif
