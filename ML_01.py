
# Practical 1: Uber Fare Prediction

import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

# 1. Load Dataset
df = pd.read_csv("uber.csv")

# 2. Data Preprocessing
df = df.dropna()
df = df.drop_duplicates()

# Remove unnecessary columns if present
df = df.drop(columns=["Unnamed: 0", "key"], errors="ignore")

# Remove invalid fare and coordinates
df = df[df["fare_amount"] > 0]
df = df[
    df["pickup_latitude"].between(-90, 90) &
    df["dropoff_latitude"].between(-90, 90) &
    df["pickup_longitude"].between(-180, 180) &
    df["dropoff_longitude"].between(-180, 180)
]

# 3. Select Features and Target
X = df[[
    "pickup_latitude",
    "pickup_longitude",
    "dropoff_latitude",
    "dropoff_longitude"
]]

y = df["fare_amount"]

# 4. Split Dataset
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# 5. Linear Regression
lr = LinearRegression()
lr.fit(X_train, y_train)

pred_lr = lr.predict(X_test)

# 6. Random Forest Regression
rf = RandomForestRegressor(n_estimators=100, random_state=42)
rf.fit(X_train, y_train)

pred_rf = rf.predict(X_test)

# 7. Model Evaluation
print("Linear Regression")
print("MAE:", mean_absolute_error(y_test, pred_lr))
print("RMSE:", np.sqrt(mean_squared_error(y_test, pred_lr)))
print("R2 Score:", r2_score(y_test, pred_lr))

print("\nRandom Forest Regression")
print("MAE:", mean_absolute_error(y_test, pred_rf))
print("RMSE:", np.sqrt(mean_squared_error(y_test, pred_rf)))
print("R2 Score:", r2_score(y_test, pred_rf))

# 8. Predict New Uber Fare
new_ride = pd.DataFrame([{
    "pickup_latitude": 40.7580,
    "pickup_longitude": -73.9855,
    "dropoff_latitude": 40.7484,
    "dropoff_longitude": -73.9857
}])

print("\nPredicted Fare using Linear Regression:",
      lr.predict(new_ride)[0])

print("Predicted Fare using Random Forest:",
      rf.predict(new_ride)[0])

