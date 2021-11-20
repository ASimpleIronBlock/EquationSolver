#include "ProcessorPow.h"
#include <cmath>

int ProcessorPow::getPriority()
{
    return 3;
}

double ProcessorPow::apply(double number1, double number2)
{
    return pow(number1,number2);
}

char ProcessorPow::getChar()
{
    return '^';
}
