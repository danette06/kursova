#pragma once

namespace BanduraCursovaPharmacy {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;

	/// <summary>
	/// Summary for EditMedicine
	/// </summary>
	public ref class EditMedicine : public System::Windows::Forms::Form
	{
		System::Data::SqlServerCe::SqlCeConnection^ connect;
		int medicineId;
		int distributorId;
	public:
		EditMedicine(int temp, int distributorid)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf;";
			connect = gcnew SqlCeConnection("Data Source=PharmacyDB.sdf;");
			this->medicineId = -1;
			this->distributorId = distributorid;
			textBox1->Text = "";
			textBox2->Text = "";
			textBox3->Text = "";
			textBox4->Text = "";
			connect->Open();
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT d_name FROM distributor";
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				comboBox2->Items->Add(System::Convert::ToString(sqlRead["d_name"]));
			}
			connect->Close();
			sqlRead->Close();
		}
		EditMedicine(int mId) {
			InitializeComponent();
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf;";
			connect = gcnew SqlCeConnection("Data Source=PharmacyDB.sdf;");
			connect->Open();
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT d_name FROM distributor";
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				comboBox2->Items->Add(System::Convert::ToString(sqlRead["d_name"]));
			}
			connect->Close();
			sqlRead->Close();
			this->medicineId = mId;
			int distributor;
			connect->Open();
			SqlCeCommand^ command2 = connect->CreateCommand();
			command2->CommandText = "SELECT * FROM medicine WHERE [m_id]=@mId";
			command2->Parameters->AddWithValue("@mId", mId);
			SqlCeDataReader^ sqlRead2 = command2->ExecuteReader();
			while (sqlRead2->Read()) {
				textBox1->Text = System::Convert::ToString(sqlRead2["m_name"]);
				comboBox1->Text = System::Convert::ToString(sqlRead2["m_pharm_group"]);
				textBox2->Text = System::Convert::ToString(sqlRead2["m_active_substance"]);
				textBox3->Text = System::Convert::ToString(sqlRead2["m_term"]);
				textBox4->Text = System::Convert::ToString(sqlRead2["m_price"]);
				distributor = System::Convert::ToInt32(sqlRead2["m_distributor_id"]);
			}
			connect->Close();
			sqlRead2->Close();
			this->currComboBoxSet(distributor);
		}
		void currComboBoxSet(int id)
		{
			connect->Open();
			System::String^ query = "SELECT d_name FROM distributor WHERE d_id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				comboBox2->Text = System::Convert::ToString(sqlRead["d_name"]);
			}
			connect->Close();
			sqlRead->Close();
		}

		int getCurrComboBox()
		{
			int id;
			connect->Open();
			System::String^ queryS = "SELECT d_id FROM distributor WHERE d_name LIKE '" + comboBox2->Text + "';";
			SqlCeCommand^ commandS = connect->CreateCommand();
			commandS->CommandText = queryS;
			SqlCeDataReader^ sqlReadS = commandS->ExecuteReader();
			bool hasRow = sqlReadS->Read();
			if (hasRow) {
				id = System::Convert::ToInt32(sqlReadS["d_id"]);
			}
			sqlReadS->Close();
			connect->Close();
			return id;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditMedicine()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox3;
	protected:
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ comboBox1;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox2;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Label^ label6;

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
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(304, 156);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(194, 34);
			this->textBox3->TabIndex = 86;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(12, 116);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(235, 29);
			this->label3->TabIndex = 85;
			this->label3->Text = L"Активна речовина";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"від застуди", L"від кашлю", L"від температури",
					L"від болю в животі", L"знеболюючі", L"харчові добавки"
			});
			this->comboBox1->Location = System::Drawing::Point(303, 61);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(194, 28);
			this->comboBox1->TabIndex = 84;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(270, 326);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(211, 63);
			this->button2->TabIndex = 82;
			this->button2->Text = L"Відміна";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &EditMedicine::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(43, 326);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(211, 63);
			this->button1->TabIndex = 81;
			this->button1->Text = L"Зберегти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &EditMedicine::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(303, 111);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(194, 34);
			this->textBox2->TabIndex = 80;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(12, 222);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(67, 29);
			this->label5->TabIndex = 78;
			this->label5->Text = L"Ціна";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(304, 6);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(194, 34);
			this->textBox1->TabIndex = 77;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(12, 61);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(289, 29);
			this->label2->TabIndex = 76;
			this->label2->Text = L"Фармацептична група";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(86, 29);
			this->label1->TabIndex = 75;
			this->label1->Text = L"Назва";
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(12, 156);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(286, 66);
			this->label4->TabIndex = 87;
			this->label4->Text = L"Термін придатності в місяцях";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(303, 217);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(194, 34);
			this->textBox4->TabIndex = 88;
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(303, 268);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(194, 28);
			this->comboBox2->TabIndex = 90;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(12, 268);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(132, 29);
			this->label6->TabIndex = 89;
			this->label6->Text = L"Виробник";
			// 
			// EditMedicine
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(517, 408);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"EditMedicine";
			this->Text = L"Новий препарат";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void insert() {
		try {
			int dCB = this->getCurrComboBox();
			connect->Open();
			System::String^ query = "INSERT INTO medicine([m_name], [m_pharm_group], [m_active_substance], [m_term], [m_price], [m_distributor_id])" + 
				"VALUES('" + textBox1->Text + "', '" + comboBox1->Text + "', '" + textBox2->Text + "', " + textBox3->Text + ", " + textBox4->Text + ", " + dCB + ");";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Добавлено!");
			}
			else MessageBox::Show("Введіть усі данні!");
			connect->Close();
		}
		catch (...)
		{
			MessageBox::Show("Дані введено не правильно");
		}
	}
	private: void update() {
		try {
			int dID = this->getCurrComboBox();
			connect->Open();
			System::String^ query = "UPDATE medicine SET [m_name]='" + textBox1->Text + "', [m_pharm_group]='" + comboBox1->Text + "', [m_active_substance]='" + textBox2->Text + "', [m_term]=" + textBox3->Text + ", [m_price]=" + textBox4->Text + ", [m_distributor_id]=" + dID + " WHERE [m_id]=" + this->medicineId + ";";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			if (command->ExecuteNonQuery() == 0) {
				MessageBox::Show("Оновлено!");
			}
			connect->Close();
		}
		catch (...)
		{
			MessageBox::Show("Дані введено не правильно");
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text->Length != 0 && comboBox1->Text->Length != 0 && textBox2->Text->Length != 0 && textBox3->Text->Length != 0 && textBox4->Text->Length != 0 && comboBox2->Text->Length != 0) {
			if (this->medicineId == -1) insert();
			else update();
			this->Close();
		}
		else {
			MessageBox::Show("Введіть більше даних");
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
