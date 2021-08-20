#ifndef EQUATION_H
#define EQUATION_H
#include "Tenzor.h"
#include "rule.h"
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

class equation : rule
{
public:
	equation(std::string s);
	void analyzeEquation(std::string equation_name);
	void createTenzorMap(std::string name, struct Tenzor *T);
	void solveEquation();
private:
	int findOperation(int number);
	int findLastOf(std::string s, std::vector<std::string> name);
	int findFirstOf(std::string s, std::vector<std::string> name);
	int solvePriority(int number);
	Tenzor *operation(std::string operand1, std::string op_name, std::string operand2);
	int deleteBrackets();
protected:
	const std::vector<std::string> possible_operations = { "(" , ")", "+" , "-" , "*x" , "x*" , "**" , "nabla" , "xx", "*" , "x" };
	const std::vector<int> standart_priority = {0,0,0,0,1,1,1,1,1,1,1};
	std::vector<int> priority;
	std::vector<std::string> tenzor_name;
	std::vector<std::string> op_name;
	std::map<std::string, Tenzor*> tenzorMap;
};
#endif