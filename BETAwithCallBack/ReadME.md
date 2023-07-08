+ At the user request I added the function with CallBack, also updated the examples for Delphi and C/C++.
- Removed the Benchmarking possibility, because it hangs the program execution, so it's not needed here.

Delphi definition:
```delphi
Type
	PROGRESS_CALLBACK = Procedure(FileName: PWideChar; Total, Completed, Files: UInt64); cdecl;

Function CommandFor7zipWithCallBackW(const args: PWideChar; var Output, Errors: PWideChar; const CallBack: PROGRESS_CALLBACK): Integer; stdcall;
  external '7zOverlay.dll' name 'CommandFor7zipWithCallBackW';

// CallBack Procedure:
Procedure ProgressCallback(FileName: PWideChar; Total, Completed, Files: UInt64); cdecl;
	begin
		(...)
end;
```

C/C++ definition:
```cpp
typedef unsigned long UInt64;
typedef void (__cdecl *PROGRESS_CALLBACK)(wchar_t * FileName, UInt64 Total, UInt64 Completed, UInt64 Files);

typedef int Func_CommandFor7zipWithCallBackW(
	const wchar_t * args,
	wchar_t * &OutputBuffer,
	wchar_t * &ErrorsBuffer,
	const PROGRESS_CALLBACK CallBack
	);

// CallBack Procedure:
//void __cdecl ProgressCallback(wchar_t * FileName, UInt64 Total, UInt64 Completed, UInt64 Files){
/* Fix for x86 (32-bit) VS2015CE, because it swaps last two parameters in places... */
void __cdecl ProgressCallback(wchar_t * FileName, UInt64 Total, UInt64 Files, UInt64 Completed){
	(...)
}
```

**Explanation of the parameters of the CallBack Procedure, depends of List/Extract/Create/Update.**

+ **List**:
ProgressCallback(**FileName** -> path and/or name in the archive, **Total** -> packed size, **Completed** -> original size, **Files** -> file number)

+ **Extract**:
ProgressCallback(**FileName** -> path and/or name in the archive, **Total** -> total size do unpack, **Completed** -> size already done, **Files** -> file number)

+ **Create/Update**:
ProgressCallback(**FileName** -> path and/or name of currently processing, **Total** -> total size to process, **Completed** -> size already done, **Files** -> total files processed)


I share it as the BETA, because it needs to be tested, even if I tested it already on main computer and VM (virtual machine).
