#!/bin/bash

xsetroot -cursor_name left_ptr

# Start picom (compositor)
picom &

# Restore the wallpaper using nitrogen
nitrogen --restore &

dunst &

/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

xfce4-power-manager&

pkill -x greenclip
pgrep -x greenclip > /dev/null || greenclip daemon &


pkill -x sxhkd
pgrep -x sxhkd > /dev/null || sxhkd &


~/.dwm/bar.sh
