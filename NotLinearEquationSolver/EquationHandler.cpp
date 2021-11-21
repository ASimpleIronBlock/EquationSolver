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
		//std::cout << "��ǰ�ַ�:" <<  * chars << std::endl;
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
				//������

				if (currentNumber != 0)
				{
					ret->push_back(std::to_string(currentNumber));
					currentNumber = 0;
				}

				stack->push(*chars);
				
			}
			else if (*chars == ')') {
				//������

				if (currentNumber != 0)
				{
					ret->push_back(std::to_string(currentNumber));
					currentNumber = 0;
				}

				while (stack->top() != '(') {
					if (stack->empty())
					{
						std::cout << "�����������ţ�����û���ҵ�ƥ��������ţ����ⷢ���ڵ�"<<counter<<"���ַ���" << std::endl;
						break;
					}
					char top = stack->top();
					stack->pop();
					std::string a(&top,1);
					//std::cout << "����:" << a << std::endl;
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
					 //std::cout << "����:" << a << std::endl;
					 ret->push_back(a);
				 }

				 stack->push(*chars);

			 }
			else {
				std::cout << "δ��ʶ���"<<counter<<"���ַ�:" << *chars << std::endl;
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
		//std::cout << "����:" << b <<";" << std::endl;
	}
	delete stack;
	if (ret->size()==0)
	{
		ret->push_back("0");
	}
	return ret;
}
std::list<std::string>* calcReversePolish(std::list<std::string>* in) {
	//����ֵ�б�
	std::list<std::string>* list = new std::list<std::string>();
	//ջ
	std::stack<std::string> *stack = new std::stack<std::string>();
	Processor* proc = NULL;
	for (std::list<std::string>::iterator it = in->begin(); it != in->end(); ++it) {
		char c = ( * it->c_str());
		if (getProcessor(c)!=nullptr)
		{
			proc = getProcessor(c);
			if (stack->empty())
			{
				std::cout << "Ҫ����ĺ�׺���ʽ�ƺ����˵�����:(" << std::endl;
				return list;
			}
			std::string  str2 = stack->top();
			stack->pop();
			if (stack->empty())
			{
				std::cout << "Ҫ����ĺ�׺���ʽ�ƺ����˵�����:(" << std::endl;
				return list;
			}
			std::string  str1 = stack->top();
			stack->pop();
			//��������x
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
	//ջ
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
		std::cout << "��׺���ʽ�����ս����Ȼ����һ��������������" << std::endl;
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
	//�ѿո��滻��
	std::string str = replaceWith(input, " ", "");

	//�ֱ�����Ⱥŵ����������
	std::vector<std::string> two= split(str, "=");
	if (two.size() != 2)
	{
		std::cout << "��������ֻ��һ���Ⱥ�" << std::endl;
		return nullptr;
	}
	//��׺���ʽת��׺���ʽ
	std::list<std::string>* reversePolishLeft = convertToReversePolish(two[0]);
	std::list<std::string>* reversePolishRight = convertToReversePolish(two[1]);

	//�����׺���ʽ��ֵ
	std::list<std::string>* valueLeft = calcReversePolish(reversePolishLeft);
	std::list<std::string>* valueRight = calcReversePolish(reversePolishRight);


	//����
	for (std::list<std::string>::iterator it = valueRight->begin(); it != valueRight->end(); ++it) {
		valueLeft->push_back(*it);
	}
	valueLeft->push_back("-");
	std::list<std::string>* afterAll = calcReversePolish(valueLeft);




	//��ӡ
	std::cout << "�Ⱥ�����ĺ�׺���ʽ:" << std::endl;
	for (std::list<std::string>::iterator it = reversePolishLeft->begin(); it != reversePolishLeft->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "�Ⱥ�����ĺ�׺���ʽ:" << std::endl;
	for (std::list<std::string>::iterator it = reversePolishRight->begin(); it != reversePolishRight->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "�Ⱥ�����ĺ�׺���ʽ��ֵ:" << std::endl;
	for (std::list<std::string>::iterator it = valueLeft->begin(); it != valueLeft->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;


	std::cout << "�Ⱥ�����ĺ�׺���ʽ��ֵ:" << std::endl;
	for (std::list<std::string>::iterator it = valueRight->begin(); it != valueRight->end(); ++it) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "���ս���ĺ�׺���ʽ:" << std::endl;
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

//ţ�ٷ��ⷽ��
double solveEquation(std::list<std::string>* equation,double x0) {
	double x = x0;
	int itrCounter = 0;
	//����
	while (true)
	{
		itrCounter++;
		double derivative = calcDerivativeAt(equation, x);
		double value = calcReversePolish(equation, x);
		std::cout <<"��"<<itrCounter<< "�ε���:������" << x << "����б��Ϊ" << derivative << ",ֵΪ" << value << std::endl;
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
//���麯���Ƿ�ͱ����й�ϵ
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








