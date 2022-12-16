#pragma once
#include "EditPharmacy.h"
#include "Pharmacy.h"
#include <stdlib.h>

namespace BanduraCursovaPharmacy {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for PharmacyForm
	/// </summary>
	public ref class PharmacyForm : public System::Windows::Forms::Form
	{
	private: List<Pharmacy^>^ pharmacyList;
		   SqlCeConnection^ connect;
	public:
		PharmacyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf";
			connect = gcnew SqlCeConnection(dbEngine->LocalConnectionString);
			pharmacyList = gcnew List<Pharmacy^>();
		}
		// метод відображення на формі даних про аптеки
		void getPharmacy() {
			connect->Open();
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT * FROM pharmacy";
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			pharmacyList->Clear();
			while (sqlRead->Read()) {
				pharmacyList->Add(gcnew Pharmacy(
					System::Convert::ToString(sqlRead["p_name"]),
					System::Convert::ToString(sqlRead["p_address"]),
					System::Convert::ToInt32(sqlRead["p_worker_count"]),
					System::Convert::ToInt32(sqlRead["p_id"])
				));
			}
			connect->Close();
			this->updateTable();
		}

		//метод передачі запиту до БД на виконання
		void execute(System::String^ query) {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			command->ExecuteNonQuery();
			connect->Close();
		}

		// метод оновлення таблиці dataGridView
		void updateTable() {
			int i = 0;
			dataGridView1->Rows->Clear();
			for each (Pharmacy ^ pharmacy in pharmacyList) {
				this->dataGridView1->Rows->Add();
				this->dataGridView1->Rows[i]->Cells[0]->Value = pharmacy->getId();
				this->dataGridView1->Rows[i]->Cells[1]->Value = pharmacy->getName();
				this->dataGridView1->Rows[i]->Cells[2]->Value = pharmacy->getAddress();
				this->dataGridView1->Rows[i]->Cells[3]->Value = pharmacy->getWorkerCount();
				++i;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PharmacyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button3;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(575, 325);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(210, 69);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Видалити запис";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &PharmacyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(49, 325);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(204, 69);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Редагувати запис";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &PharmacyForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(307, 325);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(204, 69);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Додати запис";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &PharmacyForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Info;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Column4,
					this->Column1, this->Column2, this->Column3
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 12);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(819, 307);
			this->dataGridView1->TabIndex = 4;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Номер аптеки";
			this->Column4->MinimumWidth = 6;
			this->Column4->Name = L"Column4";
			this->Column4->Width = 125;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Назва аптеки";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 125;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Адреса аптеки";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->Width = 125;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Кількість співробітників";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->Width = 200;
			// 
			// PharmacyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(842, 410);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"PharmacyForm";
			this->Text = L"Аптеки";
			this->Load += gcnew System::EventHandler(this, &PharmacyForm::PharmacyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		//Запрограмовування відображення даних при запуску форми
	private: System::Void PharmacyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		this->getPharmacy();
	}
	// Запрограмовування кнопки Редагувати запис
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		EditPharmacy^ edit = gcnew EditPharmacy(System::Convert::ToInt32(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value));
		edit->ShowDialog();
		this->getPharmacy();
	}
	// Запрограмовування кнопки Додати запис
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		EditPharmacy^ edit = gcnew EditPharmacy(-1);
		edit->ShowDialog();
		this->getPharmacy();
	}
	// Запрограмовування кнопки Видалити запис
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			System::String^ query = "DELETE FROM pharmacy WHERE [p_id]=" +
				System::Convert::ToString(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value);
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Видалено!");
			}
			connect->Close();
			this->getPharmacy();
		}
		catch (...) {
			MessageBox::Show("Виберіть конкретний запис");
		}
	}

};
}
