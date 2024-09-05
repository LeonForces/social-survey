#pragma once
#include "AbstractGenerator1.h"
class ConcreteGenerator1 :
    public AbstractGenerator1
{
public:
    unique_ptr<Responder> UsefulFunction1(Questions questions) const override;
};

