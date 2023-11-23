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

# Function to install dependencies with apt-get (Debian/Ubuntu)
install_apt() {
    echo "Installing dependencies using apt-get..."
    sudo apt-get update
    sudo apt-get install -y build-essential libsfml-dev make pkg-config nlohmann-json3-dev
}

# Function to install dependencies with pacman (Arch)
install_pacman() {
    echo "Installing dependencies using pacman..."
    sudo pacman -Syu --needed base-devel sfml make pkgconf nlohmann-json
}

# # Function to install dependencies with yum (CentOS)
# install_yum() {
#     echo "Installing dependencies using yum..."
#     sudo yum update
#     sudo yum install -y gcc gcc-c++ make sfml-devel nlohmann-json-devel
# }

# # Function to install dependencies with dnf (Fedora)
# install_dnf() {
#     echo "Installing dependencies using dnf..."
#     sudo dnf update
#     sudo dnf install -y gcc gcc-c++ make SFML-devel nlohmann-json-devel
# }

# # Function to install dependencies with zypper (OpenSUSE)
# install_zypper() {
#     echo "Installing dependencies using zypper..."
#     sudo zypper refresh
#     sudo zypper install -y gcc gcc-c++ make sfml-devel nlohmann-json-devel
# }

# Function to install dependencies on Linux
install_linux() {
    echo "Installing dependencies for Linux..."
    
    if command -v apt-get >/dev/null 2>&1; then
        install_apt
    elif command -v pacman >/dev/null 2>&1; then
        install_pacman
    # elif command -v yum >/dev/null 2>&1; then
    #     install_yum
    # elif command -v dnf >/dev/null 2>&1; then
    #     install_dnf
    # elif command -v zypper >/dev/null 2>&1; then
    #     install_zypper
    else
        echo "Unsupported package manager. Supported: apt, pacman, yum, dnf, zypper."
        exit 1
    fi
}

# Function to install dependencies on macOS
install_mac() {
    echo "Installing dependencies for macOS..."

    # Check for Homebrew
    if command -v brew >/dev/null 2>&1; then
        echo "Using Homebrew to install packages..."
        brew install sfml make openal-soft nlohmann-json
    # Check for MacPorts
    elif command -v port >/dev/null 2>&1; then
        echo "Using MacPorts to install packages..."
        sudo port selfupdate
        sudo port install sfml make openal-soft nlohmann-json
    else
        # Neither Homebrew nor MacPorts is installed, proceed to install Homebrew
        echo "Neither Homebrew nor MacPorts detected. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        brew install sfml make openal-soft nlohmann-json
    fi
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
