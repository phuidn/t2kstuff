#!/usr/bin/python
import csv

file = csv.reader(open("list.out","rb"))
list = []
list.extend(file)
no_of_reactions_per_file = 0

for data in list:
	if data[0] == "CCQES":
		if no_of_reactions_per_file == 0:
			no_of_reactions_per_file +=1
			currentfilename = data[1]
		elif data[1] == currentfilename:
			no_of_reactions_per_file +=1
		else:
			print data[1] , " has " , no_of_reactions_per_file , " events."
			no_of_reactions_per_file =1
			currentfilename = data[1]

