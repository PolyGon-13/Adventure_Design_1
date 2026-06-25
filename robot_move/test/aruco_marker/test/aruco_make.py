import cv2
import cv2.aruco as aruco
import numpy as np

aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250)
markerImage = np.zeros((200, 200), dtype=np.uint8)
markerImage = aruco.drawMarker(aruco_dict, 3, 200, markerImage, 1)
cv2.imwrite("3.jpg", markerImage)
