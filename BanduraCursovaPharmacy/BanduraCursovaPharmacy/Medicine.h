#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Medicine {
	//������ ���� ����� ��� ���������� ����� ��� ��������
	System::String^ name;
	System::String^ pharmGroup;
	System::String^ activeSubstance;
	int term;
	float price;
	int distributorID;
	int id;
public: // ������ ����� �����
	Medicine() {}// ������� �����������
// ����������� ����������� ���� �ᒺ��� �����
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
		else throw invalid_argument("������ id");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}

	void setName(System::String^ name) {
		if (name->Length != 0) {
			this->name = name;
		}
		else throw invalid_argument("������ ����� ���");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getName() {
		return this->name;
	}

	void setPharmGroup(System::String^ pharmGroup) {
		if (pharmGroup->Length != 0) {
			this->pharmGroup = pharmGroup;
		}
		else throw invalid_argument("������ ����� ������������� �����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getPharmGroup() {
		return this->pharmGroup;
	}

	void setActiveSubstance(System::String^ activeSubstance) {
		if (activeSubstance->Length != 0) {
			this->activeSubstance = activeSubstance;
		}
		else throw invalid_argument("������ ����� ���� ��������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getActiveSubstance() {
		return this->activeSubstance;
	}

	void setTerm(int term) {
		if (term > 0) {
			this->term = term;
		}
		else throw invalid_argument("������� �����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getTerm() {
		return this->term;
	}

	void setPrice(float price) {
		if (price > 0) {
			this->price = price;
		}
		else throw invalid_argument("������ ���� ���");
		// ������� ������� ��� ����� �������� ���� �������
	}
	float getPrice() {
		return this->price;
	}

	void setDistributorID(int distributorID) {
		if (distributorID > 0) {
			this->distributorID = distributorID;
		}
		else throw invalid_argument("������ id ��������� ���");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getDistributorID() {
		return this->distributorID;
	}

	void setId(int id) {
		if (id > 0) {
			this->id = id;
		}
		else throw invalid_argument("������� id ���");
		// ������� ������� ��� ����� ������ ��� ������, ������ ����� 0
	}
	int getId() {
		return this->id;
	}
};
