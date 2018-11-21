cmake_minimum_required(VERSION 3.4)

# load app metadata
file(STRINGS "metadata.txt" AppMetadata)
foreach(metadata ${AppMetadata})
  string(REGEX REPLACE "^[ ]+" "" metadata ${metadata})
  string(REGEX MATCH "^[^=]+" key ${metadata})
  string(REPLACE "${key}=" "" value ${metadata})
  set(${key} "${value}")
endforeach()

# set extra metadata
set(APP_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")
if(APPLE)
    set(APP_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    set(APP_OUTPUT_BASENAME "${APP_NAME} - ${APP_VERSION} - MacOS")
else()
    set(APP_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/..")
    set(APP_OUTPUT_BASENAME "${APP_NAME} - ${APP_VERSION} - Windows")
endif()
set(APP_OUTPUT_DIR "${APP_BUILD_DIR}/installer/output")

# generate template files
configure_file(
    "${APP_ROOT_DIR}/installer/meeblip-controller.pkgproj"
    "${APP_BUILD_DIR}/installer/meeblip-controller.pkgproj"
)

configure_file(
    "${APP_ROOT_DIR}/installer/meeblip-controller.iss"
    "${APP_BUILD_DIR}/installer/meeblip-controller.iss"
)

project("${APP_NAME}")

list(APPEND CMAKE_MODULE_PATH "${APP_ROOT_DIR}/sdks/frut/prefix/FRUT/cmake")
include(Reprojucer)

jucer_project_begin(
)

jucer_project_settings(
  PROJECT_TYPE "Audio Plug-in"
  PROJECT_NAME "${APP_NAME}"
  PROJECT_VERSION "${APP_VERSION}"

  COMPANY_NAME "${APP_MANUFACTURER_NAME}"
  COMPANY_COPYRIGHT "${APP_MANUFACTURER_NAME}"
  COMPANY_WEBSITE "${APP_MANUFACTURER_URL}"
  COMPANY_EMAIL "${APP_MANUFACTURER_EMAIL}"

  REPORT_JUCE_APP_USAGE OFF
  DISPLAY_THE_JUCE_SPLASH_SCREEN OFF
  # SPLASH_SCREEN_COLOUR

  BUNDLE_IDENTIFIER "${APP_BUNDLE_ID}"

  INCLUDE_BINARYDATA ON
  BINARYDATA_NAMESPACE "AssetsData"
  # BINARYDATACPP_SIZE_LIMIT

  CXX_LANGUAGE_STANDARD "C++14"
  PREPROCESSOR_DEFINITIONS
    "DONT_SET_USING_JUCE_NAMESPACE=1"
    "JUCE_VST3_CAN_REPLACE_VST2=1"
  HEADER_SEARCH_PATHS
    "sdks/grape"
    "src"
)

jucer_audio_plugin_settings(
  PLUGIN_FORMATS
    "AU"
    "Standalone"
    "VST"
    "VST3"

  # PLUGIN_CHARACTERISTICS

  PLUGIN_NAME "${APP_NAME}"
  PLUGIN_DESCRIPTION "${APP_DESCRIPTION}"

  PLUGIN_MANUFACTURER "${APP_MANUFACTURER_NAME}"
  PLUGIN_MANUFACTURER_CODE "RMNC"
  PLUGIN_CODE "MBCT"

  # PLUGIN_CHANNEL_CONFIGURATIONS

  PLUGIN_MIDI_INPUT ON
  PLUGIN_MIDI_OUTPUT ON
  MIDI_EFFECT_PLUGIN ON

  PLUGIN_AAX_IDENTIFIER "${APP_BUNDLE_ID}"
  PLUGIN_AU_EXPORT_PREFIX "MeeblipControllerAU"

  PLUGIN_AU_MAIN_TYPE
    "kAudioUnitType_Effect"
  PLUGIN_VST_CATEGORY
    "kPlugCategUnknown"
  PLUGIN_VST3_CATEGORY
    "External"
  PLUGIN_RTAS_CATEGORY
    "ePlugInCategory_None"
  PLUGIN_AAX_CATEGORY
    "AAX_ePlugInCategory_None"
)

jucer_project_files("Grape/helpers"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "sdks/grape/grape/helpers/Helpers.cpp"
  .         .         .         "sdks/grape/grape/helpers/Helpers.h"
)

jucer_project_files("Grape/parameters"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "sdks/grape/grape/parameters/Parameter.cpp"
  .         .         .         "sdks/grape/grape/parameters/Parameter.h"
  x         .         .         "sdks/grape/grape/parameters/ParameterManager.cpp"
  .         .         .         "sdks/grape/grape/parameters/ParameterManager.h"
)

jucer_project_files("Grape/presets"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "sdks/grape/grape/presets/Preset.cpp"
  .         .         .         "sdks/grape/grape/presets/Preset.h"
  x         .         .         "sdks/grape/grape/presets/PresetChecker.cpp"
  .         .         .         "sdks/grape/grape/presets/PresetChecker.h"
  x         .         .         "sdks/grape/grape/presets/PresetManager.cpp"
  .         .         .         "sdks/grape/grape/presets/PresetManager.h"
)

jucer_project_files("Grape/settings"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "sdks/grape/grape/settings/Setting.cpp"
  .         .         .         "sdks/grape/grape/settings/Setting.h"
  x         .         .         "sdks/grape/grape/settings/SettingManager.cpp"
  .         .         .         "sdks/grape/grape/settings/SettingManager.h"
)

jucer_project_files("MeeblipController/assets/fonts"
# Compile   Xcode     Binary
#           Resource  Resource
  .         .         x         "src/assets/fonts/montserrat/Montserrat-ExtraLight.ttf"
  .         .         x         "src/assets/fonts/montserrat/Montserrat-Regular.ttf"
)

jucer_project_files("MeeblipController/assets/png"
# Compile   Xcode     Binary
#           Resource  Resource
  .         .         x         "src/assets/png/anode-logo-white.png"
  .         .         x         "src/assets/png/mbctrl-logo-white.png"
  .         .         x         "src/assets/png/meeblip-logo-white.png"
)

jucer_project_files("MeeblipController/assets/svg"
# Compile   Xcode     Binary
#           Resource  Resource
  .         .         x         "src/assets/svg/left-arrow.svg"
  .         .         x         "src/assets/svg/right-arrow.svg"
  .         .         x         "src/assets/svg/sync-arrow.svg"
)

jucer_project_files("MeeblipController/common"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "src/common/Parameters.cpp"
  .         .         .         "src/common/Parameters.h"
  x         .         .         "src/common/Settings.cpp"
  .         .         .         "src/common/Settings.h"
)

jucer_project_files("MeeblipController/controller"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "src/controller/MidiController.cpp"
  .         .         .         "src/controller/MidiController.h"
)

jucer_project_files("MeeblipController/ui"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "src/ui/CustomLookAndFeel.cpp"
  .         .         .         "src/ui/CustomLookAndFeel.h"
)

jucer_project_files("MeeblipController/ui/components"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "src/ui/components/AboutDialog.cpp"
  .         .         .         "src/ui/components/AboutDialog.h"
  x         .         .         "src/ui/components/ControlKnob.cpp"
  .         .         .         "src/ui/components/ControlKnob.h"
  x         .         .         "src/ui/components/ControlList.cpp"
  .         .         .         "src/ui/components/ControlList.h"
  x         .         .         "src/ui/components/ControlToggle.cpp"
  .         .         .         "src/ui/components/ControlToggle.h"
  x         .         .         "src/ui/components/PresetBar.cpp"
  .         .         .         "src/ui/components/PresetBar.h"
  x         .         .         "src/ui/components/PresetSaveDialog.cpp"
  .         .         .         "src/ui/components/PresetSaveDialog.h"
)

jucer_project_files("MeeblipController/ui/panels"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "src/ui/panels/ControlPanelAnode.cpp"
  .         .         .         "src/ui/panels/ControlPanelAnode.h"
  x         .         .         "src/ui/panels/PresetPanel.cpp"
  .         .         .         "src/ui/panels/PresetPanel.h"
  x         .         .         "src/ui/panels/SettingsPanel.cpp"
  .         .         .         "src/ui/panels/SettingsPanel.h"
)

jucer_project_files("MeeblipController/plugin"
# Compile   Xcode     Binary
#           Resource  Resource
  x         .         .         "src/plugin/PluginProcessor.cpp"
  .         .         .         "src/plugin/PluginProcessor.h"
  x         .         .         "src/plugin/PluginEditor.cpp"
  .         .         .         "src/plugin/PluginEditor.h"
)

jucer_project_module(
  juce_audio_basics
  PATH "sdks/juce/modules"
)

jucer_project_module(
  juce_audio_devices
  PATH "sdks/juce/modules"
  # JUCE_ASIO
  # JUCE_WASAPI
  # JUCE_WASAPI_EXCLUSIVE
  # JUCE_DIRECTSOUND
  # JUCE_ALSA
  # JUCE_JACK
  # JUCE_BELA
  # JUCE_USE_ANDROID_OBOE
  # JUCE_USE_ANDROID_OPENSLES
  # JUCE_USE_WINRT_MIDI
  # JUCE_DISABLE_AUDIO_MIXING_WITH_OTHER_APPS
)

jucer_project_module(
  juce_audio_formats
  PATH "sdks/juce/modules"
  # JUCE_USE_FLAC
  # JUCE_USE_OGGVORBIS
  # JUCE_USE_MP3AUDIOFORMAT
  # JUCE_USE_LAME_AUDIO_FORMAT
  # JUCE_USE_WINDOWS_MEDIA_FORMAT
)

jucer_project_module(
  juce_audio_plugin_client
  PATH "sdks/juce/modules"
  # JUCE_FORCE_USE_LEGACY_PARAM_IDS
  # JUCE_FORCE_LEGACY_PARAMETER_AUTOMATION_TYPE
  # JUCE_USE_STUDIO_ONE_COMPATIBLE_PARAMETERS
  # JUCE_STANDALONE_FILTER_WINDOW_USE_KIOSK_MODE
)

jucer_project_module(
  juce_audio_processors
  PATH "sdks/juce/modules"
  # JUCE_PLUGINHOST_VST
  # JUCE_PLUGINHOST_VST3
  # JUCE_PLUGINHOST_AU
  # JUCE_PLUGINHOST_LADSPA
)

jucer_project_module(
  juce_audio_utils
  PATH "sdks/juce/modules"
  # JUCE_USE_CDREADER
  # JUCE_USE_CDBURNER
)

jucer_project_module(
  juce_core
  PATH "sdks/juce/modules"
  # JUCE_FORCE_DEBUG
  # JUCE_LOG_ASSERTIONS
  # JUCE_CHECK_MEMORY_LEAKS
  # JUCE_DONT_AUTOLINK_TO_WIN32_LIBRARIES
  # JUCE_INCLUDE_ZLIB_CODE
  # JUCE_USE_CURL
  # JUCE_CATCH_UNHANDLED_EXCEPTIONS
  # JUCE_ALLOW_STATIC_NULL_VARIABLES
)

jucer_project_module(
  juce_data_structures
  PATH "sdks/juce/modules"
)

jucer_project_module(
  juce_events
  PATH "sdks/juce/modules"
  # JUCE_EXECUTE_APP_SUSPEND_ON_IOS_BACKGROUND_TASK
)

jucer_project_module(
  juce_graphics
  PATH "sdks/juce/modules"
  # JUCE_USE_COREIMAGE_LOADER
  # JUCE_USE_DIRECTWRITE
)

jucer_project_module(
  juce_gui_basics
  PATH "sdks/juce/modules"
  # JUCE_ENABLE_REPAINT_DEBUGGING
  # JUCE_USE_XRANDR
  # JUCE_USE_XINERAMA
  # JUCE_USE_XSHM
  # JUCE_USE_XRENDER
  # JUCE_USE_XCURSOR
)

jucer_project_module(
  juce_gui_extra
  PATH "sdks/juce/modules"
  # JUCE_WEB_BROWSER
  # JUCE_ENABLE_LIVE_CONSTANT_EDITOR
)

jucer_export_target(
  "Xcode (MacOSX)"
  VST3_SDK_FOLDER
    "sdks/vst"
  ICON_SMALL
    "installer/resources/app-icon@1x.png"
  ICON_LARGE
    "installer/resources/app-icon@2x.png"
)

jucer_export_target_configuration(
  "Xcode (MacOSX)"
  NAME "Debug"
  DEBUG_MODE ON
  OSX_DEPLOYMENT_TARGET
    "10.9"
  OSX_ARCHITECTURE
    "64-bit Intel"
)

jucer_export_target_configuration(
  "Xcode (MacOSX)"
  NAME "Release"
  DEBUG_MODE OFF
  OSX_DEPLOYMENT_TARGET
    "10.9"
  OSX_ARCHITECTURE
    "64-bit Intel"
)

jucer_export_target(
  "Visual Studio 2017"
  VST3_SDK_FOLDER
    "sdks/vst"
  ICON_SMALL
    "installer/resources/app-icon@1x.png"
  ICON_LARGE
    "installer/resources/app-icon@2x.png"
)

jucer_export_target_configuration(
  "Visual Studio 2017"
  NAME "Debug"
  DEBUG_MODE ON
)

jucer_export_target_configuration(
  "Visual Studio 2017"
  NAME "Release"
  DEBUG_MODE OFF
)

jucer_export_target(
  "Linux Makefile"
  VST3_SDK_FOLDER
    "sdks/vst"
  ICON_SMALL
    "installer/resources/app-icon@1x.png"
  ICON_LARGE
    "installer/resources/app-icon@2x.png"
)

jucer_export_target_configuration(
  "Linux Makefile"
  NAME "Debug"
  DEBUG_MODE ON
)

jucer_export_target_configuration(
  "Linux Makefile"
  NAME "Release"
  DEBUG_MODE OFF
)

jucer_project_end()
