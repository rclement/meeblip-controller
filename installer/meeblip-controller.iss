#define AppName             "${APP_NAME}"
#define AppNameUnderscore   StringChange(AppName, " ", "_")
#define AppVersion          "${APP_VERSION}"
#define AppPublisher        "${APP_MANUFACTURER_NAME}"
#define AppUrl              "${APP_MANUFACTURER_URL}"
#define AppRootDir          "${APP_ROOT_DIR}"
#define AppBuildDir         "${APP_BUILD_DIR}"

[Setup]
AppName                 = {#AppName}
AppVersion              = {#AppVersion}
AppVerName              = {#AppName} {#AppVersion}
AppPublisherURL         = {#AppUrl}
AppSupportURL           = {#AppUrl}
AppUpdatesURL           = {#AppUrl}
AppCopyright            = Copyright (C) 2018 {#AppPublisher}
DefaultDirName          = {commonappdata}\{#AppPublisher}\{#AppName}
DisableDirPage          = yes
DefaultGroupName        = {#AppPublisher}
DisableProgramGroupPage = no
OutputDir               = {#AppBuildDir}\installer\output
OutputBaseFilename      = {#AppName} - {#AppVersion}
Compression             = lzma
SolidCompression        = yes
Uninstallable           = yes
UninstallDisplayIcon    = {#AppBuildDir}\x64\icon.ico
SetupIconFile           = {#AppBuildDir}\x64\icon.ico
WizardImageFile         = {#AppRootDir}\installer\resources\innosetup-wizard-large.bmp
WizardSmallImageFile    = {#AppRootDir}\installer\resources\innosetup-wizard-small.bmp

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
Source: "{#AppBuildDir}\Win32\Release\Standalone Plugin\{#AppName}.exe";  DestDir: "{pf32}\{#AppPublisher}\{#AppName}"; DestName: "{#AppName}.exe"; Components: {#AppNameUnderscore}/standalone_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppBuildDir}\x64\Release\Standalone Plugin\{#AppName}.exe";    DestDir: "{pf64}\{#AppPublisher}\{#AppName}"; DestName: "{#AppName}.exe"; Components: {#AppNameUnderscore}/standalone_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppBuildDir}\Win32\Release\VST\{#AppName}.dll";    DestDir: "{pf32}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppBuildDir}\x64\Release\VST\{#AppName}.dll";      DestDir: "{pf64}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppBuildDir}\Win32\Release\VST3\{#AppName}.vst3";   DestDir: "{cf32}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppBuildDir}\x64\Release\VST3\{#AppName}.vst3";     DestDir: "{cf64}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

; Source: "{#AppRootDir}\installer\resources\presets\*"; DestDir: "{app}\presets"; Components: {#AppNameUnderscore}; Flags: ignoreversion createallsubdirs recursesubdirs overwritereadonly uninsremovereadonly;

