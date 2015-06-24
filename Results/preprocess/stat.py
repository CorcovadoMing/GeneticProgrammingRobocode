min_result = []
min_f_result = []

max_result = []
max_f_result = []

avg_result = []
avg_f_result = []

best_result = []
best_f_result = []

import csv

def process_result(filepath):
	global tmp_result, result
	with open(filepath) as file:
		for line in file:
			if "terminate" in line:
				break
			else:
				if "Generation" in line:
					pass
				else:
					if "Min" in line:
						min_result.append(line)
					elif "Max" in line:
						max_result.append(line)
					elif "Avg" in line:
						avg_result.append(line)
					elif "Best" in line:
						best_result.append(line)

process_result('result4.txt')

for i in min_result:
	i = i.split(']')[1]
	i = i.split('\n')[0]
	i = map(float, i.split())
	min_f_result.append(i)

for i in max_result:
	i = i.split(']')[1]
	i = i.split('\n')[0]
	i = map(float, i.split())
	max_f_result.append(i)

for i in avg_result:
	i = i.split(']')[1]
	i = i.split('\n')[0]
	i = map(float, i.split())
	avg_f_result.append(i)

for i in best_result:
	i = i.split(']')[1]
	i = i.split('\n')[0]
	i = map(float, i.split())
	best_f_result.append(i)

f = open("result4_min.csv","w")  
w = csv.writer(f)  
w.writerows(min_f_result)  
f.close()  

f = open("result4_max.csv","w")  
w = csv.writer(f)  
w.writerows(max_f_result)  
f.close()  

f = open("result4_avg.csv","w")  
w = csv.writer(f)  
w.writerows(avg_f_result)  
f.close()  

f = open("result4_best.csv","w")  
w = csv.writer(f)  
w.writerows(best_f_result)  
f.close()  