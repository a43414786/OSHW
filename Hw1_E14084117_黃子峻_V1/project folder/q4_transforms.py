import cv2
import numpy as np
img_path = 'Dataset_OpenCvDl_Hw1/Q4_Image/SQUARE-01.png'

def resize():
    img = cv2.imread(img_path)
    img_resize = cv2.resize(img, (256, 256))
    cv2.imshow('Resize', img_resize)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def translation(shift_x = 0, shift_y = 60):
    img = cv2.imread(img_path)
    img_resize = cv2.resize(img, (256, 256))
    M = np.array([[1, 0, shift_x], [0, 1, shift_y]], dtype = np.float32)
    img_trans = cv2.warpAffine(img_resize, M, (400, 300))
    cv2.imshow('Translation', img_trans)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def rotation_scaling(shift_x=0, shift_y=60, angle=10, scale=0.5):
    img = cv2.imread(img_path)
    img_resize = cv2.resize(img, (256, 256))
    M = np.array([[1, 0, shift_x], [0, 1, shift_y]], dtype=np.float32)
    img_trans = cv2.warpAffine(img_resize, M, (400, 300))
    M = cv2.getRotationMatrix2D(
        (128, 188), angle, scale)
    img_rt = cv2.warpAffine(img_trans, M, (400, 300))
    cv2.imshow('Rotate and scale', img_rt)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def shearing():
    img = cv2.imread(img_path)
    shift_x = 0
    shift_y = 60
    angle = 10
    scale = 0.5
    img_resize = cv2.resize(img, (256, 256))
    M = np.array([[1, 0, shift_x], [0, 1, shift_y]], dtype=np.float32)
    img_trans = cv2.warpAffine(img_resize, M, (400, 300))
    M = cv2.getRotationMatrix2D(
        (128, 188), angle, scale)
    img_rt = cv2.warpAffine(img_trans, M, (400, 300))
    M2 = np.float32([[50, 50], [200, 50], [50, 200]])
    M3 = np.float32([[10, 100], [200, 50], [100, 250]])
    M4 = cv2.getAffineTransform(M2, M3)
    img_shear = cv2.warpAffine(img_rt, M4, (400, 300))
    cv2.imshow('Shearing', img_shear)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return