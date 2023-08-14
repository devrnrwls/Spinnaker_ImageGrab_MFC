import cv2
import numpy as np
import matplotlib.pyplot as plt
from sklearn.mixture import GaussianMixture

# 이미지 불러오기
image_path = '0.png'
image = cv2.imread(image_path)
# hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
# hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2LAB)

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

# 클러스터 중심값 가져오기
cluster_centers_red = gmm_red.means_
cluster_centers_green = gmm_green.means_
cluster_centers_blue = gmm_blue.means_

print(cluster_centers_red)
print(cluster_centers_green)
print(cluster_centers_blue)

# 히스토그램 그리기
plt.figure(figsize=(12, 4))

plt.subplot(131)
plt.hist(data_red, bins=50, color='red', alpha=0.7)
plt.axvline(x=cluster_centers_red[0], color='black', linestyle='dashed', linewidth=2)
plt.axvline(x=cluster_centers_red[1], color='black', linestyle='dashed', linewidth=2)
plt.title('0 Channel')

plt.subplot(132)
plt.hist(data_green, bins=50, color='green', alpha=0.7)
plt.axvline(x=cluster_centers_green[0], color='black', linestyle='dashed', linewidth=2)
plt.axvline(x=cluster_centers_green[1], color='black', linestyle='dashed', linewidth=2)
plt.title('1 Channel')

plt.subplot(133)
plt.hist(data_blue, bins=50, color='blue', alpha=0.7)
plt.axvline(x=cluster_centers_blue[0], color='black', linestyle='dashed', linewidth=2)
plt.axvline(x=cluster_centers_blue[1], color='black', linestyle='dashed', linewidth=2)
plt.title('2 Channel')

plt.tight_layout()
plt.show()
