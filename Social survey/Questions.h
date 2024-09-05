#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;	

// ��������� ������
struct Question
{
	string question;
	int numberOfAnswers;
	string* answers;

	Question() { question = ""; numberOfAnswers = 0;  answers = new string[0]; }
	Question(string question, int numberOfAnswers, string* answers) :
		question(question), numberOfAnswers(numberOfAnswers), answers(answers){}
};

// ����� ���� ��������
class Questions
{
	// ���� ������
private:	// �������� �����
	string header;
	unique_ptr<Question[]> data;
	int count;

	// ������ ������
public:		// �������� �����
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

