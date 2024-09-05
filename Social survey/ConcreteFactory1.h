#pragma once
#include "AbstractFactory.h"
class ConcreteFactory1 :
    public AbstractFactory
{
public:
    unique_ptr<AbstractGenerator1> CreateGenerator1() const override {
        return make_unique<ConcreteGenerator1>();
    }
    unique_ptr<AbstractGenerator2> CreateGenerator2() const override {
        return make_unique<ConcreteGenerator2>();
    }
};

