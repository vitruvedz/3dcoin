
Debian
====================
This directory contains files used to package 3dcoind/3dcoin-qt
for Debian-based Linux systems. If you compile 3dcoind/3dcoin-qt yourself, there are some useful files here.

## 3dcoin: URI support ##


3dcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install 3dcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your 3dcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/3dcoin128.png` to `/usr/share/pixmaps`

3dcoin-qt.protocol (KDE)

