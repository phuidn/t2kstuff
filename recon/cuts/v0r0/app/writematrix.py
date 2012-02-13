#!/usr/bin/python2.6

import csv
import array
import numpy as np
import math

def printmatrix():

	file = open("kinetic-out.txt","rb")
	csv_file = csv.reader(file)
	energies = [(float(data[0])/10**9, float(data[1])/10**9) for data in csv_file]
	if math.isnan(energies[-1][0]):
		del energies[-1]
		print "killing a NaN"
	bounds = [0,0.15, 0.28, 0.40, 0.70, 4]
	matrix = np.zeros((len(bounds)-1, len(bounds)-1))
	for i in energies:
		setbin(i, bounds, matrix)
	print matrix
	
def setbin(ens, bounds, matrix):
	if not isinstance(ens, tuple) and len(ens)==2:
		print "error, error"
		return -1
	col = -1
	row = -1
	it = 0
	for i in range(len(bounds)-1):
		if bounds[i+1] > ens[0] and bounds[i] < ens[0]:
			col = i
		if bounds[i+1] > ens[1] and bounds[i] < ens[1]:
			row = i	
	matrix[row,col]+=1	

printmatrix()


