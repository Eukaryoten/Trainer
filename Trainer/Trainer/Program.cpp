#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Compile.h"
#include "Application.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	srand(time(NULL));

	Application* application = new Application(hInstance);

	if (!application->Initialize())
		return 1;

	return application->Run();

}

#endif