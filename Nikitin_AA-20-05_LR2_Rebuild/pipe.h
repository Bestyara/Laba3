#pragma once

#include <map>

using namespace std;

class Pipe { //класс трубы
public:
	static int id;
	int inid;
	int outid;
	int d;
	int l;
	bool repair;
	Pipe();//конструктор
	friend istream& operator>> (istream&, Pipe& p);//перегрузка ввода
	friend ostream& operator<< (ostream&, const unordered_map <int, Pipe>&);//перегрузка вывода
	void FixPipe();
	//void DelPipe(unordered_map <int, Pipe>&);
	//void FindandFixPipe(unordered_map<int, Pipe>&);
	/*void savefilepipe(const unordered_map <int, Pipe>&, ofstream&);*/
	//void loadfilepipe(unordered_map <int, Pipe>&, ifstream&);
	static int getid();
};