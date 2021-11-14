#include "ProcessorDivide.h"

/**
	除法的优先度第二
*/
int ProcessorDivide::getPriority()
{
	return 2;
}

double ProcessorDivide::apply(double number1, double number2)
{
	return number1 / number2;
}

char ProcessorDivide::getChar()
{
	return '/';
}