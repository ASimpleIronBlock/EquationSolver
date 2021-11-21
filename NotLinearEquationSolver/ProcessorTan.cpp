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

std::pair<std::string, std::string>* ProcessorTan::getAliase()
{
    return new std::pair<std::string, std::string>("tan", "1t");;
}
