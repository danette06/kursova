#pragma once
#include "EditOrder.h"
#include "Order.h"
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
	/// Summary for OrderForm
	/// </summary>
	public ref class OrderForm : public System::Windows::Forms::Form
	{
	private: List<Order^>^ orderList;
		   SqlCeConnection^ connect;
		   int medicineId;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
		   int pharmacyId;
	public:
		OrderForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf";
			connect = gcnew SqlCeConnection(dbEngine->LocalConnectionString);
			orderList = gcnew List<Order^>();
		}

		void getOrder()
		{
			this->pharmacyId = getSelectedPharmacyIndex();
			if (this->pharmacyId < 0)
			{
				connect->Open();
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = "SELECT * FROM [order]";
				command->Parameters->AddWithValue("@pharmacy", this->pharmacyId);
				SqlCeDataReader^ sqlRead = command->ExecuteReader();
				orderList->Clear();
				while (sqlRead->Read()) {
					orderList->Add(gcnew Order(
						System::Convert::ToDateTime(sqlRead["o_date"]),
						System::Convert::ToInt32(sqlRead["o_count"]),
						System::Convert::ToInt32(sqlRead["o_pharmacy_id"]),
						System::Convert::ToInt32(sqlRead["o_medicine_id"]),
						System::Convert::ToInt32(sqlRead["o_id"])
					));
				}
				sqlRead->Close();
				connect->Close();
				this->updateTable();
			}
			else {
				connect->Open();
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = "SELECT * FROM order WHERE [o_pharmacy_id]=@pharmacy";

				command->Parameters->AddWithValue(
					"@pharmacy",
					this->pharmacyId
				);
				SqlCeDataReader^ sqlRead = command->ExecuteReader();
				orderList->Clear();
				while (sqlRead->Read()) {
					orderList->Add(gcnew Order(
						System::Convert::ToDateTime(sqlRead["o_date"]),
						System::Convert::ToInt32(sqlRead["o_count"]),
						System::Convert::ToInt32(sqlRead["o_pharmacy_id"]),
						System::Convert::ToInt32(sqlRead["o_medicine_id"]),
						System::Convert::ToInt32(sqlRead["o_id"])
					));
				}
				connect->Close();
				this->updateTable();
			}
		}

		int getSelectedPharmacyIndex()
		{
			connect->Close();
			connect->Open();
			System::String^ query = "SELECT p_id FROM pharmacy WHERE p_name LIKE '" + comboBox1->Text + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			int result = -1;
			bool hasRow = sqlRead->Read();
			if (hasRow)
			{
				result = System::Convert::ToInt32(sqlRead["p_id"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getPharmacy(int id)
		{
			connect->Open();
			System::String^ query = "SELECT p_name FROM pharmacy WHERE p_id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["p_name"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getMedicine(int id)
		{
			connect->Open();
			System::String^ query = "SELECT m_name FROM medicine WHERE m_id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["m_name"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		System::String^ getPrice(int id, int medID)
		{
			connect->Open();
			//отримуємо кількість
			System::String^ query = "SELECT o_count FROM [order] WHERE o_id LIKE '" + id + "';";
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			int count;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				count = System::Convert::ToInt32(sqlRead["o_count"]);
			}
			//отримуємо ціну
			System::String^ query2 = "SELECT m_price FROM [medicine] WHERE m_id LIKE '" + medID + "';";
			SqlCeCommand^ command2 = connect->CreateCommand();
			command->CommandText = query2;
			SqlCeDataReader^ sqlRead2 = command2->ExecuteReader();
			int price;
			bool hasRow2 = sqlRead2->Read();
			if (hasRow2) {
				price = System::Convert::ToInt32(sqlRead["m_price"]);
			}
			connect->Close();
			sqlRead->Close();
			int result = count * price;
			return System::Convert::ToString(result);
		}


		//метод передачі запиту до БД на виконання
		void execute(System::String^ query) {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			command->ExecuteNonQuery();
			connect->Close();
		}

		// метод повернення результатів виконання запиту
		void getQueryOrder(System::String^ query) {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			orderList->Clear();
			while (sqlRead->Read()) {
				orderList->Add(gcnew Order(
					System::Convert::ToDateTime(sqlRead["o_date"]),
					System::Convert::ToInt32(sqlRead["o_count"]),
					System::Convert::ToInt32(sqlRead["o_pharmacy_id"]),
					System::Convert::ToInt32(sqlRead["o_medicine_id"]),
					System::Convert::ToInt32(sqlRead["o_id"])
				));
			}
			sqlRead->Close();
			connect->Close();
			this->updateTable();
		}

		void updateTable() {
			int i = 0;
			dataGridView1->Rows->Clear();
			for each (Order ^ orders in orderList) {
				this->dataGridView1->Rows->Add();
				this->dataGridView1->Rows[i]->Cells[0]->Value = orders->getId();
				this->dataGridView1->Rows[i]->Cells[1]->Value = orders->getCount();
				this->dataGridView1->Rows[i]->Cells[2]->Value = this->getPharmacy(orders->getPharmacyID());
				this->dataGridView1->Rows[i]->Cells[3]->Value = this->getMedicine(orders->getMedicineID());
				this->dataGridView1->Rows[i]->Cells[4]->Value = orders->getDate();
				++i;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OrderForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;

	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;













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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->dateTimePicker1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(852, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(343, 360);
			this->groupBox1->TabIndex = 39;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Пошук поставки";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(189, 162);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(125, 30);
			this->textBox1->TabIndex = 36;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &OrderForm::textBox1_TextChanged);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(36, 271);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(267, 69);
			this->button4->TabIndex = 38;
			this->button4->Text = L"Очистити фільтр";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &OrderForm::button4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(27, 52);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(125, 20);
			this->label3->TabIndex = 35;
			this->label3->Text = L"Назва аптеки";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(27, 105);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(135, 20);
			this->label2->TabIndex = 34;
			this->label2->Text = L"Дата поставки";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(32, 169);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 20);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Назва ліків";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(189, 39);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(125, 33);
			this->comboBox1->TabIndex = 11;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &OrderForm::comboBox1_SelectedIndexChanged);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->CustomFormat = L"MM.dd.yyyy";
			this->dateTimePicker1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dateTimePicker1->Location = System::Drawing::Point(189, 105);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(125, 27);
			this->dateTimePicker1->TabIndex = 32;
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &OrderForm::dateTimePicker1_ValueChanged);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(568, 394);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(210, 69);
			this->button3->TabIndex = 37;
			this->button3->Text = L"Видалити запис";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &OrderForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(21, 394);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(204, 69);
			this->button2->TabIndex = 36;
			this->button2->Text = L"Редагувати запис";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &OrderForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(285, 394);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(204, 69);
			this->button1->TabIndex = 35;
			this->button1->Text = L"Додати запис";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &OrderForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Info;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->Column9,
					this->Column1, this->Column5, this->Column3, this->Column4
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 12);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(813, 360);
			this->dataGridView1->TabIndex = 34;
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"Код поставки";
			this->Column9->MinimumWidth = 6;
			this->Column9->Name = L"Column9";
			this->Column9->Width = 125;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Кількість";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 125;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Назва аптеки";
			this->Column5->MinimumWidth = 6;
			this->Column5->Name = L"Column5";
			this->Column5->Width = 125;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Назва ліків";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->Width = 125;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Дата поставки";
			this->Column4->MinimumWidth = 6;
			this->Column4->Name = L"Column4";
			this->Column4->Width = 125;
			// 
			// OrderForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(1189, 477);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"OrderForm";
			this->Text = L"Поставки";
			this->Load += gcnew System::EventHandler(this, &OrderForm::OrderForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void OrderForm_Load(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand("SELECT p_name FROM pharmacy", connect);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				comboBox1->Items->Add(sqlRead["p_name"]);
			}
			connect->Close();
			sqlRead->Close();
			if (comboBox1->Items->Count > 0)
			{
				comboBox1->SelectedIndex = -1;
				this->getOrder();
			}
		}
		catch (...) {
			MessageBox::Show("Щось виведено неправильно");
		}
		}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		this->getOrder();
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		comboBox1->SelectedIndex = -1;
		textBox1->Clear();
		this->getOrder();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		EditOrder^ edit = gcnew EditOrder(0, getSelectedPharmacyIndex());
		edit->ShowDialog();
		this->getOrder();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		EditOrder^ edit = gcnew EditOrder(System::Convert::ToInt32(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value));
		edit->ShowDialog();
		this->getOrder();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			System::String^ query = "DELETE FROM order WHERE [o_id]=" +
				System::Convert::ToString(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value);
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Deleted!");
			}
			connect->Close();
			this->getOrder();
		}
		catch (...) {
			MessageBox::Show("Виберіть конкретний запис");
		}
	}
	private: System::Void dateTimePicker1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM [order] WHERE [o_date] = '" + dateTimePicker1->Text + "'";
		this->getQueryOrder(query);
	}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	System::String^ query = "SELECT * FROM [order] join [medicine] on m_id = o_medicine_ID  WHERE m_name ='" + textBox1->Text + "';";
	this->getQueryOrder(query);
}
};
}
