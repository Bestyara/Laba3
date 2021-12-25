#pragma once
#include <unordered_map>
#include "pipe.h"
#include "cs.h"
#include "StructCSpair.h"

using namespace std;

class Network {
public:
	unordered_map <int, Pipe> PipeMap;
	unordered_map <int, CompressorStation> CSMap;
	unordered_map <int, paircs> links;
	void AddPipe();
	void AddStation();
	void DelPipe();
	void DelStation();
	void FindandFixPipe();
	void FindandFixStation();
	void savefilepipe(ofstream&);
	void savefilestation(ofstream&);
	void loadnetwork(ifstream&);
	void loadfilepipe(ifstream&);
	void loadfilestation(ifstream&);
	void connect();
	void disconnect();
	void topologicsort();
	void showlinks();
};


