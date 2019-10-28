from statistics import mean
import csv
class pose_estimator:
    def __init__(self):
        self.femur_ratio_window = []
        self.actions = None
        self.count = 0
        self.forward_window = []
        self.backward_window = []
    def add(self, keypoints):
        array = []
        for i in range(0,len(keypoints)-1,3):
            try:
                float(keypoints[i+1])
                array.append(keypoints[i+1])
            except:
                continue
        if float(array[0]) > 0.0 and float(array[13])>0.0:
            max_dist = float(array[13])- float(array[0])
            femur_ratio = []
            if float(array[10]) > 0.0 and float(array[9]) > 0.0:
                femur_ratio.append((float(array[10])-float(array[9]))/max_dist)
            if float(array[13]) > 0.0 and float(array[12]) > 0.0:
                femur_ratio.append((float(array[13])-float(array[12]))/max_dist)
            final_femur = sum(femur_ratio)/2
            if len(self.femur_ratio_window) < 4:
                self.femur_ratio_window.append(final_femur)
            else:
                if not self.count:
                    if mean(self.femur_ratio_window) <= 0.27:
                        self.actions = 'Sitting'
                    else:
                        self.actions = 'Not Sitting'

                del self.femur_ratio_window[0]
                self.femur_ratio_window.append(final_femur)
                if mean(self.femur_ratio_window)<= 0.27:
                    # print('Sitting')
                    if self.actions == 'Not Sitting':
                        self.actions = 'Sitting'
                        return True
                else:
                    # print('Not Sitting')
                    if self.actions == 'Sitting':
                        self.actions = 'Not Sitting'
        return False

    def track(self, keypoints):
        x_points = []
        y_points = []
        result = {'x': None, 'distance':None}
        for i in range(0,len(keypoints)-1,3):
            x_points.append(keypoints[i])
            y_points.append(keypoints[i+1])
        # just going to do this with the hip point
        def x_angle(coor):
            '''
            :param coor:
            :return: string of turn left or right
            '''
            lower_bound = 140
            upper_bound = 480
            if lower_bound >= coor:
                result['x'] = 'Left'
            if upper_bound <= coor:
                result['x'] = 'Right'
        # you have to return the stop
        def measure_distance(y1, y2):
            '''
            :param y1:
            :param y2:
            :return: string move forward or backward
            '''
            lower_bound = 0.1
            upper_bound = 0.4
            max_size = 480
            if not y1:
                result['distance'] = 'Backward'

            difference =  y2-y1
            if difference < 0.0:
                return result
            ratio = difference/max_size
            leg = y_points[10] - y_points[9]
            leg_ratio = leg/max_size
            if len(self.forward_window):
                mean_upper = mean(self.forward_window)
                if mean_upper:
                    if mean_upper < lower_bound:
                        result['distance'] =  'Forward'
            if len(self.backward_window):
                mean_leg = mean(self.backward_window)
                if mean_leg:
                    if mean_leg > upper_bound:
                        result['distance'] =  'Backward'
            if len(self.forward_window) > 15:
                del self.forward_window[0]
            if len(self.backward_window) > 15:
                del self.backward_window[0]
            self.forward_window.append(ratio)
            self.backward_window.append(ratio)

        eight_node_y =  float(y_points[8])
        eight_node_x = float(x_points[8])
        zero_node = float(x_points[0])
        if eight_node_x > 0.0:
            x_angle(float(eight_node_x))
        if zero_node > 0.0 and eight_node_y > 0.0 :
                measure_distance(float(zero_node), float(eight_node_y))
        print(result)
        return result






# v  = pose_estimator()
# with open(r"G:\data_csv\MoveingTestData\tracking.csv") as csv_file:
#     csv_reader = csv.reader(csv_file, delimiter=',')
#     for index,image in enumerate(csv_reader):
#         if index:
#             print(v.track(image))
#             print(index)
