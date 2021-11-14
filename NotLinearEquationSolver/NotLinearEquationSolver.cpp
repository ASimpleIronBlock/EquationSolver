﻿// NotLinearEquationSolver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "PrefixProcessor.h"
#include "ProcessorAdd.h"
#include "NotLinearEquationSolver.h"
#include "ProcessorSubtract.h"
#include "ProcessorMutilply.h"
#include "ProcessorDivide.h"
int main()
{
	std::cout << "请输入要解的方程"<<std::endl;
	std::cout << "^为次方符号"<<std::endl;
	std::string input;
	std::cin >> input;
	std::cout << "输入的方程为:" << input;
	Processor* add = new ProcessorAdd();
	Processor* sub = new ProcessorSubtract();
	Processor* multi = new ProcessorMutilply();
	Processor* divide = new ProcessorDivide();
	registerProcessor(*add);
	std::list<std::string>* result = convertToReversePolish(input);

	std::cout << std::endl;
	for (std::list<std::string>::iterator it = result->begin(); it != result->end(); ++it) {
		std::cout << *it;
	}


	delete add;
	
}


