#!/bin/sh

#####################
# Setup linuxdeploy #
#####################

DEPLOY_NAME="linuxdeploy"
DEPLOY_BIN="linuxdeploy-x86_64.AppImage"

if [ ! -f $DEPLOY_BIN ]; then
    wget "https://github.com/$DEPLOY_NAME/$DEPLOY_NAME/releases/download/continuous/$DEPLOY_BIN"
fi

chmod +x $DEPLOY_BIN

#########################
# Setup output binaries #
#########################

cp "${APP_BUILD_DIR}/${APP_NAME}" "${APP_BUILD_DIR}/${APP_NAME_SAFE}"

#################
# Make AppImage #
#################

./$DEPLOY_BIN \
    --output appimage \
    --appdir="${APP_BUILD_DIR}/AppDir" \
    --executable="${APP_BUILD_DIR}/${APP_NAME_SAFE}" \
    --desktop-file="${APP_BUILD_DIR}/installer/resources/application.desktop" \
    --icon-file="${APP_ROOT_DIR}/installer/resources/appimage-icon.png"

###########
# Cleanup #
###########

rm $DEPLOY_BIN
rm "${APP_BUILD_DIR}/${APP_NAME_SAFE}"

#################
# Deploy output #
#################

mkdir -p "${APP_OUTPUT_DIR}"
mkdir -p "${APP_OUTPUT_DIR}/licenses"
mkdir -p "${APP_OUTPUT_DIR}/licenses/frut"
mkdir -p "${APP_OUTPUT_DIR}/licenses/grape"
mkdir -p "${APP_OUTPUT_DIR}/licenses/juce"
mkdir -p "${APP_OUTPUT_DIR}/licenses/pluginval"
mkdir -p "${APP_OUTPUT_DIR}/licenses/vst"

mv *.AppImage "${APP_OUTPUT_DIR}/${APP_NAME}.AppImage"
cp "${APP_BUILD_DIR}/lib${APP_NAME}.so" "${APP_OUTPUT_DIR}/${APP_NAME}.so"
cp -R "${APP_ROOT_DIR}/installer/presets" "${APP_OUTPUT_DIR}/presets"
cp -R "${APP_ROOT_DIR}/LICENSE.txt" "${APP_OUTPUT_DIR}/licenses/LICENSE.txt"
cp -R "${APP_ROOT_DIR}/sdks/frut/LICENSE" "${APP_OUTPUT_DIR}/licenses/frut/LICENSE.txt"
cp -R "${APP_ROOT_DIR}/sdks/grape/LICENSE" "${APP_OUTPUT_DIR}/licenses/grape/LICENSE.txt"
cp -R "${APP_ROOT_DIR}/sdks/juce/LICENSE.md" "${APP_OUTPUT_DIR}/licenses/juce/LICENSE.txt"
cp -R "${APP_ROOT_DIR}/sdks/pluginval/LICENSE" "${APP_OUTPUT_DIR}/licenses/pluginval/LICENSE.txt"
cp -R "${APP_ROOT_DIR}/sdks/vst/LICENSE.txt" "${APP_OUTPUT_DIR}/licenses/vst/LICENSE.txt"

cp "${APP_BUILD_DIR}/installer/resources/install.sh" "${APP_OUTPUT_DIR}/install.sh"
cp "${APP_BUILD_DIR}/installer/resources/uninstall.sh" "${APP_OUTPUT_DIR}/uninstall.sh"

