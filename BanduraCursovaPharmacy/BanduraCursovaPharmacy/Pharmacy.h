#pragma once
#include <stdexcept>
#include <String.h>
// підключення просторів імен std і System
using namespace std;
//using namespace System;
// оголошення класу
ref class Pharmacy {
	//закриті поля класу для збереження даних про аптеки
	System::String^ name;
	System::String^ address;
	int workerCount;
	int id;
public: // відкриті члени класу
	Pharmacy() {} // порожній конструктор
	// конструктор ініціалізації полів об’єктів класу
	Pharmacy(System::String^ n, System::String^ a, int w, int i) {
		this->name = n;
		this->address = a;
		this->workerCount = w;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("Невірне id");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}
	void setName(System::String^ name) {
		if (name->Length != 0) {
			this->name = name;
		}
		else throw invalid_argument("Невірна назва аптеки");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getName() {
		return this->name;
	}
	void setAddress(System::String^ address) {
		if (address->Length != 0) {
			this->address = address;
		}
		else throw invalid_argument("Невірна адреса");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getAddress() {
		return this->address;
	}
	void setWorkerCount(int workerCount) {
		if (workerCount > 0) {
			this->workerCount = workerCount;
		}
		else throw invalid_argument("Невірна кількість працівників");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getWorkerCount() {
		return this->workerCount;
	}
	void setId(int id) {
		if (id > 0) {
			this->id = id;
		}
		else throw invalid_argument("Невірне id");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}
	int getId() {
		return this->id;
	}
};
