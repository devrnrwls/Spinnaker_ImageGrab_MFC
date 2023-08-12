import numpy as np
import matplotlib.pyplot as plt
from sklearn.mixture import GaussianMixture
import cv2

# 이미지 불러오기
image_path = '0.png'  # 이미지 경로 설정
image = cv2.imread(image_path)
# hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
# hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2LAB)

# 이미지를 2D 배열로 변환
height, width, channels = hsv_image.shape
pixels = hsv_image.reshape((height * width, channels))

# EM 알고리즘을 사용하여 클러스터링
n_clusters = 2  # 클러스터 수
gmm = GaussianMixture(n_components=n_clusters)
gmm.fit(pixels)

cluster_centers = gmm.means_

channel_diffs = np.abs(np.diff(cluster_centers, axis=0))
most_different_channel = np.argmax(channel_diffs[0])
most_different_cluster_centers = cluster_centers[:, most_different_channel]

print("cluster_centers", cluster_centers)
print("channel_diffs: ", channel_diffs[0])
print("most_different_channel: ", most_different_channel)
print("most_different_cluster_centers: ", most_different_cluster_centers)

# cluster_center =[]
# for cluster_idx in range(n_clusters):
#     cluster_center.append(cluster_centers[cluster_idx][most_different_channel])

most_different_channel_pixels = pixels[:, most_different_channel]
most_different_channel_pixel = most_different_channel_pixels.reshape((height * width, 1))
most_different_channel_gmm = GaussianMixture(n_components=n_clusters)
most_different_channel_gmm.fit(most_different_channel_pixel)

cluster_center = most_different_channel_gmm.means_
cluster_covariance = most_different_channel_gmm.covariances_

cluster_ranges = []
center_threshold = 2
for center, covariance in zip(cluster_center, cluster_covariance):
    std_devs = np.sqrt(covariance)  # 분산의 제곱근을 표준편차로 사용
    cluster_range = [(center - center_threshold * std_devs).tolist(), (center + center_threshold * std_devs).tolist()]
    cluster_ranges.append(cluster_range)

print("Cluster Ranges:")
for i, cluster_range in enumerate(cluster_ranges):
    print(f"Cluster {i + 1}: {cluster_range}")


image_path = '3.png'  # 이미지 경로 설정
target_image = cv2.imread(image_path)
# target_hsv_image = cv2.cvtColor(target_image, cv2.COLOR_BGR2RGB)
target_hsv_image = cv2.cvtColor(target_image, cv2.COLOR_BGR2HSV)
# target_hsv_image = cv2.cvtColor(target_image, cv2.COLOR_BGR2LAB)
#
# most_different_channel의 채널 불러오기
most_different_channel_image = target_hsv_image[:, :, most_different_channel]

for i, cluster_range in enumerate(cluster_ranges):
    lower_bound, upper_bound = cluster_range
    selected_pixels = np.logical_or(most_different_channel_image < lower_bound, most_different_channel_image > upper_bound)

    # plt.imshow(selected_pixels)
    # plt.tight_layout()
    # plt.show()

    if i == 0:
        combined_selected_pixels = selected_pixels
    else:
        # 두 조건을 모두 만족하는 픽셀 찾기
        combined_selected_pixels = np.logical_and(combined_selected_pixels, selected_pixels)

##contour detection
thresholded_thickness = 70

gray_image = cv2.cvtColor(target_image, cv2.COLOR_BGR2GRAY)

# 배경 제거
_, thresholded = cv2.threshold(gray_image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

# 외곽선 찾기
contours, _ = cv2.findContours(thresholded, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 빈 마스크 생성
mask = np.zeros_like(gray_image)

# 각각의 외곽선에 대해 처리
for contour in contours:
    # 작은 외곽선은 무시
    if cv2.contourArea(contour) < 100:
        continue

    # 외곽선 영역을 마스크에 적용
    cv2.drawContours(mask, [contour], -1, 255, thickness=thresholded_thickness)

# 마스크 반전
inverted_mask = cv2.bitwise_not(mask)

# 마스크를 이용하여 원본 이미지에서 해당 부분 추출
# masked_image = cv2.bitwise_and(red_marked_image, red_marked_image, mask=inverted_mask)

combined_mask = np.logical_and(inverted_mask, combined_selected_pixels)


red_marked_image = target_hsv_image.copy()
red_marked_image[combined_mask, :] = [255, 0, 0]  # 빨간색으로 표시 (RGB 순서)

# Display the original and highlighted images side by side
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(target_hsv_image)
plt.title('Original New Image')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(combined_mask)
plt.title('Highlighted Outliers in Red')
plt.axis('off')

plt.tight_layout()
plt.show()