#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;	

// Структура опроса
struct Question
{
	string question;
	int numberOfAnswers;
	string* answers;

	Question() { question = ""; numberOfAnswers = 0;  answers = new string[0]; }
	Question(string question, int numberOfAnswers, string* answers) :
		question(question), numberOfAnswers(numberOfAnswers), answers(answers){}
};

// Набор всех вопросов
class Questions
{
	// Поля класса
private:	// закрытая часть
	string header;
	unique_ptr<Question[]> data;
	int count;

	// Методы класса
public:		// открытая часть
	Questions();
	Questions(const Questions&);
	~Questions();

	bool Load(string& questFile);
	void Print(Question&);
	void Print(int);
	void Print();

	string GetHeader() { return header; }
	Question* GetQuestions() { return data.get(); }
	int GetCountAnswers(int index);
	int Count() { return count; }

	Questions& operator=(const Questions& q);
};

