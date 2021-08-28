#include "Tenzor.h"
#include <cassert>

Tenzor::Tenzor() : rows(0), columns(0), rank(0)
{
}
void Tenzor::createTenzor(QString s = "")
{
    clearTenzor();
	if (s != "")
	{
        QString elements = " ()*";
		for (int i = 0; i < elements.size(); i++)
            s.remove(elements[i]);
        checkFormat(s);
		if (s[0] != '-' && s[0] != '+') s = " " + s;
        findDigit(s);
        //findIndex(s);
        findRowsAndColumns();
        simplify();
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
void Tenzor::checkFormat(QString s)
{
    QString const index = "ijk+-.0123456789";
    for(int i=0;i< s.size();i++)
        if(index.indexOf(s[i]) == -1)
           throw "Calculation support only ortogonal vectors";
}
/*int Tenzor::findDigit(QString s)
{
	char const* digit = "01234567890.";
    int n = s.toStdString().find_first_of(digit), m = s.toStdString().find_first_not_of(digit, n);
	if (n == -1) return 0;
	if (m == -1) m = s.size();
	while (n != -1)
	{
        QString newElement = "";
		for (int i = n; i < m; i++) newElement += s[i];
		if (s[n - 1] == '-')
            tenzorValue.push_back(-1 * newElement.toInt());
		else
            tenzorValue.push_back(newElement.toInt());
        s.remove(n - 1, m);
        n = s.toStdString().find_first_of(digit);
        m = s.toStdString().find_first_not_of(digit, n);
	}
	return 0;
}*/
int Tenzor::findDigit(QString s)
{
    char const* digit = "ijk";
    int n = s.toStdString().find_first_of(digit), m = s.toStdString().find_first_not_of(digit);
    if (n == -1) return 0;
    while (n != -1)
    {
        QString newElement = "";
        for (int i = m; i < n; i++) newElement += s[i];
        tenzorValue.push_back(newElement.toDouble());
        s.remove(m, n);
        int l = s.toStdString().find_first_not_of(digit);
        if(l == -1) l = s.size();
        newElement = "";
        for (int i = 0; i < l; i++) newElement += s[i];
        tenzorIndex.push_back(newElement);
        s.remove(0, l);
        n = s.toStdString().find_first_of(digit);
        m = s.toStdString().find_first_not_of(digit);
    }
    return 0;
}
/*int Tenzor::findIndex(QString s)
{
	char const* index = "ijk";
    int n = s.toStdString().find_first_of(index), m = s.toStdString().find_first_not_of(index, n);
	if (n == -1) return 0;
	if (m == -1) m = s.size();
	while (n != -1)
	{
        QString newElement = "";
		for (int i = n; i < m; i++) newElement += s[i];
		tenzorIndex.push_back(newElement);
        s.remove(n - 1, m);
        n = s.toStdString().find_first_of(index);
        m = s.toStdString().find_first_not_of(index, n);
		if (m == -1) m = s.size();
	}
	for(int i=0;i<tenzorIndex.size();i++)
		if (tenzorIndex[i].size() != tenzorIndex[0].size())
			throw "Not correct tenzor index formats";
	return 0;
}*/
QString Tenzor::printTenzorForm()
{
    QString s;
    if (rank == 0)
	{
        s = QString::number(tenzorValue[0]);
        return s;
	}
    s = QString::number(tenzorValue[0]) + tenzorIndex[0];
	for (int i = 1; i < tenzorIndex.size(); i++)
	{
		if (tenzorValue[i] > 0)
            s += " +" + QString::number(tenzorValue[i]) + tenzorIndex[i];
		else if (tenzorValue[i] < 0)
            s += " " + QString::number(tenzorValue[i]) + tenzorIndex[i];
	}
    return s;
}
QString* Tenzor::printMatrixForm()
{
    QString *s;
    s = new QString[3];
    QString halfResult = "";
    if (rank == 3)
		throw "It is impossible to build a 3 dimension matrix";
    if(rank == 1)
    {
        for (int i = 0; i < rows; i++)
            s[i] = QString::number(findElementWithIndexVector(i));
        return s;
    }
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
            halfResult+= QString::number(findElementWithIndex(i, j)) + " ";
        s[i] = halfResult;
        halfResult = "";
	}
    return s;
}
double Tenzor::findElementWithIndexVector(int a)
{
    QString index = ijk[a];
    for (int i = 0; i < tenzorIndex.size(); i++)
        if (tenzorIndex[i] == index)
            return tenzorValue[i];
    return 0;
}
double Tenzor::findElementWithIndex(int a, int b)
{
    QString index = ijk[a] + ijk[b];
	for (int i = 0; i < tenzorIndex.size(); i++)
		if (tenzorIndex[i] == index)
			return tenzorValue[i];
	return 0;
}
void Tenzor::simplify()
{
    for (int i = 0; i < tenzorIndex.size(); i++)
        for (int j = 0; j < tenzorIndex.size(); j++)
            if (i != j && tenzorIndex[i] == tenzorIndex[j] && tenzorValue[i]!=0)
            {
                tenzorValue[i] = tenzorValue[i] + tenzorValue[j];
                if (tenzorValue[i] == 0)
                {
                    tenzorIndex.remove(i);
                    tenzorValue.remove(i);
                }
                tenzorValue[j]=0;
            }
    for(int i=tenzorIndex.size() - 1; i>0;i--)
        if(tenzorValue[i]==0)
        {
            tenzorIndex.remove(i);
            tenzorValue.remove(i);
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
    /*if (rank != obj.rank)
        throw "Unable to do operation for object with different rank";*/
	for (int i = 0;i < tenzorIndex.size();i++)
		for (int j = 0; j < obj.tenzorIndex.size(); j++)
		{
			if (tenzorIndex[i][rank - 1] == obj.tenzorIndex[j][0])
			{
                QString newString = tenzorIndex[i].mid(0,rank - 1) + obj.tenzorIndex[j].mid(1,obj.rank - 1);
                //QString newString = "" + tenzorIndex[i].toStdString().substr(0, rank - 1) + obj.tenzorIndex[j].toStdString().substr(1,obj.rank);
                res.tenzorIndex.push_back(newString);
				res.tenzorValue.push_back(tenzorValue[i] * obj.tenzorValue[j]);
			}
		}
	res.findRowsAndColumns();
	res.simplify();
	return res;
}
