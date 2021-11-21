#pragma once
#include "Processor.h"
#include <cmath>
class ProcessorSin :
    public Processor
{
public:
    virtual int  getPriority();

    virtual double apply(double number1, double number2);

    virtual char getChar();

    virtual std::pair<std::string, std::string>* getAliase();
};

