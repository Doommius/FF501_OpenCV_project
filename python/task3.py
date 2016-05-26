import cv2
import numpy as np
import os
import cPickle as pickle

globalTrainedSVM = None

def getDescriptors(img, mask):
    fd = cv2.BRISK_create(30)
    if mask is not None:
        mask = cv2.erode(mask, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #kp = fd.detect(img, mask)
    keypoints = list()
    kp = cv2.goodFeaturesToTrack(img, 50, 0.01, 5, mask=mask)
    if kp is not None and len(kp) > 0:
        for p in kp:
            keypoints.append(cv2.KeyPoint(p[0][0],p[0][1],1))
    return fd.compute(img, keypoints)

def trainSVM():
    global globalTrainedSVM
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

        kp, des = getDescriptors(img, mask)
        if des is not None:
            for descriptor in des:
                data.append(descriptor)
                responses.append([1])


    for file in os.listdir("images\\contours"):
        print file
        img = cv2.imread("images\\contours\\" + file)
        mask = cv2.imread("images\\mask\\" + file, cv2.IMREAD_GRAYSCALE)
        #reduce the mask as to not detect corners

        kp, des = getDescriptors(img, mask)

        if not des == None:
            for descriptor in des:
                data.append(descriptor)
                responses.append([0])

    data = np.array(data, np.float32)
    responses = np.array(responses, np.int32)

    svm.train(data, cv2.ml.ROW_SAMPLE, responses)

    globalTrainedSVM = svm
    svm.save('mySVM.xml')
    pickle.dump([data, responses], open('mySVM.pickle', 'wb'))

def getROIs(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (7, 7), 1.5)
    canny = cv2.Canny(blur, 80, 80 * 3)

    # find contours
    conImg, contours, h = cv2.findContours(canny, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)

    out = []

    for contour in contours:
        perimeter = cv2.arcLength(contour, True)
        approxPoly = cv2.approxPolyDP(contour, perimeter * 0.02, True)

        if cv2.contourArea(approxPoly) > 50: #only do this for big enough areas
            mask = np.zeros(img.shape, np.uint8)

            #draw the region extracted
            rect = cv2.minAreaRect(approxPoly)
            rectPoints = np.array(cv2.boxPoints(rect), np.int32)
            rectPoints = rectPoints.reshape((-1, 1, 2))
            cv2.fillPoly(mask, [rectPoints], (255, 255, 255))

            masked = img * mask * mask
            out.append([masked, mask])

    return out

trainSVM()

#load support vector machine
svm = cv2.ml.SVM_create()
svm.setKernel(cv2.ml.SVM_RBF)
svm.setType(cv2.ml.SVM_C_SVC)
svm.setC(2.6)
svm.setGamma(2.34)
cold = pickle.load(open( "mySVM.pickle", "rb" ))
svm.train(cold[0], cv2.ml.ROW_SAMPLE, cold[1])

winName = 'window' #window name
#recursively get all file names
imageNames = []
for file in os.walk("C:\\Users\\mikke_000\\Desktop\\images"):
    imageNames += [file[0] + "\\" + f for f in file[2]]

images = [None for name in imageNames]

def onChange(index):
    if images[index] == None:
        images[index] = cv2.imread(imageNames[index])

    img = images[index]

    for roi in getROIs(img):
        kp, des = getDescriptors(roi[0], None)
        print svm.predict(np.array(des, np.float32))
        cv2.drawKeypoints(img, kp, img, (0, 255, 0))

    cv2.imshow(winName, img)

# Create a black image, a window
cv2.namedWindow(winName)
onChange(0)

# create trackbar
cv2.createTrackbar('Image', winName, 0, len(images) - 1, onChange)

while (1):
    if cv2.waitKey(1) == 27:
        break

cv2.destroyAllWindows()