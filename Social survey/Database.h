#pragma once
#include "Responder.h"
#include <unordered_map>
#include <vector>
#include "ConcreteFactory1.h"
#include <memory>

class Database
{
private:
	Questions questions;
	unique_ptr<Responder[]> data;
	int count;

public:
	Database(string& pathLoadFile);
	Database& operator=(const Database& database) = delete;
	~Database();

	void Menu(int& act);

	void Copy(Responder* from, Responder* to, int n, int excl);
	void Add(Responder& d);
	void TakeTheSurvey();
	void DeleteTheSurvey();
	void Search();
	void Load(string& path_lfile);
	void Save(string& path_sfile);
	void PrintResponders();
	void PrintQuestions();
	void AbsoluteValuesResults();
	void RelativeValuesResults();
	void GenerateOneSurvey();
	void GenerateMultipleSurveys();
};

