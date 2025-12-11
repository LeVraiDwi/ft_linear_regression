import numpy as np
import pandas as pd
import sys
import math
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

i = 1

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


    print(f"MSE: {meanSQuareError(df_pred)}")

    fig, ax = plt.subplots()
    ax.scatter(dataset_test['price'], dataset_test['km'])
    ln, = ax.plot(df_pred[f"price_{i}"], df_pred['km'])
    i += 1

    def artist():
        return ln

    def Update(frame):
        global i
        ax.clear()
        ax.scatter(dataset_test['price'], dataset_test['km'])
        ax.plot(df_pred[f"price_{i}"], df_pred['km'])
        i += 1

    amimation = FuncAnimation(fig, Update, interval=10, init_func=artist, cache_frame_data=False)
    plt.grid(True)
    plt.tight_layout()
    plt.show()
except:
    print("fail Procesing Thetas or data")
    exit(1)