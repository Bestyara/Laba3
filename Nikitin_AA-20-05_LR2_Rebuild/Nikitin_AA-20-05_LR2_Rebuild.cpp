// try catch мусор в редактировании, проверить добавлена труба или нет 1000;993;986;979;
using namespace std;
#include <iostream>
#include <string>
#include "windows.h"
#include <fstream>
#include <unordered_map>
#include "cs.h"
#include "pipe.h"
#include "Network.h"

int proverkavvodaint() {
	int a;
	while (true) {
		cin >> a;
		if (cin.fail() || a < -1) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Введите другое значение" << endl;
		}
		else
			return a;
	}
}

double proverkavvodadouble() {// перегрузка функций
	double a;
	while (true) {
		cin >> a;
		if (cin.fail() || a < -1) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Введите другое значение" << endl;
		}
		else
			return a;
	}
}

int Pipe::id = 0;

int CompressorStation::id = 0;

void mainmenu() {
	cout << "Введите одно из представленных чисел" << endl;
	cout << "1 - Добавить трубу" << endl;
	cout << "2 - Добавить КС" << endl;
	cout << "3 - Просмотр всех объектов" << endl;
	cout << "4 - Редактировать трубу" << endl;
	cout << "5 - Редактировать КС" << endl;
	cout << "6 - Сохранить" << endl;
	cout << "7 - Загрузить" << endl;
	cout << "8 - Удалить данные о трубах" << endl;
	cout << "9 - Удалить данные о КС" << endl;
	cout << "10 - Найти трубы в ремонте и выполнить пакетное редактирование" << endl;
	cout << "11 - Найти КС по названию, проценту задействованных цехов и выполнить пакетное редактирование" << endl;
	cout << "12 - Подключить трубы и КС в ГТС" << endl;
	cout << "13 - Отключить трубу из ГТС" << endl;
	cout << "14 - Топологи в деле" << endl;
	cout << "15 - Посмотреть связи" << endl;
	cout << "0 - Выход" << endl << endl;
}

void proverkamenu(const int& menu) {
	if ((menu > 17) || (menu < 0)) {
		cout << "Введите другое число" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int menu = 1;
	Network seti;
	while (menu != 0) {
		mainmenu();
		menu = proverkavvodaint();
		proverkamenu(menu);
		switch (menu) {
		case 1: {
			seti.AddPipe();
			break;
		}
		case 2: {
			seti.AddStation();
			break;
		}
		case 3: {
			cout << seti.PipeMap;
			cout << seti.CSMap;
			break;
		}
		case 4: {
			cout << endl << "Введите ID трубы для редактирования: ";
			int i = proverkavvodaint();
			if (seti.PipeMap.count(i) != 0) {
				seti.PipeMap[i].FixPipe();
			}
			else {
				cout << "Введите другое значение" << endl;
			}
			break;
		}
		case 5: {
			cout << endl << "Введите ID КС для редактирования: ";
			int j = proverkavvodaint();
			if (seti.CSMap.count(j) != 0) {
				seti.CSMap[j].FixStation();
			}
			else {
				cout << "Введите другое значение" << endl;
			}
			break;
		}
		case 6: {
			cout << endl << "Введите название файла: " << endl;
			string filenam;
			cin.ignore(32767, '\n');
			getline(cin, filenam);
			ofstream filesave(filenam + ".txt");
			if (filesave.fail()) {
				cout << "Файл для считывания информации не был создан" << endl;
			}
			else {
				seti.savefilepipe(filesave);
				seti.savefilestation(filesave);
				filesave.close();
			}
			break;
		}
		case 7: {
			Pipe::id = 0;
			CompressorStation::id = 0;
			cout << endl << "Введите название файла: " << endl;
			string filenam;
			cin.ignore(32767, '\n');
			getline(cin, filenam);
			ifstream fileload(filenam + ".txt");
			if (fileload.fail()) {
				cout << "Файл для считывания информации не был создан" << endl;
			}
			else {
				//seti.loadfilepipe(fileload);//loadnetwork
				//fileload.close();
				//ifstream fileload(filenam + ".txt");
				//seti.loadfilestation(fileload);
				seti.loadnetwork(fileload);
				fileload.close();
			}
			break;
		}
		case 8: {
			seti.DelPipe();
			break;
		}
		case 9: {
			seti.DelStation();
			break;
		}
		case 10: {
			seti.FindandFixPipe();
			break;
		}
		case 11: {
			seti.FindandFixStation();
			break;
		}
		case 12: {
			seti.connect();
			break;
		}
		case 13: {
			seti.disconnect();
			break;
		}
		case 14 : {
			seti.topologicsort();
			break;
		}
		case 15: {
			seti.showlinks();
			break;
		}
		}
		system("pause");
		system("cls");
	}
}

