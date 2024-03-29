# Computer Vision and Control
## Quick Start Guide
1. Download [OpenPose v1.5.1 compiled version](https://github.com/CMU-Perceptual-Computing-Lab/openpose/releases/download/v1.5.1/openpose-1.5.1-binaries-win64-gpu-python-flir-3d_recommended.zip) or [Original GitHub Repostory](https://github.com/CMU-Perceptual-Computing-Lab/openpose/releases)
2. Unzip and put `openpose_compiled` folder inside `/CV`.  
   * Keep in mind that there are two ```openpose_compiled``` folder, put the one that is the root of the zip file in side `/CV` and don't change anything else.
3. Download all required python packages:
   * `os`
   * `json`
   * `numpy`
   * `serial`
   * `time`
   * `statistics`
   * `csv` (Only for reading and writing CSV files for the purposes of improving detection algorithms)
   * `tkinter` (For manual control only)
4. Change the port number and baud rate inside `main.py`
5. Run `main.py` and enjoy.

## Files Description
* main.py
  - Main control loop of the program.
  - Author: Louis ([@Beepbloop](https://github.com/Beepbloop))
* RESTRequest.py
  - ```pose_estimator``` class
  - Author: Nico ([@Nico](https://youtu.be/dQw4w9WgXcQ))
* manual.py
  - Manual control loop for testing the robot.
  - Author: Someone
* SittingTest.csv / NotSittingTest.csv
  - Datasets for sitting and not sitting.
  - X,Y pixel poisons using the webcam.
  - 0 for all points that are not detected.
  ![](https://raw.githubusercontent.com/CMU-Perceptual-Computing-Lab/openpose/master/doc/media/keypoints_pose_25.png)

## New Features
* Auto start OpenPoseDemo.exe
* No port connection support. *(Untested)*

## Things To Improve
* Better pose estimator
* Using the OpenPose API insted of reading and deleting JSON files.
