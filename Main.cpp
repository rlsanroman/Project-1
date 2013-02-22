#include "Database.h"
#include <iostream>

using namespace std;

void upcase(string &word)
{
	for (int i = 0; i < word.size(); i++)
	{
		if(word[i] > 96 && word[i] < 123)
			word[i] -= 32;
	}
}

int main()
{
	char ch;
	cout << "This is the ultimate test, MUAHAHAHAHAHA!" << endl;
	
	
	Database database;
	Table table;

	vector<string> record1;
	record1.push_back("Rosbel");
	record1.push_back("Sanroman");
	record1.push_back("21");
	record1.push_back("2001/09/11");

	vector<string> record2;
	record2.push_back("Jordan");
	record2.push_back("Heaps");
	record2.push_back("20");
	record2.push_back("1992/05/27");

	vector<string> record3;
	record3.push_back("Matt");
	record3.push_back("Dillard");
	record3.push_back("20");
	record3.push_back("1991/09/20");

	Record person1(record1);
	Record person2(record2);
	Record person3(record3);

	Attribute attribute1("First",'s');
	Attribute attribute2("Last",'s');
	Attribute attribute3("Age",'i');
	Attribute attribute4("DOB",'d');
	table.addColumn(attribute1);
	table.addColumn(attribute2);
	table.addColumn(attribute3);
	table.addColumn(attribute4);

	table.insertRecord(person1);
	table.insertRecord(person2);
	table.insertRecord(person3);

	/*database.addTable(table,"Group14");

	database.printTable(table);
	cout << endl << endl;
	Table* t = database.Query("*","Age>=21","Group14");
	database.addTable(*t,"Query");
	database.printTable(*t);*/
	
	//vector<Record*> t = table.checkAgainst("DOB != 2001/09/11 && First == Matt");
	cin >> ch;
}
