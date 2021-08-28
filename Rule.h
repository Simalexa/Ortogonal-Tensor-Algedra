#ifndef RULE_H
#define RULE_H
#include <QString>
#include <QDebug>

class rule
{
public:
    struct Tenzor* cross(struct Tenzor* T1, struct Tenzor* T2);
    struct Tenzor* crossDot(struct Tenzor* T1, struct Tenzor* T2);
    struct Tenzor* dotCross(struct Tenzor* T1, struct Tenzor* T2);
    struct Tenzor* dotDot(struct Tenzor* T1, struct Tenzor* T2);
    struct Tenzor* crossCross(struct Tenzor* T1, struct Tenzor* T2);
protected:
private:
    QString crossRule(QChar c1, QChar c2);
};
#endif

