import os
import json
import numpy as np
import serial
# import csv
import time
from RESTRequest import pose_estimator
# import pandas as pd

def delAll():
    path_to_json = './json_file_stream/'
    json_files = [pos_json for pos_json in os.listdir(path_to_json) if pos_json.endswith('.json')]
    for i, js in enumerate(json_files,0):
        os.remove(os.path.join(path_to_json, js))



PAUSFRAME = 2
print("Port starting...")
ser = serial.Serial('COM10',9600)
delAll()
i=0
print('File mointor starting...')
estmator = pose_estimator()
waitFrame = 0
Points = 0
while True:
    path_to_json = './json_file_stream/'
    json_files = [pos_json for pos_json in os.listdir(path_to_json) if pos_json.endswith('.json')]

    # Have found 1 or more json file
    if len(json_files)>=1:

        try:
            with open(os.path.join(path_to_json, json_files[0])) as json_file:
                json_text = json.load(json_file)
                Points = json_text["people"][0]["pose_keypoints_2d"]

        except:
            Points = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

        # if waitFrame<=0:
        #     resDic = estmator.track(Points)
        #     # print(resDic)
        #     if resDic['x']=='Left':
        #         print('go left')
        #         waitFrame = PAUSFRAME
        #         ser.write(b'turn -1 0\n')
        #     elif resDic['x']=='Right':
        #         print('go right')
        #         waitFrame = PAUSFRAME
        #         ser.write(b'turn 1 0\n')
        #     elif resDic['x'] is None and resDic['distance'] is None:
        #         ser.write(b'stop\n')
        #         waitFrame = 0
        #         if estmator.add(Points):
        #             print('give')
        #             time.sleep(0.5)
        #             ser.write(b'serve\n')
        #     elif resDic['distance']=='Forward':
        #         print('go forward')
        #         waitFrame = PAUSFRAME
        #         ser.write(b'turn 0 1\n')
        #         estmator.add(Points)
        #     elif resDic['distance']=='Backward':
        #         waitFrame = PAUSFRAME
        #         print('go back')
        #         ser.write(b'turn 0 -1\n')
        #         estmator.add(Points)
        # else:
        #     # print('skip')
        #     waitFrame-=1

        if estmator.add(Points):
            ser.write(b'serve\n')
            print('Good dog')
        else:
            print('Bad dog')

        try:
            for i, js in enumerate(json_files,0):
                os.remove(os.path.join(path_to_json, js))
        except:
            i=0
            # print('You Suck Haha')
'''
bin\OpenPoseDemo.exe --write_json ../json_file_stream --number_people_max 1
'''

# df[['X1','Y1','C1','X2','Y2','C2','X3','Y3','C3','X4','Y4','C4','X5','Y5','C5','X6','Y6','C6','X7','Y7','C7','X8','Y8','C8','X9','Y9','C9','X10','Y10','C10','X11','Y11','C11','X12','Y12','C12','X13','Y13','C13','X14','Y14','C14','X15','Y15','C15','X16','Y16','C16','X17','Y17','C17','X18','Y18','C18','X19','Y19','C19','X20','Y20','C20','X21','Y21','C21','X22','Y22','C22','X23','Y23','C23','X24','Y24','C24','X25','Y25','C25']] = pd.DataFrame(df.Points.values.tolist(), index= df.index)
# df.drop("Points", axis=1, inplace=True)
# df["Sitting"]=True
# df.to_csv(r'SittingTest.csv',index = None, header=True)
