import os
path = "C:\\Users\\kcaro\\OneDrive\\Documents\\of_v0.10.1_vs2017_release\\apps\\myApps\\Sketch_8\\bin\\data\\"
index = 0
fileNameArr = []
for filename in os.listdir(path):
	
	if filename[0 : 3] == "dot":
		if index == 10:
			dst = path + "d0" + str(index) + ".png"
			src = path + filename		
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "d00" + str(index) + ".png"
			src = path + filename			
			os.rename(src, dst)
			index += 1
					
	elif filename[0 : 4] == "zero":
		if index == 10:
			dst = path + "n0" + str(index) + ".png"
			src = path + filename			
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n00" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 3] == "one":
		if index == 10:
			dst = path + "n1" + str(index) + ".png"
			src = path + filename				
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n10" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 3] == "two":
		if index == 10:
			dst = path + "n2" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n20" + str(index) + ".png"
			src = path + filename			
			os.rename(src, dst)
			index += 1
	elif filename[0 : 5] == "three":
		if index == 10:
			dst = path + "n3" + str(index) + ".png"
			src = path + filename			
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n30" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 4] == "four":
		if index == 10:
			dst = path + "n4" + str(index) + ".png"
			src = path + filename		
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n40" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 4] == "five":
		if index == 10:
			dst = path + "n5" + str(index) + ".png"
			src = path + filename		
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n50" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 3] == "six":
		if index == 10:
			dst = path + "n6" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n60" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 5] == "seven":
		if index == 10:
			dst = path + "n7" + str(index) + ".png"
			src = path + filename		
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n70" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 5] == "eight":
		if index == 10:
			dst = path + "n8" + str(index) + ".png"
			src = path + filename		
			os.rename(src, dst)
			index = 0
		else:
			dst = path + "n80" + str(index) + ".png"
			src = path + filename	
			os.rename(src, dst)
			index += 1
	elif filename[0 : 4] == "nine":
		if index == 10:
			dst = path + "n9" + str(index) + ".png"
			src = path + filename		
			os.rename(src, dst)
			index = 0
		else:
			dst = "n90" + str(index) + ".png"
			src = path + filename
			dst = path + dst		
			os.rename(src, dst)
			index += 1

# copy and paste the result to tileFileNames
dotIndex = 0
numberIndex = 0
numberArr = ["n0", "n9", "n8", "n7", "n6", "n5", "n4", "n3", "n2", "n1"]
print("{", end = '')
for i in range(0, 11):
	for j in range(0, 11):
		if j == dotIndex:
			if i == 10 and j == 10:
				print("\"d0%.2d.png\"}"  % (j), end = '')
			else:
				print("\"d0%.2d.png\","  % (j), end = '')
		else:
			print("\"%s%.2d.png\"," % (numberArr[numberIndex], i), end = '')
			numberIndex += 1
			if numberIndex == 10:
				numberIndex = 0
	dotIndex += 1
				
		
			
			
			
			
		

