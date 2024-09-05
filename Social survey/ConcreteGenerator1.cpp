#include "ConcreteGenerator1.h"

unique_ptr<Responder> ConcreteGenerator1::UsefulFunction1(Questions questions) const
{
    unique_ptr<Responder> r = make_unique<Responder>();
    r->SetCount(questions.Count());
    r->TakeRandomTheSurvey(questions);
    return r;
}
