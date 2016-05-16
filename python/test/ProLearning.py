import cv2
import numpy as np

trainData = np.array([0,1,2,3,4,5,6,7,8,9,12,13], np.float32)
responses = np.array([1,0,1,0,1,0,1,0,1,0,1,0], np.int32)

svm = cv2.SVM()
svm.train(trainData, responses, params=SVM_PARAMS)

#print svm.predict(np.array([5.0,5.1,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9], np.float32))
print svm.predict(np.array([10,11], np.float32))