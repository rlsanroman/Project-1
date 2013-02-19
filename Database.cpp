#include "Database.h"
#include <iostream>

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

Table* Database::Query(vector<string> strSelect, string strWhere, string strFrom)
{
	Table table = getTables()[strFrom];
	Table* newTable = new Table();
	
	for (int i=0; i < strSelect.size(); i++)
	{
		Attribute* att = new Attribute(strSelect[i],'s');
		newTable->addColumn(*att);
	}

	vector<string> operators = parse(strWhere);
	int index;
	bool found = false;
	for(index = 0; index < table.getAttributes().size(); index++)
	{
		if(table.getAttributes()[index].getName() == operators[0])
		{
			found = true;
			break;
		}
	}

	return newTable;
}
	
bool Database::Delete(vector<string> strSelect, string strWhere, string strFrom)
{
	return true;
}


/////////////////////////Private Functions///////////////////////////////////

vector<string> Database::parse(string strWhere)
{
	string leftop;
	string rightop;
	bool passedOperator = false;
	string op;
	for (int i = 0; i < strWhere.size(); i++)
	{
		switch(strWhere[i])
		{
			case '>':
				if(strWhere[i+1] == '=')
				{
					op = ">=";
					passedOperator = true;
					i++;
					break;
				}
				op = ">";
				passedOperator = true;
				break;
			case '<':
				if(strWhere[i+1] == '=')
				{
					op = "<=";
					i++;
					passedOperator = true;
					break;
				}
				op = "<";
				passedOperator = true;
				break;
			case '=':
				op = "=";
				passedOperator = true;
				break;
			case '!':
				i++;
				op = "!=";
				passedOperator = true;
				break;
			default:
				passedOperator = false;
				break;
		}

		if(isdigit(strWhere[i]) || isalpha(strWhere[i]))
		{
			if(passedOperator)
				rightop.push_back(strWhere[i]);
			else 
				leftop.push_back(strWhere[i]);
		}
	}
	vector<string> operators;
	operators.push_back(leftop);
	operators.push_back(op);
	operators.push_back(rightop);

	return operators;
}


//Debugging Function to print table
void Database::printTable(Table table)
{
	for(int i = 0; i < table.getSize(); i++)
	{
		for(int j = 0; j < table.getAttributes().size(); j++)
		{
			cout << table.getRecord(i).getTuple(j) << " ";
		}
		cout << endl;
	}
}
