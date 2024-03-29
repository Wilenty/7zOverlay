# 7zOverlay

[![Latest Version](https://img.shields.io/github/release/Wilenty/7zOverlay.svg)](https://github.com/Wilenty/7zOverlay/releases/latest)
[![Total Downloads](https://img.shields.io/github/downloads/Wilenty/7zOverlay/total.svg)](https://github.com/Wilenty/7zOverlay/releases)
[![Latest Release Downloads](https://img.shields.io/github/downloads/Wilenty/7zOverlay/latest/total.svg)](https://github.com/Wilenty/7zOverlay/releases/latest)
[![v19.09b Release Downloads](https://img.shields.io/github/downloads/Wilenty/7zOverlay/v19.09b/total.svg)](https://github.com/Wilenty/7zOverlay/releases/v19.09b)

You can use this dll if your program/project is completely free of charge. If you get any income even from donations or ads, please support me.<br>
<br>
For my overlay to work fully, you need the 7z.dll, so if you don't have this file yet, you can download it from there: <a href=https://www.7-zip.org/>https://www.7-zip.org/</a><br>
<br>
The parameters for the 7zOverlay.dll file can be found in the 7-ZIP help file, the 7zOverlay.dll uses the same parameters as the 7z.exe file. I hope that the move/change will be easy.<br>
if you don't add any parameters to the 7zOverlay.dll, it returns help of the parameters in the output buffer, and it returns -1 (without parameters).<br>
<br>
By default it loads 7z.dll file from the 7zOverlay.dll location, it doesn't matter if you call 7zOverlay.dll from the %tmp% location or from your .exe location. But, you can change the 7z.dll file location by the functions <b>Set7zDllPathFileA</b> or <b>Set7zDllPathFileW</b> (example below). Only before any of the functions <b>CommandFor7zipA</b> or <b>CommandFor7zipW</b> you can change the 7z.dll file location. After 7z.dll file is loaded, functions to change the 7z.dll file location does not work.<br>
<br>
I tested the 7zOverlay.dll with 7z.dll versions of: 15.05, 16.04, 19.00, 20.00 Alpha and 20.01 alpha. It works fine.<br>
<br>
This dll contains four functions, two for <b>ANSI</b> (Set7zDllPathFileA, CommandFor7zipA) and two for <b>UNICODE</b> (Set7zDllPathFileW, CommandFor7zipW) characters.<br>
<br>
Two basic examples of use, separately for characters encoding:<br>
<br>
<b>ANSI</b>:<br>
C++: <b>BOOL Set7zDllPathFileA(const char * FullPathToThe7zDLL);</b><br>
Delphi: <b>Set7zDllPathFileA(const FullPathToThe7zDLL: PAnsiChar): BOOL; stdcall;</b><br>
---<br>
C++: <b>int CommandFor7zipA(const char * params, char * &OutputBuffer, char * &ErrorsBuffer);</b><br>
Delphi: <b>CommandFor7zipA(const params: PAnsiChar; var OutputBuffer, ErrorsBuffer: PAnsiChar): Integer;</b><br>
<br>
<b>UNICODE</b>:<br>
C++: <b>BOOL Set7zDllPathFileW(const wchar_t * FullPathToThe7zDLL);</b><br>
Delphi: <b>Set7zDllPathFileW(const FullPathToThe7zDLL: PWideChar): BOOL; stdcall;</b><br>
---<br>
C++: <b>int CommandFor7zipW(const wchar_t * params, wchar_t * &OutputBuffer, wchar_t * &ErrorsBuffer);</b><br>
Delphi: <b>CommandFor7zipW(const params: PWideChar; var OutputBuffer, ErrorsBuffer: PWideChar): Integer;</b><br>
<br>
I also prepared other examples of use for other programming languages available for download above.<br>
Any examples does not have included the 7zOverlay.dll, so you need to download it separately and place it in the extracted example(s) location.<br>
<br>
Here I share only X86 (32-bit) version of this dll for free programs, which works only with X86 (32-bit) build of the 7z.dll. X64 (64-bit) build of this dll is available also and we can talk about its price on my patreon, or here in private messages (if available).<br>
<br>
Build info.<br>
This 7zOverlay.dll was built from original 7-ZIP source using VisualStudio2015CE with some modifications to use it as dll, but not as command line program. So, this dll uses this same parameters as you used for 7-ZIP command line program (7z.exe) - first parameter (input), and it returns the output messages to the output buffer - second parameter (output), and all warning/errors messages it returns in the errors buffer - third parameter (output).<br>
<br>
Short project story, you can skip it, if you are not interested.<br>
This project was started long time ago. At the beginning I created this dll in old Delphi with use of the JCL for 7-ZIP, it's was quite fast, but the JCL does not support all archives as I wanted. So, I started modify original 7-ZIP source to create the overlayed dll from it. I don't wanted to create this dll as in some other projects, which builds these dll(s) with current version of 7-ZIP. Yes, these dll(s) from other projects are single and don't need original 7z.dll to work, but you need to wait for new version. With my overlayed dll you can use any version of 7-ZIP.<br>
