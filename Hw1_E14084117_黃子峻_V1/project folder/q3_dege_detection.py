import cv2
import numpy as np

path = "Dataset_OpenCvDl_Hw1/Q3_Image/House.jpg"

def Gaussian_filter(dimensions = 3, sigma = 1):
    assert dimensions % 2 == 1, "Dimensions must be odd"
    assert dimensions == 3, "Can only work on dimension 3 now ..."
    G_init = np.zeros((dimensions, dimensions, 2))
    G_init[:, 0, 0] = np.array([-1, -1, -1])
    G_init[:, 1, 0] = np.array([0, 0, 0])
    G_init[:, 2, 0] = np.array([1, 1, 1])
    G_init[0, :, 1] = np.array([-1, -1, -1])
    G_init[1, :, 1] = np.array([0, 0, 0])
    G_init[2, :, 1] = np.array([1, 1, 1])
    def Gaussion(x, y):
        return np.exp(-((x**2 + y**2)/(2*sigma**2)))/(2*np.pi*sigma**2)

    G = np.array([Gaussion(element[0], element[1])
        for row in G_init for element in row])
    G = G.reshape(dimensions, dimensions)
    G_norm = G / np.sum(G)
    print("G_init: \n", G_init)
    print("G: \n", G)
    print("G_norm: \n", G_norm)
    return G_norm

def sobel_x_filter():
    filter = np.array([[-1, 0, 1],
                       [-2, 0, 2],
                       [-1, 0, 1]])
    return filter

def sobel_y_filter():
   filter = np.array([[1, 2, 1],
                      [0, 0, 0],
                      [-1, -2, -1]])
   return filter

def image_padding(img, padding_size = (1, 1)):
    img_pad = np.zeros((img.shape[0] + padding_size[0]*2, img.shape[1] + padding_size[1]*2), dtype = np.uint8)
    img_pad[padding_size[0]:img.shape[0] + padding_size[0], padding_size[1]:img.shape[1] + padding_size[1]] = img
    return img_pad


def apply_filter(img, filter, Abs = True):
    assert len(img.shape) == 2, "Image must be changed to grayscale"
    img_new = image_padding(img, (1, 1))
    # filter = np.flipud(np.fliplr(filter))
    print("Filter :\n", filter)
    img_result = np.zeros(img.shape, dtype = np.uint8)
    for i in range(img_new.shape[0]-2):
        for j in range(img_new.shape[1]-2):
            value = np.sum(img_new[i:i+3, j:j+3] * filter)
            if Abs:
                value = abs(value)
            if value > 255:
                img_result[i, j] = 255
            elif value < 0:
                img_result[i, j] = 0
            else:
                img_result[i, j] = value
    return np.uint8(img_result)
    
def Gaussian_blur():
    img = cv2.imread(path)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    filter = Gaussian_filter(3, 0.707)
    img_blur = apply_filter(img, filter)
    cv2.imshow('before', img)
    cv2.imshow('Gaussian Blur ', img_blur)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def sobel_x():
    img = cv2.imread(path)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    filter = Gaussian_filter(3, 0.707)
    img_blur = apply_filter(img, filter)
    filter = sobel_x_filter()
    img_x = apply_filter(img_blur, filter)
    cv2.imshow('Sobel X', img_x)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return

def sobel_y():
    img = cv2.imread(path)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    filter = Gaussian_filter(3, 0.707)
    img_blur = apply_filter(img, filter)
    filter = sobel_y_filter()
    img_y = apply_filter(img_blur, filter)
    cv2.imshow('Sobel Y', img_y)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return 

def magnitude():
    img = cv2.imread(path)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    filter = Gaussian_filter(3, 0.707)
    img_blur = apply_filter(img, filter, False)
    img_x = np.uint32(apply_filter(img_blur, sobel_x_filter()))
    img_y = np.uint32(apply_filter(img_blur, sobel_y_filter()))
    img_magnitude = np.zeros(img_x.shape, dtype=np.uint32)
    img_magnitude = np.sqrt(img_x**2 + img_y**2)
    img_magnitude[img_magnitude > 255] = 255
    img_magnitude[img_magnitude < 0] = 0
    img_magnitude = np.uint8(img_magnitude)
    
    cv2.imshow('Magnitude', img_magnitude)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print()
    return 
