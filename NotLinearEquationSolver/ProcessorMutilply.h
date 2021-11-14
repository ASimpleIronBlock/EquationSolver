#pragma once
#include "Processor.h"
class ProcessorMutilply :
    public Processor
{
    virtual int getPriority();

    virtual double apply(double number1, double number2);

    virtual char getChar();
};

