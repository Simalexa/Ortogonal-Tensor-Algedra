#include "Tenzor.h"
#include <cassert>

Tenzor::Tenzor() : rows(0), columns(0), rank(0)
{
}
void Tenzor::createTenzor(std::string s = "")
{
	clearTenzor();
	if (s != "")
	{
		std::string elements = " ()*";
		for (int i = 0; i < elements.size(); i++)
			s.erase(remove(s.begin(), s.end(), elements[i]), s.end());
		checkFormat(s);
		if (s[0] != '-' && s[0] != '+') s = " " + s;
		findDigit(s);
		findIndex(s);
		findRowsAndColumns();
	}
}
void Tenzor::clearTenzor()
{
	rows = 0;
	columns = 0;
	rank = 0;
	tenzorIndex.clear();
	tenzorValue.clear();
}
int Tenzor::findRowsAndColumns()
{
	if (tenzorIndex.size() == 0 || tenzorIndex[0] == "")
	{
		rank = 0;
		rows = 0;
		columns = 0;
		return 0;
	}
	rank = tenzorIndex[0].size();
	if (rank == 1)
	{
		columns = 1;
		rows = 3;
		return 0;
	}
	rows = findNumberOf(0);
	columns = findNumberOf(1);
	return 0;
}
int Tenzor::findNumberOf(int a)
{
	int counter = 0;
	while (counter < tenzorIndex.size())
	{
		if (tenzorIndex[counter][a] == 'k')
			return 3;
		counter++;
	}
	counter = 0;
	while ( counter < tenzorIndex.size())
	{
		if (tenzorIndex[counter][a] == 'j')
			return 2;
		counter++;
	}
	return 1;
}
void Tenzor::checkFormat(std::string s)
{
	char const* index = "ijk+-.0123456789";
	if(s.find_first_not_of(index) >= 0 && s.find_first_not_of(index) < s.size())
		throw "Calculation support only ortogonal vectors";
}
int Tenzor::findDigit(std::string s)
{
	char const* digit = "01234567890.";
	int n = s.find_first_of(digit), m = s.find_first_not_of(digit, n);
	if (n == -1) return 0;
	if (m == -1) m = s.size();
	while (n != -1)
	{
		std::string newElement = "";
		for (int i = n; i < m; i++) newElement += s[i];
		if (s[n - 1] == '-')
			tenzorValue.push_back(-1 * atof(newElement.c_str()));
		else
			tenzorValue.push_back(atof(newElement.c_str()));
		s.erase(s.begin() + n - 1, s.begin() + m);
		n = s.find_first_of(digit);
		m = s.find_first_not_of(digit, n);
	}
	return 0;
}
int Tenzor::findIndex(std::string s)
{
	char const* index = "ijk";
	int n = s.find_first_of(index), m = s.find_first_not_of(index, n);
	if (n == -1) return 0;
	if (m == -1) m = s.size();
	while (n != -1)
	{
		std::string newElement = "";
		for (int i = n; i < m; i++) newElement += s[i];
		tenzorIndex.push_back(newElement);
		s.erase(s.begin() + n - 1, s.begin() + m);
		n = s.find_first_of(index);
		m = s.find_first_not_of(index, n);
		if (m == -1) m = s.size();
	}
	for(int i=0;i<tenzorIndex.size();i++)
		if (tenzorIndex[i].size() != tenzorIndex[0].size())
			throw "Not correct tenzor index formats";
	return 0;
}
int Tenzor::printTenzorForm()
{
	if (rank == 0)
	{
		std::cout << tenzorValue[0];
		return 0;
	}
	std::cout << tenzorValue[0] << tenzorIndex[0];
	for (int i = 1; i < tenzorIndex.size(); i++)
	{
		if (tenzorValue[i] > 0)
			std::cout << " +" << tenzorValue[i] << tenzorIndex[i];
		else if (tenzorValue[i] < 0)
			std::cout << " " << tenzorValue[i] << tenzorIndex[i];
	}
	std::cout << std::endl;
	return 0;
}
int Tenzor::printMatrixForm()
{
	if (rank == 3)
		throw "It is impossible to build a 3 dimension matrix";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			std::cout << findElementWithIndex(i, j) << " ";
		std::cout << std::endl;
	}
	return 0;
}
double Tenzor::findElementWithIndex(int a, int b)
{
	std::string index = std::string() + ijk[a] + ijk[b];
	for (int i = 0; i < tenzorIndex.size(); i++)
		if (tenzorIndex[i] == index)
			return tenzorValue[i];
	return 0;
}
void Tenzor::simplify()
{
	for (int i = 0; i < tenzorIndex.size(); i++)
	{
		for (int j = 0; j < tenzorIndex.size(); j++)
		{
			if (i != j && tenzorIndex[i] == tenzorIndex[j])
			{
				tenzorValue[i] = tenzorValue[i] + tenzorValue[j];
				if (tenzorValue[i] == 0)
				{
					tenzorIndex.erase(tenzorIndex.begin() + i);
					tenzorValue.erase(tenzorValue.begin() + i);
				}
				tenzorIndex.erase(tenzorIndex.begin() + j);
				tenzorValue.erase(tenzorValue.begin() + j);
			}
		}
	}
}
Tenzor Tenzor::operator+(Tenzor obj)
{
	Tenzor res;
	if (rank != obj.rank)
		throw "Unable to do operation for object with different rank";
	for (int i = 0;i < tenzorIndex.size();i++)
	{
		res.tenzorIndex.push_back(tenzorIndex[i]);
		res.tenzorValue.push_back(tenzorValue[i]);
	}
	for (int j = 0; j < obj.tenzorIndex.size() ; j++)
	{
		res.tenzorIndex.push_back(obj.tenzorIndex[j]);
		res.tenzorValue.push_back(obj.tenzorValue[j]);
	}
	res.findRowsAndColumns();
	res.simplify();
	return res;
}
Tenzor Tenzor::operator*(Tenzor obj)
{
	Tenzor res;
	if (rank != obj.rank)
		throw "Unable to do operation for object with different rank";
	for (int i = 0;i < tenzorIndex.size();i++)
		for (int j = 0; j < obj.tenzorIndex.size(); j++)
		{
			if (tenzorIndex[i][rank - 1] == obj.tenzorIndex[j][0])
			{
				res.tenzorIndex.push_back(std::string() + tenzorIndex[i].substr(0, rank - 1) + obj.tenzorIndex[j].substr(1,obj.rank));
				res.tenzorValue.push_back(tenzorValue[i] * obj.tenzorValue[j]);
			}
		}
	res.findRowsAndColumns();
	res.simplify();
	return res;
}