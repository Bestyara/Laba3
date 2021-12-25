using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "cs.h"

int proverkavvodaint();

double proverkavvodadouble();

CompressorStation::CompressorStation()
{
	this->name = "";
	this->kol = 0;
	this->kolinwork = 0;
	this->effectiveness = 0;
}

istream& operator>> (istream& in, CompressorStation& cs) {
	cout << "Введите наименование: ";
	in.ignore(32767, '\n');//https://ravesli.com/urok-57-vvedenie-v-std-string/
	getline(in, cs.name);
	cout << "Количество цехов: ";
	cs.kol = proverkavvodaint();
	cout << "Количество цехов в работе: ";
	cs.kolinwork = proverkavvodaint();
	while ((cs.kolinwork < 1) || (cs.kolinwork > cs.kol)) {
		cout << "Ошибка ввода, введите другое значение" << endl;
		cs.kolinwork = proverkavvodaint();
	}
	cout << "Эффективность: ";
	cs.effectiveness = proverkavvodadouble();
	return in;
}
ostream& operator<< (ostream& out, const unordered_map <int, CompressorStation>& CSMap) {
	if (CSMap.size() != 0) {
		for (auto& i : CSMap) {
			out << endl << "Компрессорная станция:" << endl;
			out << endl << "ID: " << i.first << endl;
			out << "Наименование: " << i.second.name << endl;
			out << "Количество цехов: " << i.second.kol << endl;
			out << "Количество цехов в работе: " << i.second.kolinwork << endl;
			out << "Эффективность: " << i.second.effectiveness << endl;
		}
	}
	else
		out << endl << "КС не была добавлена" << endl;
	return out;
}
void CompressorStation::FixStation() { //Редактирование данных о КС
	cout << "Введите что нужно сделать (возобновить работу цехов, остановить работу цехов)" << endl;
	cout << "1 - Возобновить работу цехов " << endl;
	cout << "2 - Остановить работу цехов " << endl << endl;
	kol = proverkavvodaint();
	switch (kol) {
	case 1: {
		cout << "У скольких цехов нужно возобновить работу: ";
		int kolvo = proverkavvodaint();
		while (kolinwork + kolvo > kol) {
			cout << "Ошибка ввода, введите другое значение" << endl;
			kolvo = proverkavvodaint();
		}
		kolinwork += kolvo;
		break;
	}
	case 2: {
		cout << "У скольких цехов нужно остановить работу: ";
		int kolvo = proverkavvodaint();
		while (kolinwork - kolvo < 0) {
			cout << "Ошибка ввода, введите другое значение" << endl;
			kolvo = proverkavvodaint();
		}
		kolinwork -= kolvo;
		break;
	}
	default:
		cout << endl << "Ошибка при вводе значения";
		break;
	}
}

int CompressorStation::getid() {
	return id;
}