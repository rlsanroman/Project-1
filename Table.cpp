#include "Table.h"
#include <stdlib.h>

Table::Table() { }

Table::Table(vector<Attribute> a) : attributes(a) { }

unsigned long Table::convertDate(char* date)
{
	const int ATOI = 48;  //ascii to integer conversion constant
	unsigned long days = 10*(date[8]-ATOI)+(date[9]-ATOI);
	unsigned long months = 10*(date[5]-ATOI)+(date[6]-ATOI);
	unsigned long years = 1000*(date[0]-ATOI)+100*(date[1]-ATOI)+10*(date[2]-ATOI)+date[3]-ATOI;
	days += (31*months+365*years); //uniform conversion to days to easily subtract dates
	return days;
}

void Table::addColumn(Attribute att)
{
	attributes.push_back(att);
}

void Table::deleteColumn(string name)
{
	bool found = false;
	for(int i = 0; i < attributes.size() && !found; i++)
	{
		if( name == attributes[i].getName() )
		{
			attributes.erase(attributes.begin() + i);
			for (vector<Record>::iterator it = records.begin(); it != records.end(); ++it)
				it->tuples.erase(it->tuples.begin() + i);
			found = true;
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

unsigned long Table::getIndex(const string& ref) {
	for (int i=0; i<attributes.size(); i++) {
		if (attributes[i].getName() == ref) {
			return i;
		}
	}
	throw noEntryTable();
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
			for (int j=1; j<records.size(); j++)
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
			for (int j=1; j<records.size(); j++)
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

string Table::getToken(string& str) {
	if (str.size() == 0)
		return "";
	
	string ret;
	
	switch (str[0]) {
		case '(':
			ret = "(";
			break;
		case ')':
			ret = ")";
			break;
		case '=':
			if (str[1] == '=')
				ret = "==";
			else
				throw improperSyntax();
			break;
		case '!':
			if (str[1] == '=')
				ret = "!=";
			else
				throw improperSyntax();
			break;
		case '<':
			if (str[1] == '=')
				ret = "<=";
			else
				ret = "<";
			break;
		case '>':
			if (str[1] == '=')
				ret = ">=";
			else
				ret = ">";
			break;
		case '&':
			if (str[1] == '&')
				ret = "&&";
			else
				throw improperSyntax();
			break;
		case '|':
			if (str[1] == '|')
				ret = "||";
			else
				throw improperSyntax();
			break;
		default:
			unsigned long index = str.find_first_of("()=!<>&|");
			ret = str.substr(0,index);
			if(ret[ret.size()-1] == ' ')
				ret.pop_back();
			break;
	}
	
	str.erase(0,ret.size() + (str[ret.size()] == ' '));
	
	return ret;
}

Table::boolTree* Table::makeTree(string& cond){
	boolTree* tree = new boolTree(true);
	bool negate = false;
	
	// negate if necessary
	if (cond[0] == '!' && cond[1] == '('){
		negate = true;
		cond.erase(0,1);
	}
		
	// left side of possible boolean operation
	string token = getToken(cond);
	if (token == ")" || token == "==" || token == "!=" || token == ">" || token == ">=" ||
		token == "<" || token == "<=" || token == "&&" || token == "||")
		throw improperSyntax();
	else if (token == "(") {
		tree->left = makeTree(cond);
		if (negate) {
			tree->left->negated = true;
			negate = false;
		}
		
		if(getToken(cond) != ")")
			throw improperSyntax();
	}
	else {
		// THIS ASSUMES GOOD SYNTAX
		tree->left = new boolTree(getToken(cond));
		tree->left->left = new boolTree(token);
		tree->left->right = new boolTree(getToken(cond));
	}
	
	token = getToken(cond);
	// if this has no boolean operator
	if (token == ")" || token == "") {
		cond = token + cond;
		return tree->left;
	}
	
	// get actual value
	if (token != "&&" && token != "||")
		throw improperSyntax();
	else {
		tree->value = token;
	}
	
	if (cond[0] == '!' && cond[1] == '('){
		negate = true;
		cond.erase(0,1);
	}
	
	// right side
	token = getToken(cond);
	if (token == ")" || token == "==" || token == "!=" || token == ">" || token == ">=" || token == "<" || token == "<=" || token == "&&" || token == "||")
		throw improperSyntax();
	else if (token == "(") {
		tree->right = makeTree(cond);
		if (negate) {
			tree->right->negated = true;
			negate = false;
		}
		
		if(getToken(cond) != ")")
			throw improperSyntax();
	}
	else {
		// THIS ASSUMES GOOD SYNTAX
		tree->right = new boolTree(getToken(cond));
		tree->right->left = new boolTree(token);
		tree->right->right = new boolTree(getToken(cond));
	}
	
	return tree;
}

bool Table::checkEntry(boolTree* conditions, Record* r) {
	bool ret = false;
	
	if (conditions->isBoolean) {
		bool left = checkEntry(conditions->left, r);
		bool right = checkEntry(conditions->right, r);
		if(conditions->value == "&&")
			ret = left && right;
		else
			ret = left || right;
	}
	else {
		unsigned long index = getIndex(conditions->left->value);
		string left = r->tuples[index];
		char type = attributes[index].getType();
		if (conditions->value == "==") {
			switch (type) {
				case 's':
					return left == conditions->right->value;
					break;
				case 'i':
					return atoi(left.c_str()) == atoi(conditions->right->value.c_str());
					break;
				case 'f':
					return atof(left.c_str()) == atof(conditions->right->value.c_str());
					break;
				case 'd':
					return false;
					break;
			}
		}
		if (conditions->value == "!=") {
			switch (type) {
				case 's':
					return left != conditions->right->value;
					break;
				case 'i':
					return atoi(left.c_str()) != atoi(conditions->right->value.c_str());
					break;
				case 'f':
					return atof(left.c_str()) != atof(conditions->right->value.c_str());
					break;
				case 'd':
					return false;
					break;
			}
		}
		if (type == 's')
			throw improperSyntax();
		if (conditions->value == "<=") {
			switch (type) {
				case 'i':
					return atoi(left.c_str()) <= atoi(conditions->right->value.c_str());
					break;
				case 'f':
					return atof(left.c_str()) <= atof(conditions->right->value.c_str());
					break;
				case 'd':
					return false;
					break;
			}
		}
		if (conditions->value == "<") {
			switch (type) {
				case 'i':
					return atoi(left.c_str()) < atoi(conditions->right->value.c_str());
					break;
				case 'f':
					return atof(left.c_str()) < atof(conditions->right->value.c_str());
					break;
				case 'd':
					return false;
					break;
			}
		}
		if (conditions->value == ">=") {
			switch (type) {
				case 'i':
					return atoi(left.c_str()) >= atoi(conditions->right->value.c_str());
					break;
				case 'f':
					return atof(left.c_str()) >= atof(conditions->right->value.c_str());
					break;
				case 'd':
					return false;
					break;
			}
		}
		if (conditions->value == ">") {
			switch (type) {
				case 'i':
					return atoi(left.c_str()) > atoi(conditions->right->value.c_str());
					break;
				case 'f':
					return atof(left.c_str()) > atof(conditions->right->value.c_str());
					break;
				case 'd':
					return false;
					break;
			}
		}
	}
	
	if (conditions->negated)
		ret = !ret;
	
	return ret;
}

vector<Record*> Table::checkAgainst(string cond){
	vector<Record*> ret;
	boolTree* conditions = makeTree(cond);
	
	for(int i = 0; i < records.size(); ++i) {
		if(checkEntry(conditions, &records[i]))
			ret.push_back(&records[i]);
	}
	
	return ret;
}
