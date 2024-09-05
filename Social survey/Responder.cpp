#include "Responder.h"

Responder::Responder()
{
	this->count = 0;
	responds = make_unique<Respond[]>(0);
}

Responder::Responder(int count)
{
	this->count = count;
	responds = make_unique<Respond[]>(count);
}

Responder::~Responder()
{
}

Respond Responder::Get(int index)
{
	if (index < 0 || index >= count)
		throw "������ ��� ���������!\n";

	return responds[index];
}

void Responder::SetCount(int count)
{
	this->count = count;
	responds = make_unique<Respond[]>(count);
}

void Responder::Set(int index, Respond& d)
{
	if (index < 0 || index >= count)
		throw "������ ��� ���������!\n";

	responds[index] = d;
}

void Responder::TakeTheSurvey(Questions& questions)
{
	if (questions.Count() == 0) {
		throw "����������� �������!\n";
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < count; i++) {
		questions.Print(i);
		cout << "��� �����: " << endl;

		getline(cin, responds[i].respond);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		responds[i].questionNumber = i;

		int num = static_cast<int>(responds[i].respond[0]) - '0';
		if (num < 1 || num > questions.GetCountAnswers(i)) {
			cout << "�������� ����, ���������� �����!" << endl;
			system("pause");
			i--;
		}

		system("cls");
	}
}

void Responder::TakeRandomTheSurvey(Questions& questions)
{
	if (questions.Count() == 0) {
		throw "����������� �������!\n";
	}

	for (int i = 0; i < count; i++) {
		responds[i].questionNumber = i;
		int num = 1 + rand() % questions.GetCountAnswers(i);
		responds[i].respond = to_string(num);
	}
}

void Responder::Print(Respond& d)
{
	cout << "�����: " << d.respond << endl;
}

void Responder::Print()
{
	if (count == 0) {
		throw "������ �����������!\n";
	}

	for (int i = 0; i < count; i++) {
		Print(responds[i]);
		cout << endl;
	}
}

void Responder::Print(Questions& questions)
{
	if (count == 0) {
		throw "������ �����������!\n";
	}

	for (int i = 0; i < count; i++) {
		questions.Print(responds[i].questionNumber);
		Print(responds[i]);
		cout << endl;
	}
}

Responder& Responder::operator=(const Responder& d)
{
	count = d.count;
	responds = make_unique<Respond[]>(count);
	for(int i = 0; i<count; i++)
		responds[i] = d.responds[i];

	return *this;
}
