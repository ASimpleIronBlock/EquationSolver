#include "ProcessorSubtract.h"
/**
	�ӷ������ȶ����
*/
int ProcessorSubtract::getPriority()
{
    return 1;
}

double ProcessorSubtract::apply(double number1, double number2)
{
	return number1 - number2;
}

char ProcessorSubtract::getChar()
{
	return '-';
}
