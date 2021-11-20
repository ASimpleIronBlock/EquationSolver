#include "ProcessorTan.h"
int ProcessorTan::getPriority()
{
    return 4;
}

double ProcessorTan::apply(double number1, double number2)
{
    return std::tan(number2);
}

char ProcessorTan::getChar()
{
    return 't';
}