// Overlay7ZipDllTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <string>
#include <conio.h>

extern "C" {
	typedef int(WINAPI *Func_CommandFor7zipW)(
		const wchar_t * args,
		wchar_t * &OutputBuffer,
		wchar_t * &ErrorsBuffer
		);
}

typedef unsigned long UInt64;
typedef void (__cdecl *PROGRESS_CALLBACK)(wchar_t * FileName, UInt64 Total, UInt64 Completed, UInt64 Files);

//extern "C" {
	typedef int Func_CommandFor7zipWithCallBackW(
		const wchar_t * args,
		wchar_t * &OutputBuffer,
		wchar_t * &ErrorsBuffer,
		const PROGRESS_CALLBACK CallBack
		);
//}

wchar_t * ErrorsStringsArray[] = {
	L"Successful operation",                           // kSuccess       = 0
	L"Non fatal error(s) occurred",                    // kWarning       = 1
	L"A fatal error occurred",                         // kFatalError    = 2
	L"A CRC error occurred when unpacking",            // kCRCError      = 3
	L"Attempt to modify an archive previously locked", // kLockedArchive = 4
	L"Write to disk error",                            // kWriteError    = 5
	L"Open file error",                                // kOpenError     = 6
	L"Command line option error",                      // kUserError     = 7
	L"Not enough memory for operation",                // kMemoryError   = 8
	L"Create file error"                               // kCreateFileError = 9
	};

//void __cdecl ProgressCallback(wchar_t * FileName, UInt64 Total, UInt64 Completed, UInt64 Files){
/* Fix for x86 (32-bit) VS2015CE, because it swaps last two parameters in places... */
void __cdecl ProgressCallback(wchar_t * FileName, UInt64 Total, UInt64 Files, UInt64 Completed){
	try
	{
		if ( Total == (UInt64)-1 )
			return;

		float percent = 0;
		if ( Total > Completed )
			percent = Completed * 100 / Total;

		wprintf(L"CallBack:\n %d\n %d\n %s\n %d\n---\n", Total, Files, FileName, Completed);
		//		Sleep( 200 );
	}
	catch (...)
	{
		throw;
	}
}

int wmain(int argsCount, wchar_t * args[])
{
	int Ret;
	HMODULE Overlay7Z = LoadLibraryW(L"7zOverlay.dll");
	if (Overlay7Z == NULL)
	{
		printf("Can't load the '7zOverlay.dll'.");
		Ret = -3210;
	}
	else
	{
		std::wstring test = GetCommandLineW();
		size_t pos = test.find(args[0]);
		if (pos > 0) {
			test.replace(pos, wcslen(args[0]), L"");
			pos = test.find(L"\"\"");
			if(pos != std::wstring::npos)
				test.replace(pos, wcslen(L"\"\""), L"");
		}
		const wchar_t * Params = test.c_str();

		wprintf(L"Params: %s\n---\n", Params);

		wchar_t * OutputBuffer;
		wchar_t * ErrorsBuffer;
/*
		Func_CommandFor7zipW CommandFor7zipW = (Func_CommandFor7zipW)GetProcAddress(Overlay7Z, "CommandFor7zipW");
		try
		{
			Ret = CommandFor7zipW(Params, OutputBuffer, ErrorsBuffer);
			wprintf(OutputBuffer);
		}
*/
		Func_CommandFor7zipWithCallBackW* CommandFor7zipWithCallBackW = (Func_CommandFor7zipWithCallBackW*)GetProcAddress(Overlay7Z, "CommandFor7zipWithCallBackW");
		try
		{
			Ret = CommandFor7zipWithCallBackW(Params, OutputBuffer, ErrorsBuffer, &ProgressCallback);
//			wprintf(OutputBuffer);
			wprintf(ErrorsBuffer);
		}
		catch (...)
		{
			wprintf(L"DLL exception caught!");
			Ret = -890;
		}
		FreeLibrary(Overlay7Z);

		wprintf(L"\n---\n");

		if (Ret >= 0)
			wprintf(L"Result: %s", ErrorsStringsArray[Ret]);
		else
			if(Ret == -1)
				wprintf(L"No params.");
			else
				wprintf(L"Result: %d", Ret);
	}

	wprintf(L"\n---\nPress any key to exit.\n");
	_getch();
    return Ret;
}
