import numpy as np
import matplotlib.pyplot as plt
from sklearn.mixture import GaussianMixture
from PIL import Image, ImageColor
import cv2

# 이미지 로드
# image_path = '0.png'
# image = Image.open(image_path)
# hsv_image = ImageColor.rgb2hsv(image)
# image_array = np.array(hsv_image)

# 이미지 불러오기
image_path = '0.png'  # 이미지 경로 설정
image = cv2.imread(image_path)
# hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
# hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2LAB)


# 이미지를 RGB 채널로 분리
red_channel = hsv_image[:, :, 0]
green_channel = hsv_image[:, :, 1]
blue_channel = hsv_image[:, :, 2]

# 데이터 준비 (각 채널을 2D 배열로 변환)
data_red = red_channel.reshape(-1, 1)
data_green = green_channel.reshape(-1, 1)
data_blue = blue_channel.reshape(-1, 1)

# EM 알고리즘을 사용하여 GMM 피팅
n_clusters = 2
gmm_red = GaussianMixture(n_components=n_clusters)
gmm_red.fit(data_red)

gmm_green = GaussianMixture(n_components=n_clusters)
gmm_green.fit(data_green)

gmm_blue = GaussianMixture(n_components=n_clusters)
gmm_blue.fit(data_blue)

# 분산 시각화
x_range = np.arange(0, 256).reshape(-1, 1)

# hue_range = np.linspace(0, 360, 361).reshape(-1, 1)
# saturation_range = np.linspace(0, 1, 256).reshape(-1, 1)
# value_range = np.linspace(0, 1, 256).reshape(-1, 1)

plt.figure(figsize=(15, 5))

plt.subplot(131)
plt.plot(x_range, np.exp(gmm_red.score_samples(x_range)), color='red')
plt.title('0 Channel Variance')
plt.xlabel('Pixel Intensity')
plt.ylabel('Density')

plt.subplot(132)
plt.plot(x_range, np.exp(gmm_green.score_samples(x_range)), color='green')
plt.title('1 Channel Variance')
plt.xlabel('Pixel Intensity')
plt.ylabel('Density')

plt.subplot(133)
plt.plot(x_range, np.exp(gmm_blue.score_samples(x_range)), color='blue')
plt.title('2 Channel Variance')
plt.xlabel('Pixel Intensity')
plt.ylabel('Density')

plt.tight_layout()
plt.show()
