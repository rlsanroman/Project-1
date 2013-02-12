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
	attributes = t1.getAttributes();

	for(int i = 0; i < t1.getSize(); i++)
	{
		records.push_back(t1.getRecord(i));
	}
}
int Table::sum(string name)
{
	int sum = 0;
	bool found = false;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{	
			found = true;
			for (int j = 0; j<records.size(); j++)
			{
				sum += atoi(records[j].getTuple(i).c_str());
			}
			return sum;
		}
	}
	if (!found)
	{
		throw noEntry();
	}
}
unsigned int Table::count(string name)
{
	bool found = false;
	unsigned int count = 0;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{
			found = true;
			for (int j=0; j<records.size(); j++)
			{
				//count only non-empty values
				if (records[j].getTuple(i) != "")	
				{
					count++;
				}
			}
			return count;
		}
	}
	if (!found)
	{
		throw noEntry();
	}
}
int Table::min (string name) 
{
	bool found = false;
	int min = 0;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{
			found = true;
			min = atoi(records[i].getTuple(0).c_str());
			for (int j=0; j<records.size(); j++)
			{
				if (atoi(records[j].getTuple(i).c_str()) < min)
				{
					min = atoi(records[j].getTuple(i).c_str());
				}
			}
			return min;
		}
	}
	if (!found)
	{
		throw noEntry();
	}
}
int Table::max (string name)
{
	bool found = false;
	int max = 0;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{
			found = true;
			max = atoi(records[i].getTuple(0).c_str());
			for (int j=0; j<records.size(); j++)
			{
				if (atoi(records[j].getTuple(i).c_str()) > max)
				{
					max = atoi(records[j].getTuple(i).c_str());
				}
			}
			return max;
		}
	}
	if (!found)
	{
		throw noEntry();
	}
}