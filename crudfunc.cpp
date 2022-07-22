#include <iostream>
#include <fstream>
#include <limits>
#include "crud.h"

void crud::checkdata(std::fstream &data) {
		data.open("data.bin", std::ios::in | std::ios::out | std::ios::binary);

		if(data.is_open()) {
			std::cout << "status: data exist\n";
		}else {
			data.close();
			std::cout << "status: file not found\n";
			data.open("data.bin", std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
		}
	}

int crud::getOptions() {
	int choice;

	system("cls");
	std::cout << "================================\n";
	std::cout << "===== CRUD DATA MAHASISWA ======\n";
	std::cout << "================================\n";
	std::cout << "1. Tambah Data Mahasiswa\n";
	std::cout << "2. Tampilkan Data Mahasiswa\n";
	std::cout << "3. Update Data Mahasiswa\n";
	std::cout << "4. Hapus Data Mahasiswa\n";
	std::cout << "5. Akhiri Program\n";
	std::cout << "================================\n";
	std::cout << "Pilih Angka [1-5] ? ";
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

	return choice;
}

void crud::writedata(std::fstream &data, int position, crud::Mahasiswa &input) {
	data.seekp((position - 1)*sizeof(crud::Mahasiswa), std::ios::beg);
	data.write(reinterpret_cast<char*>(&input), sizeof(crud::Mahasiswa));
}

crud::Mahasiswa crud::readData(std::fstream &data, int position) {
	crud::Mahasiswa readMahasiswa;
	data.seekp((position - 1)*sizeof(crud::Mahasiswa), std::ios::beg);
	data.read(reinterpret_cast<char*>(&readMahasiswa), sizeof(crud::Mahasiswa));
	return readMahasiswa;
}

int crud::getDataSize(std::fstream &data) {
	int start, end;

	data.seekg(0, std::ios::beg);
	start = data.tellg();
	data.seekg(0, std::ios::end);
	end = data.tellg();

	return (end - start) / sizeof(crud::Mahasiswa);
}

void crud::displayDataMahasiswa(std::fstream &data) {
	crud::Mahasiswa showMahasiswa;
	int size = crud::getDataSize(data);
	std::cout << "No.\tPK.\tNIM.\tNama.\t\tJurusan.\n";
	for(int i = 1; i <= size; i++) {
		showMahasiswa = crud::readData(data, i);
		std::cout << i << "\t";
		std::cout << showMahasiswa.pk << "\t";
		std::cout << showMahasiswa.NIM << "\t";
		std::cout << showMahasiswa.nama << "\t";
		std::cout << showMahasiswa.jurusan << std::endl;
	}
}

void crud::addDataMahasiswa(std::fstream &data) {
	crud::Mahasiswa inputMahasiswa;
	crud::Mahasiswa lastMahasiswa;

	int size = crud::getDataSize(data);

	std::cout << "Data size : " << size << std::endl;

	if(size == 0) {
		inputMahasiswa.pk = 1;
	}else {
		lastMahasiswa = crud::readData(data, size);
		inputMahasiswa.pk = lastMahasiswa.pk + 1;
	}

	std::cout << "Nama    : ";
	std::cin.get(inputMahasiswa.nama, 25);
	std::cin.ignore();
	std::cout << "Jurusan : ";
	std::cin.get(inputMahasiswa.jurusan, 25);
	std::cin.ignore(); 
	std::cout << "NIM     : ";
	std::cin.get(inputMahasiswa.NIM, 25);
	std::cin.ignore();

	crud::writedata(data, size + 1, inputMahasiswa);
}

void crud::updateDataMahasiswa(std::fstream &data) {
	crud::Mahasiswa updateMahasiswa;
	int nomor;

	std::cout << "Number of data : ";
	std::cin >> nomor;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	updateMahasiswa = crud::readData(data, nomor);

	std::cout << "Data Selected : \n";
	std::cout << "Nama    : " << updateMahasiswa.nama << std::endl;
	std::cout << "NIM     : " << updateMahasiswa.NIM << std::endl;
	std::cout << "Jurusan : " << updateMahasiswa.jurusan << std::endl;

	std::cout << "\nData Edit : \n";
	std::cout << "Nama : ";
	std::cin.get(updateMahasiswa.nama, 25);
	std::cin.ignore();
	std::cout << "NIM : ";
	std::cin.get(updateMahasiswa.NIM, 25);
	std::cin.ignore();
	std::cout << "Jurusan : ";
	std::cin.get(updateMahasiswa.jurusan, 25);
	std::cin.ignore();

	crud::writedata(data, nomor, updateMahasiswa);
}

void crud::deleteDataMahasiswa(std::fstream &data) {
	int number, size, offset;
	crud::Mahasiswa blankMahasiswa, tempMahasiswa;
	std::fstream tempData;

	size = crud::getDataSize(data);

	std::cout << "Number Delete : ";
	std::cin >> number;

	crud::writedata(data, number, blankMahasiswa);
	tempData.open("temp.dat", std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);

	offset = 0;

	for(int i = 1; i <= size; i++) {
		tempMahasiswa = readData(data, i);
		if(tempMahasiswa.nama[0] != 0) {
			crud::writedata(tempData, i - offset, tempMahasiswa);
		}else {
			offset++;
			std::cout << "deleted item" << std::endl;
		}
	}

	size = crud::getDataSize(tempData);
	data.close();
	data.open("data.bin", std::ios::trunc | std::ios::out | std::ios::binary);
	data.close();
	data.open("data.bin", std::ios::out | std::ios::in | std::ios::binary);

	for(int i = 1; i <= size; i++) {
		tempMahasiswa = readData(tempData, i);
		crud::writedata(data, i, tempMahasiswa);
	}
}	