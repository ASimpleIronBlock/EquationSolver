#include "ProcessorAdd.h"
/**
	加法的优先度最低
*/
int ProcessorAdd::getPriority()
{
	return 1;
}

double ProcessorAdd::apply(double number1, double number2)
{
	return number1+number2;
}

char ProcessorAdd::getChar()
{
	return '+';
}
