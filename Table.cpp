#include "Table.h"
#include <stdlib.h>

Table::Table() { }

Table::Table(vector<Attribute> a) : attributes(a) { }

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
		throw noEntryTable();

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
		throw noEntryTable();
	}
}

Table Table::crossJoin(const Table& t1, const Table& t2)
{
	vector<Attribute> combo(t1.getAttributes());
	
	// Join attributes
	for(vector<Attribute>::const_iterator it = t2.attributes.begin(); it != t2.attributes.end(); ++it) {
		combo.push_back(*it);
	}
	
	Table* fusion = new Table(combo);

	for(vector<Record>::const_iterator it1 = t1.records.begin(); it1 != t1.records.end(); ++it1) {
		for(vector<Record>::const_iterator it2 = t2.records.begin(); it2 != t2.records.end(); ++it2) {
			Record add = Record(it1->tuples);
			add.tuples.insert(add.tuples.end(), it2->tuples.begin(), it2->tuples.end());
			fusion->insertRecord(add);
		}
	}
	
	return *fusion;
}

int Table::sum(string name)
{
	int sum = 0;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{	
			for (int j = 0; j<records.size(); j++)
			{
				sum += atoi(records[j].getTuple(i).c_str());
			}
			return sum;
		}
	}
	throw noEntryTable();
}

unsigned int Table::count(string name)
{
	unsigned int count = 0;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{
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
	throw noEntryTable();
}

int Table::min (string name) 
{
	int min = 0;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{
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
	throw noEntryTable();
}

int Table::max (string name)
{
	int max = 0;
	for (int i=0; i<attributes.size(); i++)
	{
		if ( name == attributes[i].getName() )
		{
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
	throw noEntryTable();
}