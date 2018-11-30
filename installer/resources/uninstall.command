#!/bin/sh

sudo rm -rf "/Applications/${APP_NAME}.app"
sudo rm -rf "/Library/Audio/Plug-Ins/VST3/${APP_NAME}.vst3"
sudo rm -rf "/Library/Audio/Plug-Ins/VST/${APP_NAME}.vst"
sudo rm -rf "/Library/Audio/Plug-Ins/Components/${APP_NAME}.component"
sudo rm -rf "/Library/Application Support/${APP_MANUFACTURER_NAME}/${APP_NAME}/presets"
sudo rm -rf "/Library/Application Support/${APP_MANUFACTURER_NAME}/${APP_NAME}/licenses"
sudo rm -rf "/Library/Application Support/${APP_MANUFACTURER_NAME}/${APP_NAME}/uninstall.command"

