## 라즈베리파이4B에 우분투 22.04를 설치하고 opencv 4.8.0을 이용해 aruco marker를 인식하는 코드를 작성하였다.
---
### assets
test 디렉터리의 aruco_make.py를 이용해 생성한 aruco maker를 담았다.

---
### sripts
1. aruco_camera_NoModule
aruco 모듈을 사용하지 않고 라즈베리파이의 카메라를 이용해 aruco marker를 인식하면 id를 출력하는 코드
(카메라 성능 문제인지 aruco 모듈을 사용하지 않음에 따른 문제인지 동일한 aruco marker를 인식시켜도 다른 id가 계속 출력된다...)

2. aruco_camera
aruco 모듈을 사용하여 라즈베리파이 카메라로 aruco marker를 인식하여 id를 출력하는 코드
(카메라로 aruco marker를 인식시켜도 아무런 값도 출력되지 않는다...)

---
### test
1. camera_test
라즈베리파이의 카메라가 켜지는지 확인하는 코드

2. aruco_make
파이썬 코드를 이용해 원하는 id의 aruco marker를 생성하는 코드

3. aruco_file_detect_NoModule
aruco 모듈을 사용하지 않고 디렉터리 내의 aruco marker의 id를 출력하는 코드
(어째서인지 aruco_make.py에서 설정한 id와 다른 id가 출력된다...)

4. bluetooth
aruco marker를 인식한 횟수를 쌓아 이를 블루투스 통신으로 아두이노 우노에 전송하는 코드
