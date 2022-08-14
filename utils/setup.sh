#!/bin/bash

sudo apt-get install git ssh vim texlive-full

echo "configuring vim..."

echo "set tabstop=4" >>  $HOME/.vimrc
echo "set autoindent" >>  $HOME/.vimrc
echo ":map z o<Esc>" >>  $HOME/.vimrc
echo ":map t 0i<tab><Esc>j" >>  $HOME/.vimrc
echo ":map dt 0x" >>  $HOME/.vimrc
echo ":map dd dd_" >>  $HOME/.vimrc
echo ":map q \$xj" >>  $HOME/.vimrc
echo ":map s 0i<space><space><space><space><Esc>j" >>  $HOME/.vimrc

echo "vim configured"

echo "configuring bash..."

echo "alias vss='cd /home/kenji/Documents/ITAndroids/itandroids-vss/binaries'" >> $HOME/.bashrc
echo "alias lib='cd /home/kenji/Documents/ITAndroids/itandroids-lib'" >> $HOME/.bashrc
echo "alias firasim='cd /home/kenji/Documents/ITAndroids/FIRASim/bin'" >> $HOME/.bashrc
echo "alias referee='cd /home/kenji/Documents/ITAndroids/VSSReferee/bin'" >> $HOME/.bashrc

echo "bash configured"

sudo apt-get install gimp poppler-utils

