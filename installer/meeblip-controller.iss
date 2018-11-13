#define AppName             "Meeblip Controller"
#define AppNameUnderscore   StringChange(MyAppName, " ", "_")
#define AppVersion          "0.1.0"
#define AppPublisher        "Romain Clement"
#define AppURL              ""

[Setup]
AppName                 = {#AppName}
AppVersion              = {#AppVersion}
AppVerName              = {#AppName} {#AppVersion}
AppPublisherURL         = {#AppUrl}
AppSupportURL           = {#AppUrl}
AppUpdatesURL           = {#AppUrl}
DefaultDirName          = C:\ProgramData\{#AppPublisher}\{#AppName}
DisableDirPage          = yes
DefaultGroupName        = {#AppPublisher}
DisableProgramGroupPage = yes
OutputBaseFilename      = {#AppPublisher} - {#AppName} - {#AppVersion}
Compression             = lzma
SolidCompression        = yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Types]
Name: "full";   Description: "Full installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
Name: "{#AppNameUnderscore}";         Description: "{#AppPublisher} {#AppName}";    Types: full;
Name: "{#AppNameUnderscore}/vst2_32"; Description: "VST2 (32 bits)";                Types: full;
Name: "{#AppNameUnderscore}/vst2_64"; Description: "VST2 (64 bits)";                Types: full; Check: IsWin64;
Name: "{#AppNameUnderscore}/vst3_32"; Description: "VST3 (32 bits)";                Types: full;
Name: "{#AppNameUnderscore}/vst3_64"; Description: "VST3 (64 bits)";                Types: full; Check: IsWin64;

[Files]
Source: "..\build\Win32\Release\{#AppName}.dll";    DestDir: "{pf32}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "..\build\x64\Release\{#AppName}.dll";      DestDir: "{pf64}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "..\build\Win32\Release\{#AppName}.vst3";   DestDir: "{cf32}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "..\build\x64\Release\{#AppName}.vst3";     DestDir: "{cf64}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

