#pragma once
#include "AbstractGenerator2.h"
class ConcreteGenerator2 :
    public AbstractGenerator2
{
public:
    unique_ptr<Responder[]> UsefulFunction2(Questions questions, int n) const override;
};

