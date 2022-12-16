#pragma once
#include <stdexcept>
#include <String.h>
// ���������� �������� ���� std � System
using namespace std;
//using namespace System;
// ���������� �����
ref class Distributor {
	//������ ���� ����� ��� ���������� ����� ��� ��������� ���
	System::String^ name;
	System::String^ country;
	System::String^ gmail;
	int id;
public: // ������ ����� �����
	Distributor() {} // ������� �����������
	// ����������� ����������� ���� �ᒺ��� �����
	Distributor(System::String^ n, System::String^ c, System::String^ g, int i) {
		this->name = n;
		this->country = c;
		this->gmail = g;
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
		else throw invalid_argument("������ ����� ��������� ���");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getName() {
		return this->name;
	}
	void setCountry(System::String^ country) {
		if (country->Length != 0) {
			this->country = country;
		}
		else throw invalid_argument("������ ����� �����");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getCountry() {
		return this->country;
	}
	void setGmail(System::String^ gmail) {
		if (gmail->Length != 0) {
			this->gmail = gmail;
		}
		else throw invalid_argument("������ ���������� ������");
		// ������� ������� ��� ����� �������� ���� �������
	}
	System::String^ getGmail() {
		return this->gmail;
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
