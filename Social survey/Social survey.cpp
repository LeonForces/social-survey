#include <Windows.h>
#include "Database.h"

#include "AbstractFactory.h"
#include "AbstractGenerator1.h"
#include "AbstractGenerator2.h"
#include "ConcreteFactory1.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	string saveFile = "..\\Resources\\data.txt";
	string questFile = "..\\Resources\\форма.txt";
	Database db (questFile);
	int act = 0;
	//srand(time(0));

	try {
		do {
			db.Menu(act);

			switch (act)
			{
			case 0:
				break;

			case 1:
				db.TakeTheSurvey();
				break;

			case 2:
				db.DeleteTheSurvey();
				break;

			case 3:
				db.PrintResponders();
				break;

			case 4:
				db.PrintQuestions();
				break;

			case 5:
				db.Load(saveFile);
				break;

			case 6:
				db.Save(saveFile);
				break;

			case 7:
				db.Search();
				break;

			case 8:
				db.AbsoluteValuesResults();
				break;

			case 9:
				db.RelativeValuesResults();
				break;

			case 10:
				db.GenerateOneSurvey();
				break;

			case 11:
				db.GenerateMultipleSurveys();
				break;

			default:
				cout << "Неверный выбор!" << endl;
				break;
			}

			system("pause");
			system("cls");
		} while (act != 0);
	}
	catch (const char* message) {
		cout << "Вызвано исключение!\nСообщение:" << message << endl;
	}
}