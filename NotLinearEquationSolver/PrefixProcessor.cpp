#include "PrefixProcessor.h"
#include "Processor.h"
#include <iostream>
#include <stack>

static std::map<char, Processor*> processorNameMap;


std::list<std::string>* convertToReversePolish(std::string& nifix)
{
	char *chars = new char[nifix.size()+1];
	char** ptr = &chars;
	strcpy_s(chars,nifix.size()+1, nifix.c_str());


	std::list<std::string>* ret = new std::list<std::string>();
	std::stack<Processor>* stack = new std::stack<Processor>();

	int currentNumber = 0;
	while (*chars != '\0') {
		std::cout << "当前字符:" <<  * chars << std::endl;
		if (*chars>='0'&&*chars<='9')
		{
			currentNumber *= 10;
			currentNumber += *chars - '0';
			std::cout << "这是数字" << std::endl;
		}else {
			std::cout << currentNumber <<std:: endl;

			currentNumber = 0;



		}



		chars++;
	}

	return nullptr;
}
void registerProcessor(Processor& processor)
{
	processorNameMap.insert(std::pair<char,Processor*>::pair(processor.getChar(),&processor));
}
