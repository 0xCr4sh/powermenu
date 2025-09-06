#!/usr/bin/bash

set -e  # stop on errors

APP_NAME="powermenu"
INSTALL_DIR="/usr/local/bin"
CONFIG_DIR="$HOME/.config/0xCr4sh-powermenu"

echo "Building $APP_NAME..."
sudo mkdir -p build
cd build
sudo cmake ..
sudo cmake --build .
cd ..
echo "Build completed."

echo "Installing binary to $INSTALL_DIR..."
sudo cp build/$APP_NAME $INSTALL_DIR

echo "Installing default configs to $CONFIG_DIR..."
mkdir -p "$CONFIG_DIR"
sudo cp -rf configs/* "$CONFIG_DIR/"

# Hyprland rules
echo "Configuring Hyprland rules..."
RULE_FLOAT="windowrulev2 = float, class:^(com.powermenu.app)\$"
RULE_FULLSCREEN="windowrulev2 = fullscreen, class:^(com.powermenu.app)\$"

echo "Adding rules to Hyprland config..."
HYPR_CONF="$HOME/.config/hypr/hyprland.conf"

# Append rules only if not already present
grep -qxF "$RULE_FLOAT" "$HYPR_CONF" 2>/dev/null || echo "$RULE_FLOAT" >> "$HYPR_CONF"
grep -qxF "$RULE_FULLSCREEN" "$HYPR_CONF" 2>/dev/null || echo "$RULE_FULLSCREEN" >> "$HYPR_CONF"

echo "Done! Installed and configured."