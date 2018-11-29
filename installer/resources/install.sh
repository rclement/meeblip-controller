#!/bin/sh

INSTALL_DIR="/opt/${APP_MANUFACTURER_NAME}/${APP_NAME}"
USER_VST_DIR="$HOME/.vst"

sudo mkdir -p "$INSTALL_DIR"
mkdir -p "$USER_VST_DIR"

sudo cp "${APP_NAME}.AppImage" "$INSTALL_DIR/${APP_NAME}.AppImage"
sudo cp -R "presets" "$INSTALL_DIR/presets"
sudo cp -R "licenses" "$INSTALL_DIR/licenses"
sudo cp "uninstall.sh" "$INSTALL_DIR/uninstall.sh"
cp "${APP_NAME}.so" "$USER_VST_DIR/${APP_NAME}.so"
