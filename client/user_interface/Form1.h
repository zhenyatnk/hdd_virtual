#pragma once

namespace UserInterface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
   private: System::Windows::Forms::ListView^  listView1;
   protected:
   private: System::Windows::Forms::MenuStrip^  menuStrip1;
   private: System::Windows::Forms::ToolStripMenuItem^  íàñòðîéêèToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem;
   private: System::Windows::Forms::SplitContainer^  splitContainer1;
   private: System::Windows::Forms::ListBox^  listBox1;
   private: System::Windows::Forms::ImageList^  imageList1;
   private: System::Windows::Forms::ColumnHeader^  columnHeader1;
   private: System::Windows::Forms::ColumnHeader^  columnHeader2;
   private: System::Windows::Forms::ColumnHeader^  columnHeader3;
   private: System::Windows::Forms::ColumnHeader^  columnHeader4;
   private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;


   private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
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
         System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
         this->listView1 = (gcnew System::Windows::Forms::ListView());
         this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
         this->íàñòðîéêèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
         this->listBox1 = (gcnew System::Windows::Forms::ListBox());
         this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
         this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
         this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
         this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
         this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
         this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
         this->menuStrip1->SuspendLayout();
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
         this->splitContainer1->Panel1->SuspendLayout();
         this->splitContainer1->Panel2->SuspendLayout();
         this->splitContainer1->SuspendLayout();
         this->tableLayoutPanel1->SuspendLayout();
         this->SuspendLayout();
         // 
         // listView1
         // 
         this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
            this->columnHeader1, this->columnHeader2,
               this->columnHeader3, this->columnHeader4
         });
         this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
         this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(2) { listViewItem1, listViewItem2 });
         this->listView1->LargeImageList = this->imageList1;
         this->listView1->Location = System::Drawing::Point(0, 0);
         this->listView1->Name = L"listView1";
         this->listView1->Size = System::Drawing::Size(366, 162);
         this->listView1->TabIndex = 0;
         this->listView1->UseCompatibleStateImageBehavior = false;
         this->listView1->View = System::Windows::Forms::View::Details;
         // 
         // menuStrip1
         // 
         this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->íàñòðîéêèToolStripMenuItem });
         this->menuStrip1->Location = System::Drawing::Point(0, 0);
         this->menuStrip1->Name = L"menuStrip1";
         this->menuStrip1->Size = System::Drawing::Size(522, 24);
         this->menuStrip1->TabIndex = 2;
         this->menuStrip1->Text = L"menuStrip1";
         // 
         // íàñòðîéêèToolStripMenuItem
         // 
         this->íàñòðîéêèToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem });
         this->íàñòðîéêèToolStripMenuItem->Name = L"íàñòðîéêèToolStripMenuItem";
         this->íàñòðîéêèToolStripMenuItem->Size = System::Drawing::Size(79, 20);
         this->íàñòðîéêèToolStripMenuItem->Text = L"Íàñòðîéêè";
         // 
         // ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem
         // 
         this->ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem->Name = L"ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem";
         this->ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem->Size = System::Drawing::Size(206, 22);
         this->ïàðàìåòðûÑîåäèíåíèÿToolStripMenuItem->Text = L"Ïàðàìåòðû ñîåäèíåíèÿ";
         // 
         // splitContainer1
         // 
         this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
         this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
         this->splitContainer1->Location = System::Drawing::Point(3, 3);
         this->splitContainer1->Name = L"splitContainer1";
         this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
         // 
         // splitContainer1.Panel1
         // 
         this->splitContainer1->Panel1->Controls->Add(this->listView1);
         // 
         // splitContainer1.Panel2
         // 
         this->splitContainer1->Panel2->Controls->Add(this->listBox1);
         this->splitContainer1->Size = System::Drawing::Size(366, 231);
         this->splitContainer1->SplitterDistance = 162;
         this->splitContainer1->TabIndex = 3;
         // 
         // listBox1
         // 
         this->listBox1->Dock = System::Windows::Forms::DockStyle::Fill;
         this->listBox1->FormattingEnabled = true;
         this->listBox1->Location = System::Drawing::Point(0, 0);
         this->listBox1->Name = L"listBox1";
         this->listBox1->Size = System::Drawing::Size(366, 65);
         this->listBox1->TabIndex = 0;
         // 
         // imageList1
         // 
         this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
         this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
         this->imageList1->Images->SetKeyName(0, L"hdd_icon.png");
         // 
         // columnHeader1
         // 
         this->columnHeader1->Text = L"Íàçâàíèå";
         this->columnHeader1->Width = 83;
         // 
         // columnHeader2
         // 
         this->columnHeader2->Text = L"Çàãðóçî÷íûé";
         this->columnHeader2->Width = 56;
         // 
         // columnHeader3
         // 
         this->columnHeader3->Text = L"Ðàçìåð (ÃÁ)";
         this->columnHeader3->Width = 91;
         // 
         // columnHeader4
         // 
         this->columnHeader4->Text = L"Ôàéëîâàÿ ñèñòåìà";
         this->columnHeader4->Width = 113;
         // 
         // tableLayoutPanel1
         // 
         this->tableLayoutPanel1->ColumnCount = 2;
         this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
            100)));
         this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
            150)));
         this->tableLayoutPanel1->Controls->Add(this->splitContainer1, 0, 0);
         this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
         this->tableLayoutPanel1->Location = System::Drawing::Point(0, 24);
         this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
         this->tableLayoutPanel1->RowCount = 1;
         this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
         this->tableLayoutPanel1->Size = System::Drawing::Size(522, 237);
         this->tableLayoutPanel1->TabIndex = 4;
         // 
         // Form1
         // 
         this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
         this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
         this->ClientSize = System::Drawing::Size(522, 261);
         this->Controls->Add(this->tableLayoutPanel1);
         this->Controls->Add(this->menuStrip1);
         this->MainMenuStrip = this->menuStrip1;
         this->Name = L"Form1";
         this->Text = L"Èíôîðìàöèÿ î äèñêàõ è ðàçäåëàõ VM";
         this->menuStrip1->ResumeLayout(false);
         this->menuStrip1->PerformLayout();
         this->splitContainer1->Panel1->ResumeLayout(false);
         this->splitContainer1->Panel2->ResumeLayout(false);
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
         this->splitContainer1->ResumeLayout(false);
         this->tableLayoutPanel1->ResumeLayout(false);
         this->ResumeLayout(false);
         this->PerformLayout();

      }
#pragma endregion
	};
}

