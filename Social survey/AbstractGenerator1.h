#pragma once

#include "Responder.h"

class AbstractGenerator1
{
public:
	virtual ~AbstractGenerator1() {};
	virtual unique_ptr<Responder> UsefulFunction1(Questions questions) const = 0;
};

