#include "ProcessorMutilply.h"
/**
	�˷������ȶȵڶ�
*/
int ProcessorMutilply::getPriority()
{
	return 2;
}

double ProcessorMutilply::apply(double number1, double number2)
{
	return number1 * number2;
}

char ProcessorMutilply::getChar()
{
	return '*';
}