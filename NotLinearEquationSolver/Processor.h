#pragma once
class Processor
{
	public:
		virtual  int getPriority();
		/**
		*	number1�Ǳ���������number2�ǲ�����,����1+2,1�Ǳ���������2�ǲ����� 
		*/
		virtual double apply(double number1,double number2);

		virtual char getChar();
};

