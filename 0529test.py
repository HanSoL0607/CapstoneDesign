
import numpy as np
import cv2
import pytesseract
import serial
import time

# 새로운 코드
arduino = serial.Serial('com4', 9600)    # 아두이노 컴포트
time.sleep(1)

where = str(input("where do you want to go? : "))
cap = cv2.VideoCapture(2)
empty_list = []
idx = 0


while True:
    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    img_blurred = cv2.GaussianBlur(gray, ksize=(5, 5), sigmaX=0)
    img_blur_thresh = cv2.adaptiveThreshold(
        img_blurred,
        maxValue=255.0,
        adaptiveMethod=cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
        thresholdType=cv2.THRESH_BINARY_INV,
        blockSize=19,
        C=9)
    cv2.imshow('blur_thresh', img_blur_thresh)
    # 이때 text는 str 이다.
    text = pytesseract.image_to_string(
        img_blur_thresh, config='--psm 10 --oem 3 -c tessedit_char_whitelist=0123456789')
    if text != "\x0c":
        pass
    if len(text) != 3:
        empty_list.append(text.strip("\n\x0c"))
        if empty_list[-1] == where:
            print("아두이노 코드 동작 시작")
            item = "1"  # 아두이노 동작 시작을 위한 변수 설정
            item = item.encode('utf-8')
            arduino.write(item)
    if cv2.waitKey(20) & 0xFF == ord('q'):
        break

# q 누르면 웹캠 창 꺼짐
cap.release()
cv2.destroyAllWindows()
