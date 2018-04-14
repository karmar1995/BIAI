import collections

filename="chromosomes.txt"
file=open(filename, "r")
number=1
err_ctr=0;
for line in file:
	print("\n")
	print("Chromosome number: " + str(number))
	chromosome = line.strip().split(" ")
	print("Chromosome length: " + str(len(chromosome)))
	if str(0) in chromosome:
		err_ctr = err_ctr + 1
		print("detected 0 node - error")
	cnt=collections.Counter(chromosome)
	counted=cnt.items()
	for single in counted:
		if single[1]>1:
			err_ctr = err_ctr + 1
			print("duplicate: " + single[0] + " " + str(single[1]))
	for i in range(1, len(chromosome)):
		if str(i) not in chromosome:
			err_ctr = err_ctr + 1
			print("missing " + str(i))
	if err_ctr==0:
		print("\nChromosome is OK\n")
	else:
		print("Errors: " + str(err_ctr))
		print("\n")
	err_ctr=0
	number=number+1