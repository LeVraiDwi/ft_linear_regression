import numpy as np
import pandas as pd
import sys
import math
import matplotlib.pyplot as plt

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python logreg_predict.py dataset_test.csv")
        sys.exit(1)

    dataset_test = pd.read_csv(sys.argv[1])
    result = pd.read_csv(sys.argv[2])

    plt.figure(figsize=(8, 6))
    plt.scatter(dataset_test['price'], dataset_test['km'])
    plt.plot(result['price'], result['km'])
    plt.grid(True)
    plt.tight_layout()
    plt.show()