import cv2
import numpy as np
import os

def getDescriptors(img, mask):
    fd = cv2.BRISK_create(30)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #kp = fd.detect(img, mask)
    keypoints = list()
    kp = cv2.goodFeaturesToTrack(img, 50, 0.01, 5, mask=mask)
    if kp is not None and len(kp) > 0:
        for p in kp:
            keypoints.append(cv2.KeyPoint(p[0][0],p[0][1],1))
    return fd.compute(img, keypoints)

def trainSVM():
    #setup the SVM
    svm = cv2.SVM()
    svm.setKernel(cv2.SVM_RBF)
    svm.setType(cv2.SVM_C_SVC)
    svm.setGamma(0.05)
    svm.setC(2)

    data = []
    responses = []

    #first go through the positive
    for file in os.listdir("images\\positive"):
        print file
        img = cv2.imread("images\\positive\\" + file)
        mask = cv2.imread("images\\mask\\" + file, cv2.IMREAD_GRAYSCALE)
        #reduce the mask as to not detect corners
        mask = cv2.erode(mask, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))

        kp, des = getDescriptors(img, mask)

        for descriptor in des:
            data.append(descriptor)
            responses.append([1])


    for file in os.listdir("images\\contours"):
        print file
        img = cv2.imread("images\\contours\\" + file)
        mask = cv2.imread("images\\mask\\" + file, cv2.IMREAD_GRAYSCALE)
        #reduce the mask as to not detect corners
        mask = cv2.erode(mask, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))

        kp, des = getDescriptors(img, mask)

        if not des == None:
            for descriptor in des:
                data.append(descriptor)
                responses.append([0])

    data = np.array(data, np.float32)
    responses = np.array(responses, np.int32)

    svm.train(data, cv2.ml.ROW_SAMPLE, responses)

    svm.save('mySVM.dat')

