#pragma once

#include "Questions.h"

// Структура ответа
struct Respond
{
	int questionNumber = 0;
	string respond;
};

// Ответник на вопросы одного объекта
class Responder
{
private:
	//Respond* responds;
	unique_ptr<Respond[]> responds;
	int count;

public:
	Responder();
	Responder(int count);
	~Responder();

	Respond Get(int index);
	void SetCount(int count);
	void Set(int index, Respond& d);
	void TakeTheSurvey(Questions& questions);
	void TakeRandomTheSurvey(Questions& questions);
	void Print(Respond&);
	void Print();
	void Print(Questions& questions);

	Responder& operator=(const Responder& d);
};

