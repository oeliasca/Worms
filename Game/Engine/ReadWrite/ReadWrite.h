#pragma once
#include <fstream>
#include <iostream>
#include "../Definitions/definition.h"


class ReadWrite
{
	
public:


	~ReadWrite();
	static ReadWrite* getInstance();

	int initWrite(const char* file);
	void writeBinary(std::vector<ScoreInfo>& _ladder);
	void readBinary(const char* file);

	std::vector<ScoreInfo> getLadder() { return ladder; };


private:
	ReadWrite();
	static ReadWrite* pInstance;
	
	std::ofstream write;
	
	std::vector<ScoreInfo> ladder;
	


};


