#include "ProcessorSin.h"

int ProcessorSin::getPriority()
{
    return 4;
}

double ProcessorSin::apply(double number1, double number2)
{
    return std::sin(number2);
}

char ProcessorSin::getChar()
{
    return 's';
}
