import cv2
import numpy as np
import random as rng

imageNames = ["2715DTZ.jpg", "3028BYS.JPG", "3154FFY.JPG",
              "3266CNT.JPG", "3732FWW.JPG", "5445BSX.JPG",
              "7215BGN.JPG", "8995CCN.JPG", "9588DWV.jpg",
              "9773BNB.jpg", "DSC_0562.jpg", "DSC_0566.jpg"]

images = []
winName = 'images'

outIndex = 0

# load all pictures
for name in imageNames:
    images.append(cv2.imread("images\\" + name))

# define what happens on the trackbar
def onImage(index):
    global outIndex
    img = images[index].copy()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (7, 7), 1.5)
    canny = cv2.Canny(blur, 80, 80 * 3)

    # find contours
    conImg, contours, h = cv2.findContours(canny, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        perimeter = cv2.arcLength(contour, True)
        approxPoly = cv2.approxPolyDP(contour, perimeter * 0.02, True)
        # use fillPoly instead of fillConvexPoly and pack into array, because some polys are non-convex
        #cv2.fillPoly(img, [approxPoly], (0, 255, 0), cv2.LINE_8)

        if cv2.contourArea(approxPoly) > 50: #only do this for big enough areas
            print (outIndex, cv2.contourArea(approxPoly))
            mask = np.zeros(img.shape, np.uint8)

            #draw the region extracted
            rect = cv2.minAreaRect(approxPoly)
            rectPoints = np.array(cv2.boxPoints(rect), np.int32)
            rectPoints = rectPoints.reshape((-1, 1, 2))
            cv2.fillPoly(mask, [rectPoints], (255, 255, 255))

            out = img * mask * mask
            print(cv2.imwrite("images\\contours\\" + str(outIndex) + ".jpg", out))
            print(cv2.imwrite("images\\mask\\" + str(outIndex) + ".jpg", mask))
            outIndex += 1

    cv2.imshow(winName, img)


# Create a black image, a window
cv2.namedWindow(winName)

# create trackbar
cv2.createTrackbar('Image', winName, 0, len(images) - 1, onImage)

onImage(0)

while (1):
    if cv2.waitKey(1) == 27:
        break

cv2.destroyAllWindows()
