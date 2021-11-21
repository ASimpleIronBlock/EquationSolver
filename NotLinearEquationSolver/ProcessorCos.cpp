#include "ProcessorCos.h"
int ProcessorCos::getPriority()
{
    return 4;
}

double ProcessorCos::apply(double number1, double number2)
{
    return std::cos(number2);
}

char ProcessorCos::getChar()
{
    return 'c';
}

std::pair<std::string, std::string>* ProcessorCos::getAliase()
{
    return new std::pair<std::string,std::string>("cos","1c");
}
