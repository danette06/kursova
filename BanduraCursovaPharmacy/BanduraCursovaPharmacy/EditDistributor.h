#pragma once

namespace BanduraCursovaPharmacy {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;;

	/// <summary>
	/// Summary for EditDistributor
	/// </summary>
	public ref class EditDistributor : public System::Windows::Forms::Form
	{
		System::Data::SqlServerCe::SqlCeConnection^ connect;
		int distributorId;
	public:
		EditDistributor(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		EditDistributor(int dId) {
			InitializeComponent();
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf";
			connect = gcnew SqlCeConnection("Data Source=PharmacyDB.sdf");
			connect->Open();
			this->distributorId = dId;
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = "SELECT * FROM distributor WHERE [d_id]=@dId";
			command->Parameters->AddWithValue(
				"@dId",
				dId
			);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				textBox1->Text = System::Convert::ToString(sqlRead["d_name"]);
				textBox2->Text = System::Convert::ToString(sqlRead["d_country"]);
				textBox3->Text = System::Convert::ToString(sqlRead["d_gmail"]);
			}
			connect->Close();
			sqlRead->Close();
		}
		int IfDuplicate()
		{
			int count;
			connect->Open();
			System::String^ query = "SELECT COUNT([d_name]) FROM[distributor] WHERE [d_name] = '" + textBox1->Text + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			bool hasRow = sqlRead->Read();
			if (hasRow)
			{
				count = System::Convert::ToInt32(sqlRead["Column1"]);
			}
			sqlRead->Close();
			connect->Close();
			return count;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditDistributor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label3;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;

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
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(12, 124);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(237, 75);
			this->label3->TabIndex = 24;
			this->label3->Text = L"Електронна адреса виробника";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(229, 202);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(211, 63);
			this->button2->TabIndex = 23;
			this->button2->Text = L"Відміна";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &EditDistributor::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(12, 202);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(211, 63);
			this->button1->TabIndex = 22;
			this->button1->Text = L"Зберегти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &EditDistributor::button1_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(246, 140);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(194, 34);
			this->textBox3->TabIndex = 21;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(246, 74);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(194, 47);
			this->textBox2->TabIndex = 20;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(246, 4);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(194, 34);
			this->textBox1->TabIndex = 19;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(12, 74);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(193, 41);
			this->label2->TabIndex = 18;
			this->label2->Text = L"Країна виробника";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(223, 29);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Назва виробника";
			// 
			// EditDistributor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(481, 286);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"EditDistributor";
			this->Text = L"Додати виробника ліків";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Редагування запису
	private: void update() {
		try {
			connect->Open();
			System::String^ query = "UPDATE distributor SET [d_name]='" + textBox1->Text + "', [d_country]='" + textBox2->Text + "', [d_gmail]='" + textBox3->Text + "' WHERE [d_id]=" + this->distributorId + ";";
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
			if (IfDuplicate() > 0)
			{
				MessageBox::Show("Такий виробник ліків вже існує");
				this->Close();
			}
			else
			{
				connect->Open();
				System::String^ query = "INSERT INTO distributor([d_name], [d_country], [d_gmail])" +
					"VALUES('" + textBox1->Text + "','" + textBox2->Text + "','" + textBox3->Text + "');";
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = query;
				if (command->ExecuteNonQuery() > 0) {
					MessageBox::Show("Добавлено!");
				}
				connect->Close();
			}
		}
		catch (...) {
			MessageBox::Show("Щось введено не правильно");
			this->Close();
		}
	}

	//Кнопка збереження даних
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text->Length != 0 && textBox2->Text->Length != 0 && textBox3->Text->Length != 0) {
			if (this->distributorId == -1)
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
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
