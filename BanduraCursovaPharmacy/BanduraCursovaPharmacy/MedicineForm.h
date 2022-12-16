#pragma once
#include "EditMedicine.h"
#include "Medicine.h"
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
	/// Summary for MedicineForm
	/// </summary>
	public ref class MedicineForm : public System::Windows::Forms::Form
	{
	private: List<Medicine^>^ medicineList;
		   SqlCeConnection^ connect;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ òàáëèö³ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ çàÖ³íîþToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ çàÀëôàâ³òîìToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ïîÇðîñòàííþToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ïîÑïàäàííþToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ïîÑïàäàííþToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ ïîÇðîñòàííþToolStripMenuItem1;





		   int distributorId;
	public:
		MedicineForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			SqlCeEngine^ dbEngine = gcnew SqlCeEngine();
			dbEngine->LocalConnectionString = "Data Source=PharmacyDB.sdf";
			connect = gcnew SqlCeConnection(dbEngine->LocalConnectionString);
			medicineList = gcnew List<Medicine^>();
		}

		void getMedicine()
		{
			this->distributorId = getSelectedDistributorIndex();
			if (this->distributorId < 0)
			{
				connect->Open();
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = "SELECT * FROM medicine";
				command->Parameters->AddWithValue("@distributor", this->distributorId);
				SqlCeDataReader^ sqlRead = command->ExecuteReader();
				medicineList->Clear();
				while (sqlRead->Read()) {
					medicineList->Add(gcnew Medicine(
						System::Convert::ToString(sqlRead["m_name"]),
						System::Convert::ToString(sqlRead["m_pharm_group"]),
						System::Convert::ToString(sqlRead["m_active_substance"]),
						System::Convert::ToInt32(sqlRead["m_term"]),
						System::Convert::ToSingle(sqlRead["m_price"]),
						System::Convert::ToInt32(sqlRead["m_distributor_id"]),
						System::Convert::ToInt32(sqlRead["m_id"])
					));
				}
				sqlRead->Close();
				connect->Close();
				this->updateTable();
			}
			else {
				connect->Open();
				SqlCeCommand^ command = connect->CreateCommand();
				command->CommandText = "SELECT * FROM medicine WHERE [m_distributor_id]=@distributor";

				command->Parameters->AddWithValue(
					"@distributor",
					this->distributorId
				);
				SqlCeDataReader^ sqlRead = command->ExecuteReader();
				medicineList->Clear();
				while (sqlRead->Read()) {
					medicineList->Add(gcnew Medicine(
						System::Convert::ToString(sqlRead["m_name"]),
						System::Convert::ToString(sqlRead["m_pharm_group"]),
						System::Convert::ToString(sqlRead["m_active_substance"]),
						System::Convert::ToInt32(sqlRead["m_term"]),
						System::Convert::ToSingle(sqlRead["m_price"]),
						System::Convert::ToInt32(sqlRead["m_distributor_id"]),
						System::Convert::ToInt32(sqlRead["m_id"])
					));
				}
				connect->Close();
				this->updateTable();
			}
		}

		int getSelectedDistributorIndex()
		{
			connect->Close();
			connect->Open();
			System::String^ query = "SELECT d_id FROM distributor WHERE d_name LIKE '" + comboBox1->Text + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			int result = -1;
			bool hasRow = sqlRead->Read();
			if (hasRow)
			{
				result = System::Convert::ToInt32(sqlRead["d_id"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		void getQueryMedicine(System::String^ query) {
			connect->Open();
			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			medicineList->Clear();
			while (sqlRead->Read()) {
				medicineList->Add(gcnew Medicine(
					System::Convert::ToString(sqlRead["m_name"]),
					System::Convert::ToString(sqlRead["m_pharm_group"]),
					System::Convert::ToString(sqlRead["m_active_substance"]),
					System::Convert::ToInt32(sqlRead["m_term"]),
					System::Convert::ToSingle(sqlRead["m_price"]),
					System::Convert::ToInt32(sqlRead["m_distributor_id"]),
					System::Convert::ToInt32(sqlRead["m_id"])
				));
			}
			sqlRead->Close();
			connect->Close();
			this->updateTable();
		}

		System::String^ getDistributorName(int id)
		{
			connect->Open();
			System::String^ query = "SELECT d_name FROM distributor WHERE d_id LIKE '" + id + "';";

			SqlCeCommand^ command = connect->CreateCommand();
			command->CommandText = query;
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			System::String^ result;
			bool hasRow = sqlRead->Read();
			if (hasRow) {
				result = System::Convert::ToString(sqlRead["d_name"]);
			}
			connect->Close();
			sqlRead->Close();
			return result;
		}

		void updateTable() {
			int i = 0;
			dataGridView1->Rows->Clear();
			for each (Medicine ^ medicine in medicineList) {
				this->dataGridView1->Rows->Add();
				this->dataGridView1->Rows[i]->Cells[0]->Value = medicine->getId();
				this->dataGridView1->Rows[i]->Cells[1]->Value = medicine->getName();
				this->dataGridView1->Rows[i]->Cells[2]->Value = medicine->getPharmGroup();
				this->dataGridView1->Rows[i]->Cells[3]->Value = medicine->getActiveSubstance();
				this->dataGridView1->Rows[i]->Cells[4]->Value = medicine->getTerm();
				this->dataGridView1->Rows[i]->Cells[5]->Value = medicine->getPrice();
				this->dataGridView1->Rows[i]->Cells[6]->Value = this->getDistributorName(medicine->getDistributorID());
				++i;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MedicineForm()
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


	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;

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
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->òàáëèö³ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çàÖ³íîþToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïîÇðîñòàííþToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïîÑïàäàííþToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïîÑïàäàííþToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïîÇðîñòàííþToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çàÀëôàâ³òîìToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->groupBox1->Controls->Add(this->comboBox2);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(902, 42);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(350, 360);
			this->groupBox1->TabIndex = 39;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Ïîøóê ë³êàðñòâà";
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"â³ä çàñòóäè", L"â³ä êàøëþ", L"â³ä òåìïåðàòóðè",
					L"â³ä áîëþ â æèâîò³", L"çíåáîëþþ÷³", L"õàð÷îâ³ äîáàâêè"
			});
			this->comboBox2->Location = System::Drawing::Point(210, 168);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(125, 33);
			this->comboBox2->TabIndex = 39;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MedicineForm::comboBox2_SelectedIndexChanged);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(38, 259);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(267, 69);
			this->button4->TabIndex = 38;
			this->button4->Text = L"Î÷èñòèòè ô³ëüòð";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MedicineForm::button4_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(210, 107);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(125, 30);
			this->textBox1->TabIndex = 36;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MedicineForm::textBox1_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(17, 46);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(132, 20);
			this->label3->TabIndex = 35;
			this->label3->Text = L"Âèðîáíèê ë³ê³â";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(17, 107);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(165, 20);
			this->label2->TabIndex = 34;
			this->label2->Text = L"Àêòèâíà ðå÷îâèíà";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(6, 175);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(198, 20);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Ôàðìàöåïòè÷íà ãðóïà";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(210, 33);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(125, 33);
			this->comboBox1->TabIndex = 11;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MedicineForm::comboBox1_SelectedIndexChanged);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(568, 424);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(210, 69);
			this->button3->TabIndex = 37;
			this->button3->Text = L"Âèäàëèòè çàïèñ";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MedicineForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(21, 424);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(204, 69);
			this->button2->TabIndex = 36;
			this->button2->Text = L"Ðåäàãóâàòè çàïèñ";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MedicineForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(285, 424);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(204, 69);
			this->button1->TabIndex = 35;
			this->button1->Text = L"Äîäàòè çàïèñ";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MedicineForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Info;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {
				this->Column9,
					this->Column1, this->Column2, this->Column5, this->Column3, this->Column4, this->Column6
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 42);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(867, 360);
			this->dataGridView1->TabIndex = 34;
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"Êîä ë³êàðñòâà";
			this->Column9->MinimumWidth = 6;
			this->Column9->Name = L"Column9";
			this->Column9->Width = 125;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Íàçâà ë³êàðñòâà";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 125;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Ôàðìàöåâòè÷íà ãðóïà";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->Width = 125;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Àêòèâíà ðå÷îâèíà";
			this->Column5->MinimumWidth = 6;
			this->Column5->Name = L"Column5";
			this->Column5->Width = 125;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Òåðì³í çáåð³ãàííÿ(ì³ñÿö³)";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->Width = 125;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Ö³íà ë³ê³â";
			this->Column4->MinimumWidth = 6;
			this->Column4->Name = L"Column4";
			this->Column4->Width = 125;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Âèðîáíèê ë³ê³â";
			this->Column6->MinimumWidth = 6;
			this->Column6->Name = L"Column6";
			this->Column6->Width = 125;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->òàáëèö³ToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1257, 28);
			this->menuStrip1->TabIndex = 40;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// òàáëèö³ToolStripMenuItem
			// 
			this->òàáëèö³ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->çàÖ³íîþToolStripMenuItem,
					this->çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem, this->çàÀëôàâ³òîìToolStripMenuItem
			});
			this->òàáëèö³ToolStripMenuItem->Name = L"òàáëèö³ToolStripMenuItem";
			this->òàáëèö³ToolStripMenuItem->Size = System::Drawing::Size(105, 24);
			this->òàáëèö³ToolStripMenuItem->Text = L"Ñîðòóâàííÿ";
			// 
			// çàÖ³íîþToolStripMenuItem
			// 
			this->çàÖ³íîþToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ïîÇðîñòàííþToolStripMenuItem,
					this->ïîÑïàäàííþToolStripMenuItem
			});
			this->çàÖ³íîþToolStripMenuItem->Name = L"çàÖ³íîþToolStripMenuItem";
			this->çàÖ³íîþToolStripMenuItem->Size = System::Drawing::Size(260, 26);
			this->çàÖ³íîþToolStripMenuItem->Text = L"Çà ö³íîþ";
			// 
			// ïîÇðîñòàííþToolStripMenuItem
			// 
			this->ïîÇðîñòàííþToolStripMenuItem->Name = L"ïîÇðîñòàííþToolStripMenuItem";
			this->ïîÇðîñòàííþToolStripMenuItem->Size = System::Drawing::Size(190, 26);
			this->ïîÇðîñòàííþToolStripMenuItem->Text = L"ïî çðîñòàííþ";
			this->ïîÇðîñòàííþToolStripMenuItem->Click += gcnew System::EventHandler(this, &MedicineForm::ïîÇðîñòàííþToolStripMenuItem_Click);
			// 
			// ïîÑïàäàííþToolStripMenuItem
			// 
			this->ïîÑïàäàííþToolStripMenuItem->Name = L"ïîÑïàäàííþToolStripMenuItem";
			this->ïîÑïàäàííþToolStripMenuItem->Size = System::Drawing::Size(190, 26);
			this->ïîÑïàäàííþToolStripMenuItem->Text = L"ïî ñïàäàííþ";
			this->ïîÑïàäàííþToolStripMenuItem->Click += gcnew System::EventHandler(this, &MedicineForm::ïîÑïàäàííþToolStripMenuItem_Click);
			// 
			// çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem
			// 
			this->çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ïîÑïàäàííþToolStripMenuItem1,
					this->ïîÇðîñòàííþToolStripMenuItem1
			});
			this->çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem->Name = L"çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem";
			this->çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem->Size = System::Drawing::Size(260, 26);
			this->çàÒåðì³íîìÇáåð³ãàííÿToolStripMenuItem->Text = L"Çà òåðì³íîì çáåð³ãàííÿ";
			// 
			// ïîÑïàäàííþToolStripMenuItem1
			// 
			this->ïîÑïàäàííþToolStripMenuItem1->Name = L"ïîÑïàäàííþToolStripMenuItem1";
			this->ïîÑïàäàííþToolStripMenuItem1->Size = System::Drawing::Size(190, 26);
			this->ïîÑïàäàííþToolStripMenuItem1->Text = L"ïî ñïàäàííþ";
			this->ïîÑïàäàííþToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MedicineForm::ïîÑïàäàííþToolStripMenuItem1_Click);
			// 
			// ïîÇðîñòàííþToolStripMenuItem1
			// 
			this->ïîÇðîñòàííþToolStripMenuItem1->Name = L"ïîÇðîñòàííþToolStripMenuItem1";
			this->ïîÇðîñòàííþToolStripMenuItem1->Size = System::Drawing::Size(190, 26);
			this->ïîÇðîñòàííþToolStripMenuItem1->Text = L"ïî çðîñòàííþ";
			this->ïîÇðîñòàííþToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MedicineForm::ïîÇðîñòàííþToolStripMenuItem1_Click);
			// 
			// çàÀëôàâ³òîìToolStripMenuItem
			// 
			this->çàÀëôàâ³òîìToolStripMenuItem->Name = L"çàÀëôàâ³òîìToolStripMenuItem";
			this->çàÀëôàâ³òîìToolStripMenuItem->Size = System::Drawing::Size(260, 26);
			this->çàÀëôàâ³òîìToolStripMenuItem->Text = L"Çà àëôàâ³òîì";
			this->çàÀëôàâ³òîìToolStripMenuItem->Click += gcnew System::EventHandler(this, &MedicineForm::çàÀëôàâ³òîìToolStripMenuItem_Click);
			// 
			// MedicineForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(1257, 543);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"MedicineForm";
			this->Text = L"Ë³êè";
			this->Load += gcnew System::EventHandler(this, &MedicineForm::MedicineForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MedicineForm_Load(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			SqlCeCommand^ command = gcnew SqlCeCommand("SELECT d_name FROM distributor", connect);
			SqlCeDataReader^ sqlRead = command->ExecuteReader();
			while (sqlRead->Read()) {
				comboBox1->Items->Add(sqlRead["d_name"]);
			}
			connect->Close();
			sqlRead->Close();
			if (comboBox1->Items->Count > 0)
			{
				comboBox1->SelectedIndex = -1;
				this->getMedicine();
			}
		}
		catch (...) {
			MessageBox::Show("Ùîñü âèâåäåíî íåïðàâèëüíî");
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		EditMedicine^ edit = gcnew EditMedicine(0, getSelectedDistributorIndex());
		edit->ShowDialog();
		this->getMedicine();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		EditMedicine^ edit = gcnew EditMedicine(System::Convert::ToInt32(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value));
		edit->ShowDialog();
		this->getMedicine();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			connect->Open();
			System::String^ query = "DELETE FROM medicine WHERE [m_id]=" +
				System::Convert::ToString(dataGridView1->Rows[dataGridView1->CurrentCell->RowIndex]->Cells[0]->Value);
			SqlCeCommand^ command = gcnew SqlCeCommand(query, connect);
			if (command->ExecuteNonQuery() > 0) {
				MessageBox::Show("Deleted!");
			}
			connect->Close();
			this->getMedicine();
		}
		catch (...) {
			MessageBox::Show("Âèáåð³òü êîíêðåòíèé çàïèñ");
		}
	}
	// âèá³ðêà ïî ôàðìàöåïòè÷í³é ãðóï³
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		this->getMedicine();
	}
	// ïîøóê ïî ä³þ÷³é ïå÷îâèí³
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM medicine WHERE m_active_substance ='" + textBox1->Text + "';";
		this->getQueryMedicine(query);
	}
	// ïîøóê ïî âèðîáíèêó ë³ê³â
	private: System::Void comboBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM medicine WHERE m_pharm_group ='" + comboBox2->Text + "';";
		this->getQueryMedicine(query);
	}
	// î÷èñòèòè ô³ëüòð
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		comboBox1->SelectedIndex = -1;
		textBox1->Clear();
		comboBox2->SelectedIndex = -1;
		this->getMedicine();
	}

	private: System::Void çàÀëôàâ³òîìToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM medicine order by m_name";
		this->getQueryMedicine(query);
	}
	private: System::Void ïîÇðîñòàííþToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM medicine order by m_price desc";
		this->getQueryMedicine(query);
	}
	private: System::Void ïîÑïàäàííþToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM medicine order by m_price";
		this->getQueryMedicine(query);
	}
	private: System::Void ïîÑïàäàííþToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM medicine order by m_term";
		this->getQueryMedicine(query);
	}
	private: System::Void ïîÇðîñòàííþToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ query = "SELECT * FROM medicine order by m_term desc";
		this->getQueryMedicine(query);
	}
};
}
