import numpy as np
import pandas as pd
import sys
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

i = 1

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

    mse = mean_squared_error(df_final_pred['price'], df_final_pred.iloc[:,-1:])
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(df_final_pred['price'], df_final_pred.iloc[:,-1:])
    r2 = r2_score(df_final_pred['price'], df_final_pred.iloc[:,-1:])

    print("MSE :", mse)
    print("RMSE:", rmse)
    print("MAE :", mae)
    print("R²  :", r2)

    
    fig, axes = plt.subplots()
    axes.scatter(dataset_test['price'], dataset_test['km'])
    ln, = axes.plot(df_pred[f"price_{i}"], df_pred['km'])
    axes.set_title(f"Data With Regression")
    axes.set_xlabel("Price")
    axes.set_ylabel("Mileage km")
    #axes[1].scatter(
    #        df_final_pred['price'],
    #        df_final_pred.iloc[:,-1:],
    #        alpha=0.5,
    #    )
    #axes[1].set_title(f"correlation between price and predicted price")
    #axes[1].set_xlabel("Price")
    #axes[1].set_ylabel("predicted price")
    i += 1

    def artist():
        return ln

    def Update(frame):
        global i
        axes.clear()
        axes.scatter(dataset_test['price'], dataset_test['km'])
        axes.plot(df_pred[f"price_{i}"], df_pred['km'])
        axes.set_title(f"Data With Regression")
        axes.set_xlabel("Price")
        axes.set_ylabel("Mileage km")
        i += 1

    amimation = FuncAnimation(fig, Update, interval=10, init_func=artist, cache_frame_data=False)
    plt.grid(True)
    plt.tight_layout()
    plt.show()
except:
    print("fail Procesing Thetas or data")
    exit(1)