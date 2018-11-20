#define AppName             "${APP_NAME}"
#define AppNameUnderscore   StringChange(AppName, " ", "_")
#define AppVersion          "${APP_VERSION}"
#define AppPublisher        "${APP_MANUFACTURER_NAME}"
#define AppUrl              "${APP_MANUFACTURER_URL}"
#define AppRootDir          "${APP_ROOT_DIR}"
#define AppBuildDir         "${APP_BUILD_DIR}"
#define AppOutputDir        "${APP_OUTPUT_DIR}"
#define AppOutputBaseName   "${APP_OUTPUT_BASENAME}"

[Setup]
AppName                 = {#AppName}
AppVersion              = {#AppVersion}
AppVerName              = {#AppName} {#AppVersion}
AppPublisherURL         = {#AppUrl}
AppSupportURL           = {#AppUrl}
AppUpdatesURL           = {#AppUrl}
AppCopyright            = Copyright (C) 2018 {#AppPublisher}
LicenseFile             = {#AppRootDir}\LICENSE.txt
DefaultDirName          = {commonappdata}\{#AppPublisher}\{#AppName}
DisableDirPage          = yes
DefaultGroupName        = {#AppPublisher}
DisableProgramGroupPage = no
OutputDir               = {#AppOutputDir}
OutputBaseFilename      = {#AppOutputBaseName}
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
Name: "{#AppNameUnderscore}";                           Description: "{#AppName}";                          Types: full custom;
Name: "{#AppNameUnderscore}/standalone_32";             Description: "Standalone (32-bit)";                 Types: full custom;
Name: "{#AppNameUnderscore}/standalone_64";             Description: "Standalone (64-bit)";                 Types: full custom; Check: IsWin64;
Name: "{#AppNameUnderscore}/vst2_32";                   Description: "VST2 (32-bit)";                       Types: full custom;
Name: "{#AppNameUnderscore}/vst2_64";                   Description: "VST2 (64-bit)";                       Types: full custom; Check: IsWin64;
Name: "{#AppNameUnderscore}/vst3_32";                   Description: "VST3 (32-bit)";                       Types: full custom;
Name: "{#AppNameUnderscore}/vst3_64";                   Description: "VST3 (64-bit)";                       Types: full custom; Check: IsWin64;
Name: "{#AppNameUnderscore}_required";                  Description: "{#AppName} - Required Components";    Types: full custom; Flags: fixed;
Name: "{#AppNameUnderscore}_required/licenses";         Description: "Licenses";                            Types: full custom; Flags: fixed;
Name: "{#AppNameUnderscore}_required/factorypresets";   Description: "Factory Presets";                     Types: full custom; Flags: fixed;

[Files]
Source: "{#AppBuildDir}\Win32\Release\Standalone Plugin\{#AppName}.exe";  DestDir: "{pf32}\{#AppPublisher}\{#AppName}"; DestName: "{#AppName}.exe"; Components: {#AppNameUnderscore}/standalone_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppBuildDir}\x64\Release\Standalone Plugin\{#AppName}.exe";    DestDir: "{pf64}\{#AppPublisher}\{#AppName}"; DestName: "{#AppName}.exe"; Components: {#AppNameUnderscore}/standalone_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppBuildDir}\Win32\Release\VST\{#AppName}.dll";    DestDir: "{pf32}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppBuildDir}\x64\Release\VST\{#AppName}.dll";      DestDir: "{pf64}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppBuildDir}\Win32\Release\VST3\{#AppName}.vst3";   DestDir: "{cf32}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_32; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppBuildDir}\x64\Release\VST3\{#AppName}.vst3";     DestDir: "{cf64}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\LICENSE.txt";                DestDir: "{pf32}\{#AppPublisher}\{#AppName}\licenses";              DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\LICENSE.txt";                DestDir: "{pf64}\{#AppPublisher}\{#AppName}\licenses";              DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\sdks\frut\LICENSE";          DestDir: "{pf32}\{#AppPublisher}\{#AppName}\licenses\frut";         DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\frut\LICENSE";          DestDir: "{pf64}\{#AppPublisher}\{#AppName}\licenses\frut";         DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\sdks\grape\LICENSE";         DestDir: "{pf32}\{#AppPublisher}\{#AppName}\licenses\grape";        DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\grape\LICENSE";         DestDir: "{pf64}\{#AppPublisher}\{#AppName}\licenses\grape";        DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\sdks\juce\LICENSE.md";       DestDir: "{pf32}\{#AppPublisher}\{#AppName}\licenses\juce";         DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\juce\LICENSE.md";       DestDir: "{pf64}\{#AppPublisher}\{#AppName}\licenses\juce";         DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\sdks\pluginval\LICENSE";     DestDir: "{pf32}\{#AppPublisher}\{#AppName}\licenses\pluginval";    DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\pluginval\LICENSE";     DestDir: "{pf64}\{#AppPublisher}\{#AppName}\licenses\pluginval";    DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\sdks\vst\LICENSE.txt";       DestDir: "{pf32}\{#AppPublisher}\{#AppName}\licenses\vst";          DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\vst\LICENSE.txt";       DestDir: "{pf64}\{#AppPublisher}\{#AppName}\licenses\vst";          DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\installer\presets\*"; DestDir: "{app}\presets"; Components: {#AppNameUnderscore}_required/factorypresets; Flags: ignoreversion createallsubdirs recursesubdirs overwritereadonly uninsremovereadonly skipifsourcedoesntexist;

