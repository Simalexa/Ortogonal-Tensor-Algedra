#ifndef EQUATION_H
#define EQUATION_H
#include "Tenzor.h"
#include "Rule.h"
#include <string>
#include <map>
#include <algorithm>
#include <iterator>


class equation : public rule
{
public:
    equation();
    QString printResult();
    QString* printResultMatrixForm();
    void createEquation(QString s);
    void analyzeEquation(QString equation_name);
    void createTenzorMap(QString name, struct Tenzor *T);
    int solveEquation();
    void clearEquation();
private:
    int findOperation(int number);
    int findLastOf(QString s, QVector<QString> name);
    int findFirstOf(QString s, QVector<QString> name);
    int solvePriority(int number);
    Tenzor *operation(QString operand1, QString op_name, QString operand2);
    int deleteBrackets();
protected:
    const QVector<QString> possible_operations = { "(" , ")", "+" , "-" , "*x" , "x*" , "**" , "nabla" , "xx", "*" , "x" };
    const QVector<int> standart_priority = {0,0,0,0,1,1,1,1,1,1,1};
    QVector<int> priority;
    QVector<QString> tenzor_name;
    QVector<QString> op_name;
    QMap<QString, struct Tenzor*> tenzorMap;
};
#endif
