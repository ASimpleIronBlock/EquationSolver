#pragma once
#include "Processor.h"
class ProcessorAdd :
    public Processor
{
public:
    virtual int  getPriority();

    virtual double apply(double number1, double number2);

    virtual char getChar();
};

