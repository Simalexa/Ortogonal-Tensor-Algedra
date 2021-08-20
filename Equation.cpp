#include "Equation.h"

equation::equation(std::string s = "")
{
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	analyzeEquation(s);
}

void equation::analyzeEquation(std::string equation_name)
{
	std::string check = "";
	int counter = 0;
	int n=-1, k = 0;
	for (int i = 0; i < equation_name.size();i++)
	{
		check += equation_name[i];
		if ((std::any_of(possible_operations.begin(), possible_operations.end(),
			[&check](const auto& s) { return check.find(s) != std::string::npos; }) == true && equation_name[i + 1] != '*' && equation_name[i + 1] != 'x') || equation_name[i] == ')' || equation_name[i] == '(')
		{
			while (n == -1)
			{
				if (check.find(possible_operations[k]) != std::string::npos)
					n = check.find(possible_operations[k]);
				k++;
			}
			priority.push_back(standart_priority[k - 1]);
			op_name.push_back(std::string() + check.substr(n, std::string::npos));
			if (op_name[op_name.size() - 1] == "(") counter++;
			if (n!= 0) tenzor_name.push_back(std::string() + check.substr(0, n));
			n = -1; k = 0;
			check = "";
		}
	}
	if(check != "") tenzor_name.push_back(std::string() + check);
	for (int i = 0; i < counter;i++) deleteBrackets();
	//for (int i = 0;i < tenzor_name.size();i++) std::cout << tenzor_name[i] << "_";
	//for (int i = 0;i < op_name.size();i++) std::cout << op_name[i] << "_";
	//for (int i = 0;i < op_name.size();i++) std::cout << priority[i] << "_";
}
int equation::deleteBrackets()
{
	int first = findLastOf("(", op_name);
	int last = findFirstOf(")", op_name);
	if ((first == -1 && last != -1) || (first != -1 && last == -1))
		throw "Not enough brackets";
	if (first > last)
		throw "Problem in order of brackets";
	if (first == -1 && last == -1)
		return 0;
	if (last - first == 1) { op_name.erase(op_name.begin() + first); op_name.erase(op_name.begin() + last - 1); return 0; }
	for (int i = first + 1; i < last; i++)
		priority[i] += 2;
	op_name.erase(op_name.begin() + first);
	op_name.erase(op_name.begin() + last - 1);
	priority.erase(priority.begin() + first); 
	priority.erase(priority.begin() + last - 1);
}
int equation::findFirstOf(std::string s, std::vector<std::string> name)
{
	for (int i = 0; i < name.size();i++)
		if (name[i] == s)
			return i;
	return -1;
}
int equation::findLastOf(std::string s, std::vector<std::string> name)
{
	int counter = -1;
	for (int i = 0; i < name.size();i++)
		if (name[i] == s)
			counter = i;
	return counter;
}
void equation::createTenzorMap(std::string name, struct Tenzor *T)
{
	tenzorMap[name] = T;
}
Tenzor *equation::operation(std::string operand1, std::string op_name, std::string operand2)
{
	Tenzor *res;
	if (tenzorMap.find(operand1) == tenzorMap.end() || tenzorMap.find(operand2) == tenzorMap.end())
		throw "One of the tenzor is not defined";
	res = tenzorMap[operand1];
	if (op_name == "+")
		*res = *tenzorMap[operand1] + *tenzorMap[operand2];
	if (op_name == "*")
		*res = *tenzorMap[operand1] * *tenzorMap[operand2];
	if (op_name == "x")
		res = cross(tenzorMap[operand1], tenzorMap[operand2]);
	if (op_name == "x*")
		res = crossDot(tenzorMap[operand1], tenzorMap[operand2]);
	if (op_name == "*x")
		res = dotCross(tenzorMap[operand1], tenzorMap[operand2]);
	if (op_name == "**")
		res = dotDot(tenzorMap[operand1], tenzorMap[operand2]);
	if (op_name == "xx")
		res = crossCross(tenzorMap[operand1], tenzorMap[operand2]);
	return res;
}
int equation::findOperation(int number)
{
	int counter=0;
	while(counter < op_name.size())
	{
		if (priority[counter] == number)
			return counter;
		counter++;
	}
	return -1;
}
int equation::solvePriority(int number)
{
	int opNumber = findOperation(number);
	if (opNumber == -1) return 0;
	while (opNumber != -1)
	{
		std::string s = tenzor_name[opNumber] + op_name[opNumber] + tenzor_name[opNumber + 1];
		tenzorMap[s] = operation(tenzor_name[opNumber], op_name[opNumber], tenzor_name[opNumber + 1]);
		tenzor_name[opNumber] = s;
		tenzor_name.erase(tenzor_name.begin() + opNumber + 1);
		op_name.erase(op_name.begin() + opNumber);
		priority.erase(priority.begin() + opNumber);
		opNumber = findOperation(number);
	}
}
void equation::solveEquation()
{
	int max = *std::max_element(priority.begin(),priority.end());
	for(int i = max; i>=0 ; i--)
		solvePriority(i);
	tenzorMap[tenzor_name[0]]->printTenzorForm();
}