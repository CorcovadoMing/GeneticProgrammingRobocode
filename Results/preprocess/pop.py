result = []
tmp_result = []

import csv

def process_result(filepath):
	global tmp_result, result
	with open(filepath) as file:
		for line in file:
			if "terminate" in line:
				break
			else:
				if "Generation" in line:
					result.append(tmp_result)
					tmp_result = []
				else:
					if "[" in line or "Done" in line:
						continue
					else:
						tmp_result.append(line)

process_result('result4.txt')
result.pop(0)

for i in result:
	for x in xrange(len(i)):
		i[x] = i[x].split('\n')[0]
	print i

f = open("result4.csv","w")  
w = csv.writer(f)  
w.writerows(result)  
f.close()  
