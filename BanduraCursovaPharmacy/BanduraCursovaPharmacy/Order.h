#pragma once
#include <stdexcept>
#include <String.h>
// підключення просторів імен std і System
using namespace std;
//using namespace System;
// оголошення класу
ref class Order {
	//закриті поля класу для збереження даних про поставки
	System::DateTime date;
	int count;
	int pharmacyID;
	int medicineID;
	int id;
public: // відкриті члени класу
	Order() {}// порожній конструктор
// конструктор ініціалізаціі полів об’єктів класу
	Order(System::DateTime d, int c, int p, int m, int i) {
		this->count = c;
		this->pharmacyID = p;
		this->medicineID = m;
		this->date = d;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("Невірне id");
		// обробка помилки при спробі ввести код запису, менший або рівний 0
	}

	void setCount(int count) {
		if (count > 0) {
			this->count = count;
		}
		else throw invalid_argument("Невірна кількість");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getCount() {
		return this->count;
	}

	void setPharmacyID(int pharmacyID) {
		if (pharmacyID > 0) {
			this->pharmacyID = pharmacyID;
		}
		else throw invalid_argument("Невірне id аптеки");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getPharmacyID() {
		return this->pharmacyID;
	}

	void setMedicineID(int medicineID) {
		if (medicineID > 0) {
			this->medicineID = medicineID;
		}
		else throw invalid_argument("Невірне id ліків");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getMedicineID() {
		return this->medicineID;
	}

	void setDate(System::DateTime date) {
		this->date = date;
	}
	System::DateTime getDate() {
		return this->date;
	}

	void setId(int id) {
		if (id > 0) {
			this->id = id;
		}
		else throw invalid_argument("Невірний id клієнта");
		// обробка помилки при спробі ввести код запису, менший рівний 0
	}
	int getId() {
		return this->id;
	}
};
