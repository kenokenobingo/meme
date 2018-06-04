#!/bin/bash

# Meme Package Manager Installer
# Author: K E N O
# only for macOS right now
# slightly intrusive installer script

username=$(whoami)
tmp_dir=~./meme_tmp

# Borrowed from the lein downloader
HTTP_CLIENT=${HTTP_CLIENT:-"wget -O"}
if type -p curl >/dev/null 2>&1; then
    if [ "$https_proxy" != "" ]; then
        CURL_PROXY="-x $https_proxy"
    fi
    HTTP_CLIENT="curl $CURL_PROXY -f -k -L -o"
fi

# Check to see if Homebrew is installed, and install it if it is not
command -v brew >/dev/null 2>&1 || { echo >&2 "Installing Homebrew Now"; \
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"; }

# Install dependencies
brew install asciidoc automake gcc gpg gettext make openssl

# Create temporary directory for working within
rm -rf $tmp_dir
mkdir $tmp_dir

# Get the latest release and install it
$HTTP_CLIENT $tmp_dir/meme_install.zip https://github.com/kenokenobingo/meme/archive/0.0.1.zip
unzip meme_install.zip
cd meme_install
./autogen.sh
./configure
make
sudo make install

echo "Have fun!"
