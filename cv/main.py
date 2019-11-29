    import os
import json
import numpy as np
import serial
import time
from RESTRequest import pose_estimator

PORTNUM = 'COM10'
BAUDRATE = 9600
PAUSFRAME = 2

connected = True

def delAll():
    path_to_json = './json_file_stream/'
    json_files = [pos_json for pos_json in os.listdir(path_to_json) if pos_json.endswith('.json')]
    for i, js in enumerate(json_files,0):
        os.remove(os.path.join(path_to_json, js))

print("Port starting...")
try:
    ser = serial.Serial(port = PORTNUM,baudrate = BAUDRATE)
    print('Port start successful. ')
    connected = True
except:
    print("Port {} failed to connect, starting with out connection".format(PORTNUM))
    ser = None
    connected = False

def sendCom(ser,msg):
    if connected:
        try:
            ser.write(msg)
        except:
            print("Failed to send {} to port {}.".format(msg,PORTNUM))

print("OpenPose starting...")
os.system('start cmd /k "cd openpose_compiled & bin\OpenPoseDemo.exe --write_json ../json_file_stream --number_people_max 1"')
time.sleep(1)

print('File mointor starting...')
estmator = pose_estimator()
waitFrame = 0
Points = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
last_points = Points
delAll()
i=0
while True:
    last_points = Points
    path_to_json = './json_file_stream/'
    json_files = [pos_json for pos_json in os.listdir(path_to_json) if pos_json.endswith('.json')]

    # Have found 1 or more json file
    if len(json_files)>=1:
        try:
            with open(os.path.join(path_to_json, json_files[0])) as json_file:
                json_text = json.load(json_file)
                Points = json_text["people"][0]["pose_keypoints_2d"]
        except:
            Points = last_points

        if waitFrame<=0:
            resDic = estmator.track(Points)
            if resDic['x']=='Left':
                print('go left')
                waitFrame = PAUSFRAME
                sendCom(ser,b'turn -1 0\n')
            elif resDic['x']=='Right':
                print('go right')
                waitFrame = PAUSFRAME
                sendCom(ser,b'turn 1 0\n')
            elif resDic['x'] is None and resDic['distance'] is None:
                sendCom(ser,b'stop\n')
                waitFrame = 0
                if estmator.add(Points):
                    print('give')
                    time.sleep(0.5)
                    sendCom(ser,b'serve\n')
            elif resDic['distance']=='Forward':
                print('go forward')
                waitFrame = PAUSFRAME
                sendCom(ser,b'turn 0 1\n')
                estmator.add(Points)
            elif resDic['distance']=='Backward':
                waitFrame = PAUSFRAME
                print('go back')
                sendCom(ser,b'turn 0 -1\n')
                estmator.add(Points)
        else:
            # print('skip')
            waitFrame-=1

        try:
            for i, js in enumerate(json_files,0):
                os.remove(os.path.join(path_to_json, js))
        except:
            i=0
'''
Command to run OpenPoseDemo: 
bin\OpenPoseDemo.exe --write_json ../json_file_stream --number_people_max 1
'''
