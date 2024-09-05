#include "ConcreteGenerator2.h"

unique_ptr<Responder[]> ConcreteGenerator2::UsefulFunction2(Questions questions, int n) const
{
    unique_ptr<Responder[]> r = make_unique<Responder[]>(n);
    for (int i = 0; i < n; i++)
        r[i].SetCount(questions.Count());

    for (int i = 0; i < n; i++)
        r[i].TakeRandomTheSurvey(questions);
 
    return r;
}
