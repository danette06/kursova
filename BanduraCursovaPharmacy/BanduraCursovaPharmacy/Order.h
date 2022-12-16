#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Order {
	//������ ���� ����� ��� ���������� ����� ��� ��������
	System::DateTime date;
	int count;
	int pharmacyID;
	int medicineID;
	int id;
public: // ������ ����� �����
	Order() {}// ������� �����������
// ����������� ����������� ���� �ᒺ��� �����
	Order(System::DateTime d, int c, int p, int m, int i) {
		this->count = c;
		this->pharmacyID = p;
		this->medicineID = m;
		this->date = d;
		if (i > 0) {
			this->id = i;
		}
		else throw invalid_argument("������ id");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}

	void setCount(int count) {
		if (count > 0) {
			this->count = count;
		}
		else throw invalid_argument("������ �������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getCount() {
		return this->count;
	}

	void setPharmacyID(int pharmacyID) {
		if (pharmacyID > 0) {
			this->pharmacyID = pharmacyID;
		}
		else throw invalid_argument("������ id ������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getPharmacyID() {
		return this->pharmacyID;
	}

	void setMedicineID(int medicineID) {
		if (medicineID > 0) {
			this->medicineID = medicineID;
		}
		else throw invalid_argument("������ id ���");
		// ������� ������� ��� ����� �������� ���� �������
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
		else throw invalid_argument("������� id �볺���");
		// ������� ������� ��� ����� ������ ��� ������, ������ ����� 0
	}
	int getId() {
		return this->id;
	}
};
