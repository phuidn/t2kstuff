#!/usr/bin/python2.6

import csv
import array
import numpy as np
import math

def findtruth():
	file = open("baskettpcmom.txt","rb")
	csv_file = csv.reader(file)
	energies = np.array([(float(data[0]), float(data[1])) for data in csv_file])
	energies /= 1000000.
	bounds = np.array([0.,0.25, 0.5, 0.75, 1., 1.25])
	otherfile = open("magnetTPC.txt","rb")
	magmoms = np.array([(float(data[0]), float(data[1])) for data in csv.reader(otherfile)])
	magmoms /= 1000000.
	#recon and truth are last 1/3 (from 2/3 onwards)
	recon = makevector(energies,0, bounds)
	truth = makevector(energies,1, bounds)

	magrecon = makevector(magmoms,0,bounds)
	magtruth = makevector(magmoms,1,bounds)
	#matrix is calculated from first 2/3 of MC data
	matrix = makematrix(energies, bounds)
	
	#unsmear recon
	outfile = open("energyhists.txt", "w")
	outfile.write(str(len(bounds)-1) + ",\n")
	writelist(outfile, bounds)
	writelist(outfile, magtruth)
	unfolded = matrix.dot(magrecon)
	writelist(outfile, unfolded)
	print magtruth
		
def writelist(file, list):
	for i in list:
		file.write(str(i) + ',')
	file.write('\n')

def makematrix(ens, bounds):
	energies = ens
	numbins = len(bounds)-1
	matrix = np.matrix(np.zeros((numbins,numbins)))
	for i in energies:
		setbin(i, bounds, matrix)
	for i in range(numbins):
		matrix[:,i]/=matrix[:,i].sum() #normalising matrix, possibly not required for TSVDUnfold
	return matrix.I
	
def setbin(ens, bounds, matrix):
	rec = -1
	tru = -1
	it = 0
	for i in range(len(bounds)-1):
		if bounds[i+1] > ens[0] and bounds[i] < ens[0]:
			rec = i
		if bounds[i+1] > ens[1] and bounds[i] < ens[1]:
			tru = i
	if rec != -1 and tru != -1:	
		matrix[rec,tru]+=1	

def makevector(energies,usecol,bounds):
	numbins = len(bounds)-1
	vector = np.zeros(numbins)
	for energy in energies:
		element = -1
		if energy[1 - usecol]>0 and energy[1 - usecol]<bounds[-1]:
			for i in range(numbins):
				if bounds[i+1] > energy[usecol] and bounds[i] < energy[usecol]:
					element = i
			if element != -1:
				vector[element]+=1
	return vector

def finalvalues(truth, corrected, tothits):
	errors = np.sqrt(corrected)
	hits = truth.sum()
	scale = tothits/hits
	truth *= scale
	corrected *= scale
	errors *= scale
	print truth
	print corrected
	print errors

findtruth()

