#pragma once
#include "Processor.h"
class ProcessorMutilply :
    public Processor
{
    int getPriority();

    double apply(double number1, double number2);

    char getChar();
};

