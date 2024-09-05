#pragma once
#include "ConcreteGenerator1.h"
#include "ConcreteGenerator2.h"
class AbstractFactory
{
public:
	virtual unique_ptr<AbstractGenerator1> CreateGenerator1() const = 0;
	virtual unique_ptr<AbstractGenerator2> CreateGenerator2() const = 0;
	virtual ~AbstractFactory() {}
};

