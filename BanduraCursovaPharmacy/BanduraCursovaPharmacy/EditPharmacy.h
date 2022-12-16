#pragma once

namespace BanduraCursovaPharmacy {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;

	/// <summary>
	/// Summary for EditPharmacy
	/// </summary>
	public ref class EditPharmacy : public System::Windows::Forms::Form
	{
		System::Data::SqlServerCe::SqlCeConnection^ connect;
		int pharmacyId;
	public:
		EditPharmacy(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		EditPharmacy(int pId) {
			InitializeComponent();
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf";
			connect = gcnew SqlCeConnection("Data Source=PharmacyDB.sdf");
			connect->Open();
			this->pharmacyId = pId;
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT * FROM pharmacy WHERE [p_id]=@pId";
			command->Parameters->AddWithValue(
				"@pId",
				pId
			);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				textBox1->Text = System::Convert::ToString(sqlRead["p_name"]);
				textBox2->Text = System::Convert::ToString(sqlRead["p_address"]);
				textBox3->Text = System::Convert::ToString(sqlRead["p_worker_count"]);
			}
			connect->Close();
			sqlRead->Close();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditPharmacy()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button2;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label3;

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
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(229, 202);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(211, 63);
			this->button2->TabIndex = 15;
			this->button2->Text = L"Відміна";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &EditPharmacy::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(12, 202);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(211, 63);
			this->button1->TabIndex = 14;
			this->button1->Text = L"Зберегти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &EditPharmacy::button1_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(229, 140);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(194, 34);
			this->textBox3->TabIndex = 13;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(229, 74);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(194, 47);
			this->textBox2->TabIndex = 12;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(229, 4);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(194, 34);
			this->textBox1->TabIndex = 11;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(12, 74);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(193, 41);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Адреса аптеки";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(177, 29);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Назва аптеки";
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(12, 124);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(211, 66);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Кількість співробітників";
			// 
			// EditPharmacy
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(461, 303);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"EditPharmacy";
			this->Text = L"Нова аптека";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Редагування запису
	private: void update() {
		try {
			connect->Open();
			System::String^ query = "UPDATE pharmacy SET [p_name]='" + textBox1->Text + "', [p_address]='" + textBox2->Text + "', [p_worker_count]='" + textBox3->Text + "' WHERE [p_id]=" + this->pharmacyId + ";";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			if (command->ExecuteNonQuery() == 0) {
				MessageBox::Show("Змінено!");
			}
			connect->Close();
		}
		catch (...) {
			MessageBox::Show("Щось введено не правильно");
			this->Close();
		}
	}
		   // Добавлення запису
	private: void insert() {
		try {
			connect->Open();
			System::String^ query = "INSERT INTO pharmacy([p_name], [p_address], [p_worker_count])" +
				"VALUES('" + textBox1->Text + "','" + textBox2->Text + "','" + textBox3->Text + "');";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Добавлено!");
			}
			connect->Close();
		}
		catch (...) {
			MessageBox::Show("Щось введено не правильно");
			this->Close();
		}
	}

	//Кнопка збереження даних
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text->Length != 0 && textBox2->Text->Length != 0 && textBox3->Text->Length != 0) {
			if (this->pharmacyId == -1)
			{
				try {
					insert();
				}
				catch (...)
				{
					MessageBox::Show("Щось введено не правильно");
					this->Close();
				}
			}
			else
			{
				try {
					update();
				}
				catch (...)
				{
					MessageBox::Show("Щось введено не правильно");
					this->Close();
				}

			}
			this->Close();
		}
		else {
			MessageBox::Show("Добавте більше даних");
		}
	}

	//Кнопка відміни
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
