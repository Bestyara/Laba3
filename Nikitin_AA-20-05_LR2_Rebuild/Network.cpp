#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <unordered_map>
#include "Network.h"
#include "StructCSpair.h"

using namespace std;

int proverkavvodaint();

double proverkavvodadouble();

void Network::AddPipe() {
	Pipe::id++;
	if (PipeMap.count(Pipe::getid()) == 0) {
		PipeMap.insert(pair <int, Pipe>(Pipe::getid(), Pipe()));//getnextid
		cin >> PipeMap[Pipe::getid()];
	}
}

void Network::AddStation() {
	CompressorStation::id++;
	if (CSMap.count(CompressorStation::getid()) == 0) {
		CSMap.insert(pair <int, CompressorStation>(CompressorStation::getid(), CompressorStation()));
		cin >> CSMap[CompressorStation::getid()];
	}
}

void Network::DelPipe() {
	cout << endl << "Введите ID трубы, данные о которой нужно удалить (для окончания ввода напишите -1)" << endl;
	int ch = proverkavvodaint();
	if (PipeMap.count(ch) != 0) {
		if (links.count(ch) == 0) {
			while (ch != -1 && PipeMap.count(ch) != 0) {
				PipeMap.erase(PipeMap.find(ch));
				cout << endl << "Введите ID трубы, данные о которой нужно удалить (для окончания ввода напишите -1)" << endl;
				ch = proverkavvodaint();
			}
		}
		else
			cout << endl << "Сначала отключите трубу от станций" << endl;
	}
	else {
		cout << endl << "Данных о трубе с таким ID нет, попробуйте ввести другой ID" << endl;
	}
}

void Network::DelStation() {
	cout << endl << "Введите ID КС, данные о которой нужно удалить (для окончания ввода напишите -1)" << endl;
	int ch = proverkavvodaint();
	if (CSMap.count(ch) != 0) {
		while (ch != -1 && CSMap.count(ch) != 0) {
			CSMap.erase(CSMap.find(ch));
			cout << endl << "Введите ID КС, данные о которой нужно удалить (для окончания ввода напишите -1)" << endl;
			ch = proverkavvodaint();
		}
	}
	else {
		cout << endl << "Данных о КС с таким ID нет, попробуйте ввести другой ID" << endl;
	}
}

void Network::FindandFixPipe() {//поиск и пакетное редактирование труб
	cout << endl << "Данные о трубах, которые находятся в ремонте: " << endl;
	if (PipeMap.size() != 0) {
		for (auto& i : PipeMap) {
			if (i.second.repair == 1) {
				cout << endl << "Труба";
				cout << endl << "ID: " << i.first;
				cout << endl << "Длина трубы: " << i.second.l;
				cout << endl << "Диаметр трубы: " << i.second.d;
				cout << endl << "Труба в ремонте:(0 - Нет, 1 - Да): " << i.second.repair << endl;
			}
		}
	}
	cout << endl << "Данные о трубах, которые не находятся в ремонте: " << endl;
	if (PipeMap.size() != 0) {
		for (auto& i : PipeMap) {
			if (i.second.repair == 0) {
				cout << endl << "Труба";
				cout << endl << "ID: " << i.first;
				cout << endl << "Длина трубы: " << i.second.l;
				cout << endl << "Диаметр трубы: " << i.second.d;
				cout << endl << "Труба в ремонте:(0 - Нет, 1 - Да): " << i.second.repair << endl;
			}
		}
	}
	cout << endl << "Введите ID труб, данные о ремонте которых хотели бы изменить (для окончания ввода напишите -1):" << endl;
	int ch = proverkavvodaint();
	while (PipeMap.count(ch) == 0 && ch != -1) {
		cout << "Ошибка при вводе данных, данные о трубе с данным ID не найдены, введите другое значение" << endl;
		ch = proverkavvodaint();
	}
	while (ch != -1 && PipeMap.count(ch) != 0) {
		if (PipeMap[ch].repair == 0) {
			PipeMap[ch].repair = 1;
		}
		else {
			PipeMap[ch].repair = 0;
		}
		cout << endl << "Данные изменены" << endl;
		cout << endl << "Введите ID труб, данные о ремонте которых хотели бы изменить (для окончания ввода напишите -1):" << endl;
		ch = proverkavvodaint();
		while (PipeMap.count(ch) == 0 && ch != -1) {
			cout << "Ошибка при вводе данных, данные о трубе с данным ID не найдены, введите другое значение" << endl;
			ch = proverkavvodaint();
		}
	}
}

void Network::FindandFixStation() {//поиск и пакетное редактирование КС
	cout << endl << "Поиск по какому параметру произвести?" << endl;
	cout << "1 - Название";
	cout << endl << "2 - Процент задейстованных цехов" << endl;
	int ch = proverkavvodaint();
	switch (ch) {
	case 1: {//название
		cout << endl << "Введите название КС:" << endl;
		string str;
		cin.ignore(32767, '\n');
		getline(cin, str);
		cout << endl << "Результат поиска: ";
		for (auto& i : CSMap) {
			if (i.second.name == str) {
				cout << endl << "Компрессорная станция:" << endl;
				cout << endl << "ID: " << i.first << endl;
				cout << "Наименование: " << i.second.name << endl;
				cout << "Количество цехов: " << i.second.kol << endl;
				cout << "Количество цехов в работе: " << i.second.kolinwork << endl;
				cout << "Эффективность: " << i.second.effectiveness << endl;
			}
		}
		cout << endl << "Выберите действие (для выхода введите -1):";
		cout << endl << "1 - Изменить данные всех найденных КС";
		cout << endl << "2 - Выборочно изменить данные некоторых КС" << endl;
		int ch1 = proverkavvodaint();
		switch (ch1) {
		case 1: {
			string str1;
			cout << "Введите новое название КС" << endl;
			cin.ignore(32767, '\n');
			getline(cin, str1);
			for (auto& i : CSMap) {
				if (i.second.name == str) {
					i.second.name = str1;
				}
			}
			cout << "Данные изменены" << endl;
			break;
		}
		case 2: {
			string str1;
			cout << "Введите новое название КС" << endl;
			cin.ignore(32767, '\n');
			getline(cin, str1);
			cout << endl << "Введите ID КС, название которой хотели бы изменить (для окончания ввода напишите -1):" << endl;
			ch1 = proverkavvodaint();
			while (CSMap.count(ch1) == 0 && ch1 != -1) {
				cout << "Ошибка при вводе данных, данные о КС с данным ID не найдены, введите другое значение" << endl;
				ch1 = proverkavvodaint();
			}
			while (ch1 != -1 && CSMap.count(ch1) != 0) {
				CSMap[ch1].name = str1;
				cout << endl << "Данные изменены" << endl;
				cout << endl << "Введите ID КС, название которой хотели бы изменить (для окончания ввода напишите -1):" << endl;
				ch1 = proverkavvodaint();
				while (CSMap.count(ch1) == 0 && ch1 != -1) {
					cout << "Ошибка при вводе данных, данные о КС с данным ID не найдены, введите другое значение" << endl;
					ch1 = proverkavvodaint();
				}
			}
			break;
		}
		default: {
			cout << "Ошибка при вводе данных";
			break;
		}
		}
		break;
	}
	case 2: {//процент задейстованных цехов
		cout << endl << "Введите минимальный процент задейстованных цехов: " << endl;
		int percent;
		cin >> percent;
		cout << endl << "Результат поиска: ";
		for (auto& i : CSMap) {
			if ((double(i.second.kolinwork) / double(i.second.kol) * 100) >= percent) {
				cout << endl << "Компрессорная станция:" << endl;
				cout << endl << "ID: " << i.first << endl;
				cout << "Наименование: " << i.second.name << endl;
				cout << "Количество цехов: " << i.second.kol << endl;
				cout << "Количество цехов в работе: " << i.second.kolinwork << endl;
				cout << "Эффективность: " << i.second.effectiveness << endl;
			}
		}
		cout << endl << "Результат поиска (меньше минимума): ";
		for (auto& i : CSMap) {
			if ((double(i.second.kolinwork) / double(i.second.kol) * 100) < percent) {
				cout << endl << "Компрессорная станция:" << endl;
				cout << endl << "ID: " << i.first << endl;
				cout << "Наименование: " << i.second.name << endl;
				cout << "Количество цехов: " << i.second.kol << endl;
				cout << "Количество цехов в работе: " << i.second.kolinwork << endl;
				cout << "Эффективность: " << i.second.effectiveness << endl;
			}
		}
		cout << endl << "Выберите действие (для выхода введите -1):";
		cout << endl << "1 - Изменить данные всех найденных КС";
		cout << endl << "2 - Выборочно изменить данные некоторых КС" << endl;
		int num = -2;
		num = proverkavvodaint();
		switch (num) {
		case 1: {
			cout << "Введите у скольких цехов возобновить работу:" << endl;
			int kolvo = proverkavvodaint();
			for (auto& i : CSMap) {
				if (((double(i.second.kolinwork) / double(i.second.kol) * 100) >= percent) && (i.second.kolinwork + kolvo <= i.second.kol)) {
					i.second.kolinwork += kolvo;
					cout << "Данные КС с ID " << i.first << " изменены" << endl;
				}
				else if (i.second.kolinwork + kolvo > i.second.kol) {
					cout << "Ошибка при вводе числа, у КС с ID " << i.first << " значение не может быть изменено" << endl;
				}
			}
			break;
		}
		case 2: {
			cout << "Введите у скольких цехов возобновить работу:" << endl;
			int kolvo = proverkavvodaint();
			cout << endl << "Введите ID КС, число рабочих цехов которой хотели бы изменить (для окончания ввода напишите -1):" << endl;
			int ch1 = proverkavvodaint();
			while (CSMap.count(ch1) == 0 && ch1 != -1) {
				cout << "Ошибка при вводе данных, данные о КС с данным ID не найдены, введите другое значение" << endl;
				ch1 = proverkavvodaint();
			}
			while (ch1 != -1 && CSMap.count(ch1) != 0) {
				if (CSMap[ch1].kolinwork + kolvo <= CSMap[ch1].kol) {
					CSMap[ch1].kolinwork += kolvo;
					cout << "Данные КС с ID " << ch1 << " изменены" << endl;
					cout << endl << "Введите ID КС, число рабочих цехов которой хотели бы изменить (для окончания ввода напишите -1):" << endl;
					ch1 = proverkavvodaint();
					while (CSMap.count(ch1) == 0 && ch1 != -1) {
						cout << "Ошибка при вводе данных, данные о КС с данным ID не найдены, введите другое значение" << endl;
						ch1 = proverkavvodaint();
					}
				}
				else if (CSMap[ch1].kolinwork + kolvo > CSMap[ch1].kol) {
					cout << "Ошибка при вводе числа, у КС с ID " << ch1 << " значение не может быть изменено" << endl;
				}
			}
			break;
		}
		default: {
			cout << "Ошибка при вводе данных";
			break;
		}
		}
		break;
	}
	default: {
		cout << "Ошибка при вводе данных";
		break;
	}
	}
}

void Network::savefilepipe(ofstream& filesave) {
	if (Pipe::id != 0) {
		for (auto& i : PipeMap) {
			filesave << "Труба:" << endl;
			filesave << i.first << endl;
			filesave << i.second.l << endl;
			filesave << i.second.d << endl;
			filesave << i.second.repair << endl;
		}
	}
	else
		filesave << "Нет данных о трубах" << endl;
}

void Network::savefilestation(ofstream& filesave) {
	if (CSMap.size() != 0) {
		for (auto& i : CSMap) {
			filesave << "Компрессорная станция:" << endl;
			filesave << i.first << endl;
			filesave << i.second.name << endl;
			filesave << i.second.kol << endl;
			filesave << i.second.kolinwork << endl;
			filesave << i.second.effectiveness << endl;
		}
	}
	else
		filesave << "Нет данных о КС" << endl;
}

void Network::loadnetwork(ifstream& fileload) {
	string str;
	Pipe p;
	CompressorStation cs;
	while (!fileload.eof()) {
		getline(fileload, str);
		if (str == "Pipe") {
			int strid;
			getline(fileload, str);//считываем id
			strid = stoi(str);
			if (Pipe::id < strid)
				Pipe::id = strid;
			if (PipeMap.count(strid) != 0) {
				getline(fileload, str);//считываем диаметр
				PipeMap[strid].d = stoi(str);
				getline(fileload, str);//считываем длину
				PipeMap[strid].l = stoi(str);
				getline(fileload, str);//считываем длину
				PipeMap[strid].inid = stoi(str);
				getline(fileload, str);//считываем длину
				PipeMap[strid].outid = stoi(str);
			}
			else {
				getline(fileload, str);//считываем диаметр
				p.d = stoi(str);
				getline(fileload, str);//считываем длину
				p.l = stoi(str);
				getline(fileload, str);//считываем длину
				p.inid = stoi(str);
				getline(fileload, str);//считываем длину
				p.outid = stoi(str);
				PipeMap.insert(pair <int, Pipe>(strid, p));
			}
		}
		else if (str == "Compressor Station") {
			int strid;
			getline(fileload, str);//считываем id
			strid = stoi(str);
			if (CompressorStation::id < strid)
				CompressorStation::id = strid;
			if (CSMap.count(strid) != 0) {
				getline(fileload, str);//считываем название
				CSMap[strid].name = str;
				getline(fileload, str);//считываем кол-во цехов
				CSMap[strid].kol = stoi(str);
				getline(fileload, str);//считываем кол-во рабочих цехов
				CSMap[strid].kolinwork = stoi(str);
				getline(fileload, str);//считываем эффективность
				CSMap[strid].effectiveness = stoi(str);
				getline(fileload, str);//считываем
				CSMap[strid].inpipe = stoi(str);
				getline(fileload, str);//считываем
				CSMap[strid].outpipe = stoi(str);
			}
			else {
				getline(fileload, str);//считываем название
				cs.name = str;
				getline(fileload, str);//считываем кол-во цехов
				cs.kol = stoi(str);
				getline(fileload, str);//считываем кол-во рабочих цехов
				cs.kolinwork = stoi(str);
				getline(fileload, str);//считываем эффективность
				cs.effectiveness = stoi(str);
				getline(fileload, str);//считываем входящие трубы
				cs.inpipe = stoi(str);
				getline(fileload, str);//считываем исходящие трубы
				cs.outpipe = stoi(str);
				CSMap.insert(pair <int, CompressorStation>(strid, cs));
			}
		}
	}
	if (PipeMap.size() != 0) {
		for (int i = 0; i < PipeMap.size();i++) {
			links.insert({ i, {PipeMap[i].inid, PipeMap[i].outid} });
		}
	}
}

//void Network::loadfilepipe(ifstream& fileload) {
//	string str;
//	Pipe p;
//	while (!fileload.eof()) {
//		getline(fileload, str);
//		if (str == "Pipe") {
//			int strid;
//			getline(fileload, str);//считываем id
//			strid = stoi(str);
//			if (Pipe::id < strid)
//				Pipe::id = strid;
//			if (PipeMap.count(strid) != 0) {
//				getline(fileload, str);//считываем диаметр
//				PipeMap[strid].d = stoi(str);
//				getline(fileload, str);//считываем длину
//				PipeMap[strid].l = stoi(str);
//				getline(fileload, str);//считываем длину
//				PipeMap[strid].inid = stoi(str);
//				getline(fileload, str);//считываем длину
//				PipeMap[strid].outid = stoi(str);
//			}
//			else {
//				getline(fileload, str);//считываем диаметр
//				p.d = stoi(str);
//				getline(fileload, str);//считываем длину
//				p.l = stoi(str);
//				getline(fileload, str);//считываем длину
//				p.inid = stoi(str);
//				getline(fileload, str);//считываем длину
//				p.outid = stoi(str);
//				PipeMap.insert(pair <int, Pipe>(strid, p));
//			}
//		}
//		else if (str == "Compressor Station") {
//			getline(fileload, str);
//			getline(fileload, str);
//			getline(fileload, str);
//			getline(fileload, str);
//			getline(fileload, str);
//		}
//	}
//}


//void Network::loadfilestation(ifstream& fileload) {
//	string str;
//	CompressorStation cs;
//	while (!fileload.eof()) {
//		getline(fileload, str);
//		if (str == "Pipe") {
//			getline(fileload, str);
//			getline(fileload, str);
//			getline(fileload, str);
//		}
//		else if (str == "Compressor Station") {
//			int strid;
//			getline(fileload, str);//считываем id
//			strid = stoi(str);
//			if (CompressorStation::id < strid)
//				CompressorStation::id = strid;
//			if (CSMap.count(strid) != 0) {
//				getline(fileload, str);//считываем название
//				CSMap[strid].name = str;
//				getline(fileload, str);//считываем кол-во цехов
//				CSMap[strid].kol = stoi(str);
//				getline(fileload, str);//считываем кол-во рабочих цехов
//				CSMap[strid].kolinwork = stoi(str);
//				getline(fileload, str);//считываем эффективность
//				CSMap[strid].effectiveness = stoi(str);
//				getline(fileload, str);//считываем
//				CSMap[strid].inpipe = stoi(str);
//				getline(fileload, str);//считываем
//				CSMap[strid].outpipe = stoi(str);
//			}
//			else {
//				getline(fileload, str);//считываем название
//				cs.name = str;
//				getline(fileload, str);//считываем кол-во цехов
//				cs.kol = stoi(str);
//				getline(fileload, str);//считываем кол-во рабочих цехов
//				cs.kolinwork = stoi(str);
//				getline(fileload, str);//считываем эффективность
//				cs.effectiveness = stoi(str);
//				getline(fileload, str);//считываем входящие трубы
//				cs.inpipe = stoi(str);
//				getline(fileload, str);//считываем исходящие трубы
//				cs.outpipe = stoi(str);
//				CSMap.insert(pair <int, CompressorStation>(strid, cs));
//			}
//		}
//	}
//}

void Network::connect() {
	if (PipeMap.size() != 0) {
		cout << "Введите ID трубы для добавления: " << endl;
		int id = proverkavvodaint();
		if ((links.count(id) == 0)) {
			while (PipeMap.count(id) == 0) {
				cout << "Трубы с данным id не существует, попробуйте еще раз" << endl;
				id = proverkavvodaint();
			}
			if (CSMap.size() >= 2) {
				cout << "Введите ID первой КС, которую нужно законнектить: " << endl;
				int cs1 = proverkavvodaint();
				while (CSMap.count(cs1) == 0) {
					cout << "КС с данным id не существует, попробуйте еще раз" << endl;
					cs1 = proverkavvodaint();
				}
				cout << "Введите ID второй КС, которую нужно законнектить: " << endl;
				int cs2 = proverkavvodaint();
				while (CSMap.count(cs2) == 0) {
					cout << "КС с данным id не существует, попробуйте еще раз" << endl;
					cs2 = proverkavvodaint();
				}
				if (((CSMap[cs1].inpipe + CSMap[cs1].outpipe) < CSMap[cs1].kol)
					&& ((CSMap[cs2].inpipe + CSMap[cs2].outpipe) < CSMap[cs2].kol)
					&& (cs1 != cs2)) {//не в сумме, а отдельно 
					links.insert({ id, {cs1, cs2} });
					CSMap[cs1].outpipe++;
					CSMap[cs2].inpipe++;
					cout << "Подключение произошло" << endl;
				}
				else
					cout << "Количество подключенных труб между этими КС максимально" << endl;
			}
			else
				cout << endl << "Количество КС меньше 2, подключить трубу нельзя/ID трубы неверный" << endl;
		}
		else
			cout << "Труба с данным ID уже подключена" << endl;
	}
	else
		cout << "Нет данных о трубах, подключение невозможно" << endl;
}

void Network::disconnect() {
	if (links.size() != 0) {
		cout << "Введите ID трубы для отключения: " << endl;
		int id = proverkavvodaint();
		if (PipeMap.count(id) == 0) {
			while (PipeMap.count(id) == 0) {
				cout << "Трубы с данным id не существует, попробуйте еще раз" << endl;
				id = proverkavvodaint();
			}
		}
		if (links.count(id) != 0) {
			CSMap[links[id].incs].inpipe--;
			CSMap[links[id].outcs].outpipe--;
			links.erase(id);
			cout << "Отключение произошло" << endl;
		}
		else {
			cout << "Труба с данным ID не подключена" << endl;
		}
	}
	else {
		cout << "Связей нет, отключение невозможно"<< endl;
	}
}


void Network::topologicsort() {
	vector <int> ans;
	vector <int> buf;
	vector <int> indbuf;
	while (links.size() != 0) {
		for (auto& i : CSMap) {//записываем вершины, в которых полустепень захода равна 0
			if (i.second.inpipe == 0) {
				ans.push_back(i.first);
				buf.push_back(i.first);
				i.second.inpipe = 9999;
			}
		}
		//for (int i = 0; i < links.size(); i++) {//удаляем связи, в которых участвуют вершины из set ans
		//	for (int j = 0; j < buf.size(); j++) {
		//		if (links.count(i) != 0) {
		//			if ((links[i].incs == buf[j]) || (links[i].outcs == buf[j])) {
		//				if (links[i].incs == buf[j])
		//					CSMap[links[i].outcs].inpipe--;
		//				else
		//					CSMap[links[i].incs].inpipe--;
		//				links.erase(i);
		//			}
		//		}
		//	}
		//}
		//while (CSMap[k].inpipe + CSMap[k].outpipe != 0 && k < CSMap.size()) {
		for (auto& i : links) {//удаляем связи, в которых участвуют вершины из ans
			for (int j = 0; j < buf.size(); j++) {
				if (links.count(i.first) != 0) {
					if ((i.second.incs == buf[j]) || (i.second.outcs == buf[j])) {
						if (i.second.incs == buf[j])
							CSMap[i.second.outcs].inpipe--;
						else
							CSMap[i.second.incs].inpipe--;
						//links.erase(i);
						i.second.incs = -1;
						i.second.outcs = -1;
						indbuf.push_back(i.first);
					}
				}
			}
		}
		buf.clear();
		for (int i = 0; i < indbuf.size(); i++) {
			links.erase(indbuf[i]);
		}
		indbuf.clear();
		//cout << CSMap.size() << endl;
	}
	for (auto& i : CSMap) {//записываем вершины, в которых полустепень захода равна 0
		if (i.second.inpipe == 0) {
			ans.push_back(i.first);
			i.second.inpipe = 9999;
		}
	}
	//while (links.size() != 0) {
	//	for (auto& i : CSMap) {//записываем вершины, в которых полустепень захода равна 0
	//		if (i.second.inpipe == 0) {
	//			ans.push_back(i.first);
	//			buf.push_back(i.first);
	//		}
	//	}
	//	for (int i = 0; i < links.size(); i++) {//удаляем связи, в которых участвуют вершины из set ans
	//		for (int j = 0; j < buf.size(); j++) {
	//			if ((links[i].incs == buf[j]) || (links[i].outcs == buf[j])) {
	//				links.erase(i);
	//			}
	//		}
	//	}
	//	buf.clear();
	//}
	cout << "Топологическая сортировка:" << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}

void Network::showlinks() {
	cout << "Связи: " << endl;
	for (auto& i : links) {
		cout << i.second.incs << " " << i.second.outcs << endl;
	}
}
