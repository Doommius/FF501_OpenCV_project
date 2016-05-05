import cv2
import numpy as np
import random as rng

winName = "contour"
cap = cv2.VideoCapture(0)
cv2.namedWindow(winName)

while(True):
    ret, frame = cap.read()

    #get edges
    dst = np.zeros(frame.shape)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (7, 7), 1.5)
    canny = cv2.Canny(blur, 30, 30 * 3)

    #find contours
    img, contours, h = cv2.findContours(canny, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)
    for cnt in range(0, len(contours)):
        cv2.drawContours(dst, contours, cnt, (rng.random(), rng.random(), rng.random()), -1, 1, h)

    cv2.imshow(winName, dst)

    if cv2.waitKey(1) == 27:
        break

cap.release()
cv2.destroyAllWindows()