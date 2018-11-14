#define AppName             "Meeblip Controller"
#define AppNameUnderscore   StringChange(AppName, " ", "_")
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
DefaultDirName          = {commonappdata}\{#AppPublisher}\{#AppName}
DisableDirPage          = yes
DefaultGroupName        = {#AppPublisher}
DisableProgramGroupPage = no
OutputDir               = ..\build\installers
OutputBaseFilename      = {#AppName} - {#AppVersion}
Compression             = lzma
SolidCompression        = yes
Uninstallable           = yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Types]
Name: "full";   Description: "Full installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
Name: "{#AppNameUnderscore}";               Description: "{#AppName}";          Flags: fixed;
Name: "{#AppNameUnderscore}/standalone_32"; Description: "Standalone (32-bit)"; Types: full;
Name: "{#AppNameUnderscore}/standalone_64"; Description: "Standalone (64-bit)"; Types: full; Check: IsWin64;
Name: "{#AppNameUnderscore}/vst2_32";       Description: "VST2 (32-bit)";       Types: full;
Name: "{#AppNameUnderscore}/vst2_64";       Description: "VST2 (64-bit)";       Types: full; Check: IsWin64;
Name: "{#AppNameUnderscore}/vst3_32";       Description: "VST3 (32-bit)";       Types: full;
Name: "{#AppNameUnderscore}/vst3_64";       Description: "VST3 (64-bit)";       Types: full; Check: IsWin64;

[Files]
Source: "..\build\Win32\Release\Standalone Plugin\{#AppName}.exe";  DestDir: "{pf32}\{#AppPublisher}\{#AppName}"; DestName: "{#AppName}.exe"; Components: {#AppNameUnderscore}/standalone_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "..\build\x64\Release\Standalone Plugin\{#AppName}.exe";    DestDir: "{pf64}\{#AppPublisher}\{#AppName}"; DestName: "{#AppName}.exe"; Components: {#AppNameUnderscore}/standalone_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "..\build\Win32\Release\VST\{#AppName}.dll";    DestDir: "{pf32}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "..\build\x64\Release\VST\{#AppName}.dll";      DestDir: "{pf64}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "..\build\Win32\Release\VST3\{#AppName}.vst3";   DestDir: "{cf32}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "..\build\x64\Release\VST3\{#AppName}.vst3";     DestDir: "{cf64}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

; Source: ".\resources\presets\*"; DestDir: "{app}\presets"; Components: {#AppNameUnderscore}; Flags: ignoreversion createallsubdirs recursesubdirs overwritereadonly uninsremovereadonly;

