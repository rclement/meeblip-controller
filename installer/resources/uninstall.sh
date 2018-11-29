#!/bin/sh

INSTALL_DIR="/opt/${APP_MANUFACTURER_NAME}/${APP_NAME}"
USER_VST_DIR="$HOME/.vst"

sudo rm -rf "$INSTALL_DIR/${APP_NAME}.AppImage"
sudo rm -rf "$INSTALL_DIR/presets"
sudo rm -rf "$INSTALL_DIR/licenses"
rm -rf "$USER_VST_DIR/${APP_NAME}.so"
sudo rm -rf "$INSTALL_DIR/uninstall.sh"
