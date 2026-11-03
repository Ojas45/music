import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
import scipy.cluster.hierarchy as sch

# 1. Load Sales Data
df = pd.read_csv('sales_data_sample.csv', encoding='latin1')
numeric_features = df.select_dtypes(include=[np.number]).dropna(axis=1)

# 2. Scale Features
scaler = StandardScaler()
scaled_data = scaler.fit_transform(numeric_features)

# 3. Calculate WCSS for Elbow Method
wcss = []
for k in range(1, 11):
    kmeans = KMeans(n_clusters=k, init='k-means++', random_state=42)
    kmeans.fit(scaled_data)
    wcss.append(kmeans.inertia_)

# 4. Plot Elbow Method & Hierarchical Dendrogram
plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)
plt.plot(range(1, 11), wcss, marker='o')
plt.title('Elbow Method for Optimal K')
plt.xlabel('Number of Clusters (K)')
plt.ylabel('WCSS (Inertia)')

plt.subplot(1, 2, 2)
dendrogram = sch.dendrogram(sch.linkage(scaled_data[:50], method='ward'))
plt.title('Hierarchical Clustering Dendrogram')
plt.xlabel('Customers / Data Points')
plt.ylabel('Euclidean Distances')
plt.tight_layout()
plt.show()

