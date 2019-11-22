echo on
set MSBUILD_EXE=C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\MSBuild.exe

set ROOT=%cd%
cd "%ROOT%"

cd Scripts
mkdir bin
mkdir bin\win

cd "..\plugin\Builds\VisualStudio2017"
"%MSBUILD_EXE%" RP2A03.sln /p:VisualStudioVersion=15.0 /m /t:Build /p:Configuration=Release64 /p:Platform=x64 /p:PreferredToolArchitecture=x64
if %errorlevel% neq 0 exit /b %errorlevel%
"%MSBUILD_EXE%" RP2A03.sln /p:VisualStudioVersion=15.0 /m /t:Build /p:Configuration=Release /p:PlatformTarget=x86 /p:PreferredToolArchitecture=x64
if %errorlevel% neq 0 exit /b %errorlevel%

cd "%ROOT%\Scripts\bin"

copy "%ROOT%\plugin\Builds\VisualStudio2017\x64\Release64\VST\RP2A03_64b.dll" .
copy "%ROOT%\plugin\Builds\VisualStudio2017\Win32\Release\VST\RP2A03_32b.dll" .

7z a RP2A03_Win.zip RP2A03_32b.dll RP2A03_64b.dll
copy RP2A03_Win.zip win