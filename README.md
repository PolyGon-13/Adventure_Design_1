# 어드벤쳐디자인1 - 자율주행 분리수거 쓰레기통

[![YouTube](https://img.shields.io/badge/YouTube-FF0000?logo=youtube&logoColor=white)](https://youtu.be/tZrXBu0co70?si=BNptzdELSQ7ZVaE2)

광장, 역 등 유동 인구가 많은 공간을 대상으로 한 이동형 분리수거 쓰레기통 제작 프로젝트

## 개요

- DYNAMIXEL 모터 기반 이동 플랫폼
- 초음파 센서 기반 사람 및 장애물 감지
- Raspberry Pi 카메라 기반 ArUco Marker 인식
- 버튼 입력 기반 내부 레일 이동 및 하단 개폐식 배출 구조
- 후면 아크릴 구조와 미니 디스플레이 기반 상태 확인

## 전체 구조

### 이동 플랫폼과 외부 프레임

<p align="left">
  <img src="./image/robot-01.jpg" alt="이동 플랫폼과 외부 프레임" width="360">
</p>

### 전면 수거부와 센서 배치

<p align="left">
  <img src="./image/robot-03.jpg" alt="전면 수거부와 센서 배치" width="360">
</p>

## 분리수거 구조

### 내부 레일과 분리수거 공간

<p align="left">
  <img src="./image/robot-02.jpg" alt="내부 레일과 분리수거 공간" width="360">
</p>

### 미니 디스플레이와 초음파 센서

<p align="left">
  <img src="./image/robot-04.jpg" alt="미니 디스플레이와 초음파 센서" width="360">
</p>

## 동작 흐름

```mermaid
%%{init: {"theme": "base", "themeVariables": {"fontSize": "15px"}} }%%
flowchart LR
    A[사람/장애물 감지] --> B[로봇 정지] --> C[쓰레기 투입]
    C --> D[분리수거 버튼 입력] --> E[내부 레일 이동] --> F[지정 칸 배출]
```
