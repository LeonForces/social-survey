#include "Questions.h"

Questions::Questions()
{
	data = make_unique<Question[]>(0);
	count = 0;
}

Questions::Questions(const Questions& q)
{
	header = q.header;
	count = q.count;
	data = make_unique<Question[]>(count);
	for (int i = 0; i < count; i++) {
		data[i] = q.data[i];
	}
}

Questions::~Questions()
{
}

bool Questions::Load(string& questFile)
{
	ifstream load(questFile);

	if (!load)
		throw "Ошибка открытия файла \"Resources\\форма.txt\"\n";
		
	int numAnswer = 0;
	int i = 0;
	int idLine = -1;
	string line;

	while (getline(load, line)) {

		if (idLine == -1) {
			count = atoi(line.c_str());
			data = make_unique<Question[]>(count);
		}
		else if (idLine == 0)
			header = line;
		else if (idLine == 1) {
			data[i].question = line;
		}
		else if (idLine == 2) {
			data[i].numberOfAnswers = atoi(line.c_str());
			data[i].answers = new string[data[i].numberOfAnswers];
		}
		else if (idLine == 3 && numAnswer < data[i].numberOfAnswers) {
			idLine = 2;
			data[i].answers[numAnswer++] = line;
		}
		else {
			numAnswer = 0;
			idLine = 1;
			data[++i].question = line;
		}

		idLine++;
	}

	load.close();
	return true;
}

void Questions::Print(Question& q)
{
	cout << q.question << endl;
	for(int i = 0; i<q.numberOfAnswers; i++)
		cout << q.answers[i] << endl;
}

void Questions::Print(int i)
{
	Print(data[i]);
}

void Questions::Print()
{
	if (count == 0) {
		throw "Вопросы отсутствуют!\n";
	}

	cout << header << endl << endl;
	for (int i = 0; i < count; i++) {
		Print(data[i]);
		cout << endl;
	}
}

int Questions::GetCountAnswers(int index)
{
	if (index < 0 || index >= count)
		throw "Индекс вне диапазона!\n";

	return data[index].numberOfAnswers;
}

Questions& Questions::operator=(const Questions& q)
{
	header = q.header;
	count = q.count;
	data = make_unique<Question[]>(count);
	for (int i = 0; i < count; i++) {
		data[i] = q.data[i];
	}
	return*this;
}
