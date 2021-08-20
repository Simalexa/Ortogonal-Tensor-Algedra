#ifndef TENZOR_H
#define TENZOR_H
#include <vector>
#include <iostream>
#include <string>
#include <map>
//#include "Equation.h"

struct Tenzor
{
	Tenzor();
	int printTenzorForm();
	int printMatrixForm();
	void createTenzor(std::string s);
	void simplify();
	void clearTenzor();
	Tenzor operator+(Tenzor obj);
	Tenzor operator*(Tenzor obj);
	friend class rule;
	friend class equation;
private:
	void checkFormat(std::string s);
	int findDigit(std::string s);
	int findIndex(std::string s);
	int findRowsAndColumns();
	int findNumberOf(int a);
	double findElementWithIndex(int a, int b);
	std::map <int, char> ijk = { {0,'i'},{1,'j'},{2,'k'} };
protected:
	int rows = 0;
	int columns = 0;
	int rank = 0;
	std::vector<std::string> tenzorIndex;
	std::vector<double> tenzorValue;
};

#endif