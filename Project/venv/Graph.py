import numpy as np
import pandas as pd
import sys
import math
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

i = 1

# Mean
def Mean(values: list[float]) -> float:
    total = 0.0
    n = len(values)
    for v in values:
        total += v
    mean = total / n if n else float('nan')
    return mean

# Std
def Std(values: list[float]) -> float:
    squared_diff = 0.0
    n = len(values)
    mean = Mean(values)
    for v in values:
        squared_diff += (v - mean) ** 2
    std = (squared_diff / n) ** 0.5 if n else float('nan')
    return std

def Cov(v1: list[float], v2: list[float]) -> list[float]:
    valueX = np.array(v1)
    valueY = np.array(v2)

    if (len(valueX) != len(valueY)):
        raise ValueError("list don't have the same size")

    meanX = Mean(v1)
    meanY = Mean(v2)
    
    cov = np.sum((valueX - meanX) * (valueY - meanY))

    return cov

# Correlation between two set
def Corr(dataFrame: pd.DataFrame) -> list[float]:
    features = dataFrame.columns

    if (len(features) != 2):
        raise ValueError("must have 2 feature")
    
    if (features[0] == features[1]):
        return 1
    v1 = dataFrame[features[0]]
    v2 = dataFrame[features[1]]
    n = len(v1)
    cov = Cov(v1.values, v2.values)
    std1 = Std(v1)
    std2 = Std(v2)

    if std1 == 0 or std2 == 0:
        return 0
    return (cov / (std1 * std2)) / n # normalize with n

# return correlation matrix
def CorrMatrix(dataFrame: pd.DataFrame) -> pd.DataFrame:
    
    features = dataFrame.columns
    n = len(features)
    corr_matrix = np.zeros((n, n))

    for i in range(1, n):
        for j in range(1, n):
            new_df = dataFrame[[features[i], features[j]]].dropna()
            if (j >= i):
                corr_matrix[i, j] = Corr(new_df)
            else:
                corr_matrix[i, j] = corr_matrix[j, i]
    
    corr_df = pd.DataFrame(corr_matrix, index=features, columns=features)
    return corr_df

def meanSQuareError(df):
    nbCol = len(df.columns)
    sum = 0
    for index, row in df.iterrows():
        sum += row['price'] - row[f"price_{nbCol - 2}"]
    mse = sum / len(df.index)
    mse = (mse * mse) ** 0.5
    return mse

def Update(ln, mileage, thetax, thetay):
    ln.set_data([mileage * thetay + thetax],mileage)


def PredictPrice(mileage, thetaX, thetaY):
    return mileage * thetaY + thetaX

if len(sys.argv) != 3:
    print("Usage: python graph.py dataset_test.csv histoTheta.csv")
    sys.exit(1)

try:
    dataset_test = pd.read_csv(sys.argv[1])
    thetas = pd.read_csv(sys.argv[2])
except:
    print("fail reading csv")
    exit(1)

try:
    df = dataset_test.copy()

    # 1) Construire toutes les nouvelles colonnes dans un dict
    new_cols = {}

    for idx, row in thetas.iterrows():
        theta0 = row["theta0"]
        theta1 = row["theta1"]
        col_name = f"price_{idx+1}"
        new_cols[col_name] = dataset_test["km"] * theta1 + theta0

    # 2) Convertir le dict en DataFrame
    df_prices = pd.DataFrame(new_cols)

    # 3) Concaténer une seule fois
    df_pred = pd.concat([df, df_prices], axis=1)

    df_final_pred = df_pred.iloc[:, [ 1, -1]]
    cor = Corr(df_final_pred)
    print(cor)
    print(f"MSE: {meanSQuareError(df_pred)}")

    fig, axes = plt.subplots(nrows=1, ncols=2)
    axes[0].scatter(dataset_test['price'], dataset_test['km'])
    ln, = axes[0].plot(df_pred[f"price_{i}"], df_pred['km'])
    axes[1].scatter(
            df_final_pred['price'],
            df_final_pred['price_2662'],
            alpha=0.5,
        )
    i += 1

    def artist():
        return ln

    def Update(frame):
        global i
        axes[0].clear()
        axes[0].scatter(dataset_test['price'], dataset_test['km'])
        axes[0].plot(df_pred[f"price_{i}"], df_pred['km'])
        i += 1

    amimation = FuncAnimation(fig, Update, interval=10, init_func=artist, cache_frame_data=False)
    plt.grid(True)
    plt.tight_layout()
    plt.show()
except:
    print("fail Procesing Thetas or data")
    exit(1)