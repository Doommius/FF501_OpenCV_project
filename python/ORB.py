import numpy as np
import cv2
import os
dir = "C:\Users\zlyza\Source\Repos\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\python\images\positivePlate"
for file in os.listdir(dir):
    if(file.endswith(".jpg") or file.endswith(".JPG")):
        print(file)
        img = cv2.imread(dir+'\\'+file)
        orb = cv2.ORB()
        # find the keypoints with ORB
        kp = orb.detect(img, None)
        # compute the descriptors with ORB
        kp, des = orb.compute(img, kp)
        #svm = cv2.SVM()
        #svm.train(trainData,responses, params=svm_params)

        # cv2.BRISK.detectAndCompute()
        # draw only keypoints location,not size and orientation
        cv2.drawKeypoints(img, kp, img, color=(0,255,0))
        cv2.imshow("fdf", img)

        # for x in range(3):
        #     cv2.imwrite("test\\"+str(x)+".jpg", img)
        cv2.waitKey(1000)