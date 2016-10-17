from statistics import mean, pstdev, pvariance

class myMath(object):		
	data = []

	def __init__(self, input):
		self.data = input

	def stdev(self):
		x = range(len(self.data))
		tens = []
		tx= range(0,len(self.data), len(self.data) /  2) # half of data array

		for i in tx:
			tens.append(self.data[i:(i+25)]) # 2D array

		# t=[mean(i) for i in tens ]
		self.s=[pstdev(i) for i in tens ]

		return self.s

