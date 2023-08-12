import numpy as np
import matplotlib.pyplot as plt
from sklearn.mixture import GaussianMixture

# 가상의 데이터 생성
np.random.seed(0)
cluster1 = np.random.randn(100, 2) + np.array([3, 3])
cluster2 = np.random.randn(100, 2) + np.array([-3, -3])
data = np.vstack((cluster1, cluster2))

n_clusters = 2
gmm = GaussianMixture(n_components=n_clusters)
gmm.fit(data)

# 클러스터의 중심 확인
cluster_centers = gmm.means_

print("Estimated Cluster Centers:")
for i, center in enumerate(cluster_centers):
    print(f"Cluster {i + 1}: {center}")

# 시각화
plt.scatter(data[:, 0], data[:, 1], c=gmm.predict(data), cmap='viridis')
plt.scatter(cluster_centers[:, 0], cluster_centers[:, 1], c='red', marker='X', s=100)
plt.title('GMM Clustering with Estimated Cluster Centers')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.show()
