#!/usr/bin/env python3
from sys import stdin
from statistics import mean

portal = stdin.read()
portal = portal.split()

grades = [portal[3*i + 2] for i in range(len(portal)//3) if portal[3*i + 2] not in ['S', 'SC']]
print(len(grades))
print(grades)
print(mean([float(grades[i]) for i in range(len(grades))]))
