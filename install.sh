#!/usr/bin/bash

set -e  # stop on errors

APP_NAME="powermenu"
INSTALL_DIR="/usr/local/bin"
CONFIG_DIR="$HOME/.config/0xCr4sh-powermenu"

echo "Building $APP_NAME..."
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..
echo "Build completed."

echo "Installing binary to $INSTALL_DIR..."
sudo cp build/$APP_NAME $INSTALL_DIR

echo "Installing default configs to $CONFIG_DIR..."
mkdir -p "$CONFIG_DIR"
cp -r configs/* "$CONFIG_DIR/"

echo "Done! Installing"