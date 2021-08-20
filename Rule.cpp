#include "Rule.h"

std::string rule::crossRule(char c1, char c2)
{
	if (c1 == 'i')
	{
		if (c2 == 'j')
			return "+k";
		else if (c2 == 'k')
			return "-j";
	}
	else if (c1 == 'j')
	{
		if (c2 == 'k')
			return "+i";
		else if (c2 == 'i')
			return "-k";
	}
	else if (c1 == 'k')
	{
		if (c2 == 'i')
			return "+j";
		else if (c2 == 'j')
			return "-i";
	}
	return "NULL";
}
Tenzor* rule::cross(struct Tenzor* T1, struct Tenzor* T2)
{
	Tenzor* res = new Tenzor;
	for (int i = 0; i < T1->tenzorIndex.size(); i++)
		for (int j = 0; j < T2->tenzorIndex.size(); j++)
		{
			std::string newIndex = crossRule(T1->tenzorIndex[i][T1->tenzorIndex[i].size() - 1], T2->tenzorIndex[j][0]);
			if (newIndex != "NULL")
			{
				char sign = newIndex[0];
				res->tenzorIndex.push_back(std::string() + T1->tenzorIndex[i].substr(0, T1->rank - 1) + newIndex[1] + T2->tenzorIndex[j].substr(1, T2->rank));
				if (sign == '-')
					res->tenzorValue.push_back(-1 * T1->tenzorValue[i] * T2->tenzorValue[j]);
				else
					res->tenzorValue.push_back(T1->tenzorValue[i] * T2->tenzorValue[j]);
			}
		}
	res->findRowsAndColumns();
	res->simplify();
	return res;
}
Tenzor* rule::crossDot(struct Tenzor* T1, struct Tenzor* T2)
{
	Tenzor* res = new Tenzor;
	for (int i = 0; i < T1->tenzorIndex.size(); i++)
		for (int j = 0; j < T2->tenzorIndex.size(); j++)
		{
			std::string newIndex = crossRule(T1->tenzorIndex[i][T1->tenzorIndex[i].size() - 1], T2->tenzorIndex[j][0]);
			if (newIndex != "NULL")
			{
				if (T1->tenzorIndex[i][T1->rank - 2] == T2->tenzorIndex[j][1])
				{
					char sign = newIndex[0];
					res->tenzorIndex.push_back(std::string() + T1->tenzorIndex[i].substr(0, T1->rank - 2) + newIndex[1] + T2->tenzorIndex[j].substr(2, T2->rank));
					if (sign == '-')
						res->tenzorValue.push_back(-1 * T1->tenzorValue[i] * T2->tenzorValue[j]);
					else
						res->tenzorValue.push_back(T1->tenzorValue[i] * T2->tenzorValue[j]);
				}
			}
		}
	res->findRowsAndColumns();
	res->simplify();
	return res;
}
Tenzor* rule::dotCross(struct Tenzor* T1, struct Tenzor* T2)
{
	Tenzor* res = new Tenzor;
	for (int i = 0; i < T1->tenzorIndex.size(); i++)
		for (int j = 0; j < T2->tenzorIndex.size(); j++)
		{
			if (T1->tenzorIndex[i][T1->rank - 1] == T2->tenzorIndex[j][0])
			{
				std::string newIndex = crossRule(T1->tenzorIndex[i][T1->tenzorIndex[i].size() - 2], T2->tenzorIndex[j][1]);
				if (newIndex != "NULL")
				{
					char sign = newIndex[0];
					res->tenzorIndex.push_back(std::string() + T1->tenzorIndex[i].substr(0, T1->rank - 2) + newIndex[1] + T2->tenzorIndex[j].substr(2, T2->rank));
					if (sign == '-')
						res->tenzorValue.push_back(-1 * T1->tenzorValue[i] * T2->tenzorValue[j]);
					else
						res->tenzorValue.push_back(T1->tenzorValue[i] * T2->tenzorValue[j]);
				}
			}
		}
	res->findRowsAndColumns();
	res->simplify();
	return res;
}
Tenzor* rule::dotDot(struct Tenzor* T1, struct Tenzor* T2)
{
	Tenzor* res = new Tenzor;
	for (int i = 0; i < T1->tenzorIndex.size(); i++)
		for (int j = 0; j < T2->tenzorIndex.size(); j++)
		{
			if (T1->tenzorIndex[i][T1->rank - 1] == T2->tenzorIndex[j][0] && T1->tenzorIndex[i][T1->rank - 2] == T2->tenzorIndex[j][1])
			{
				res->tenzorIndex.push_back(std::string() + T1->tenzorIndex[i].substr(0, T1->rank - 2) + T2->tenzorIndex[j].substr(2, T2->rank));
				res->tenzorValue.push_back(T1->tenzorValue[i] * T2->tenzorValue[j]);
			}
		}
	if (res->tenzorValue.size() == 0) { res->tenzorValue.push_back(0); res->tenzorIndex.push_back(std::string() + " "); }
	res->findRowsAndColumns();
	res->simplify();
	return res;
}
Tenzor* rule::crossCross(struct Tenzor* T1, struct Tenzor* T2)
{
	Tenzor* res = new Tenzor;
	for (int i = 0; i < T1->tenzorIndex.size(); i++)
		for (int j = 0; j < T2->tenzorIndex.size(); j++)
		{
			std::string newIndex = crossRule(T1->tenzorIndex[i][T1->tenzorIndex[i].size() - 1], T2->tenzorIndex[j][0]);
			std::string newIndex2 = crossRule(T1->tenzorIndex[i][T1->tenzorIndex[i].size() - 2], T2->tenzorIndex[j][1]);
			if (newIndex != "NULL" && newIndex2 != "NULL")
			{
				char sign = newIndex[0]; char sign2 = newIndex2[0];
				res->tenzorIndex.push_back(std::string() + T1->tenzorIndex[i].substr(0, T1->rank - 2) + newIndex[1] + newIndex2[1] + T2->tenzorIndex[j].substr(2, T2->rank));
				if ((sign == '-' && sign2 == '+') || (sign == '-' && sign2 == '+'))
					res->tenzorValue.push_back(-1 * T1->tenzorValue[i] * T2->tenzorValue[j]);
				else
					res->tenzorValue.push_back(T1->tenzorValue[i] * T2->tenzorValue[j]);
			}
		}
	res->findRowsAndColumns();
	res->simplify();
	return res;
}