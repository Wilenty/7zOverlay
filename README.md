# 7zOverlay
You can use this dll if your program/project is completely free of charge. If you get any income even from donations or ads, please support me.

For my overlay to work fully, you need the 7z.dll, so if you don't have this file yet, you can download it from here: https://www.7-zip.org/

The parameters for the 7zOverlay.dll file can be found in the 7-ZIP help file, the 7zOverlay.dll uses the same parameters as the 7z.exe file. I hope that the move/change will be easy.
if you don't add any parameters to the 7zOverlay.dll, it returns help of the parameters in the output buffer, and it returns -1 (without parameters);

It loads 7z.dll from the 7zOverlay.dll location, it doesn't matter if you call 7zOverlay.dll from the %tmp% location or from your .exe location. Therefore, the 7z.dll file must be in the same location as the 7zOverlay.dll location.

I tested the 7zOverlay.dll with 7z.dll versions of: 15.05, 16.04, 19.00 and 20.00 Alpha. It works fine.

Two basic examples of use:
C++: int CommandFor7ZIP(const char * params, char * &OutputBuffer, char * &ErrorsBuffer);
Delphi: CommandFor7ZIP(const params: PAnsiChar; var OutputBuffer, ErrorsBuffer: PAnsiChar): Integer;

I also prepared other examples of use for other programming languages available for download above.
Any examples does not have included the 7zOverlay.dll, so you need to download it separately and place it in the extracted example(s) location.

Here I share only X86 (32-bit) version of this dll for free programs, which works only with X86 (32-bit) build of the 7z.dll. X64 (64-bit) build of this dll is available also and we can talk about its price on my patreon, or here in private messages (if available).

Build info.
This 7zOverlay.dll was built from original 7-ZIP source using VisualStudio2015ce with some modifications to use it as dll, but not as command line program. So, this dll uses this same parameters as you used for 7-ZIP command line program (7z.exe) - first parameter (input), and it returns the output messages to the output buffer - second parameter (output), and all warning/errors messages it returns in the errors buffer - third parameter (output).

Short project story, you can skip it, if you are not interested.
This project was started long time ago. At the beginning I created this dll in old Delphi with use of the JCL for 7-ZIP, it's was quite fast, but the JCL does not support all archives as I wanted. So, I started modify original 7-ZIP source to create the overlayed dll from it. I don't wanted to create this dll as in some other projects, which builds these dll(s) with current version of 7-ZIP. Yes, these dll(s) from other projects are single and don't need original 7z.dll to work, but you need to wait for new version. With mine overlayed dll you can use any version of 7-ZIP.
