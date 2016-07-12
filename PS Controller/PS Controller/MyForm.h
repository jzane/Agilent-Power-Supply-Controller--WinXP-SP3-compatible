#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include "visa.h"
#include "visatype.h"
#include <time.h> //for delay func

#pragma once






namespace PSController {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;





	ViSession defaultRM; /* Resource manager id */
	ViSession power_supply; /* Identifies power supply */
	int bGPIB = 0; /* Set the number to 0 for use with the RS-232
				   interface */
	long ErrorStatus; /* VISA Error code */
	char commandString[256];
	char ReadBuffer[256];
	void delay(clock_t wait);
	void SendSCPI(char* pString);
	void CheckError(char* pMessage);
	double voltage; /* Value of voltage sent to power supply */
	char Buffer[256]; /* String returned from power supply */
	double current; /* Value of current output of power supply */
	bool cancel_var; //var holds whether to stay in loop or not







	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}



		//////////////////////////////////////////////////////////
		//user defined functions

		void MyForm::OpenPort()
		{
			std::string comm;
			comm = msclr::interop::marshal_as<std::string>(this->textBox1->Text); //wrapper to convert Ssytem::String to std::string
			//comm is now std::string
			const char * p = comm.c_str(); //converting std::string to char *

			char GPIB_Address[3];
			char COM_Address[2];
			char VISA_address[40]; // Complete VISA address sent to card 
			if(bGPIB)
				strcpy(GPIB_Address,"5"); // Select GPIB address between 0 to 30
			else
				strcpy(COM_Address,p); // Set the number to 2 for COM2 port 
			if(bGPIB){ // For use with GPIB 7 address, use "GPIB::7::INSTR" address format 
				strcpy(VISA_address,"GPIB::");
				strcat(VISA_address,GPIB_Address);
				strcat(VISA_address,"::INSTR");
			}
			else{ // For use with COM2 port, use "ASRL2::INSTR" address format 
				strcpy(VISA_address,"ASRL");
				strcat(VISA_address,COM_Address);
				strcat(VISA_address,"::INSTR");
			}
			// Open communication session with the power supply 
			ErrorStatus = viOpenDefaultRM(&defaultRM);
			ErrorStatus = viOpen(defaultRM,VISA_address,0,0,&power_supply);
			CheckError((char *)"Unable to open port");
			if(!bGPIB)
				SendSCPI((char *)"System:Remote"); //added to cast as char *
			delay(500);

		}//end openPort()



		////////////////////////////////////////////////////////
		//close port
		void MyForm::ClosePort()
		{
			/* Close the communication port */
			viClose(power_supply);
			viClose(defaultRM);
		}//end closeport



		////////////////////////////////////////////////////////
		//check error
		void MyForm::CheckError(char* pMessage)
		{
			if (ErrorStatus < VI_SUCCESS){
				int error = (int)ErrorStatus; //casting long to int

				this->label18->Text = gcnew String(pMessage); //creating System::String data using char * type as argument


				ClosePort();

			}
			else
			{
				this->label18->Text = "";

			}
		}//end check error


		////////////////////////////////////////////////////
		//send scpi to device
		void MyForm::SendSCPI(char* pString)
		{
			char* pdest;
			strcpy(commandString,pString);
			strcat(commandString,(ViString)"\n");
			ErrorStatus = viPrintf(power_supply,commandString);
			CheckError((ViString)"Can’t Write to Driver");
			if (bGPIB == 0)
				delay(70); /* Unit is milliseconds */ //NEEDS TO BE HERE!!!!!!!!!!!!!!!!!!!!!
			pdest = strchr(commandString, '?'); /* Search for query command */
			if( pdest != NULL ){
				ErrorStatus = viScanf(power_supply,(char *)"%s",&ReadBuffer);
				CheckError((ViString)"Can’t Read From Driver");

				strcpy(pString,ReadBuffer);
			}
		}//end sendSCPI

		///////////////////////////////////////////////
		//delay time
		void MyForm::delay(clock_t wait)
		{
			clock_t goal;
			goal = wait + clock();
			while( goal > clock() ) ;
		}




	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
	private: Microsoft::VisualBasic::PowerPacks::LineShape^  lineShape1;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	protected: 

	protected: 




	protected: 
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->lineShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::LineShape());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(224, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Connect to device through COM port:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(242, 8);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(34, 20);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(119, 38);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 37);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(342, 11);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Device ID:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(419, 14);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"label3";
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(1) {this->lineShape1});
			this->shapeContainer1->Size = System::Drawing::Size(567, 422);
			this->shapeContainer1->TabIndex = 5;
			this->shapeContainer1->TabStop = false;
			// 
			// lineShape1
			// 
			this->lineShape1->Name = L"lineShape1";
			this->lineShape1->X1 = 21;
			this->lineShape1->X2 = 367;
			this->lineShape1->Y1 = 118;
			this->lineShape1->Y2 = 118;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->radioButton1->Location = System::Drawing::Point(54, 132);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(76, 17);
			this->radioButton1->TabIndex = 6;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Output ON";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->radioButton2->Location = System::Drawing::Point(136, 132);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(80, 17);
			this->radioButton2->TabIndex = 7;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Output OFF";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(12, 187);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(543, 181);
			this->tabControl1->TabIndex = 8;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->textBox3);
			this->tabPage1->Controls->Add(this->textBox2);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(535, 155);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(268, 51);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(106, 45);
			this->button2->TabIndex = 7;
			this->button2->Text = L"SET!";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(223, 79);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(18, 16);
			this->label8->TabIndex = 6;
			this->label8->Text = L"V";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(223, 51);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(18, 16);
			this->label7->TabIndex = 5;
			this->label7->Text = L"A";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(112, 76);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 4;

			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(112, 48);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 3;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(22, 76);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(58, 16);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Voltage:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(22, 53);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(83, 16);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Current Limit:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(18, 15);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(71, 20);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Output 1";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->button3);
			this->tabPage2->Controls->Add(this->label16);
			this->tabPage2->Controls->Add(this->textBox7);
			this->tabPage2->Controls->Add(this->label15);
			this->tabPage2->Controls->Add(this->label14);
			this->tabPage2->Controls->Add(this->label13);
			this->tabPage2->Controls->Add(this->label12);
			this->tabPage2->Controls->Add(this->textBox6);
			this->tabPage2->Controls->Add(this->textBox5);
			this->tabPage2->Controls->Add(this->textBox4);
			this->tabPage2->Controls->Add(this->label11);
			this->tabPage2->Controls->Add(this->label10);
			this->tabPage2->Controls->Add(this->label9);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(535, 155);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(329, 51);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(106, 45);
			this->button3->TabIndex = 12;
			this->button3->Text = L"SET!";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(233, 109);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(18, 16);
			this->label16->TabIndex = 11;
			this->label16->Text = L"A";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(127, 107);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 20);
			this->textBox7->TabIndex = 10;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(18, 107);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(83, 16);
			this->label15->TabIndex = 9;
			this->label15->Text = L"Current Limit:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(233, 80);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(18, 16);
			this->label14->TabIndex = 8;
			this->label14->Text = L"S";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(233, 55);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(18, 16);
			this->label13->TabIndex = 7;
			this->label13->Text = L"V";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(233, 27);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(18, 16);
			this->label12->TabIndex = 6;
			this->label12->Text = L"V";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(127, 77);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 5;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(127, 52);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 4;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(127, 24);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 3;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(18, 81);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(73, 16);
			this->label11->TabIndex = 2;
			this->label11->Text = L"Rise Time:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(18, 53);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(103, 16);
			this->label10->TabIndex = 1;
			this->label10->Text = L"Ending Voltage:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(18, 25);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(105, 16);
			this->label9->TabIndex = 0;
			this->label9->Text = L"Starting Voltsge:";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(15, 385);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(47, 16);
			this->label17->TabIndex = 9;
			this->label17->Text = L"Errors:";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label18->ForeColor = System::Drawing::Color::Red;
			this->label18->Location = System::Drawing::Point(68, 385);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(52, 16);
			this->label18->TabIndex = 10;
			this->label18->Text = L"label18";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(567, 422);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->shapeContainer1);
			this->Name = L"MyForm";
			this->Text = L"Agilent PS Controller";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->label3->Text = ""; //set text to blank
				 this->radioButton2->Checked = true; //set output off to default
				 this->textBox1->Text = "4";
				 this->tabPage1->Text = "Manual Voltage Control";
				 this->tabPage2->Text = "Voltage Ramp";
				 this->textBox2->Text = "1.4"; //default current limits to 1.4 A
				 this->textBox7->Text = "1.4";
				 this->label18->Text = ""; //set error code to null first
			 }



			 //connect to device via comm
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 OpenPort(); //opens port with comm number specifier
				 sprintf_s(Buffer, "*IDN?");
				 SendSCPI(Buffer);
				 //getting instrument ID string
				 this->label3->Text = gcnew String(Buffer); //again, creates system string type via char type

			 }


			 //setting output on and off
	private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 SendSCPI((char*)"Output on");
			 }

	private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 SendSCPI((char*)"Output off");
			 }

			 //sending the scpi commands to set current and voltage
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

				 //error checking
				 //voltage is negative

				 if (System::Convert::ToDouble(this->textBox2->Text) < 0) //hjave to convert System::String to double
				 {
					 this->label18->Text = "Current must be positive";
					 return;
				 }

				 //current is negative
				 if (System::Convert::ToDouble(this->textBox3->Text) < 0)
				 {
					 this->label18->Text = "Voltage must be positive";
					 return;
				 }

				 //current is too high
				 if (System::Convert::ToDouble(this->textBox2->Text) > 1.4)
				 {
					 this->label18->Text = "Current must be equal to or less than 1.4 A";
					 return;
				 }

				 //voltage is too high
				 if (System::Convert::ToDouble(this->textBox3->Text)  > 35)
				 {
					 this->label18->Text = "Voltage must be equal to or less than 35 V";
					 return;
				 }

				 std::string current = "CURRENT " + msclr::interop::marshal_as<std::string>(this->textBox2->Text) + "\n"; //create string message to set voltage
				 const char * curr = current.c_str();
				 SendSCPI((char*)curr);
				 SendSCPI((char*)"Output on"); /* Turn output on */

				 //set voltage
				 std::string voltage1 = "VOLT " + msclr::interop::marshal_as<std::string>(this->textBox3->Text) + "\n"; //create string message to set voltage
				 const char * volt = voltage1.c_str();
				 SendSCPI((char*)volt);
				 this->radioButton1->Checked = true; //default to output radio button checked

			 }


};
}
