import matplotlib.pyplot as plt
import csv
from KalmanFilter import KalmanFilter
from statistics import mean, pstdev
from myMath import myMath

data = []
with open('lab2-sample.csv', 'rb') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
	for row in spamreader:
 		data.append(float(row[0]))

print 'data stdev: ', myMath(input=data).stdev()

kf = KalmanFilter(p=300, r=10, q=2.0, k=0.0, x_initial_value=data[0]);
kalman_output = []
for elem in data:
	kalman_output.append(kf.update(elem))

kf2 = KalmanFilter(p=300, r=10, q=1.0, k=0.0, x_initial_value=data[0]);
kalman_output2 = []
for elem in data:
	kalman_output2.append(kf2.update(elem))

kf3 = KalmanFilter(p=300, r=50, q=2.0, k=0.0, x_initial_value=data[0]);
kalman_output3 = []
for elem in data:
	kalman_output3.append(kf3.update(elem))

kf4 = KalmanFilter(p=300, r=50, q=1.0, k=0.0, x_initial_value=data[0]);
kalman_output4 = []
for elem in data:
	kalman_output4.append(kf4.update(elem))

kf5 = KalmanFilter(p=100, r=10, q=2.0, k=0.0, x_initial_value=data[0]);
kalman_output5 = []
for elem in data:
	kalman_output5.append(kf5.update(elem))

kf6 = KalmanFilter(p=100, r=10, q=1.0, k=0.0, x_initial_value=data[0]);
kalman_output6 = []
for elem in data:
	kalman_output6.append(kf6.update(elem))

kf7 = KalmanFilter(p=300, r=50, q=2.0, k=0.0, x_initial_value=data[0]);
kalman_output7 = []
for elem in data:
	kalman_output7.append(kf7.update(elem))

kf8 = KalmanFilter(p=300, r=50, q=1.0, k=0.0, x_initial_value=data[0]);
kalman_output8 = []
for elem in data:
	kalman_output8.append(kf8.update(elem))

one = myMath(input=kalman_output)

print 'kalman_output  stdev: ', one.stdev()
print 'kalman_output2 stdev: ', myMath(input=kalman_output2).stdev()
print 'kalman_output3 stdev: ', myMath(input=kalman_output3).stdev()
print 'kalman_output4 stdev: ', myMath(input=kalman_output4).stdev()
print 'kalman_output5 stdev: ', myMath(input=kalman_output5).stdev()
print 'kalman_output6 stdev: ', myMath(input=kalman_output6).stdev()
print 'kalman_output6 stdev: ', myMath(input=kalman_output7).stdev()
print 'kalman_output6 stdev: ', myMath(input=kalman_output8).stdev()


plt.plot(data, 'b', kalman_output, 'r', kalman_output2, 'm', kalman_output6, 'g')
# plt.plot(x, data, 'b', x, kalman_output, 'r', x, kalman_output2, 'm',tx, s, 'c', x, kalman_output3, 'g')

plt.ylabel('Temperature (C)')
plt.xlabel('Time (100 micro seconds)')
plt.title('Temperature with Different Kalman Filter Parameters')
plt.show()