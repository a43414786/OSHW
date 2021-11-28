import cv2

def Gaussion_blur():
    path = "Dataset_OpenCvDl_Hw1/Q2_Image/"
    img = cv2.imread(path + "Lenna_whiteNoise.jpg")
    new_img = cv2.GaussianBlur(img, (5, 5), 0)
    cv2.imshow('Lenna_whiteNoise', img)
    cv2.imshow('Gaussian Blur', new_img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def Bilateral_filter():
    path = "Dataset_OpenCvDl_Hw1/Q2_Image/"
    img = cv2.imread(path + "Lenna_whiteNoise.jpg")
    new_img = cv2.bilateralFilter(img, 9, 90, 90)
    cv2.imshow('Lenna_whiteNoise', img)
    cv2.imshow('Bilateral Filter', new_img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def Median_filter():
    path = "Dataset_OpenCvDl_Hw1/Q2_Image/"
    img = cv2.imread(path + "Lenna_pepperSalt.jpg")
    new_img1 = cv2.medianBlur(img, 3)
    new_img2 = cv2.medianBlur(img, 5)
    cv2.imshow('Lenna_pepperSalt', img)
    cv2.imshow('3x3 median filter', new_img1)
    cv2.imshow('5x5 median filter', new_img2)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return
