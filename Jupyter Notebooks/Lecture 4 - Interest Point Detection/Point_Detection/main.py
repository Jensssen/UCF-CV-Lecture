import numpy as np
import cv2
import math
import time as t
from matplotlib import pyplot as plt
import matplotlib.image as mpimg
import matplotlib.mlab as mlab
from random import randint
import copy


cap = cv2.VideoCapture(0)

while(cap.isOpened()):
    ret, frame = cap.read()
    if (ret == True):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        gray = np.float32(gray)
        dst = cv2.cornerHarris(gray,2,3,0.01)
        dst = cv2.dilate(dst,None)
        frame[dst>0.01*dst.max()]=[0,0,255]

        cv2.imshow('dst',frame)
        if(cv2.waitKey(1) % 0xFF == ord('q')):
            break
    else:
        break


cap.release()
cv2.destroyAllWindows()
