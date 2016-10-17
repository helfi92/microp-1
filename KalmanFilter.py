class KalmanFilter(object):
	q = 0.0
	r = 0.0
	x = 0.0
	p = 0.0
	k = 0.0

	def __init__(self, x_initial_value, q = 0.1, r = 0.1, p = 0.1, k = 0.0):
		self.q = q
		self.r = r
		self.x = x_initial_value
		self.p = p
		self.k = k

	def update(self, input_i):
		self.p = self.p + self.q
		self.k = self.p / (self.p + self.r)
		self.p = (1 - self.k) * self.p
		self.x = self.x + self.k * (input_i - self.x)
		return self.x