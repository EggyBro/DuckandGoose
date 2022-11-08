/*!*************************************************************************
****
\file			EntryPoint.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain the main entry point for all our functions

****************************************************************************
***/
#pragma once
#include "Application.h"


#ifdef EM_PLATFORM_WINDOWS

extern EM::Application* EM::CreateApplication();

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	//Mermory leak check
	int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpDbgFlag);
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_NORMAL);
	
	
	EM::Log::Init();
	auto app = EM::CreateApplication();
	app->Run();
	delete app;
}


#endif