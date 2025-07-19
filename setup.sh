#!/bin/bash

# Define target directory
INSTALL_DIR="$HOME/.nlsh"

echo "Creating installation directory at $INSTALL_DIR..."
mkdir -p "$INSTALL_DIR"

echo "Copying nlsh binary, Python scripts, and .env file..."
cp nlsh "$INSTALL_DIR"
cp nlp_translate.py "$INSTALL_DIR"
cp .env "$INSTALL_DIR" 2>/dev/null

echo "🔧 Adding $INSTALL_DIR to your PATH in ~/.zshrc if not already present..."
if ! grep -q 'export PATH="$HOME/.nlsh:$PATH"' "$HOME/.zshrc"; then
    echo 'export PATH="$HOME/.nlsh:$PATH"' >> "$HOME/.zshrc"
    echo "✅ PATH updated. Run 'source ~/.zshrc' to apply changes."
else
    echo "✅ PATH already set."
fi

echo "Done! You can now run your shell by typing: nlsh"