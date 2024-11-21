#!/bin/bash

# Update system
echo "Updating system..."
sudo pacman -Syu --noconfirm

# mkr dir
mkdir -p  ~/.config
mkdir -p  ~/Pictures/ss
mkdir -p  ~/.icons

# Create symbolic links
ln -sf ~/suckless/.dwm  ~/
ln -sf ~/suckless/config/*  ~/.config/

# Build and install DWM
echo "Building and installing DWM..."
cd dwm
sudo make clean install
rm -f drw.o dwm.o dwm-msg.o util.o config.h
cd ..

# Change default shell to fish
echo "Changing default shell to fish..."
chsh -s "$(which fish)"

# create the .desktop file

# Define the directory and file path
XSESSION_DIR="/usr/share/xsessions"
DESKTOP_FILE="$XSESSION_DIR/dwm.desktop"

# Create the directory if it does not exist
mkdir -p "$XSESSION_DIR"

# Create or overwrite the .desktop file with the specified contents
cat <<EOF | sudo tee "$DESKTOP_FILE" > /dev/null
[Desktop Entry]
Encoding=UTF-8
Name=dwm
Comment=Dynamic window manager
Exec=dwm
Icon=dwm
Type=XSession
EOF

# Fix touchpad configuration
echo "Configuring touchpad settings..."
CONFIG_FILE="/etc/X11/xorg.conf.d/40-libinput.conf"
CONFIG_CONTENT='Section "InputClass"
 Identifier "libinput touchpad"
 Driver "libinput"
 MatchIsTouchpad "on"
 Option "Tapping" "on"
 Option "NaturalScrolling" "on"
EndSection'

if [ ! -f "$CONFIG_FILE" ]; then
    echo "Creating $CONFIG_FILE"
fi

echo "$CONFIG_CONTENT" | sudo tee -a "$CONFIG_FILE" > /dev/null
echo "Touchpad configuration added successfully."

# icon for dunst
cp icon/BeautyLine ~/.icons/

# installing necessary app

sudo pacman -S --noconfirm alacritty rofi dunst fish fastfetch kitty mpv picom sxhkd yazi fzf zoxide pamixer maim xclip lsd nitrogen ttf-jetbrains-mono-nerd lxappearance noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra polkit-gnome xorg-xsetroot acpi awk

# promt

curl -s https://ohmyposh.dev/install.sh | bash -s

