Program Overlay7ZipDllTest;

{$APPTYPE CONSOLE}

Uses
  Windows,
  SysUtils;

Type
	PROGRESS_CALLBACK = Procedure(FileName: PWideChar; Total, Completed, Files: UInt64); cdecl;

Function Set7zDllPathFileW(const Dll7zFileName: PWideChar): BOOL; stdcall;
  external '7zOverlay.dll' name 'Set7zDllPathFileW';

Function CommandFor7zipWithCallBackW(const args: PWideChar; var Output, Errors: PWideChar; const CallBack: PROGRESS_CALLBACK): Integer; stdcall;
  external '7zOverlay.dll' name 'CommandFor7zipWithCallBackW';

Function CommandFor7zipW(const args: PWideChar; var Output, Errors: PWideChar): Integer; stdcall;
  external '7zOverlay.dll' name 'CommandFor7zipW';

Var
  ErrorsStringsArray: Array[0..9] of String = (
    'Successful operation',                           // kSuccess       = 0
    'Non fatal error(s) occurred',                    // kWarning       = 1
    'A fatal error occurred',                         // kFatalError    = 2
    'A CRC error occurred when unpacking',            // kCRCError      = 3
    'Attempt to modify an archive previously locked', // kLockedArchive = 4
    'Write to disk error',                            // kWriteError    = 5
    'Open file error',                                // kOpenError     = 6
    'Command line option error',                      // kUserError     = 7
    'Not enough memory for operation',                // kMemoryError   = 8
    'Create file error'                               // kCreateFileError = 9
    );
  Params: WideString;
  OutputBuffer, ErrorsBuffer: PWideChar;
  Output, Errors: PAnsiChar;
  DefaultCharUsed: PBool;

Procedure ProgressCallback(FileName: PWideChar; Total, Completed, Files: UInt64); cdecl;
  var
    percent: Extended;
	begin
    try
      If (Total = UInt64(-1)) then
    		exit;

	percent := 0;
	if ( Total > Completed ) then
      percent := Completed * 100 / Total;

  		WriteLn( Format( 'CallBack:' + #13#10 +' %d'+ #13#10 + ' %d' + #13#10 + ' %s' + #13#10 + ' %d' + #13#10 + '---', [ Total, Files, FileName, Completed ] ) );
////      Sleep(200);
    except
    end;
end;

Begin
  Params := StringReplace(GetCommandLineW(), ParamStr(0), '', [rfReplaceAll, rfIgnoreCase]);
  Params := StringReplace(Params, '""', '', [rfReplaceAll]);
  WriteLn( 'Params:' + Params );
  WriteLn( '---' );
  Try
    Try
//      Set7zDllPathFileW('b:\7z.dll');
//      ExitCode := CommandFor7zipW( PWideChar(Params), OutputBuffer, ErrorsBuffer );
      ExitCode := CommandFor7zipWithCallBackW( PWideChar(Params), OutputBuffer, ErrorsBuffer, @ProgressCallback );
    except
      WriteLn('DLL exception caught!');
			ExitCode := -890;
    end;
  finally
//    Output := PAnsiChar( StringOfChar( #1, Length(OutputBuffer) ) );
//    WideCharToMultiByte( CP_OEMCP, 0, OutputBuffer, Length(OutputBuffer), Output, Length(Output), PAnsiChar(#0), DefaultCharUsed );
//    Write( Output );
    Errors := PAnsiChar( StringOfChar( #1, Length(ErrorsBuffer) ) );
    WideCharToMultiByte( CP_OEMCP, 0, ErrorsBuffer, Length(ErrorsBuffer), Errors, Length(Errors), PAnsiChar(#0), DefaultCharUsed );
    Write( Errors );
    WriteLn( '---' );
    if (ExitCode >= 0) then
      WriteLn( 'Result: ' + ErrorsStringsArray[ExitCode] )
    else
      WriteLn( 'No params.' );
  end;
  WriteLn( '---' );
  WriteLn('Press [enter] to exit.');
  ReadLn;
end.