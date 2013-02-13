#ifndef DATABASE_H_
#define DATABASE_H_

#include <map>
#include "Table.h"

using namespace std;

class __declspec(dllexport) duplicateEntry: public exception
{
	virtual const char* what() const throw()
  {
    return "Entry already exists in Database";
  }
};

class __declspec(dllexport) noEntry:  public exception
{
  virtual const char* what() const throw()
  {
    return "Entry does not exist in Database";
  }
};


class __declspec(dllexport) Database
{
private:
	map<string,Table> tables;
public:
	Database();

	void addTable(Table& t, string name);
	void dropTable(string name);
	vector<string> listTables();
	map<string,Table> getTables() { return tables; }

};

#endif