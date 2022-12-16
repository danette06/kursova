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
	/// Summary for EditOrder
	/// </summary>
	public ref class EditOrder : public System::Windows::Forms::Form
	{
		System::Data::SqlServerCe::SqlCeConnection^ connect;
		int orderId;
		int medicineId;
		int pharmacyId;
	public:
		EditOrder(int temp, int pharmacyid)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf;";
			connect = gcnew SqlCeConnection("Data Source=PharmacyDB.sdf;");
			this->orderId = -1;
			this->pharmacyId = pharmacyid;
			textBox1->Text = "";
			textBox2->Text = "";
			connect->Open();
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT p_name FROM pharmacy";
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				comboBox1->Items->Add(System::Convert::ToString(sqlRead["p_name"]));
			}
			connect->Close();
			sqlRead->Close();
		}
		EditOrder(int oId) {
			InitializeComponent();
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf;";
			connect = gcnew SqlCeConnection("Data Source=PharmacyDB.sdf;");
			connect->Open();
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT p_name FROM pharmacy";
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				comboBox1->Items->Add(System::Convert::ToString(sqlRead["p_name"]));
			}
			connect->Close();
			sqlRead->Close();
			this->orderId = oId;
			int pharmacy;
			int medicine;
			connect->Open();
			SqlCeCommand^ command2 = connect->CreateCommand();
			command2->CommandText = "SELECT * FROM [order] WHERE [o_id]=@oId";
			command2->Parameters->AddWithValue("@oId", oId);
			SqlCeDataReader^ sqlRead2 = command2->ExecuteReader();
			while (sqlRead2->Read()) {
				textBox1->Text = System::Convert::ToString(sqlRead2["o_count"]);
				medicine = System::Convert::ToInt32(sqlRead2["o_medicine_ID"]);
				dateTimePicker1->Text = System::Convert::ToString(sqlRead2["o_date"]);
				pharmacy = System::Convert::ToInt32(sqlRead2["o_pharmacy_ID"]);
			}
			connect->Close();
			sqlRead2->Close();
			this->currComboBoxSet(pharmacy);
			this->currTextBox2Set(medicine);
		}
		void currComboBoxSet(int id)
		{
			connect->Open();
			System::String^ query = "SELECT p_name FROM pharmacy WHERE p_id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				comboBox1->Text = System::Convert::ToString(sqlRead["p_name"]);
			}
			connect->Close();
			sqlRead->Close();
		}

		void currTextBox2Set(int id)
		{
			connect->Open();
			System::String^ query = "SELECT m_name FROM medicine WHERE m_id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				textBox2->Text = System::Convert::ToString(sqlRead["m_name"]);
			}
			connect->Close();
			sqlRead->Close();
		}

		int getCurrComboBox()
		{
			int id;
			connect->Open();
			System::String^ queryS = "SELECT p_id FROM pharmacy WHERE p_name LIKE '" + comboBox1->Text + "';";
			SqlCeCommand^ commandS = connect->CreateCommand();
			commandS->CommandText = queryS;
			SqlCeDataReader^ sqlReadS = commandS->ExecuteReader();
			bool hasRow = sqlReadS->Read();
			if (hasRow) {
				id = System::Convert::ToInt32(sqlReadS["p_id"]);
			}
			sqlReadS->Close();
			connect->Close();
			return id;
		}
		int getMedicineID()
		{
			int ClientID;
			connect->Open();
			System::String^ queryForClientID = "SELECT m_id FROM medicine WHERE m_name LIKE '" + textBox2->Text + "';";
			SqlCeCommand^ commandForClientID = connect->CreateCommand();
			commandForClientID->CommandText = queryForClientID;
			SqlCeDataReader^ sqlRead = commandForClientID->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow)
			{
				ClientID = System::Convert::ToInt32(sqlRead["m_id"]);
			}
			sqlRead->Close();
			connect->Close();
			return ClientID;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditOrder()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label3;
	protected:
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;

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
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(13, 76);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(148, 29);
			this->label3->TabIndex = 85;
			this->label3->Text = L"Назва ліків";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(305, 132);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(194, 28);
			this->comboBox1->TabIndex = 84;
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->CustomFormat = L"MM.dd.yyyy";
			this->dateTimePicker1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dateTimePicker1->Location = System::Drawing::Point(304, 184);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(195, 27);
			this->dateTimePicker1->TabIndex = 83;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(260, 235);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(211, 63);
			this->button2->TabIndex = 82;
			this->button2->Text = L"Відміна";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &EditOrder::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(33, 235);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(211, 63);
			this->button1->TabIndex = 81;
			this->button1->Text = L"Зберегти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &EditOrder::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(305, 71);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(194, 34);
			this->textBox2->TabIndex = 80;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(13, 132);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(173, 29);
			this->label4->TabIndex = 79;
			this->label4->Text = L"назва аптеки";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(13, 182);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(193, 29);
			this->label5->TabIndex = 78;
			this->label5->Text = L"Дата поставки";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(305, 16);
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
			this->label2->Location = System::Drawing::Point(12, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(130, 29);
			this->label2->TabIndex = 76;
			this->label2->Text = L"Кількість ";
			// 
			// EditOrder
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(530, 321);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Name = L"EditOrder";
			this->Text = L"Нова поставка";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: void insert() {
			try {
				int pID = this->getCurrComboBox();
				int mID = this->getMedicineID();
				connect->Open();
				System::String^ query = "INSERT INTO [order]([o_count], [o_pharmacy_id], [o_medicine_id], [o_date])" +
					"VALUES('" + textBox1->Text + "', " + pID + ", " + mID + ", '" + dateTimePicker1->Text + "');";
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
			int pID = this->getCurrComboBox();
			int mID = this->getMedicineID();
			connect->Open();
			System::String^ query = "UPDATE [order] SET [o_count]='" + textBox1->Text + "', [o_pharmacy_id]=" + pID + ", [o_medicine_id]=" + mID + ", [o_date]='" + dateTimePicker1->Text + "' WHERE [o_id]=" + this->orderId + ";";
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
		if (textBox1->Text->Length != 0 && textBox2->Text->Length != 0 && comboBox1->Text->Length != 0) {
			if (this->orderId == -1) insert();
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
