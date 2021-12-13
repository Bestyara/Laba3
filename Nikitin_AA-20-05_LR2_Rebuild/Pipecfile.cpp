using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "pipe.h"

int proverkavvodaint();

double proverkavvodadouble();

Pipe::Pipe()
{
	this->d = 0;
	this->l = 0;
	this->repair = 0;
}

istream& operator>> (istream& in, Pipe& p) {
	cout << "Введите диаметр трубы: ";
	p.d = proverkavvodaint();
	cout << "Введите длину трубы: ";
	p.l = proverkavvodaint();
	p.repair = 0;
	return in;
}

ostream& operator<< (ostream& out, const unordered_map <int, Pipe>& PipeMap) {
	if (PipeMap.size() != 0) {
		for (auto& i : PipeMap) {// https://stackoverflow.com/questions/14555751/how-to-iterate-over-a-c-stl-map-data-structure-using-the-auto-keyword
			out << endl << "Труба: " << endl;
			out << endl << "ID: " << i.first;
			out << endl << "Длина трубы: " << i.second.l;
			out << endl << "Диаметр трубы: " << i.second.d;
			out << endl << "Труба в ремонте:(0 - Нет, 1 - Да): " << i.second.repair << endl;
		}
	}
	else
		out << endl << "Труба не была добавлена" << endl;
	return out;
}

void Pipe::FixPipe() { //Редактирование данных трубы
	repair = !repair;
	if (repair == 0) {
		cout << "Теперь труба не в ремонте" << endl;
	}
	if (repair == 1) {
		cout << "Теперь труба в ремонте" << endl;
	}
}

int Pipe::getid() {
	return id;
}