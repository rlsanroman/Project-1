#include "Table.h"

Table::Table()
{

}
Table::Table(vector<Attribute> a)
{
	attributes = a;
}

void Table::addColumn(Attribute att)
{
	attributes.push_back(att);
}

void Table::deleteColumn(string name)
{
	bool found = false;
	for(int i = 0; i < attributes.size(); i++)
	{
		if( name == attributes[i].getName() )
		{
			attributes.erase(attributes.begin() + i);
			found = true;
			break;
		}
	}
	if (!found)
		throw noEntry();

}
void Table::insertRecord(Record r)
{
	records.push_back(r);
}



void Table::renameAttribute(string oldname, string newname)
{
	bool found = false;
	for (int i = 0; i < attributes.size(); i++)
	{
		if ( oldname == attributes[i].getName() )
		{
			attributes[i].setName(newname);
			found = true;
			break;
		}
	}
	if (!found)
	{
		throw noEntry();
	}
}
void Table::crossJoin(const Table& t1, const Table& t2)
{

}
int Table::sum(string name)
{

}
unsigned int Table::count(string name)
{

}
int Table::min (string name)
{

}
int Table::max (string name)
{

}