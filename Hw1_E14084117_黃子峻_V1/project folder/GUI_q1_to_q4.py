import sys
from PyQt5.QtWidgets import QApplication, QLabel, QWidget, QPushButton


import q1_image_processing as q1
import q2_image_smoothing as q2
import q3_dege_detection as q3
import q4_transforms as q4

class GUI:
    def __init__(self):
        
        app = QApplication(sys.argv)
        
        widget = QWidget()
        widget.setGeometry(50, 50, 800, 200)
        widget.setWindowTitle("2021 Opencvdl Hw1")
        
        label1 = QLabel(widget)
        label2 = QLabel(widget)
        label3 = QLabel(widget)
        label4 = QLabel(widget)
        
        label1.setText("1. Image Processing")
        label2.setText("2. Image Smoothing")
        label3.setText("3. Edge Detection")
        label4.setText("4. Transforms")
        
        label1.move(64, 10)
        label2.move(250, 10)
        label3.move(394, 10)
        label4.move(576, 10)
        
        
        button1 = QPushButton(widget)
        button1.setText("1.1 Load ImageFile")
        button1.move(64, 32)
        button1.clicked.connect(self.__button_1_1)
        
        button2 = QPushButton(widget)
        button2.setText("1.2 Color Separation")
        button2.move(64, 64)
        button2.clicked.connect(self.__button_1_2)
        
        button3 = QPushButton(widget)
        button3.setText("1.3 Color Transformation")
        button3.move(64, 96)
        button3.clicked.connect(self.__button_1_3)

        button4 = QPushButton(widget)
        button4.setText("1.4 Blending")
        button4.move(64, 128)
        button4.clicked.connect(self.__button_1_4)
        
        button5 = QPushButton(widget)
        button5.setText("2.1 Gaussian blur")
        button5.move(250, 32)
        button5.clicked.connect(self.__button_2_1)

        button6 = QPushButton(widget)
        button6.setText("2.2 Bilateral filter")
        button6.move(250, 64)
        button6.clicked.connect(self.__button_2_2)

        button7 = QPushButton(widget)
        button7.setText("2.3 Median filter")
        button7.move(250, 96)
        button7.clicked.connect(self.__button_2_3)
        
        button8 = QPushButton(widget)
        button8.setText("3.1 Gaussian Blur")
        button8.move(394, 32)
        button8.clicked.connect(self.__button_3_1)

        button9 = QPushButton(widget)
        button9.setText("3.2 Sobel X")
        button9.move(394, 64)
        button9.clicked.connect(self.__button_3_2)

        button10 = QPushButton(widget)
        button10.setText("3.3 Sobel Y")
        button10.move(394, 96)
        button10.clicked.connect(self.__button_3_3)

        button11 = QPushButton(widget)
        button11.setText("3.4 Magnitude")
        button11.move(394, 128)
        button11.clicked.connect(self.__button_3_4)

        button12 = QPushButton(widget)
        button12.setText("4.1 Resize")
        button12.move(576, 32)
        button12.clicked.connect(self.__button_4_1)
        
        button13 = QPushButton(widget)
        button13.setText("4.2 Translation")
        button13.move(576, 64)
        button13.clicked.connect(self.__button_4_2)

        button14 = QPushButton(widget)
        button14.setText("4.3 Rotation, Scaling")
        button14.move(576, 96)
        button14.clicked.connect(self.__button_4_3)

        button15 = QPushButton(widget)
        button15.setText("4.4 Shearing")
        button15.move(576, 128)
        button15.clicked.connect(self.__button_4_4)
        
        widget.show()
        print("GUI initialized")
        sys.exit(app.exec_())
    
    def __button_1_1(self):
        print("1.1Load Image File ")
        q1.load_image_file()
        return

    def __button_1_2(self):
        print("1.2 Color Separation")
        q1.color_separation()
        return
    
    def __button_1_3(self):
        print("1.3 Color Transformation")
        q1.color_transformation()
        return

    def __button_1_4(self):
        print("1.4 Blending")
        q1.blending()
        q1.blending_trackbar()
        return

    def __button_2_1(self):
        print("2.1 Gaussian blur")
        q2.Gaussion_blur()
        return

    def __button_2_2(self):
        print("2.2 Bilateral filter")
        q2.Bilateral_filter()
        return

    def __button_2_3(self):
        print("2.3 Median filter")
        q2.Median_filter()
        return

    def __button_3_1(self):
        print("3.1 Gaussian Blur")
        q3.Gaussian_blur()
        return

    def __button_3_2(self):
        print("3.2 Sobel X")
        q3.sobel_x()
        return

    def __button_3_3(self):
        print("3.3 Sobel Y")
        q3.sobel_y()
        return

    def __button_3_4(self):
        print("3.4 Magnitude")
        q3.magnitude()
        return
    
    def __button_4_1(self):
        print("4.1 Resize")
        q4.resize()
        return
    
    def __button_4_2(self):
        print("4.2 Translation")
        q4.translation()
        return

    def __button_4_3(self):
        print("4.3 Rotation, Scaling")
        q4.rotation_scaling()
        return

    def __button_4_4(self):
        print("4.4 Shearing")
        q4.shearing()
        return

if __name__ == '__main__':
    gui = GUI()
