#pragma once
#include "Processor.h"
#include <cmath>
class ProcessorTan :
    public Processor
{
public:
    virtual int  getPriority();

    virtual double apply(double number1, double number2);

    virtual char getChar();
};

