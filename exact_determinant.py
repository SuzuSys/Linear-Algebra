import numpy as np
import pandas as pd

data = pd.read_csv('data.csv', delimiter=' ', skiprows=[0], header=None).to_numpy()
determinant = np.linalg.det(data)
print('{:.15g}'.format(determinant))