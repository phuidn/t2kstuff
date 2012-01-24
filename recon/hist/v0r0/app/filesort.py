#!/usr/bin/python
import sys

file = open('list.out', 'r')
lines = file.readlines()
datas = [tup.split(',') for tup in lines]
paths = [["path","NCQES", "CCQES", "DIS", "RES", "events"]]
for event in datas:
	print event
	nces = int(event[0] == "NCQES")
	ccqes = int(event[0] == "CCQES")
	dis = int(event[0] == "DIS")
	res = int(event[0] == "RES") 	
	if event[1] in paths[:][0]:
		paths[-1][1] += nces
		paths[-1][2] += ccqes
		paths[-1][3] += dis
		paths[-1][4] += res
		paths[-1][5].append(int(event[2]))
	else:
		paths.append([event[1], nces, ccqes, dis, res, int(event[2])])
print datas[0]

