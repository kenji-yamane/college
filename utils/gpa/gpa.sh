#!/bin/bash

xclip -selection clipboard -o | xargs | tr ',' '.' | ./gpa.py

