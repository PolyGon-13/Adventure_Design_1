import cv2
import cv2.aruco as aruco

cap = cv2.VideoCapture(0)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 320)

aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)

parameters = aruco.DetectorParameters()
parameters.adaptiveThreshWinSizeMin = 3
parameters.adaptiveThreshWinSizeMax = 23

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    if not ret:
        break

    # Convert to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect ArUco markers
    corners, ids, rejectedImgPoints = aruco.detectMarkers(gray, aruco_dict, parameters=parameters)

    # Check if markers are detected and print their IDs
    if ids is not None:
        print("Detected IDs:", ids.flatten())

        # Draw detected markers
        aruco.drawDetectedMarkers(frame, corners, ids)

    # Display the resulting frame
    cv2.imshow('Frame', frame)

    # Break the loop with 'q' key
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
