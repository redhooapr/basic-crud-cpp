#include <iostream>
#include <fstream>
#include <limits>
#include "crud.h"

int main() {
	std::fstream data;
	int input;
	char isContinue;

	crud::checkdata(data);

	enum choice {CREATE = 1, READ, UPDATE, DELETE, FINISH};
	input = crud::getOptions();

	while(input != FINISH) {
		switch(input) {
			case CREATE:
				std::cout << "========= Create Mode =========\n";
				crud::addDataMahasiswa(data);
				break;
			case READ:
				std::cout << "========== Read Mode ==========\n";
				crud::displayDataMahasiswa(data);
				break;
			case UPDATE:
				std::cout << "========= Update Mode =========\n";
				crud::updateDataMahasiswa(data);
				break;
			case DELETE:
				std::cout << "========= Delete Mode =========\n";
				crud::deleteDataMahasiswa(data);
				break;
			default:
				std::cout << "======== Wrong Command ========\n";
				break;
		}
		label_options:

		std::cout << "Continue (y/n) ? ";
		std::cin >> isContinue;

		if(isContinue == 'y' | isContinue == 'Y') {
			input = crud::getOptions();
		}else if(isContinue == 'n' | isContinue == 'N') {
			break;
		}else {
			goto label_options;
		}
	}

	std::cout << "******** End Of Program ********\n";

	return 0;
}
