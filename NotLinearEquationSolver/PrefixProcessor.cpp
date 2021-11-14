#include "PrefixProcessor.h"
#include "Processor.h"
#include <iostream>
#include <stack>
#include <sstream>
static std::map<char, Processor*> processorNameMap;


std::list<std::string>* convertToReversePolish(std::string& nifix)
{
	char *chars = new char[nifix.size()+1];
	char** ptr = &chars;
	strcpy_s(chars,nifix.size()+1, nifix.c_str());


	std::list<std::string>* ret = new std::list<std::string>();
	std::stack<Processor*>* stack = new std::stack<Processor*>();

	int currentNumber = 0;
	while (*chars != '\0') {
		//std::cout << "��ǰ�ַ�:" <<  * chars << std::endl;
		if (( * chars >= '0' && *chars <= '9') )
		{
			currentNumber *= 10;
			currentNumber += *chars - '0';
			//std::cout << "��������" << std::endl;
		}
		else if ((*chars == 'x'))
		{
			std::cout << "����δ֪��" << std::endl;
			if (currentNumber!=0)
			{
				ret->push_back(std::to_string(currentNumber));
			}

			ret->push_back("x");
		}else {
			std::cout << currentNumber <<std:: endl;
			ret->push_back(std::to_string(currentNumber));
			currentNumber = 0;
			if (getProcessor(*chars)!=nullptr)
			{
				while ( !stack->empty()&&stack->top()->getPriority() > getProcessor(*chars)->getPriority()) {
					char top = stack->top()->getChar();
					stack->pop();
					std::string a(&top,1);
					//std::cout << "����:" << a << std::endl;
					ret->push_back(a);
				}

				stack->push(getProcessor(*chars));

			}
			else {
				std::cout << "δ��ʶ���ַ�:" << *chars << std::endl;
			}



		}
		chars++;
	}
	if (currentNumber!=0)
	{
		ret->push_back(std::to_string(currentNumber));
	}

	while (!stack->empty())
	{
		char a = stack->top()->getChar();
		stack->pop();
		std::string b(&a,1);
		ret->push_back(b);
		//std::cout << "����:" << b <<";" << std::endl;
	}


	return ret;
}
void registerProcessor(Processor& processor)
{
	processorNameMap.insert(std::pair<char,Processor*>::pair(processor.getChar(),&processor));
}


Processor* getProcessor(char& name) {
	Processor* pro = processorNameMap[name];
	//std::cout << "getProcessor(),name:"<<name<<",����:"<<pro->getChar() << std::endl;
	return pro;
}
