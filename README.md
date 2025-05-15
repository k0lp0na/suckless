# 🖼️ SHOOW CASE

![Alt text](assets/previews/1.png?raw=true "Optional Title")
![Alt text](assets/previews/2.png?raw=true "Optional Title")
![Alt text](assets/previews/3.png?raw=true "Optional Title")


## Software 

+ **Window Manager** = Dynamic window manager
   - patched with 25+ patches including 9 Layouts and scratchpads

+ **Terminal** : Alacritty, kitty.

+ **Shell** : Fish.
   - with zoxide , fzf , lsd and oh-my-posh.

+ **Text Editor** : Nano

+ **File Browser**
  -  **TUI** : Kitty + yazi
  -  **GUI** : Nemo

+ **Launcher** : Rofi.
  - with greenclip and rofi-emoji.

+ **Notification** : Dunst.

+ **Compositor** : Picom.

+ **Hotkey Daemon** : SXHKD.

+ **Screenshot utility** : Maim with xclip

+ **Music** : Cmus and Spotify.

+ **Colors** : Gruvbox.

+ **Fonts** : Jetbrains Mono Nerd Font and Noto Sans CJK.

+ **Icons** : https://github.com/Fausto-Korpsvart/Gruvbox-GTK-Theme/tree/master/icons

+ **Cursor** : https://github.com/phisch/phinger-cursors

+ **GTK Theme** : I forgor💀

+ **Login Mananger** : SDDM


## Instalation

connect to the internet

```
nmcli device wifi connect !name! password !psswd!
```

config pacman 

```
sudo nano /etc/pacman.conf
```

and add

```
Color
CheckSpace
VerbosePkgLists
ParallelDownloads = 5
ILoveCandy
```

install git and reflector

```
sudo pacman -S git reflector
```

fic mirrors

```
sudo reflector --country 'Bangladesh' --latest 10 --sort rate --save /etc/pacman.d/mirrorlist 
```

cd into .config

```
mkdir -p ~/.config
cd ~/.config/
```

clone the repo and run the install script

```
git clone --depth 1 https://github.com/k0lp0na/Suckless.git

cd suckless/

./install[arch].sh
```
Optionally run extras (please read it before running)

```
./extras.sh
```

REboot into your new environment and enjoy 💙
