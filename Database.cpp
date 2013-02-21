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

Table* Database::Query(string strSelect, string strWhere, string strFrom)
{
	Table table = getTables()[strFrom];
	Table* newTable = new Table();
	int selindex;
	int whereindex;
	vector<string> operators = parse(strWhere);
	/* Currently for multiple selects, though requirements do not specify */
	if (strSelect == "*")
	{
		selindex = -1;	//-1 indicates select ALL
		for (int i=0; i < table.getAttributes().size(); i++)
		{
			Attribute att = *new Attribute(strSelect,'s');
			newTable->addColumn(att);
		}
	}
	else //only one select (first element of the strSelect Vector)
	{
		for (selindex=0; selindex < table.getAttributes().size(); selindex++)
		{
			if(table.getAttributes()[selindex].getName() == strSelect)
			{
				Attribute att = *new Attribute(strSelect,'s');
				newTable->addColumn(att);
				break;
			}
		}
	}
	bool wherefound = false;
	for(whereindex =0; whereindex < table.getAttributes().size(); whereindex++)
	{
		if(table.getAttributes()[whereindex].getName() == operators[0])
		{
			wherefound = true; // we found the where case
			break; //we got our where index
		}
	}
	if(!wherefound)
	{
		//throw an exception because where does not exist
	}

	//Checking operations
	for (int i=0; i<table.getSize(); i++)
	{
		if(operators[1] == "<")
		{
			if(selindex == -1)
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) < atof(operators[2].c_str()))
					newTable->insertRecord(table.getRecord(i));
			}
			else
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) < atof(operators[2].c_str()))
				{
					vector<string> record;
					record.push_back(table.getRecord(i).getTuple(selindex));
					Record newrecord = *new Record(record);
					newTable->insertRecord(newrecord);
				}
			}
		}
		else if(operators[1] == ">")
		{
			if(selindex == -1)
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) > atof(operators[2].c_str()))
					newTable->insertRecord(table.getRecord(i));
			}
			else
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) > atof(operators[2].c_str()))
				{
					vector<string> record;
					record.push_back(table.getRecord(i).getTuple(selindex));
					Record newrecord = *new Record(record);
					newTable->insertRecord(newrecord);
				}
			}
		}
		else if(operators[1] == "=")
		{
			if(selindex == -1)
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) == atof(operators[2].c_str()))
					newTable->insertRecord(table.getRecord(i));
			}
			else
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) == atof(operators[2].c_str()))
				{
					vector<string> record;
					record.push_back(table.getRecord(i).getTuple(selindex));
					Record newrecord = *new Record(record);
					newTable->insertRecord(newrecord);
				}
			}
		}
		else if(operators[1] == "<=")
		{
			if(selindex == -1)
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) <= atof(operators[2].c_str()))
					newTable->insertRecord(table.getRecord(i));
			}
			else
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) <= atof(operators[2].c_str()))
				{
					vector<string> record;
					record.push_back(table.getRecord(i).getTuple(selindex));
					Record newrecord = *new Record(record);
					newTable->insertRecord(newrecord);
				}
			}
		}
		else if(operators[1] == ">=")
		{
			if(selindex == -1)
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) >= atof(operators[2].c_str()))
					newTable->insertRecord(table.getRecord(i));
			}
			else
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) >= atof(operators[2].c_str()))
				{
					vector<string> record;
					record.push_back(table.getRecord(i).getTuple(selindex));
					Record newrecord = *new Record(record);
					newTable->insertRecord(newrecord);
				}
			}
		}
		else if(operators[1] == "!=")
		{
			if(selindex == -1)
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) != atof(operators[2].c_str()))
					newTable->insertRecord(table.getRecord(i));
			}
			else
			{
				if(atof(table.getRecord(i).getTuple(whereindex).c_str()) != atof(operators[2].c_str()))
				{
					vector<string> record;
					record.push_back(table.getRecord(i).getTuple(selindex));
					Record newrecord = *new Record(record);
					newTable->insertRecord(newrecord);
				}
			}
		}
	}

	return newTable;
}
	
bool Database::Delete(string strSelect, string strWhere, string strFrom)
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
