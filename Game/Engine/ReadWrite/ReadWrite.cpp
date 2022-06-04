#include "ReadWrite.h"


ReadWrite* ReadWrite::pInstance = NULL;
ReadWrite::~ReadWrite()
{
}
ReadWrite::ReadWrite()
{
	
}

ReadWrite* ReadWrite::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new ReadWrite();
	}
	return pInstance;
}



int ReadWrite::initWrite(const char* file)
{
	write.open(file, std::ios::binary|std::ios::out| std::ofstream::trunc);
	if (!write.is_open()) {
		std::cout << "No s'ha obert" << std::endl;
		return 1;
	}
	return 0;
}

//s'ha de passar _ladder ja ordenat per puntuacio
void ReadWrite::writeBinary(std::vector<ScoreInfo> &_ladder)
{
	int length = (int)_ladder.size();
	write.write((char*)&length, sizeof(int));//----------------------------------------------------0
	

	for (int i = 0; i < _ladder.size(); i++)
	{
		int str_len = _ladder[i].teamName.length();
		write.write((char*)&str_len, sizeof(str_len));//-------------------------------------------1
		write.write((char*)_ladder[i].teamName.c_str(),sizeof(_ladder[i].teamName));//--------------------2
		write.write((char*)&_ladder[i].punctuation, sizeof(_ladder[i].punctuation));//-------------3
	}

	write.close();
}



void ReadWrite::readBinary(const char* file)
{
	ladder.clear();
	std::ifstream readBinaryFile;
	int size = 0;

	readBinaryFile.open(file, std::ios::out | std::ios::app);
	readBinaryFile.close();

	readBinaryFile.open(file, std::ios::in | std::ios::binary);
	readBinaryFile.seekg(0, std::ios::end);
	size = (int)readBinaryFile.tellg();

	readBinaryFile.seekg(0, std::ios::beg);
	if (size != 0) {
		char* buffer = new char[size];
		readBinaryFile.read((char*)buffer, size);

		readBinaryFile.close();
		int punter = 0;

		int  length = *(int*)&buffer[punter];//---------------0
		punter += sizeof(int);
		printf("%d", length);
		for (int i = 0; i < length; i++)
		{
			int str_len = *(int*)&buffer[punter];//-----------1
			punter += sizeof(int);
			ScoreInfo aux;
			for (int j = 0; j < str_len; j++) {
				aux.teamName.push_back(buffer[punter + j]);//------------------------------------------------------------2
			}
			punter += sizeof(std::string);
			aux.punctuation = *(int*)&buffer[punter];//--------3
			punter += sizeof(int);
			ladder.push_back(aux);
		}
	}
}


