// NotLinearEquationSolver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "NotLinearEquationSolver.h"
#include <list>
#include "EquationHandler.h"
int main()
{


	init();
	std::cout << "请输入要解的方程"<<std::endl;
	//std::cout << "^为次方符号,1s为sin,1c为cos,1t为tan"<<std::endl;
	std::cout << "不要输入小数和负数"<<std::endl;
	std::string input;
	std::cin >> input;
	std::cout << "输入的方程为:" << input<<std::endl;

	std::list<std::string>* equation = phaseEquation(input);
	if (isConstant(equation))
	{
		std::cout << "方程中的x约掉了，这个方程与x无关" << std::endl;
	}
	else {
		while (true)
		{
			std::cout << "请输入方程的一个近似解" << std::endl;
			std::string x0;
			std::cin >> x0;

			double result = solveEquation(equation, std::atof(x0.c_str()));

			if (result == INFINITY)
			{
				std::cout << "方程的一个解离输入的x0有点问题或不在定义域内，请重新输入" << std::endl;
			}
			else {
				std::cout << "方程的一个近似解是" << result << std::endl;
				break;
			}
		}
	}

	

	destroy();
	system("pause");

	
	
	
}


