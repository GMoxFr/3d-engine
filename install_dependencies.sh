#!/bin/bash

# Function to detect the OS
detect_os() {
    unameOut="$(uname -s)"
    case "${unameOut}" in
        Linux*)     machine=Linux;;
        Darwin*)    machine=Mac;;
        *)          machine="UNKNOWN:${unameOut}"
    esac
    echo ${machine}
}

# Function to install dependencies on Linux
install_linux() {
    echo "Installing dependencies for Linux..."
    
    sudo apt-get update
    sudo apt-get install -y build-essential libsfml-dev make pkg-config
}

# Function to install dependencies on macOS
install_mac() {
    echo "Installing dependencies for macOS..."
    
    # Check for Homebrew, install if we don't have it
    if test ! $(which brew); then
        echo "Installing homebrew..."
        ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    fi
    brew install sfml make openal-soft
}

OS=$(detect_os)

if [ "$OS" == "Linux" ]; then
    install_linux
elif [ "$OS" == "Mac" ]; then
    install_mac
else
    echo "Unsupported OS"
    exit 1
fi
