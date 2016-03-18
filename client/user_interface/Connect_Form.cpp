#include "stdafx.h"
#include "Connect_Form.h"

namespace UserInterface
{

   Connect_Form::Connect_Form(void)
   {
      InitializeComponent();
   }

   Connect_Form::~Connect_Form()
   {
      if (components)
      {
         delete components;
      }
   }

#pragma region Windows Form Designer generated code
   void Connect_Form::InitializeComponent(void)
   {
      this->tlMainTableLayot = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->tlBottomTableLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->bOk = (gcnew System::Windows::Forms::Button());
      this->bCancel = (gcnew System::Windows::Forms::Button());
      this->tlMainTableLayot->SuspendLayout();
      this->tlBottomTableLayout->SuspendLayout();
      this->SuspendLayout();
      // 
      // tlMainTableLayot
      // 
      this->tlMainTableLayot->ColumnCount = 1;
      this->tlMainTableLayot->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
         100)));
      this->tlMainTableLayot->Controls->Add(this->tlBottomTableLayout, 0, 1);
      this->tlMainTableLayot->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tlMainTableLayot->Location = System::Drawing::Point(0, 0);
      this->tlMainTableLayot->Name = L"tlMainTableLayot";
      this->tlMainTableLayot->RowCount = 2;
      this->tlMainTableLayot->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
      this->tlMainTableLayot->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
      this->tlMainTableLayot->Size = System::Drawing::Size(272, 299);
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
      this->tlBottomTableLayout->Location = System::Drawing::Point(3, 267);
      this->tlBottomTableLayout->Name = L"tlBottomTableLayout";
      this->tlBottomTableLayout->RowCount = 1;
      this->tlBottomTableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
      this->tlBottomTableLayout->Size = System::Drawing::Size(266, 29);
      this->tlBottomTableLayout->TabIndex = 0;
      // 
      // bOk
      // 
      this->bOk->Anchor = System::Windows::Forms::AnchorStyles::None;
      this->bOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->bOk->Location = System::Drawing::Point(93, 3);
      this->bOk->Name = L"bOk";
      this->bOk->Size = System::Drawing::Size(75, 23);
      this->bOk->TabIndex = 6;
      this->bOk->Text = L"OK";
      this->bOk->UseVisualStyleBackColor = true;
      // 
      // bCancel
      // 
      this->bCancel->Anchor = System::Windows::Forms::AnchorStyles::None;
      this->bCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->bCancel->Location = System::Drawing::Point(183, 3);
      this->bCancel->Name = L"bCancel";
      this->bCancel->Size = System::Drawing::Size(75, 23);
      this->bCancel->TabIndex = 64;
      this->bCancel->Text = L"Отмена";
      this->bCancel->UseVisualStyleBackColor = true;
      // 
      // Connect_Form
      // 
      this->AcceptButton = this->bOk;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(272, 299);
      this->Controls->Add(this->tlMainTableLayot);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"Connect_Form";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Параметры подключения";
      this->tlMainTableLayot->ResumeLayout(false);
      this->tlBottomTableLayout->ResumeLayout(false);
      this->ResumeLayout(false);

   }
#pragma endregion

}
