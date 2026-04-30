; RP2A03 installer (Inno Setup)

#define MyAppName "RP2A03"
#define MyAppCompany "SocaLabs"
#define MyAppPublisher "SocaLabs"
#define MyAppCopyright "2026 SocaLabs"
#define MyAppURL "https://socalabs.com/"
#define MyAppVersion GetStringFileInfo("bin\VST3\RP2A03.vst3\Contents\x86_64-win\RP2A03.vst3", "ProductVersion")
#define MyDefaultDirName "{commoncf64}\VST3"

[Setup]
AppID={{14A1972A-F25A-49BA-833C-F8021A109271}
AppName={#MyAppCompany} {#MyAppName} {#MyAppVersion}
AppVerName={#MyAppCompany} {#MyAppName} {#MyAppVersion}
AppVersion={#MyAppVersion}
AppCopyright={#MyAppCopyright}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={#MyDefaultDirName}
DisableProgramGroupPage=yes
OutputDir=.\bin
OutputBaseFilename=RP2A03
Compression=lzma/ultra
SolidCompression=true
ShowLanguageDialog=auto
LicenseFile=..\EULA.rtf
InternalCompressLevel=ultra
MinVersion=0,6.1.7600
FlatComponentsList=false
AppendDefaultDirName=false
AlwaysShowDirOnReadyPage=yes
DirExistsWarning=no
DisableDirPage=yes
DisableWelcomePage=no
DisableReadyPage=no
DisableReadyMemo=no
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
VersionInfoVersion={#MyAppVersion}
VersionInfoCompany={#MyAppPublisher}
VersionInfoCopyright={#MyAppCopyright}
VersionInfoProductName={#MyAppCompany} {#MyAppName} {#MyAppVersion} (64-bit)
VersionInfoProductVersion={#MyAppVersion}
VersionInfoProductTextVersion={#MyAppVersion}
UsePreviousGroup=False
Uninstallable=no
PrivilegesRequired=admin

[Languages]
Name: english; MessagesFile: compiler:Default.isl

[Components]
Name: "vst";       Description: "VST plug-in";   Types: full custom; Flags: checkablealone
Name: "vst3";      Description: "VST3 plug-in";  Types: full custom; Flags: checkablealone
Name: "clap";      Description: "CLAP plug-in";  Types: full custom; Flags: checkablealone
Name: "resources"; Description: "Factory presets"; Types: full custom; Flags: fixed

[InstallDelete]
Type: files;          Name: "{commoncf64}\VST2\RP2A03.dll";   Components: vst
Type: filesandordirs; Name: "{commoncf64}\VST3\RP2A03.vst3"; Components: vst3
Type: files;          Name: "{commoncf64}\CLAP\RP2A03.clap"; Components: clap
Type: filesandordirs; Name: "{commonappdata}\SocaLabs\RP2A03\Presets";        Components: resources

[Files]
Source: "bin\VST\RP2A03.dll";    DestDir: "{commoncf64}\VST2";                     Flags: ignoreversion overwritereadonly; Components: vst
Source: "bin\VST3\RP2A03.vst3\*"; DestDir: "{commoncf64}\VST3\RP2A03.vst3\"; Flags: ignoreversion overwritereadonly recursesubdirs; Components: vst3
Source: "bin\CLAP\RP2A03.clap";   DestDir: "{commoncf64}\CLAP";                    Flags: ignoreversion overwritereadonly; Components: clap
Source: "..\_flat_presets\*.xml"; DestDir: "{commonappdata}\SocaLabs\RP2A03\Presets\"; Flags: ignoreversion; Components: resources
