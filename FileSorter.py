#!/usr/bin/env python
import sys
import os.path
import math
import random
#import ROOT as r

runs0 = []
runs1 = []
runs2 = []
runs3 = []
runs4 = []
runs5 = []
runs6 = []
runs7 = []
runs8 = []
runs9 = []
linecount=0
for line in open("files_400to500.txt"):
    temp=line.split()
    if linecount%10 == 0 : runs0.append(temp[0])
    if linecount%10 == 1 : runs1.append(temp[0])
    if linecount%10 == 2 : runs2.append(temp[0])
    if linecount%10 == 3 : runs3.append(temp[0])
    if linecount%10 == 4 : runs4.append(temp[0])
    if linecount%10 == 5 : runs5.append(temp[0])
    if linecount%10 == 6 : runs6.append(temp[0])
    if linecount%10 == 7 : runs7.append(temp[0])
    if linecount%10 == 8 : runs8.append(temp[0])
    if linecount%10 == 9 : runs9.append(temp[0])
    linecount = linecount+1
    
file0 = open('Runs0_400to500.txt','w')
file0.write("UsefulStuff/src/histoAdd -f Sum0_400to500.root ")
for itom in runs0:
    file0.write("%s " %itom)
file0.close()

file1 = open('Runs1_400to500.txt','w')
file1.write("UsefulStuff/src/histoAdd -f Sum1_400to500.root ")
for itom in runs1:
    file1.write("%s " %itom)
file1.close()

file2 = open('Runs2_400to500.txt','w')
file2.write("UsefulStuff/src/histoAdd -f Sum2_400to500.root ")
for itom in runs2:
    file2.write("%s " %itom)
file2.close()

file3 = open('Runs3_400to500.txt','w')
file3.write("UsefulStuff/src/histoAdd -f Sum3_400to500.root ")
for itom in runs3:
    file3.write("%s " %itom)
file3.close()

file4 = open('Runs4_400to500.txt','w')
file4.write("UsefulStuff/src/histoAdd -f Sum4_400to500.root ")
for itom in runs4:
    file4.write("%s " %itom)
file4.close()

file5 = open('Runs5_400to500.txt','w')
file5.write("UsefulStuff/src/histoAdd -f Sum5_400to500.root ")
for itom in runs5:
    file5.write("%s " %itom)
file5.close()

file6 = open('Runs6_400to500.txt','w')
file6.write("UsefulStuff/src/histoAdd -f Sum6_400to500.root ")
for itom in runs6:
    file6.write("%s " %itom)
file6.close()

file7 = open('Runs7_400to500.txt','w')
file7.write("UsefulStuff/src/histoAdd -f Sum7_400to500.root ")
for itom in runs7:
    file7.write("%s " %itom)
file7.close()

file8 = open('Runs8_400to500.txt','w')
file8.write("UsefulStuff/src/histoAdd -f Sum8_400to500.root ")
for itom in runs8:
    file8.write("%s " %itom)
file8.close()

file9 = open('Runs9_400to500.txt','w')
file9.write("UsefulStuff/src/histoAdd -f Sum9_400to500.root ")
for itom in runs9:
    file9.write("%s " %itom)
file9.close()
