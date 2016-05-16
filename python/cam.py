import cv2
import numpy as np
winName = "surf"
cap = cv2.VideoCapture(0)
cv2.namedWindow(winName)
thresh = 30
def onThresh(x):
    global thresh
    thresh = x
cv2.createTrackbar("Threshold", winName, 30, 255, onThresh)
while(True):
    ret, frame = cap.read(0)
    #frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    fd = cv2.AKAZE_create(edgeThreshold = 1)
    kp = fd.detect(frame, None)
    kp, des = fd.compute(frame, kp)
    #kp, des = fd.detectAndCompute(frame, None)
    cv2.drawKeypoints(frame, kp, frame, color=(0, 255, 0))
    cv2.imshow(winName, frame)
    if cv2.waitKey(1) == 27:
        break
cap.release()
cv2.destroyAllWindows()