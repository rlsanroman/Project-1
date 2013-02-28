#include "Record.h"

void Record::setTuple(int index, string newdata) {
	tuples[index] = newdata;
}

string Record::operator[](const unsigned long index) {
	return tuples[index];
}

int Record::getSize()
{
	return tuples.size();
}
