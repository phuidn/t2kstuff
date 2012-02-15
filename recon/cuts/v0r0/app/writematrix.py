#!/usr/bin/python2.6

import csv
import array
import numpy as np
import math

def findtruth():
	file = open("kinetic-out2.txt","rb")
	csv_file = csv.reader(file)
	energies = np.array([(float(data[0]), float(data[1])) for data in csv_file])
	energies /= (2*938)
	bounds = np.array([0,0.13, 0.25, 0.40, 0.90, 17])
	bounds *= 1000000/(2*938)
	#recon and truth are last 1/3 (from 2/3 onwards)
	recon = makevector(energies[int(len(energies)*(2/3)):],0, bounds)
	truth = makevector(energies[int(len(energies)*(2/3)):],1, bounds)
	#matrix is calculated from first 2/3 of MC data
	matrix = makematrix(energies[:int(len(energies)*(2/3))], bounds)
	#unsmear recon
	corrected = matrix.dot(recon)
	#multiply both recon and truth by their efficiency factors to normalise
	#
	#
	print "Using bounds: ",bounds
	print "Recon vector and sum:  ",recon, recon.sum()
	print "Truth vector and sum:  ",truth, truth.sum()
	print "Corrected Vector and sum :  ",corrected, corrected.sum()
	print "Corrected / truth : ", corrected/truth

def makematrix(ens, bounds):
	energies = ens
	numbins = len(bounds)-1
	matrix = np.matrix(np.zeros((numbins,numbins)))
	for i in energies:
		setbin(i, bounds, matrix)
	for i in range(numbins):
		matrix[:,i]/=matrix[:,i].sum()
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


findtruth()
#debug()

