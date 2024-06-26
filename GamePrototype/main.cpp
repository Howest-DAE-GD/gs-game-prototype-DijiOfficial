#include "pch.h"
#include <ctime>
#include "Game.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

void StartHeapControl();
void DumpMemoryLeaks();

//struct AtExit
//{
//	~AtExit() { DumpMemoryLeaks(); }
//} doAtExit;

int SDL_main(int argv, char** args)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	StartHeapControl();

	Game* pGame{ new Game{ Window{ "Project name - Name, first name - 1DAEXX", 846.f , 500.f } } };
	pGame->Run();
	delete pGame;

	//DumpMemoryLeaks();
	return 0;
}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc(232);
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}


