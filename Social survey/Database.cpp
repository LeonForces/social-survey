#include "Database.h"

Database::Database(string& pathLoadFile)
{
	questions.Load(pathLoadFile);

	if (questions.Count() == 0) {
		throw" Вопросы отсутствуют!\n";
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
	cout << "Выберите: " << endl
		<< "0 - выход" << endl
		<< "================================" << endl
		<< "1 - пройти опрос" << endl
		<< "2 - удалить опрос" << endl
		<< "================================" << endl
		<< "3 - просмотр результатов опросов" << endl
		<< "4 - просмотр вопросов" << endl
		<< "================================" << endl
		<< "5 - загрузить результаты опросов" << endl
		<< "6 - сохранить результаты опросов" << endl
		<< "================================" << endl
		<< "7 - поиск по результатам опросов" << endl
		<< "8 - подсчитать абсолютные величины результатам опросов" << endl
		<< "9 - подсчитать относительные величины результатам опросов" << endl
		<< "================================" << endl
		<< "10 - сгенерировать один результат опроса" << endl
		<< "11 - сгенерировать несколько результатов опроса" << endl
		<< "Ваш выбор: ";
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
		// Перенести данные во временный массив
		unique_ptr<Responder[]> buf = make_unique<Responder[]>(count);
		Copy(data.get(), buf.get(), count, -1);

		// Выделить новую память
		//delete[] data;
		count++;
		data = make_unique<Responder[]>(count);

		// Вернуть данные
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
		cout << "Данные пусты!" << endl;
		return;
	}

	int index = 0;
	cout << "0 - назад\n";
	cout << "Выберите индекс ответника (от 1 до " << count << "): ";
	cin >> index;
	system("cls");

	if (index == 0)
		return;

	index--;
	if (index < 0 || index >= count) {
		cout << "Индекс вне диапазона!" << endl;
		return;
	}

	// Перенести данные во временный массив
	// std::unique_ptr
	auto buf = make_unique<Responder[]>(count);
	Copy(data.get(), buf.get(), count, -1);

	// Выделить новую память
	//delete[] data;
	count--;
	data = make_unique<Responder[]>(count);

	// Вернуть данные
	Copy(buf.get(), data.get(), count + 1, index);

	cout << "Данные удалены!" << endl;
}

void Database::Search()
{
	if (count == 0) {
		cout << "Данные пусты!" << endl;
		return;
	}

	// Вводим исходные данные
	int countAnswers = 0;
	cout << "Введите количество интересующих ответов: ";
	cin >> countAnswers;
	system("cls");

	if (countAnswers > questions.Count() || countAnswers <= 0) {
		cout << "Введено некорректное значение!" << endl;
		return;
	}

	auto numQuestions = make_unique<int[]>(countAnswers);
	auto numAnswers = make_unique<int[]>(countAnswers);

	cout << "Введите номера интересующих ответов (от 1 до " << questions.Count() <<"): \n";
	for (int i = 0; i < countAnswers; i++) {
		cin >> numQuestions[i];

		if (numQuestions[i] <= 0 || numQuestions[i] > questions.Count()) {
			cout << "Введено некорректное значение!" << endl;
			//delete[] numQuestions;
			return;
		}
	}
	system("cls");

	for (int i = 0; i < countAnswers; i++) {
		cout << "Введите номер ответа вопроса №" << numQuestions[i] << "(от 1 до " << questions.GetCountAnswers(numQuestions[i]) << "): ";
		cin >> numAnswers[i];

		if (numAnswers[i] <= 0 || numAnswers[i] > questions.GetCountAnswers(numQuestions[i])) {
			cout << "Введено некорректное значение!" << endl;
			//delete[] numAnswers;
			return;
		}
		system("cls");
	}

	// Ищем совпадение
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
		cout << "Совпадений не найдено!" << endl;
	}

	//delete[] numAnswers;
	//delete[] numQuestions;
}

void Database::Load(string& path_file1)
{
	ifstream load(path_file1);

	if (!load) {
		cout << "Ошибка открытия файла \"Resources\\data.txt\"!\n";
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
	cout << "Данные считаны!" << endl;
}

void Database::Save(string& path_file2)
{
	if (count == 0) {
		cout << "Данные пусты!" << endl;
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
	cout << "Данные сохранены!" << endl;
}

void Database::PrintResponders()
{
	if (count == 0) {
		cout << "Данные пусты!" << endl;
		return;
	}

	bool next;

	for (int i = 0; i < count; i++) {
		data.get()[i].Print(questions);
		cout << endl;

		cout << "Продолжить вывод? (1-да/0-нет): ";
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
		cout << "Данные пусты!" << endl;
		return;
	}

	// № вопроса | № ответа со совпадениями
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
		cout << "Частота выбора ответов: " << endl;
		for (int j = 0; j < questions.GetCountAnswers(element.first); j++) {
			cout << j + 1 << ": " << element.second[j] << " раз" << endl;
		}
		cout << endl;
	}
}

void Database::RelativeValuesResults()
{
	if (count == 0) {
		cout << "Данные пусты!" << endl;
		return;
	}

	// № вопроса | № ответа со совпадениями
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
		cout << "Частота выбора ответов (в %): " << endl;
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
	cout << "Ответ сгенерирован!" << endl;

	bool print;
	cout << "Вывести сгенерированный ответ? (1:да/0:нет): ";
	cin >> print;
	if (print) {
		r->Print(questions);
	}
}

void Database::GenerateMultipleSurveys()
{
	int countRespond;
	cout << "Количество ответов: ";
	cin >> countRespond;

	system("cls");

	if (countRespond < 1) {
		cout << "Неверное значение!" << endl;
		return;
	}

	unique_ptr<ConcreteFactory1> f = make_unique<ConcreteFactory1>();
	auto generator2 = f->CreateGenerator2();
	auto r = generator2->UsefulFunction2(questions, countRespond);

	for (int i = 0; i < countRespond; i++)
		Add(r[i]);

	cout << "Ответы сгенерированы!" << endl;
}
