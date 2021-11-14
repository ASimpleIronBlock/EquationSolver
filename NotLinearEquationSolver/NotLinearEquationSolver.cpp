// NotLinearEquationSolver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "PrefixProcessor.h"
#include "ProcessorAdd.h"
int main()
{
	std::cout << "请输入要解的方程"<<std::endl;
	std::cout << "^为次方符号"<<std::endl;
	std::string input;
	std::cin >> input;
	std::cout << "输入的方程为:" << input;
	Processor* add = new ProcessorAdd();
	convertToReversePolish(input);


	delete add;
	
}


