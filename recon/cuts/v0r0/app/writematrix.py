#!/usr/bin/python2.6

import csv
import array
import numpy as np
import math

def findtruth():
	file = open("kinetic-out.txt","rb")
	csv_file = csv.reader(file)
	energies = [(float(data[0])/10**9, float(data[1])/10**9) for data in csv_file]
	bounds = [0,0.15, 0.28, 0.40, 0.70, 4]
	recon = makevector(energies,0, bounds)
	truth = makevector(energies,1, bounds)
	matrix = makematrix(energies, bounds)
	corrected = matrix.dot(recon)
	print recon
	print corrected
	print truth

def makematrix(ens, bounds):
	energies = ens
	numbins = len(bounds)-1
	matrix = np.matrix(np.zeros((numbins,numbins)))
	for i in energies:
		setbin(i, bounds, matrix)
	for i in range(numbins):
		matrix[i]/=matrix[i].sum()
	return matrix.I #returns the inverse of the matrix
	
def setbin(ens, bounds, matrix):
	if not isinstance(ens, tuple) and len(ens)==2:
		print "error, error"
		return -1
	col = -1
	row = -1
	it = 0
	for i in range(len(bounds)-1):
		if bounds[i+1] >= ens[0] and bounds[i] <= ens[0]:
			col = i
		if bounds[i+1] >= ens[1] and bounds[i] <= ens[1]:
			row = i
	if col != -1 and row != -1:	
		matrix[row,col]+=1	

def makevector(energies,usecol,bounds):
	numbins = len(bounds)-1
	vector = np.zeros(numbins)
	for energy in energies:
		element = -1
		for i in range(numbins):
			if bounds[i+1] >= energy[usecol] and bounds[i] <= energy[usecol]:
				element = i
		if element != -1:
			vector[element]+=1
	return vector

def debug():
	file = open("kinetic-out.txt","rb")
	csv_file = csv.reader(file)
	energies = [(float(data[0])/10**9, float(data[1])/10**9) for data in csv_file]
	bounds = [0,0.15, 0.28, 0.40, 0.70, 4]
	recon = makevector(energies,0, bounds)
	truth = makevector(energies,1, bounds)
	matrix = makematrix(energies, bounds)
	result = matrix.dot(truth)
	print recon
	print matrix
	print result


#findtruth()
debug()

