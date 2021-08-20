#ifndef RULE_H
#define RULE_H
#include <string>
#include "Tenzor.h"
class rule
{
public:
	Tenzor* cross(struct Tenzor* T1, struct Tenzor* T2);
	Tenzor* crossDot(struct Tenzor* T1, struct Tenzor* T2);
	Tenzor* dotCross(struct Tenzor* T1, struct Tenzor* T2);
	Tenzor* dotDot(struct Tenzor* T1, struct Tenzor* T2);
	Tenzor* crossCross(struct Tenzor* T1, struct Tenzor* T2);
protected:
private:
	std::string crossRule(char c1, char c2);
};
#endif

