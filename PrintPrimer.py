# 打印指定区间的素数，以逗号隔开
import math
def IsPrime(x):
	if x == 1 or x <= 0:
		return False
	a = int(math.sqrt(x))
	flag = True

	for i in range(2,a+1):
		if (x % i == 0):
			flag = False
			break
	return flag

for x in range(1,100):
	if(IsPrime(x)):
		print(x,end=',')