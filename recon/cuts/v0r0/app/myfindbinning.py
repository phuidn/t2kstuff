#!/usr/bin/python2.6
# It doesnt work with over 400 lines in the file!
# WHHYYY!
import csv
import array
import numpy as np

truth_kin = ([])
recon_kin = ([])

file = open("kinetic-out.txt","rb")
csv_file = csv.reader(file)
for data in csv_file:
	recon_kin.append(float(data[0]))
	truth_kin.append(float(data[1]))
	if not isinstance(truth_kin[-1], float):
		print "error error"

truth_kin = np.array(truth_kin)
truth_kin /= (0.5*938.72)
truth_kin.sort()

segsize = len(truth_kin)/5.0
x0 = 0.0
x1 = truth_kin[int(segsize)]
x2 = truth_kin[int(2.0*segsize)]
x3 = truth_kin[int(3.0*segsize)]
x4 = truth_kin[int(4.0*segsize)]
x5 = truth_kin[int(5.0*segsize-1)]

print "Bins based on truth!"
print "Bin1: [",x0,",",x1,"]"
print "Bin2: [",x1,",",x2,"]"
print "Bin3: [",x2,",",x3,"]"
print "Bin4: [",x3,",",x4,"]"
print "Bin5: [",x4,",",x5,"]"

recon_kin = np.array(recon_kin)
recon_kin /= (0.5*938.72)
recon_kin.sort()

segsize = len(recon_kin)/5.0
x0 = 0.0
x1 = recon_kin[int(segsize)]
x2 = recon_kin[int(2.0*segsize)]
x3 = recon_kin[int(3.0*segsize)]
x4 = recon_kin[int(4.0*segsize)]
x5 = recon_kin[int(5.0*segsize-1)]

print "Bins based on recon!"
print "Bin1: [",x0,",",x1,"]"
print "Bin2: [",x1,",",x2,"]"
print "Bin3: [",x2,",",x3,"]"
print "Bin4: [",x3,",",x4,"]"
print "Bin5: [",x4,",",x5,"]"

print "Checking bins: ",
correct = True
if x0 > x1:
	correct = False
if x1 > x2:
	correct = False
if x2 > x3:
	correct = False
if x3 > x4:
	correct = False
if x4 > x5:
	correct = False

if correct == True:
	print "It looks correct!"
else:
	print "What the fuck happened!"
