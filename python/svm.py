import cv2
import numpy as np
import random as rng
import math
import matplotlib.pyplot as plt

svm_params = dict( kernel_type = cv2.ml.SVM_LINEAR,
                    svm_type = cv2.ml.SVM_C_SVC,
                    C=2.67, gamma=5.383 )

def secret_function(x):
    return math.fabs(math.sin(x / 10.0)) * 50

data = np.random.randint(0, 75, (300, 2)).astype(np.float32)
responses = []

for point in data:
    if secret_function(point[0]) < point[1]:
        responses.append(1)
    else:
        responses.append(0)

responses = np.array(responses, np.int32)

#plot
for index in range(len(data)):
    if responses[index] == 1:
        plt.scatter(data[index][0],data[index][1],80,'g','^')
    else:
        plt.scatter(data[index][0],data[index][1],80,'r','o')

#plt.scatter(above[:,0],above[:,1],80,'g','^')

svm = cv2.ml.SVM_create()
svm.setKernel(cv2.ml.SVM_RBF)
svm.setType(cv2.ml.SVM_C_SVC)
svm.setGamma(0.05)
svm.setC(2)
svm.train(data, cv2.ml.ROW_SAMPLE, responses)

#build some test
test = []
for i in range(500):
    test.append([rng.randrange(0, 100), rng.randrange(0, 100)])

test = np.array(test, np.float32)

retval, result = svm.predict(test)

for i in range(len(result)):
    style = 'r'
    if result[i][0] == 1:
        style = 'g'
    plt.scatter(test[i][0],test[i][1],80,style,'s')

plt.show()
