#!/bin/bash

# Enable tap-to-click and natural scrolling for touchpad
echo "fixing touchpad"
sudo touch /etc/X11/xorg.conf.d/40-libinput.conf
sudo tee /etc/X11/xorg.conf.d/40-libinput.conf > /dev/null << 'EOF'
Section "InputClass"
    Identifier "libinput touchpad"
    Driver "libinput"
    MatchIsTouchpad "on"
    Option "Tapping" "on"
    Option "NaturalScrolling" "on"
EndSection
EOF

# Other pkg
sudo pacman -S --needed --noconfirm python-pip lxappearance noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra nemo mpv nano nitrogen qt5ct qt6ct htop btop cmus spotify-launcher


# Set QT and Java environment variables
echo "Setting environment variables..."

# Set QT_QPA_PLATFORMTHEME in /etc/environment
if ! grep -q "^QT_QPA_PLATFORMTHEME=qt5ct" /etc/environment; then
    echo "QT_QPA_PLATFORMTHEME=qt5ct" | sudo tee -a /etc/environment > /dev/null
fi

# Set _JAVA_AWT_WM_NONREPARENTING in /etc/profile
if ! grep -q "^export _JAVA_AWT_WM_NONREPARENTING=1" /etc/profile; then
    echo "export _JAVA_AWT_WM_NONREPARENTING=1" | sudo tee -a /etc/profile > /dev/null
fi

echo "Environment variables set successfully."


# Setup Python virtual environment
echo "Setting up Python virtual environment..."
python -m venv ~/.mv
source ~/.mv/bin/activate
pip install anipy-cli

# setup paru

echo "Setting up PARU"
sudo pacman -S --needed base-devel
git clone --depth 1 https://aur.archlinux.org/paru.git ~/Downloads/paru
cd ~/Downloads/paru
makepkg -si
rm -r ~/Downloads/paru

#  browser 

paru -S --noconfirm --needed brave-bin

echo "DOE!"