import cv2
import serial

# Define globals
MAX_SIZE = 406
SERIAL_PORT = '/dev/ttyUSB0'  # 아두이노 우노가 연결된 시리얼 포트를 확인하고 변경하세요.
BAUD_RATE = 9600  # 아두이노 우노의 보드레이트와 일치시킵니다.

# Define helper functions
# ... (extractAruco 및 findArucoID 함수를 그대로 유지)

# 시리얼 포트 초기화
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# 카메라 설정
cap = cv2.VideoCapture(0)  # 0은 일반적으로 기본 카메라입니다.

# 마커 인식 횟수
marker_count = 0

try:
    while True:
        # 카메라로부터 프레임 캡처
        ret, frame = cap.read()
        if not ret:
            break

        cv2.imshow('Camera View', frame)

        # ArUco 마커 ID 찾기
        try:
            ID = findArucoID(frame)
            print("Marker ID is", ID)
            marker_count += 1  # 마커 인식 횟수 증가

            # 아두이노에 마커 인식 횟수 전송
            ser.write(str(marker_count).encode())

        except Exception as e:
            pass

        # 'q'를 누르면 종료
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
except KeyboardInterrupt:
    print("Program interrupted.")

# 자원 해제
cap.release()
cv2.destroyAllWindows()
ser.close()
