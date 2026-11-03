import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, confusion_matrix, roc_curve, roc_auc_score
import warnings
warnings.filterwarnings('ignore')

# 1. Load and clean
df = pd.read_csv('emails.csv')
df = df.dropna(axis=1, how='all').drop_duplicates().reset_index(drop=True)

# 2. Separate Features (X) and Target (y)
X = df.iloc[:, 1:-1].copy()
y = pd.to_numeric(df.iloc[:, -1], errors='coerce').fillna(0).astype(int)

# 3. Split dataset
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state=42, stratify=y)

# 4. Feature Scaling (Crucial for KNN and SVM)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 5. Train KNN and SVM (with probability=True for ROC)
knn = KNeighborsClassifier(n_neighbors=5, weights='distance')
knn.fit(X_train_scaled, y_train)
knn_prob = knn.predict_proba(X_test_scaled)[:, 1]

svm = SVC(kernel='rbf', C=1.0, gamma='scale', probability=True, random_state=42)
svm.fit(X_train_scaled, y_train)
svm_prob = svm.predict_proba(X_test_scaled)[:, 1]

# 6. Evaluate and Compare
for name, model, prob in [('KNN', knn, knn_prob), ('SVM', svm, svm_prob)]:
    pred = model.predict(X_test_scaled)
    print(f"\n--- {name} ---")
    print("Accuracy:", accuracy_score(y_test, pred))
    print("Confusion Matrix:\n", confusion_matrix(y_test, pred))

# 7. Plot ROC Curve for Comparison
plt.figure(figsize=(8, 5))
for name, prob in [('KNN', knn_prob), ('SVM', svm_prob)]:
    fpr, tpr, _ = roc_curve(y_test, prob)
    plt.plot(fpr, tpr, label=f"{name} (AUC = {roc_auc_score(y_test, prob):.2f})")

plt.plot([0, 1], [0, 1], 'k--')
plt.title('ROC Curve: KNN vs SVM')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.legend()
plt.tight_layout()
plt.show()

