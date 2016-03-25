#include "stdafx.h"

#include <sstream>
#include <msclr/marshal_cppstd.h>
#include "Connect_Form.h"

namespace UserInterface
{

   Connect_Form::Connect_Form(TConectionParms aParmConnection, std::string aFileNameVM)
   {
      InitializeComponent();
      InitValueControls(aParmConnection);
      InitFileNameControls(aFileNameVM);
   }

   Connect_Form::~Connect_Form()
   {
      if (components)
      {
         delete components;
      }
   }

   TConectionParms Connect_Form::GetParametersConnection()
   {
      TConectionParms lParms;
      lParms.mIP  = msclr::interop::marshal_as<std::string>(nudIP1->Value.ToString()) + ".";
      lParms.mIP += msclr::interop::marshal_as<std::string>(nudIP2->Value.ToString()) + ".";
      lParms.mIP += msclr::interop::marshal_as<std::string>(nudIP3->Value.ToString()) + ".";
      lParms.mIP += msclr::interop::marshal_as<std::string>(nudIP4->Value.ToString());
      lParms.mPort = (int)nudNumberPort->Value;
      lParms.mFamily = AF_INET;
      return lParms;
   }

   std::string Connect_Form::GetFileNameVM()
   {
      return msclr::interop::marshal_as<std::string>(tbFilenameVM->Text);
   }

   void Connect_Form::InitValueControls(TConectionParms aParmConnection)
   {
      std::stringstream lStream_ip(aParmConnection.mIP);

      std::string lIPPart;
      if (std::getline(lStream_ip, lIPPart, '.'))   nudIP1->Text = gcnew System::String(lIPPart.c_str());
      if (std::getline(lStream_ip, lIPPart, '.'))   nudIP2->Text = gcnew System::String(lIPPart.c_str());
      if (std::getline(lStream_ip, lIPPart, '.'))   nudIP3->Text = gcnew System::String(lIPPart.c_str());
      if (std::getline(lStream_ip, lIPPart, '.'))   nudIP4->Text = gcnew System::String(lIPPart.c_str());
      nudNumberPort->Text = System::Convert::ToString(aParmConnection.mPort);
   }
   
   void Connect_Form::InitFileNameControls(std::string aFileNameVM)
   {
      tbFilenameVM->Text = gcnew System::String(aFileNameVM.c_str());
   }

#pragma region Windows Form Designer generated code
   void Connect_Form::InitializeComponent(void)
   {
      this->tlMainTableLayot = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->tlBottomTableLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->bOk = (gcnew System::Windows::Forms::Button());
      this->bCancel = (gcnew System::Windows::Forms::Button());
      this->pnPanelParameters = (gcnew System::Windows::Forms::Panel());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->tbFilenameVM = (gcnew System::Windows::Forms::TextBox());
      this->gbPort = (gcnew System::Windows::Forms::GroupBox());
      this->nudNumberPort = (gcnew System::Windows::Forms::NumericUpDown());
      this->gbIP = (gcnew System::Windows::Forms::GroupBox());
      this->nudIP2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lDot1 = (gcnew System::Windows::Forms::Label());
      this->nudIP1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lDot2 = (gcnew System::Windows::Forms::Label());
      this->nudIP3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lDot3 = (gcnew System::Windows::Forms::Label());
      this->nudIP4 = (gcnew System::Windows::Forms::NumericUpDown());
      this->tlMainTableLayot->SuspendLayout();
      this->tlBottomTableLayout->SuspendLayout();
      this->pnPanelParameters->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->gbPort->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudNumberPort))->BeginInit();
      this->gbIP->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP4))->BeginInit();
      this->SuspendLayout();
      // 
      // tlMainTableLayot
      // 
      this->tlMainTableLayot->ColumnCount = 1;
      this->tlMainTableLayot->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
         100)));
      this->tlMainTableLayot->Controls->Add(this->tlBottomTableLayout, 0, 1);
      this->tlMainTableLayot->Controls->Add(this->pnPanelParameters, 0, 0);
      this->tlMainTableLayot->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tlMainTableLayot->Location = System::Drawing::Point(0, 0);
      this->tlMainTableLayot->Name = L"tlMainTableLayot";
      this->tlMainTableLayot->RowCount = 2;
      this->tlMainTableLayot->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
      this->tlMainTableLayot->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
      this->tlMainTableLayot->Size = System::Drawing::Size(254, 218);
      this->tlMainTableLayot->TabIndex = 0;
      // 
      // tlBottomTableLayout
      // 
      this->tlBottomTableLayout->ColumnCount = 3;
      this->tlBottomTableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
         100)));
      this->tlBottomTableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
         90)));
      this->tlBottomTableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
         90)));
      this->tlBottomTableLayout->Controls->Add(this->bOk, 1, 0);
      this->tlBottomTableLayout->Controls->Add(this->bCancel, 2, 0);
      this->tlBottomTableLayout->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tlBottomTableLayout->Location = System::Drawing::Point(3, 186);
      this->tlBottomTableLayout->Name = L"tlBottomTableLayout";
      this->tlBottomTableLayout->RowCount = 1;
      this->tlBottomTableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
         100)));
      this->tlBottomTableLayout->Size = System::Drawing::Size(248, 29);
      this->tlBottomTableLayout->TabIndex = 0;
      // 
      // bOk
      // 
      this->bOk->Anchor = System::Windows::Forms::AnchorStyles::None;
      this->bOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->bOk->Location = System::Drawing::Point(75, 3);
      this->bOk->Name = L"bOk";
      this->bOk->Size = System::Drawing::Size(75, 23);
      this->bOk->TabIndex = 5;
      this->bOk->Text = L"OK";
      this->bOk->UseVisualStyleBackColor = true;
      // 
      // bCancel
      // 
      this->bCancel->Anchor = System::Windows::Forms::AnchorStyles::None;
      this->bCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->bCancel->Location = System::Drawing::Point(165, 3);
      this->bCancel->Name = L"bCancel";
      this->bCancel->Size = System::Drawing::Size(75, 23);
      this->bCancel->TabIndex = 6;
      this->bCancel->Text = L"Отмена";
      this->bCancel->UseVisualStyleBackColor = true;
      // 
      // pnPanelParameters
      // 
      this->pnPanelParameters->Controls->Add(this->groupBox1);
      this->pnPanelParameters->Controls->Add(this->gbPort);
      this->pnPanelParameters->Controls->Add(this->gbIP);
      this->pnPanelParameters->Dock = System::Windows::Forms::DockStyle::Fill;
      this->pnPanelParameters->Location = System::Drawing::Point(3, 3);
      this->pnPanelParameters->Name = L"pnPanelParameters";
      this->pnPanelParameters->Size = System::Drawing::Size(248, 177);
      this->pnPanelParameters->TabIndex = 1;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->tbFilenameVM);
      this->groupBox1->Location = System::Drawing::Point(10, 120);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(228, 52);
      this->groupBox1->TabIndex = 3;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Путь к файлу виртуальной машины";
      // 
      // tbFilenameVM
      // 
      this->tbFilenameVM->Location = System::Drawing::Point(10, 20);
      this->tbFilenameVM->Name = L"tbFilenameVM";
      this->tbFilenameVM->Size = System::Drawing::Size(206, 20);
      this->tbFilenameVM->TabIndex = 0;
      // 
      // gbPort
      // 
      this->gbPort->Controls->Add(this->nudNumberPort);
      this->gbPort->Location = System::Drawing::Point(10, 62);
      this->gbPort->Name = L"gbPort";
      this->gbPort->Size = System::Drawing::Size(228, 52);
      this->gbPort->TabIndex = 3;
      this->gbPort->TabStop = false;
      this->gbPort->Text = L"Порт подключения";
      // 
      // nudNumberPort
      // 
      this->nudNumberPort->Enabled = false;
      this->nudNumberPort->ImeMode = System::Windows::Forms::ImeMode::NoControl;
      this->nudNumberPort->Location = System::Drawing::Point(10, 19);
      this->nudNumberPort->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65535, 0, 0, 0 });
      this->nudNumberPort->Name = L"nudNumberPort";
      this->nudNumberPort->RightToLeft = System::Windows::Forms::RightToLeft::No;
      this->nudNumberPort->Size = System::Drawing::Size(206, 20);
      this->nudNumberPort->TabIndex = 4;
      // 
      // gbIP
      // 
      this->gbIP->Controls->Add(this->nudIP2);
      this->gbIP->Controls->Add(this->lDot1);
      this->gbIP->Controls->Add(this->nudIP1);
      this->gbIP->Controls->Add(this->lDot2);
      this->gbIP->Controls->Add(this->nudIP3);
      this->gbIP->Controls->Add(this->lDot3);
      this->gbIP->Controls->Add(this->nudIP4);
      this->gbIP->Location = System::Drawing::Point(9, 2);
      this->gbIP->Name = L"gbIP";
      this->gbIP->Size = System::Drawing::Size(229, 53);
      this->gbIP->TabIndex = 2;
      this->gbIP->TabStop = false;
      this->gbIP->Text = L"IP адрес сервера";
      // 
      // nudIP2
      // 
      this->nudIP2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
      this->nudIP2->Location = System::Drawing::Point(65, 19);
      this->nudIP2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
      this->nudIP2->Name = L"nudIP2";
      this->nudIP2->RightToLeft = System::Windows::Forms::RightToLeft::No;
      this->nudIP2->Size = System::Drawing::Size(44, 20);
      this->nudIP2->TabIndex = 1;
      // 
      // lDot1
      // 
      this->lDot1->AutoSize = true;
      this->lDot1->Location = System::Drawing::Point(163, 23);
      this->lDot1->Name = L"lDot1";
      this->lDot1->Size = System::Drawing::Size(10, 13);
      this->lDot1->TabIndex = 1;
      this->lDot1->Text = L".";
      // 
      // nudIP1
      // 
      this->nudIP1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
      this->nudIP1->Location = System::Drawing::Point(11, 19);
      this->nudIP1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
      this->nudIP1->Name = L"nudIP1";
      this->nudIP1->RightToLeft = System::Windows::Forms::RightToLeft::No;
      this->nudIP1->Size = System::Drawing::Size(44, 20);
      this->nudIP1->TabIndex = 0;
      // 
      // lDot2
      // 
      this->lDot2->AutoSize = true;
      this->lDot2->Location = System::Drawing::Point(109, 23);
      this->lDot2->Name = L"lDot2";
      this->lDot2->Size = System::Drawing::Size(10, 13);
      this->lDot2->TabIndex = 1;
      this->lDot2->Text = L".";
      // 
      // nudIP3
      // 
      this->nudIP3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
      this->nudIP3->Location = System::Drawing::Point(119, 19);
      this->nudIP3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
      this->nudIP3->Name = L"nudIP3";
      this->nudIP3->RightToLeft = System::Windows::Forms::RightToLeft::No;
      this->nudIP3->Size = System::Drawing::Size(44, 20);
      this->nudIP3->TabIndex = 2;
      // 
      // lDot3
      // 
      this->lDot3->AutoSize = true;
      this->lDot3->Location = System::Drawing::Point(55, 23);
      this->lDot3->Name = L"lDot3";
      this->lDot3->Size = System::Drawing::Size(10, 13);
      this->lDot3->TabIndex = 1;
      this->lDot3->Text = L".";
      // 
      // nudIP4
      // 
      this->nudIP4->ImeMode = System::Windows::Forms::ImeMode::NoControl;
      this->nudIP4->Location = System::Drawing::Point(173, 19);
      this->nudIP4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
      this->nudIP4->Name = L"nudIP4";
      this->nudIP4->RightToLeft = System::Windows::Forms::RightToLeft::No;
      this->nudIP4->Size = System::Drawing::Size(44, 20);
      this->nudIP4->TabIndex = 3;
      // 
      // Connect_Form
      // 
      this->AcceptButton = this->bOk;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->bCancel;
      this->ClientSize = System::Drawing::Size(254, 218);
      this->Controls->Add(this->tlMainTableLayot);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"Connect_Form";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Параметры подключения";
      this->tlMainTableLayot->ResumeLayout(false);
      this->tlBottomTableLayout->ResumeLayout(false);
      this->pnPanelParameters->ResumeLayout(false);
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->gbPort->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudNumberPort))->EndInit();
      this->gbIP->ResumeLayout(false);
      this->gbIP->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudIP4))->EndInit();
      this->ResumeLayout(false);

   }
#pragma endregion

}
