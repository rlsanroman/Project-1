#include "Database.h"

Database::Database()
{

}

void Database::addTable(Table& t, string name)
{
	if (tables.find(name) != tables.end())
		throw duplicateEntry();

	tables[name] = t;
}

void Database::dropTable(string name)
{
	if (tables.find(name) == tables.end())
		throw noEntry();

	tables.erase(tables.find(name));
}

vector<string> Database::listTables()
{
	vector<string> names;
	for (map<string,Table>::iterator it = tables.begin(); it != tables.end(); ++it) {
		names.push_back(it->first);
	}

	return names;
}

Table* Database::Query(vector<string> strSelect, string strWhere, string strFrom) const
{
	return NULL;
}
	
bool Database::Delete(vector<string> strSelect, string strWhere, string strFrom)
{
	return true;
}