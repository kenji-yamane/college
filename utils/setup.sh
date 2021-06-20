#!/bin/bash

sudo apt-get install git ssh vim texlive-full
echo "set tabstop=4" >>  $HOME/.vimrc
echo "set autoindent" >>  $HOME/.vimrc
echo ":map z o<Esc>" >>  $HOME/.vimrc
echo ":map t 0i<tab><Esc>j" >>  $HOME/.vimrc
echo ":map dt 0x" >>  $HOME/.vimrc
echo ":map dd dd_" >>  $HOME/.vimrc
echo ":map q \$xj" >>  $HOME/.vimrc
echo ":map s 0i<space><space><space><space><Esc>j" >>  $HOME/.vimrc

sudo apt-get install gimp poppler-utils

