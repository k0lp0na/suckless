#!/bin/bash

# Update system
echo "Updating system..."

sudo pacman -Syu --noconfirm

# mkr dir
echo "Making directories..."

mkdir -p  ~/Pictures/ss
mkdir -p  ~/.icons
mkdir -p  ~/.themes
mkdir -p  ~/Downloads

# Create symbolic links
echo "Syslinks..."
ln -sf ~/.config/suckless/config/*  ~/.config/
ln -sf ~/.config/suckless/scripts/* ~/.local/bin/

# Build and install DWM
echo "Building and installing DWM..."
cd dwm
sudo make clean install
rm -f drw.o dwm.o dwm-msg.o util.o config.h
cd ..

# Desktp file

echo "Creating desktop file..."

sudo touch /usr/share/xsessions/dwm.desktop

sudo tee /usr/share/xsessions/dwm.desktop > /dev/null << 'EOF'
[Desktop Entry]
Name=dwm
Comment=Dynamic window manager
Exec=dwm
Icon=dwm
Type=XSession
EOF

# icon for dunst

echo "dunst icon..."
sudo cp -r assets/BeautyLine /usr/share/icons/

# installing necessary app

sudo pacman -S --noconfirm --needed alacritty rofi dunst fish fastfetch kitty picom sxhkd yazi fzf zoxide pamixer maim xclip lsd ttf-jetbrains-mono-nerd polkit-gnome xorg-xsetroot acpi awk unzip brightnessctl playerctl imlib2 rofi-emoji xfce4-power-manager network-manager-applet bat xorg sddm

# Clipboard

echo "CLipboard"
wget -O ~/.local/bin/greenclip https://github.com/erebe/greenclip/releases/download/v4.2/greenclip
chmod +x ~/.local/bin/greenclip

# Change default shell to fish
echo "Changing default shell to fish..."
chsh -s "$(which fish)"

# promt
echo "Promt"
curl -s https://ohmyposh.dev/install.sh | bash -s

# dm
sudo systemctl disable display-manager.service
sudo systemctl enable sddm.service
echo "SDDM Enabled"

echo "Finished"