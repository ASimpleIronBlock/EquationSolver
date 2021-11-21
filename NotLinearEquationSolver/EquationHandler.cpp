#include "Processor.h"
#include <iostream>
#include <stack>
#include <sstream>
#include "EquationHandler.h"
static std::map<char, Processor*> processorNameMap;
static std::map<std::string, std::string> defineMap;


const double eposilon = 10e-5;

std::list<std::string>* convertToReversePolish(std::string& nifix)
{
	char *chars = new char[nifix.size()+1];
	char** ptr = &chars;
	strcpy_s(chars,nifix.size()+1, nifix.c_str());


	std::list<std::string>* ret = new std::list<std::string>();
	std::stack<char>* stack = new std::stack<char>();

	int counter = 0;

	int currentNumber = 0;
	while (*chars != '\0') {
		counter++;
		//std::cout << "当前字符:" <<  * chars << std::endl;
		if (( * chars >= '0' && *chars <= '9') )
		{
			currentNumber *= 10;
			currentNumber += *chars - '0';
		}
		else if ((*chars == 'x'))
		{
			if (currentNumber!=0)
			{
				ret->push_back(std::to_string(currentNumber));
				currentNumber = 0;
			}

			ret->push_back("x");
		}else {
			if (currentNumber != 0)
			{
				ret->push_back(std::to_string(currentNumber));
				currentNumber = 0;
			}
			
			 if (*chars=='(') {
				//左括号

				if (currentNumber != 0)
				{
					ret->push_back(std::to_string(currentNumber));
					currentNumber = 0;
				}

				stack->push(*chars);
				
			}
			else if (*chars == ')') {
				//右括号

				if (currentNumber != 0)
				{
					ret->push_back(std::to_string(currentNumber));
					currentNumber = 0;
				}

				while (stack->top() != '(') {
					if (stack->empty())
					{
						std::cout << "遇到了右括号，但是没有找到匹配的左括号，问题发生在第"<<counter<<"个字符上" << std::endl;
						break;
					}
					char top = stack->top();
					stack->pop();
					std::string a(&top,1);
					//std::cout << "符号:" << a << std::endl;
					ret->push_back(a);
				}
				stack->pop();

			}
			 else if (getProcessor(*chars) != nullptr)
			 {

				 if (currentNumber != 0)
				 {
					 ret->push_back(std::to_string(currentNumber));
					 currentNumber = 0;
				 }


				 while (!stack->empty()&&stack->top() != '(' && ( getProcessor(stack->top())->getPriority() >= getProcessor(*chars)->getPriority())) {
					 char top = stack->top();
					 stack->pop();
					 std::string a(&top, 1);
					 //std::cout << "符号:" << a << std::endl;
					 ret->push_back(a);
				 }

				 stack->push(*chars);

			 }
			else {
				std::cout << "未能识别第"<<counter<<"个字符:" << *chars << std::endl;
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
		char a = stack->top();
		stack->pop();
		std::string b(&a,1);
		ret->push_back(b);
		//std::cout << "符号:" << b <<";" << std::endl;
	}
	delete stack;
	if (ret->size()==0)
	{
		ret->push_back("0");
	}
	return ret;
}
std::list<std::string>* calcReversePolish(std::list<std::string>* in) {
	//返回值列表
	std::list<std::string>* list = new std::list<std::string>();
	//栈
	std::stack<std::string> *stack = new std::stack<std::string>();
	Processor* proc = NULL;
	for (std::list<std::string>::iterator it = in->begin(); it != in->end(); ++it) {
		char c = ( * it->c_str());
		if (getProcessor(c)!=nullptr)
		{
			proc = getProcessor(c);
			if (stack->empty())
			{
				std::cout << "要计算的后缀表达式似乎出了点问题:(" << std::endl;
				return list;
			}
			std::string  str2 = stack->top();
			stack->pop();
			if (stack->empty())
			{
				std::cout << "要计算的后缀表达式似乎出了点问题:(" << std::endl;
				return list;
			}
			std::string  str1 = stack->top();
			stack->pop();
			//参数里有x
			const char* c1 = str1.c_str();
			const char* c2 = str2.c_str();

			if (str1=="x"||str2=="x"||*c1<'0'||*c1>'9'||*c2<'0'||*c2>'9')
			{
				stack->push(str1);
				stack->push(str2);
				stack->push(*it);
			}
			else {
				double num1 = atof(str1.c_str());
				double num2 = atof(str2.c_str());
				double result = proc->apply(num1, num2);
				stack->push(std::to_string(result));
			}
			
		}
		else {
			stack->push(*it);
		}

	}
	while (!stack->empty())
	{
		list->push_front(stack->top());
		stack->pop();
	}

	delete stack;
	return list;

}

double calcReversePolish(std::list<std::string>* in, double x)
{
	//栈
	std::stack<std::string>* stack = new std::stack<std::string>();
	Processor* proc = NULL;
	for (std::list<std::string>::iterator it = in->begin(); it != in->end(); ++it) {
		char c = (*it->c_str());
		if (getProcessor(c) != nullptr)
		{
			proc = getProcessor(c);
			std::string  str2 = stack->top();
			stack->pop();
			std::string  str1 = stack->top();
			stack->pop();

			if (str1=="x")
			{
				str1 = std::to_string(x);
			}

			if (str2 == "x")
			{
				str2 = std::to_string(x);
			}
			
				double num1 = atof(str1.c_str());
				double num2 = atof(str2.c_str());
				double result = proc->apply(num1, num2);
				stack->push(std::to_string(result));
			

		}
		else {
			stack->push(*it);
		}

	}
	if (stack->size()!=1)
	{
		std::cout << "后缀表达式的最终结果居然不是一个数？？！！！" << std::endl;
	}
	double res = std::atof(stack->top().c_str());

	delete stack;
	return res;

}


void registerProcessor(Processor& processor)
{
	processorNameMap.insert(std::pair<char,Processor*>::pair(processor.getChar(),&processor));
	if (processor.getAliase() != nullptr)
	{
		defineMap.insert(*processor.getAliase());
	}

}


void init() {

	Processor* add = new ProcessorAdd();
	Processor* sub = new ProcessorSubtract();
	Processor* multi = new ProcessorMutilply();
	Processor* divide = new ProcessorDivide();
	Processor* pow = new ProcessorPow();
	Processor* sin = new ProcessorSin();
	Processor* cos = new ProcessorCos();
	Processor* tan = new ProcessorTan();




	registerProcessor(*add);
	registerProcessor(*sub);
	registerProcessor(*multi);
	registerProcessor(*divide);
	registerProcessor(*pow);
	registerProcessor(*sin);
	registerProcessor(*cos);
	registerProcessor(*tan);
}


void destroy() {
	std::map<char, Processor*>::iterator iter;
	iter = processorNameMap.begin();
	while (iter != processorNameMap.end()) {
		delete iter->second;
		iter++;
	}
}


Processor* getProcessor(char& name) {
	Processor* pro = processorNameMap[name];
	return pro;
}


std::list<std::string>* phaseEquation(std::string input) {
	//把空格替换掉
	std::string str = replaceWith(input, " ", "");

	//分别解析等号的左面和右面
	std::vector<std::string> two= split(str, "=");
	if (two.size() != 2)
	{
		std::cout << "方程有且只有一个等号" << std::endl;
		return nullptr;
	}
	//中缀表达式转后缀表达式
	std::list<std::string>* reversePolishLeft = convertToReversePolish(two[0]);
	std::list<std::string>* reversePolishRight = convertToReversePolish(two[1]);

	//计算后缀表达式的值
	std::list<std::string>* valueLeft = calcReversePolish(reversePolishLeft);
	std::list<std::string>* valueRight = calcReversePolish(reversePolishRight);


	//移项
	for (std::list<std::string>::iterator it = valueRight->begin(); it != valueRight->end(); ++it) {
		valueLeft->push_back(*it);
	}
	valueLeft->push_back("-");
	std::list<std::string>* afterAll = calcReversePolish(valueLeft);




	//打印
	std::cout << "等号左面的后缀表达式:" << std::endl;
	for (std::list<std::string>::iterator it = reversePolishLeft->begin(); it != reversePolishLeft->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "等号右面的后缀表达式:" << std::endl;
	for (std::list<std::string>::iterator it = reversePolishRight->begin(); it != reversePolishRight->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "等号左面的后缀表达式的值:" << std::endl;
	for (std::list<std::string>::iterator it = valueLeft->begin(); it != valueLeft->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;


	std::cout << "等号右面的后缀表达式的值:" << std::endl;
	for (std::list<std::string>::iterator it = valueRight->begin(); it != valueRight->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "最终结果的后缀表达式:" << std::endl;
	for (std::list<std::string>::iterator it = afterAll->begin(); it != afterAll->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;



	delete reversePolishLeft;
	delete reversePolishRight;
	delete valueLeft;
	delete valueRight;


	return afterAll;

}

//牛顿法解方程
double solveEquation(std::list<std::string>* equation,double x0) {
	double x = x0;
	int itrCounter = 0;
	//迭代
	while (true)
	{
		itrCounter++;
		double derivative = calcDerivativeAt(equation, x);
		double value = calcReversePolish(equation, x);
		std::cout <<"第"<<itrCounter<< "次迭代:函数在" << x << "处的斜率为" << derivative << ",值为" << value << std::endl;
		if (std::abs(value)<eposilon)
		{
			break;
		}

		if (std::abs(derivative)<eposilon||!isfinite(derivative)||!isfinite(value))
		{
			x = INFINITY;
			break;
		}

		x -= (value / derivative);
	}
	return x;
}
//检验函数是否和变量有关系
double calcDerivativeAt(std::list<std::string>* equation, double x)
{
	return (calcReversePolish(equation, x + eposilon)-calcReversePolish(equation, x) )/eposilon;
}


bool isConstant(std::list<std::string>* equation){
	double y1 = calcReversePolish(equation, rand());
	double y2 = calcReversePolish(equation, rand());
	double delta = std::abs(y1 - y2);
	return delta < eposilon;
}


std::string& replaceDefine(std::string input) {
	std::map<std::string, std::string>::iterator  it;
	for (it = defineMap.begin(); it != defineMap.end(); ++it)
	{
		replaceWith(input, it->first,it->second);
	}


}








