#ifndef TENZOR_H
#define TENZOR_H
#include <iostream>
#include <string>
#include <map>
#include <QVector>
#include <QString>
#include <QDebug>
#include "Equation.h"

struct Tenzor
{
	Tenzor();
    QString printTenzorForm();
    QString* printMatrixForm();
    void createTenzor(QString s);
    void simplify();
    void clearTenzor();
    Tenzor operator+(Tenzor obj);
    Tenzor operator*(Tenzor obj);
    friend class rule;
    friend class equation;
private:
    void checkFormat(QString s);
    int findDigit(QString s);
    int findIndex(QString s);
    int findRowsAndColumns();
    int findNumberOf(int a);
    double findElementWithIndex(int a, int b);
    double findElementWithIndexVector(int a);
    QMap <int, QString> ijk = { {0,"i"},{1,"j"},{2,"k"} };
protected:
	int rows = 0;
	int columns = 0;
	int rank = 0;
    QVector<QString> tenzorIndex;
    QVector<double> tenzorValue;
};

#endif
