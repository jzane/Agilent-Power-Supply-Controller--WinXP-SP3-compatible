//////////////////TARGETTING WINDOWS XP
#include "MyForm.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include "visa.h"
#include "visatype.h"
#include <time.h> //for delay func
#include <tchar.h>


using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)

{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	PSController::MyForm form;
	Application::Run(%form);

}
  