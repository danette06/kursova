#pragma once
#include <stdexcept>
#include <String.h>
// підключення просторів імен std і System
using namespace std;
//using namespace System;
// оголошення класу
ref class Distributor {
	//закриті поля класу для збереження даних про виробників ліків
	System::String^ name;
	System::String^ country;
	System::String^ gmail;
	int id;
public: // відкриті члени класу
	Distributor() {} // порожній конструктор
	// конструктор ініціалізації полів об’єктів класу
	Distributor(System::String^ n, System::String^ c, System::String^ g, int i) {
		this->name = n;
		this->country = c;
		this->gmail = g;
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
		else throw invalid_argument("Невірна назва виробника ліків");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getName() {
		return this->name;
	}
	void setCountry(System::String^ country) {
		if (country->Length != 0) {
			this->country = country;
		}
		else throw invalid_argument("Невірна назва країни");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getCountry() {
		return this->country;
	}
	void setGmail(System::String^ gmail) {
		if (gmail->Length != 0) {
			this->gmail = gmail;
		}
		else throw invalid_argument("Невірна електронна адреса");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getGmail() {
		return this->gmail;
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
