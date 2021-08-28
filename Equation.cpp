#include "Equation.h"

equation::equation()
{
}
void equation::createEquation(QString s = "")
{
    s.remove(' ');
    analyzeEquation(s);
}
void equation::analyzeEquation(QString equation_name)
{
    QString check = "";
    int counter = 0, n , j = 0;
    bool flag = true;
    for (int i = 0; i < equation_name.size();i++)
	{
		check += equation_name[i];
        while(flag == true)
        {
            n = check.indexOf(possible_operations[j]);
            if(n!= -1 && ((equation_name[i + 1] != '*' && equation_name[i + 1] != 'x')||(equation_name[i]==')' || equation_name[i] =='(' )))
            {
                priority.push_back(standart_priority[j]);
                op_name.push_back(check.mid(n, check.size() - n));
                if (op_name[op_name.size() - 1] == "(") counter++;
                if (n != 0) tenzor_name.push_back(check.mid(0, n));
                check = "";
                flag=false;
            }
            if( j == possible_operations.size() - 1) flag = false;
            j++;
        }
        j=0;
        flag = true;
	}
    if(check != "") tenzor_name.push_back(check);
    for (int i = 0; i < counter;i++) deleteBrackets();
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
    if (last - first == 1) { op_name.remove(first , 1); op_name.remove(last - 1 , 1); return 0; }
	for (int i = first + 1; i < last; i++)
		priority[i] += 2;
    op_name.remove(first, 1);
    op_name.remove(last - 1, 1);
    priority.remove(first, 1);
    priority.remove(last - 1, 1);
    return 0;
}
int equation::findFirstOf(QString s, QVector<QString> name)
{
	for (int i = 0; i < name.size();i++)
		if (name[i] == s)
			return i;
	return -1;
}
int equation::findLastOf(QString s, QVector<QString> name)
{
	int counter = -1;
	for (int i = 0; i < name.size();i++)
		if (name[i] == s)
			counter = i;
	return counter;
}
void equation::createTenzorMap(QString name, struct Tenzor *T)
{
    tenzorMap[name] = T;
}
Tenzor *equation::operation(QString operand1, QString op_name, QString operand2)
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
        QString s = tenzor_name[opNumber] + op_name[opNumber] + tenzor_name[opNumber + 1];
		tenzorMap[s] = operation(tenzor_name[opNumber], op_name[opNumber], tenzor_name[opNumber + 1]);
		tenzor_name[opNumber] = s;
        tenzor_name.remove(opNumber + 1,1);
        op_name.remove(opNumber, 1);
        priority.remove(opNumber, 1);
		opNumber = findOperation(number);
	}
    return 0;
}
int equation::solveEquation()
{
    if(op_name.size() == 0) return 0;
    int max = *std::max_element(priority.begin(),priority.end());
    for(int i = max; i>=0 ; i--)
        solvePriority(i);
}
QString equation::printResult()
{
    if(!tenzorMap.contains(tenzor_name[0])) throw "Impossible to build the solution.";
    return tenzorMap[tenzor_name[0]]->printTenzorForm();
}
QString* equation::printResultMatrixForm()
{
    return tenzorMap[tenzor_name[0]]->printMatrixForm();
}
void equation::clearEquation()
{
    priority.clear();
    tenzor_name.clear();
    op_name.clear();
    tenzorMap.clear();
}
