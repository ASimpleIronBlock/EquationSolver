#pragma once
class Processor
{
	public:
		virtual  int getPriority();
		/**
		*	number1是被操作数，number2是操作数,比如1+2,1是被操作数，2是操作数 
		*/
		virtual double apply(double number1,double number2);

		virtual char getChar();
};

