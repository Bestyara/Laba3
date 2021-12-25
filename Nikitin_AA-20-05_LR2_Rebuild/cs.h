#pragma once

#include <string>
#include <map>

using namespace std;

class CompressorStation { //����� ��	
public:
	static int id;
	string name;
	int kol;
	int kolinwork;
	double effectiveness;
	int inpipe = 0;
	int outpipe = 0;
	CompressorStation();//�����������
	friend istream& operator>> (istream&, CompressorStation& cs);//���������� �����
	friend ostream& operator<< (ostream&, const unordered_map <int, CompressorStation>&);//���������� ������
	void FixStation();
	//void DelStation(unordered_map <int, CompressorStation>&);
	//void FindandFixStation(unordered_map <int, CompressorStation>&);
	//void savefilestation(ofstream&);
	//void loadfilestation(ifstream&);
	static int getid();
};