#include "stdafx.h"
#include "winsock.h"

#include "Main_Form.h"
#include "Connect_Form.h"
#include "CConfig.h"

namespace
{
   TConectionParms gParm;
   IObjectFactory::Ptr gFactoryObject;
}

namespace UserInterface
{
   Main_Form::Main_Form(void)
   {
      InitializeComponent();
      InitializeDefaultChanel();
      ChangeParmsConnection();
      ReloadInfoHDDToListView();
   }

   Main_Form::~Main_Form()
   {
      if (components)
         delete components;
   }

   IObjectFactory::Ptr Main_Form::GetFactoryObjects()
   {
      if (!gFactoryObject)
         gFactoryObject = CreateClientFactory(gParm);
      return gFactoryObject;
   }

   System::Void Main_Form::smiParametersConnectionMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
   {
      if(ChangeParmsConnection())
         ReloadInfoHDDToListView();
   }
   void Main_Form::ReloadInfoHDDToListView()
   {
      try
      {
         lvHDDInfoListView->Items->Clear();
         CPartitionMeta::Ptr lHDDMeta = GetFactoryObjects()->CreatePartitionMeta(0);
         ListViewItem ^lHDDInfo = gcnew ListViewItem("HDD0");
         if (lHDDMeta->IsBoot())  lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, "*"));
         else                     lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, ""));
         lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, System::Convert::ToString((int)lHDDMeta->GetSizeInSector())));
         lHDDInfo->SubItems->Add(gcnew ListViewItem::ListViewSubItem(lHDDInfo, System::Convert::ToString((int)lHDDMeta->GetTypePart())));
         lvHDDInfoListView->Items->Add(lHDDInfo);
      }
      catch (System::Object^ e)
      {
         e->ToString();
         this->Close();
      }
   }

   void Main_Form::InitializeDefaultChanel(void)
   {
      gParm.mIP = CConfigForms::GetInstance().GetDefaultIP();
      gParm.mFamily = AF_INET;
      gParm.mPort = CConfigForms::GetInstance().GetDefaultPort();
   }

   bool Main_Form::ChangeParmsConnection()
   {
      UserInterface::Connect_Form lFormConnect(gParm);
      if (Windows::Forms::DialogResult::OK == lFormConnect.ShowDialog())
      {
         gParm = lFormConnect.GetParametersConnection();
         CConfigForms::GetInstance().SetDefaultIP(gParm.mIP);
         CConfigForms::GetInstance().SetDefaultPort(gParm.mPort);
         gFactoryObject = NULL;
         return true;
      }
      return false;
   }

#pragma region Windows Form Designer generated code
   void Main_Form::InitializeComponent(void)
   {
      this->components = (gcnew System::ComponentModel::Container());
      System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(4) {
         L"HDD0",
            L"*", L"150.5", L"NTFS"
      }, 0));
      System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(4) {
         L"HDD1",
            L"", L"51.4", L"FAT32"
      }, 0));
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Form::typeid));
      this->lvHDDInfoListView = (gcnew System::Windows::Forms::ListView());
      this->chHeader_HddLabel = (gcnew System::Windows::Forms::ColumnHeader());
      this->chHeader_Bootable = (gcnew System::Windows::Forms::ColumnHeader());
      this->chHeader_Size = (gcnew System::Windows::Forms::ColumnHeader());
      this->chHeader_FileSystem = (gcnew System::Windows::Forms::ColumnHeader());
      this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
      this->msTopMenuStrip = (gcnew System::Windows::Forms::MenuStrip());
      this->smiSettingsMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->smiParametersConnectionMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->scMainSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
      this->lbLogListBox = (gcnew System::Windows::Forms::ListBox());
      this->tlFullInformationLayot = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->msTopMenuStrip->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scMainSplitContainer))->BeginInit();
      this->scMainSplitContainer->Panel1->SuspendLayout();
      this->scMainSplitContainer->Panel2->SuspendLayout();
      this->scMainSplitContainer->SuspendLayout();
      this->tlFullInformationLayot->SuspendLayout();
      this->SuspendLayout();
      // 
      // listView1
      // 
      this->lvHDDInfoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
         this->chHeader_HddLabel, this->chHeader_Bootable,
            this->chHeader_Size, this->chHeader_FileSystem
      });
      this->lvHDDInfoListView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->lvHDDInfoListView->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(2) { listViewItem1, listViewItem2 });
      this->lvHDDInfoListView->LargeImageList = this->imageList1;
      this->lvHDDInfoListView->Location = System::Drawing::Point(0, 0);
      this->lvHDDInfoListView->Name = L"lvHDDInfoListView";
      this->lvHDDInfoListView->Size = System::Drawing::Size(366, 162);
      this->lvHDDInfoListView->TabIndex = 0;
      this->lvHDDInfoListView->UseCompatibleStateImageBehavior = false;
      this->lvHDDInfoListView->View = System::Windows::Forms::View::Details;
      // 
      // columnHeader1
      // 
      this->chHeader_HddLabel->Text = L"Название";
      this->chHeader_HddLabel->Width = 83;
      // 
      // columnHeader2
      // 
      this->chHeader_Bootable->Text = L"Загрузочный";
      this->chHeader_Bootable->Width = 56;
      // 
      // columnHeader3
      // 
      this->chHeader_Size->Text = L"Размер (ГБ)";
      this->chHeader_Size->Width = 91;
      // 
      // columnHeader4
      // 
      this->chHeader_FileSystem->Text = L"Файловая система";
      this->chHeader_FileSystem->Width = 113;
      // 
      // imageList1
      // 
      this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
      this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
      this->imageList1->Images->SetKeyName(0, L"hdd_icon.png");
      // 
      // menuStrip1
      // 
      this->msTopMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->smiSettingsMenuItem });
      this->msTopMenuStrip->Location = System::Drawing::Point(0, 0);
      this->msTopMenuStrip->Name = L"msTopMenuStrip";
      this->msTopMenuStrip->Size = System::Drawing::Size(522, 24);
      this->msTopMenuStrip->TabIndex = 2;
      this->msTopMenuStrip->Text = L"menuStrip1";
      // 
      // настройкиToolStripMenuItem
      // 
      this->smiSettingsMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->smiParametersConnectionMenuItem });
      this->smiSettingsMenuItem->Name = L"smiSettingsMenuItem";
      this->smiSettingsMenuItem->Size = System::Drawing::Size(79, 20);
      this->smiSettingsMenuItem->Text = L"Настройки";
      // 
      // параметрыСоединенияToolStripMenuItem
      // 
      this->smiParametersConnectionMenuItem->Name = L"smiParametersConnectionMenuItem";
      this->smiParametersConnectionMenuItem->Size = System::Drawing::Size(206, 22);
      this->smiParametersConnectionMenuItem->Text = L"Параметры соединения";
      this->smiParametersConnectionMenuItem->Click += gcnew System::EventHandler(this, &Main_Form::smiParametersConnectionMenuItem_Click);
      // 
      // splitContainer1
      // 
      this->scMainSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
      this->scMainSplitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
      this->scMainSplitContainer->Location = System::Drawing::Point(3, 3);
      this->scMainSplitContainer->Name = L"scMainSplitContainer";
      this->scMainSplitContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
      // 
      // splitContainer1.Panel1
      // 
      this->scMainSplitContainer->Panel1->Controls->Add(this->lvHDDInfoListView);
      // 
      // splitContainer1.Panel2
      // 
      this->scMainSplitContainer->Panel2->Controls->Add(this->lbLogListBox);
      this->scMainSplitContainer->Size = System::Drawing::Size(366, 231);
      this->scMainSplitContainer->SplitterDistance = 162;
      this->scMainSplitContainer->TabIndex = 3;
      // 
      // listBox1
      // 
      this->lbLogListBox->Dock = System::Windows::Forms::DockStyle::Fill;
      this->lbLogListBox->FormattingEnabled = true;
      this->lbLogListBox->Location = System::Drawing::Point(0, 0);
      this->lbLogListBox->Name = L"lbLogListBox";
      this->lbLogListBox->Size = System::Drawing::Size(366, 65);
      this->lbLogListBox->TabIndex = 0;
      // 
      // tableLayoutPanel1
      // 
      this->tlFullInformationLayot->ColumnCount = 2;
      this->tlFullInformationLayot->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
         100)));
      this->tlFullInformationLayot->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
         150)));
      this->tlFullInformationLayot->Controls->Add(this->scMainSplitContainer, 0, 0);
      this->tlFullInformationLayot->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tlFullInformationLayot->Location = System::Drawing::Point(0, 24);
      this->tlFullInformationLayot->Name = L"tlFullInformationLayot";
      this->tlFullInformationLayot->RowCount = 1;
      this->tlFullInformationLayot->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
      this->tlFullInformationLayot->Size = System::Drawing::Size(522, 237);
      this->tlFullInformationLayot->TabIndex = 4;
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(522, 261);
      this->Controls->Add(this->tlFullInformationLayot);
      this->Controls->Add(this->msTopMenuStrip);
      this->MainMenuStrip = this->msTopMenuStrip;
      this->Name = L"Main_Form";
      this->Text = L"Информация о дисках и разделах VM";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->msTopMenuStrip->ResumeLayout(false);
      this->msTopMenuStrip->PerformLayout();
      this->scMainSplitContainer->Panel1->ResumeLayout(false);
      this->scMainSplitContainer->Panel2->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scMainSplitContainer))->EndInit();
      this->scMainSplitContainer->ResumeLayout(false);
      this->tlFullInformationLayot->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

   }
#pragma endregion

}
