#include "Database.h"

Database::Database(string& pathLoadFile)
{
	questions.Load(pathLoadFile);

	if (questions.Count() == 0) {
		throw" ������� �����������!\n";
	}

	count = 0;
	//data = new Responder[0];
	data = make_unique<Responder[]>(0);
}

Database::~Database()
{
}

void Database::Menu(int& act)
{
	cout << "��������: " << endl
		<< "0 - �����" << endl
		<< "================================" << endl
		<< "1 - ������ �����" << endl
		<< "2 - ������� �����" << endl
		<< "================================" << endl
		<< "3 - �������� ����������� �������" << endl
		<< "4 - �������� ��������" << endl
		<< "================================" << endl
		<< "5 - ��������� ���������� �������" << endl
		<< "6 - ��������� ���������� �������" << endl
		<< "================================" << endl
		<< "7 - ����� �� ����������� �������" << endl
		<< "8 - ���������� ���������� �������� ����������� �������" << endl
		<< "9 - ���������� ������������� �������� ����������� �������" << endl
		<< "================================" << endl
		<< "10 - ������������� ���� ��������� ������" << endl
		<< "11 - ������������� ��������� ����������� ������" << endl
		<< "��� �����: ";
	cin >> act;

	system("cls");
}

void Database::Copy(Responder* from, Responder* to, int n, int excl)
{
	int q = 0;
	for (int i = 0; i < n; i++) {
		if (i != excl) {
			to[q++] = from[i];
		}
	}
}

void Database::Add(Responder& d)
{
	if (count == 0) {
		count++;
		data = make_unique<Responder[]>(count);
	}
	else {
		// ��������� ������ �� ��������� ������
		unique_ptr<Responder[]> buf = make_unique<Responder[]>(count);
		Copy(data.get(), buf.get(), count, -1);

		// �������� ����� ������
		//delete[] data;
		count++;
		data = make_unique<Responder[]>(count);

		// ������� ������
		Copy(buf.get(), data.get(), count - 1, -1);
	}
	data[count - 1] = d;
}

void Database::TakeTheSurvey()
{
	// TODO: ?!
	try {
		Responder d(questions.Count());
		d.TakeTheSurvey(questions);
		Add(d);
	}
	catch (const char* message) {
		throw message;
	}	
}

void Database::DeleteTheSurvey()
{
	if (count == 0) {
		cout << "������ �����!" << endl;
		return;
	}

	int index = 0;
	cout << "0 - �����\n";
	cout << "�������� ������ ��������� (�� 1 �� " << count << "): ";
	cin >> index;
	system("cls");

	if (index == 0)
		return;

	index--;
	if (index < 0 || index >= count) {
		cout << "������ ��� ���������!" << endl;
		return;
	}

	// ��������� ������ �� ��������� ������
	// std::unique_ptr
	auto buf = make_unique<Responder[]>(count);
	Copy(data.get(), buf.get(), count, -1);

	// �������� ����� ������
	//delete[] data;
	count--;
	data = make_unique<Responder[]>(count);

	// ������� ������
	Copy(buf.get(), data.get(), count + 1, index);

	cout << "������ �������!" << endl;
}

void Database::Search()
{
	if (count == 0) {
		cout << "������ �����!" << endl;
		return;
	}

	// ������ �������� ������
	int countAnswers = 0;
	cout << "������� ���������� ������������ �������: ";
	cin >> countAnswers;
	system("cls");

	if (countAnswers > questions.Count() || countAnswers <= 0) {
		cout << "������� ������������ ��������!" << endl;
		return;
	}

	auto numQuestions = make_unique<int[]>(countAnswers);
	auto numAnswers = make_unique<int[]>(countAnswers);

	cout << "������� ������ ������������ ������� (�� 1 �� " << questions.Count() <<"): \n";
	for (int i = 0; i < countAnswers; i++) {
		cin >> numQuestions[i];

		if (numQuestions[i] <= 0 || numQuestions[i] > questions.Count()) {
			cout << "������� ������������ ��������!" << endl;
			//delete[] numQuestions;
			return;
		}
	}
	system("cls");

	for (int i = 0; i < countAnswers; i++) {
		cout << "������� ����� ������ ������� �" << numQuestions[i] << "(�� 1 �� " << questions.GetCountAnswers(numQuestions[i]) << "): ";
		cin >> numAnswers[i];

		if (numAnswers[i] <= 0 || numAnswers[i] > questions.GetCountAnswers(numQuestions[i])) {
			cout << "������� ������������ ��������!" << endl;
			//delete[] numAnswers;
			return;
		}
		system("cls");
	}

	// ���� ����������
	bool totalFound = false;
	bool found;
	for (int i = 0; i < count; i++) {
		found = true;
		for (int j = 0; j < countAnswers; j++) {
			int num = static_cast<int>(data[i].Get(numQuestions[j] - 1).respond[0]) - '0';
			if (num != numAnswers[j]) {
				found = false;
				break;
			}
		}

		if (found) {
			totalFound = true;
			data[i].Print(questions);
		}
	}

	if (!totalFound) {
		cout << "���������� �� �������!" << endl;
	}

	//delete[] numAnswers;
	//delete[] numQuestions;
}

void Database::Load(string& path_file1)
{
	ifstream load(path_file1);

	if (!load) {
		cout << "������ �������� ����� \"Resources\\data.txt\"!\n";
		return;
	}

	int numAnswer = 0;
	int i = 0;
	int idLine = 0;
	string line;
	Respond respond;
	int countAnswer = 0;

	while (getline(load, line)) {

		if (idLine == 0) {
			count = atoi(line.c_str());
			data = make_unique<Responder[]>(count);
		}
		else if (idLine == 1) {
			numAnswer = atoi(line.c_str());

			for (int q = 0; q < count; q++)
				data.get()[q].SetCount(numAnswer);
		}
		else if (idLine == 2) {
			respond.questionNumber = atoi(line.c_str());
		}
		else if (idLine == 3) {
			idLine = 1;

			if (countAnswer >= numAnswer) {
				countAnswer = 0;
				i++;
			}

			respond.respond = line;
			data.get()[i].Set(respond.questionNumber, respond);
			countAnswer++;
		}

		idLine++;
	}

	load.close();
	cout << "������ �������!" << endl;
}

void Database::Save(string& path_file2)
{
	if (count == 0) {
		cout << "������ �����!" << endl;
		return;
	}

	ofstream save(path_file2, ios::out);

	save << count << endl;
	save << questions.Count() << endl;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < questions.Count(); j++) {
			save << data.get()[i].Get(j).questionNumber << endl;
			save << data.get()[i].Get(j).respond;

			if (i < count - 1 || j < questions.Count() - 1)
				save << endl;
		}
	}

	save.close();
	cout << "������ ���������!" << endl;
}

void Database::PrintResponders()
{
	if (count == 0) {
		cout << "������ �����!" << endl;
		return;
	}

	bool next;

	for (int i = 0; i < count; i++) {
		data.get()[i].Print(questions);
		cout << endl;

		cout << "���������� �����? (1-��/0-���): ";
		cin >> next;
		if (!next)
			break;

		system("cls");
	}
}

void Database::PrintQuestions()
{
	questions.Print();
}

void Database::AbsoluteValuesResults()
{
	if (count == 0) {
		cout << "������ �����!" << endl;
		return;
	}

	// � ������� | � ������ �� ������������
	unordered_map<int, vector<int>> map;
	
	for (int i = 0; i < questions.Count(); i++) {
		vector<int> key;
		for (int j = 0; j < questions.GetCountAnswers(i); j++)
			key.push_back(0);

		for (int j = 0; j < count; j++) {
			int num = static_cast<int>(data.get()[j].Get(i).respond[0]) - '0';
			key[num - 1]++;
		}

		map.insert({ i, key });
	}

	for (auto element : map) {
		questions.Print(element.first);
		cout << "������� ������ �������: " << endl;
		for (int j = 0; j < questions.GetCountAnswers(element.first); j++) {
			cout << j + 1 << ": " << element.second[j] << " ���" << endl;
		}
		cout << endl;
	}
}

void Database::RelativeValuesResults()
{
	if (count == 0) {
		cout << "������ �����!" << endl;
		return;
	}

	// � ������� | � ������ �� ������������
	unordered_map<int, vector<int>> map;

	for (int i = 0; i < questions.Count(); i++) {
		vector<int> key;
		for (int j = 0; j < questions.GetCountAnswers(i); j++)
			key.push_back(0);

		for (int j = 0; j < count; j++) {
			int num = static_cast<int>(data[j].Get(i).respond[0]) - '0';
			key[num - 1]++;
		}

		map.insert({ i, key });
	}

	for (auto element : map) {
		questions.Print(element.first);
		cout << "������� ������ ������� (� %): " << endl;
		int total = 0;
		for (int j = 0; j < questions.GetCountAnswers(element.first); j++) {
			total += element.second[j];
		}

		for (int j = 0; j < questions.GetCountAnswers(element.first); j++) {
			cout << j + 1 << ": " << (float)element.second[j] / total << endl;
		}

		cout << endl;
	}
}

void Database::GenerateOneSurvey()
{
	unique_ptr<ConcreteFactory1> f1 = make_unique<ConcreteFactory1>();
	//const AbstractGenerator1* generator1 = f1->CreateGenerator1();
	auto generator1 = move(f1->CreateGenerator1());
	auto r = generator1->UsefulFunction1(questions);

	Add(r.get()[0]);
	cout << "����� ������������!" << endl;

	bool print;
	cout << "������� ��������������� �����? (1:��/0:���): ";
	cin >> print;
	if (print) {
		r->Print(questions);
	}
}

void Database::GenerateMultipleSurveys()
{
	int countRespond;
	cout << "���������� �������: ";
	cin >> countRespond;

	system("cls");

	if (countRespond < 1) {
		cout << "�������� ��������!" << endl;
		return;
	}

	unique_ptr<ConcreteFactory1> f = make_unique<ConcreteFactory1>();
	auto generator2 = f->CreateGenerator2();
	auto r = generator2->UsefulFunction2(questions, countRespond);

	for (int i = 0; i < countRespond; i++)
		Add(r[i]);

	cout << "������ �������������!" << endl;
}
