#pragma once
#include <string>
#include <list>
#include "Processor.h"
#include <map>
#include "ProcessorAdd.h"
#include "NotLinearEquationSolver.h"
#include "ProcessorSubtract.h"
#include "ProcessorMutilply.h"
#include "ProcessorDivide.h"
#include "ProcessorPow.h"
#include "ProcessorSin.h"
#include "ProcessorCos.h"
#include "ProcessorTan.h"
#include "Utils.h"

std::list<std::string>* convertToReversePolish(std::string& nifix);

void registerProcessor(Processor& processor);
Processor* getProcessor(char& name);
void init();
std::list<std::string>* phaseEquation(std::string input);
void destroy();
std::list<std::string>* calcReversePolish(std::list<std::string>* in);
double calcReversePolish(std::list<std::string>* in,double x);


double solveEquation(std::list<std::string>* equation, double x0);

double calcDerivativeAt(std::list<std::string>* equation,double x);

bool isConstant(std::list<std::string>* equation);