import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

one = pd.read_csv('E:/05_Reseach/05_doan/Analysis/analysis_1003.csv')
one.head()

one.info()

custom_order = ['nhom 3', 'nhom 4-', 'nhom 4+', 'nhom 5']
one['Group'] = pd.Categorical(one['Group'], categories=custom_order, ordered = True)
one_sorted = one.sort_values(by='Group')
one_sorted.rename(columns={'Formation energy': 'fm'}, inplace=True)
one.rename(columns={'Formation energy': 'fm'}, inplace=True)

# MoS2 exchange - dp plot       
plt.figure(figsize=(8, 2.5))
plt.scatter(one_sorted['MoS2 exchange'], one_sorted['Group'], marker='o', s=30)
plt.ylim(-0.25, len(custom_order) - 0.75)
for i, category in enumerate(custom_order):
    category_data = one_sorted[one_sorted['Group'] == category]['MoS2 exchange']
    max_val = category_data.max()
    min_val = category_data.min()
    plt.text(max_val, i, f'{max_val:.4f}', verticalalignment='top', fontsize=8, color='blue')
    plt.text(min_val, i, f'{min_val:.4f}', verticalalignment='top', fontsize=8, color='red')
plt.title('MoS2 exchange - dp')
plt.xlabel('MoS2 exchange')
plt.show()