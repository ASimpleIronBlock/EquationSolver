#pragma once
#include <string>
#include <list>
#include "Processor.h"
#include <map>


std::list<std::string>* convertToReversePolish(std::string& nifix);

void registerProcessor(Processor& processor);

