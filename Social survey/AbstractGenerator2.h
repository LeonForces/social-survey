#pragma once

#include "Responder.h"

class AbstractGenerator2
{
public:
	virtual ~AbstractGenerator2() {};
	virtual unique_ptr<Responder[]> UsefulFunction2(Questions questions, int n) const = 0;
};

