#!/usr/bin/python2.6

import csv
import array
import numpy as np
import math

def findtruth():
	file = open("kinetic-out2.txt","rb")
	csv_file = csv.reader(file)
	energies = np.array([(float(data[0]), float(data[1])) for data in csv_file])
	energies /= (2.*938.)
	bounds = np.array([0.,0.13, 0.25, 0.40, 0.90, 17.])
	bounds *= 1000000./(2.*938.)
	
	#recon and truth are last 1/3 (from 2/3 onwards)
	recon = makevector(energies[:int(len(energies)*(2./3.))],0, bounds)
	truth = makevector(energies[:int(len(energies)*(2./3.))],1, bounds)
	#matrix is calculated from first 2/3 of MC data
	matrix = makematrix(energies[:int(len(energies)*(2./3.))], bounds)
	#unsmear recon
	outfile = open("energyhists.txt", "w")
	outfile.write(str(len(bounds)-1) + ",\n")
	writelist(outfile, bounds)
	writelist(outfile, recon)
	writelist(outfile, truth)
	matrix = matrix.T
	matrix = np.array(matrix)
	for i in matrix:
		writelist(outfile, i)

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
#	for i in range(numbins):
#		matrix[:,i]/=matrix[:,i].sum() #normalising matrix, possibly not required for TSVDUnfold
	return matrix
	
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

