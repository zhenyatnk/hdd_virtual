#pragma once

namespace UserInterface 
{

   using namespace System;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;

   public ref class Connect_Form 
      :public System::Windows::Forms::Form
   {
   public:
      Connect_Form(void);

   protected:
      ~Connect_Form();

   private:
      void InitializeComponent(void);

   private:
      System::Windows::Forms::TableLayoutPanel^  tlMainTableLayot;
      System::Windows::Forms::TableLayoutPanel^  tlBottomTableLayout;
      System::Windows::Forms::Button^  bOk;
      System::Windows::Forms::Button^  bCancel;
      System::ComponentModel::Container ^components;
   };
}
