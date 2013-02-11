#include "Record.h"


string Record::getTuple(int index)
{
	return tuples[index];
}

void Record::setTuple(int index, string newdata)
{
	tuples[index] = newdata;
}