#include "StartForm.h"

#include <Windows.h>

using namespace BanduraCursovaPharmacy; //назва проєкту

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew StartForm);
	return 0;
}