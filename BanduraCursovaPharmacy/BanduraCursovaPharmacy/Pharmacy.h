#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Pharmacy {
	//������ ���� ����� ��� ���������� ����� ��� ������
	System::String^ name;
	System::String^ address;
	int workerCount;
	int id;
public: // ������ ����� �����
	Pharmacy() {} // ������� �����������
	// ����������� ����������� ���� �ᒺ��� �����
	Pharmacy(System::String^ n, System::String^ a, int w, int i) {
		this->name = n;
		this->address = a;
		this->workerCount = w;
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
		else throw invalid_argument("������ ����� ������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getName() {
		return this->name;
	}
	void setAddress(System::String^ address) {
		if (address->Length != 0) {
			this->address = address;
		}
		else throw invalid_argument("������ ������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getAddress() {
		return this->address;
	}
	void setWorkerCount(int workerCount) {
		if (workerCount > 0) {
			this->workerCount = workerCount;
		}
		else throw invalid_argument("������ ������� ����������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	int getWorkerCount() {
		return this->workerCount;
	}
	void setId(int id) {
		if (id > 0) {
			this->id = id;
		}
		else throw invalid_argument("������ id");
		// ������� ������� ��� ����� ������ ��� ������, ������ ��� ����� 0
	}
	int getId() {
		return this->id;
	}
};
