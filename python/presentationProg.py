import cv2
import numpy as np
import random as rng

img = cv2.imread('images\\8995CCN.JPG')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
canny = cv2.Canny(gray, 80, 80 * 3)
dst = np.zeros(img.shape)

ret, contours, h = cv2.findContours(canny, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)

keypoints = list()
mask = np.zeros(img.shape, np.uint8)

for contour in contours:
    perimeter = cv2.arcLength(contour, True)
    approxPoly = cv2.approxPolyDP(contour, perimeter * 0.02, True)

    if cv2.contourArea(approxPoly) > 50 and cv2.isContourConvex(approxPoly):
        #cv2.drawContours(dst, [approxPoly], 0, (rng.randrange(255.0) / 255.0, rng.randrange(255) / 255.0, rng.randrange(255.0) / 255.0), -1)

        rect = cv2.minAreaRect(approxPoly)
        rectPoints = np.array(cv2.boxPoints(rect), np.int32)
        rectPoints = rectPoints.reshape((-1, 1, 2))
        cv2.fillPoly(mask, [rectPoints], (255))
        cv2.drawContours(dst, [rectPoints], 0, (0, 255, 0))

#we cheat a bit here...
cv2.imwrite("temp.jpg", mask)
maskg = cv2.imread("temp.jpg", cv2.IMREAD_GRAYSCALE)
kp = cv2.goodFeaturesToTrack(gray, 50, 0.01, 7, mask = maskg)
for p in kp:
    keypoints.append(cv2.KeyPoint(p[0][0],p[0][1],1))
cv2.drawKeypoints(img, keypoints, img, (0, 255, 0))


cv2.imshow("Read", img)

while True:
    if cv2.waitKey(1) == 27:
        break