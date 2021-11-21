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

std::pair<std::string, std::string>* ProcessorSin::getAliase()
{
    return new std::pair<std::string, std::string>("sin", "1s");;
}
