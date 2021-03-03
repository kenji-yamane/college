from tensorflow.keras.models import load_model
import cv2
import numpy as np
from utils import sigmoid
from math import exp


class YoloDetector:
    """
    Represents an object detector for robot soccer based on the YOLO algorithm.
    """
    def __init__(self, model_name, anchor_box_ball=(5, 5), anchor_box_post=(2, 5)):
        """
        Constructs an object detector for robot soccer based on the YOLO algorithm.

        :param model_name: name of the neural network model which will be loaded.
        :type model_name: str.
        :param anchor_box_ball: dimensions of the anchor box used for the ball.
        :type anchor_box_ball: bidimensional tuple.
        :param anchor_box_post: dimensions of the anchor box used for the goal post.
        :type anchor_box_post: bidimensional tuple.
        """
        self.network = load_model(model_name + '.hdf5')
        self.network.summary()  # prints the neural network summary
        self.anchor_box_ball = anchor_box_ball
        self.anchor_box_post = anchor_box_post

    def detect(self, image):
        """
        Detects robot soccer's objects given the robot's camera image.

        :param image: image from the robot camera in 640x480 resolution and RGB color space.
        :type image: OpenCV's image.
        :return: (ball_detection, post1_detection, post2_detection), where each detection is given
                by a 5-dimensional tuple: (probability, x, y, width, height).
        :rtype: 3-dimensional tuple of 5-dimensional tuples.
        """
        image = self.preprocess_image(image)
        output = self.network.predict(image)
        ball_detection, post1_detection, post2_detection = self.process_yolo_output(output)
        return ball_detection, post1_detection, post2_detection

    def preprocess_image(self, image):
        """
        Preprocesses the camera image to adapt it to the neural network.

        :param image: image from the robot camera in 640x480 resolution and RGB color space.
        :type image: OpenCV's image.
        :return: image suitable for use in the neural network.
        :rtype: NumPy 4-dimensional array with dimensions (1, 120, 160, 3).
        """
        image = cv2.resize(image, (160, 120), interpolation=cv2.INTER_AREA)
        image = np.array(image)
        image = image/255.0
        image = np.reshape(image, (1, 120, 160, 3))
        return image

    def process_yolo_output(self, output):
        """
        Processes the neural network's output to yield the detections.

        :param output: neural network's output.
        :type output: NumPy 4-dimensional array with dimensions (1, 15, 20, 10).
        :return: (ball_detection, post1_detection, post2_detection), where each detection is given
                by a 5-dimensional tuple: (probability, x, y, width, height).
        :rtype: 3-dimensional tuple of 5-dimensional tuples.
        """
        coord_scale = 4 * 8  # coordinate scale used for computing the x and y coordinates of the BB's center
        bb_scale = 640  # bounding box scale used for computing width and height
        output = np.reshape(output, (15, 20, 10))  # reshaping to remove the first dimension
        ball_probability, xb, yb, wb, hb = 0.0, 0.0, 0.0, 0.0, 0.0
        post1_probability, xp1, yp1, wp1, hp1 = 0.0, 0.0, 0.0, 0.0, 0.0
        post2_probability, xp2, yp2, wp2, hp2 = 0.0, 0.0, 0.0, 0.0, 0.0

        for i in range(15):
            for j in range(20):
                if sigmoid(output[i, j, 0]) > ball_probability:
                    ball_probability = sigmoid(output[i, j, 0])
                    xb = (j + sigmoid(output[i, j, 1]))*coord_scale
                    yb = (i + sigmoid(output[i, j, 2]))*coord_scale
                    wb = bb_scale*self.anchor_box_ball[0]*exp(output[i, j, 3])
                    hb = bb_scale*self.anchor_box_ball[1]*exp(output[i, j, 4])

                if sigmoid(output[i, j, 5]) > post1_probability:
                    post2_probability = post1_probability
                    xp2 = xp1
                    yp2 = yp1
                    wp2 = wp1
                    hp2 = hp1
                    post1_probability = sigmoid(output[i, j, 5])
                    xp1 = (j + sigmoid(output[i, j, 6]))*coord_scale
                    yp1 = (i + sigmoid(output[i, j, 7]))*coord_scale
                    wp1 = bb_scale*self.anchor_box_post[0]*exp(output[i, j, 8])
                    hp1 = bb_scale*self.anchor_box_post[1]*exp(output[i, j, 9])
        ball_detection = (ball_probability, xb, yb, wb, hb)
        post1_detection = (post1_probability, xp1, yp1, wp1, hp1)
        post2_detection = (post2_probability, xp2, yp2, wp2, hp2)
        return ball_detection, post1_detection, post2_detection
