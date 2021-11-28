import cv2
import numpy as np

def load_image_file():
    path = "Dataset_OpenCvDl_Hw1/Q1_Image/Sun.jpg"
    img = cv2.imread(path)
    height, width, _ = img.shape
    print(f"Height : {height}")
    print(f"Width : {width}")
    cv2.imshow('Hw1-1', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print("\n")
    return

def color_separation():
    path = "Dataset_OpenCvDl_Hw1/Q1_Image/Sun.jpg"
    img = cv2.imread(path)
    chanel_b, chanel_g, chanel_r = cv2.split(img)
    img_b = np.zeros(img.shape, dtype=np.uint8)
    img_b[:, :, 0] = chanel_b
    img_g = np.zeros(img.shape, dtype=np.uint8)
    img_g[:, :, 1] = chanel_g
    img_r = np.zeros(img.shape, dtype=np.uint8)
    img_r[:, :, 2] = chanel_r
    cv2.imshow('B channel', img_b)
    cv2.imshow('G channel', img_g)
    cv2.imshow('R channel', img_r)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return
    
def color_transformation():
    path = "Dataset_OpenCvDl_Hw1/Q1_Image/Sun.jpg"
    img = cv2.imread(path)
    chanel_b, chanel_g, chanel_r = cv2.split(img)
    I1 = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    I2 = chanel_b // 3 + chanel_g // 3 + chanel_r // 3
    cv2.imshow('I1', I1)
    cv2.imshow('I2', I2)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def blending(weight=128):
    path = "Dataset_OpenCvDl_Hw1/Q1_Image/"
    dog_strong = cv2.imread(path + "Dog_Strong.jpg")
    dog_weak = cv2.imread(path + "Dog_Weak.jpg")
    
    img = cv2.addWeighted(dog_strong, (255 - weight) /
                          255, dog_weak, weight / 255, 0)
    cv2.namedWindow('Blend')
    cv2.imshow('Blend', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return

def blending_trackbar(weight = 128):
    path = "Dataset_OpenCvDl_Hw1/Q1_Image/"
    dog_strong = cv2.imread(path + "Dog_Strong.jpg")
    dog_weak = cv2.imread(path + "Dog_Weak.jpg")
    img = cv2.addWeighted(dog_strong, (255 - weight) /
                          255, dog_weak, weight / 255, 0)
    cv2.namedWindow('Blend')
    def update(x):
        weight = cv2.getTrackbarPos('Blend', 'Blend')
        img = cv2.addWeighted(dog_strong, (255 - weight) /
                              255, dog_weak, weight / 255, 0)
        print('Update Weight, weight ={}'.format(weight))
        cv2.imshow('Blend', img)
    
    cv2.createTrackbar('Blend', 'Blend', 0, 255, update)
    cv2.setTrackbarPos('Blend', 'Blend', weight)
    cv2.imshow('Blend', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return
