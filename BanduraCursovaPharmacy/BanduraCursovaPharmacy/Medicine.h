#pragma once
#include <stdexcept>
#include <String.h>
// підключення просторів імен std і System
using namespace std;
//using namespace System;
// оголошення класу
ref class Medicine {
	//закриті поля класу для збереження даних про лікарства
	System::String^ name;
	System::String^ pharmGroup;
	System::String^ activeSubstance;
	int term;
	float price;
	int distributorID;
	int id;
public: // відкриті члени класу
	Medicine() {}// порожній конструктор
// конструктор ініціалізаціі полів об’єктів класу
	Medicine(System::String^ n, System::String^ ph, System::String^ a, int t, float pr, int d, int i) {
		this->name = n;
		this->pharmGroup = ph;
		this->activeSubstance = a;
		this->term = t;
		this->price = pr;
		this->distributorID = d;
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
		else throw invalid_argument("Невірна назва ліків");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getName() {
		return this->name;
	}

	void setPharmGroup(System::String^ pharmGroup) {
		if (pharmGroup->Length != 0) {
			this->pharmGroup = pharmGroup;
		}
		else throw invalid_argument("Невірна назва фармацевтичної групи");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getPharmGroup() {
		return this->pharmGroup;
	}

	void setActiveSubstance(System::String^ activeSubstance) {
		if (activeSubstance->Length != 0) {
			this->activeSubstance = activeSubstance;
		}
		else throw invalid_argument("Невірна назва діючої речовини");
		// обробка помилки при спробі залишити поле порожнім
	}
	System::String^ getActiveSubstance() {
		return this->activeSubstance;
	}

	void setTerm(int term) {
		if (term > 0) {
			this->term = term;
		}
		else throw invalid_argument("Невірний термін");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getTerm() {
		return this->term;
	}

	void setPrice(float price) {
		if (price > 0) {
			this->price = price;
		}
		else throw invalid_argument("Невірна ціна ліків");
		// обробка помилки при спробі залишити поле порожнім
	}
	float getPrice() {
		return this->price;
	}

	void setDistributorID(int distributorID) {
		if (distributorID > 0) {
			this->distributorID = distributorID;
		}
		else throw invalid_argument("Невірне id виробника ліків");
		// обробка помилки при спробі залишити поле порожнім
	}
	int getDistributorID() {
		return this->distributorID;
	}

	void setId(int id) {
		if (id > 0) {
			this->id = id;
		}
		else throw invalid_argument("Невірний id ліків");
		// обробка помилки при спробі ввести код запису, менший рівний 0
	}
	int getId() {
		return this->id;
	}
};
