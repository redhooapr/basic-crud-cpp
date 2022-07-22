#include <fstream>

namespace crud {
	struct Mahasiswa {
		int pk;
		char nama[25];
		char NIM[25];
		char jurusan[25];
	};

	int getOptions();
	void checkdata(std::fstream &data);
	void writedata(std::fstream &data, int position, Mahasiswa &input);
	Mahasiswa readData(std::fstream &data, int position);
	int getDataSize(std::fstream &data);
	void addDataMahasiswa(std::fstream &data);
	void displayDataMahasiswa(std::fstream &data);
	void updateDataMahasiswa(std::fstream &data);
	void deleteDataMahasiswa(std::fstream &data);
}