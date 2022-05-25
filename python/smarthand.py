import serial
import cv2
from cvzone.HandTrackingModule import HandDetector


cap=cv2.VideoCapture(0)
detector=HandDetector(detectionCon=0.8 , maxHands=2)
myserial = serial.Serial('com5',9600)

while True:
    success, img=cap.read()
    hands,img=detector.findHands(img)
    print(len(hands))

   # HAND -dict (lmList --bbox -center -type) el hajet el *i aadek al yed wahda w tajem ta3mel ka3ba okhra ken bech

    if hands :    #hands list mte3 el hands
        #first hand
        hand1 = hands[0]
        lmList1 = hand1["lmList"]  #list of 21 handmarks point
        bbox1 = hand1["bbox"]       #bounding box info x,y,w,h
        centerPoint1 = hand1["center"]  #center of the hand
        handtype = hand1["type"]  #left or right
        finger1 = detector.fingersUp(hand1)
        print(finger1)
        chaine = '$'+str(finger1[0])+str(finger1[1])+str(finger1[2])+str(finger1[3])+str(finger1[4])
        print(chaine)

        myserial.write(chaine.encode())
    cv2.imshow("Image", img)
    if ( cv2.waitKey(1) ) & 0xFF==ord('a') :
     break
