#!/usr/bin/python2.6

import csv
import array
import numpy as np
import math

def printmatrix():

	file = open("kinetic-out.txt","rb")
	csv_file = csv.reader(file)
	energies = [(float(data[0])/10**9, float(data[1])/10**9) for data in csv_file]
	bounds = [0,0.15, 0.28, 0.40, 0.70, 4]
	numbins = len(bounds)-1
	matrix = np.matrix(np.zeros((numbins,numbins)))
	for i in energies:
		setbin(i, bounds, matrix)
	for i in range(numbins):
		matrix[i]/=matrix[i].sum()
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
	if col != -1 and row != -1:	
		matrix[row,col]+=1	

printmatrix()


def makevector(energies,usecol,bounds):
	numbins = len(bounds)-1
	vector = np.matrix(np.zeros(numbins))
	for energy in energies:
		element = -1
		for i in range(numbins):
			if bounds[i+1] > energy[usecol] and bounds[i] < energy[usecol]:
				element = i
		if element != -1:
			vector[element]+=1
	print vector #just for debugging
	return vector
