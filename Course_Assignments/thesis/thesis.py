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

# mag - dp plot
plt.figure(figsize=(8, 2.5))
plt.scatter(one_sorted['mag'], one_sorted['Group'], marker='o', s=30)
plt.ylim(-0.25, len(custom_order) - 0.75)
for i, category in enumerate(custom_order):
    category_data = one_sorted[one_sorted['Group'] == category]['mag']
    max_val = category_data.max()
    min_val = category_data.min()
    plt.text(max_val, i, f'{max_val:.4f}', verticalalignment='top', fontsize=8, color='blue')
    plt.text(min_val, i, f'{min_val:.4f}', verticalalignment='top', fontsize=8, color='red')
plt.title('mag - dp')
plt.show()

# fm - dp plot
plt.figure(figsize=(8, 2.5))
plt.scatter(one_sorted['fm'], one_sorted['Group'], marker='o', s=30)
plt.ylim(-0.25, len(custom_order) - 0.75)
for i, category in enumerate(custom_order):
    category_data = one_sorted[one_sorted['Group'] == category]['fm']
    max_val = category_data.max()
    min_val = category_data.min()
    plt.text(max_val, i, f'Max: {max_val:.6f}', verticalalignment='top', fontsize=8, color='blue')
    plt.text(min_val, i, f'Min: {min_val:.6f}', verticalalignment='top', fontsize=8, color='red')
plt.title('fm - dp')
plt.show()

# MoS2 exchange - mag plot
plt.scatter(one['MoS2 exchange'], one['mag'], marker='o', s=30)
plt.xlabel('MoS2 exchange (eV)')
plt.ylabel('mag')
plt.title('MoS2 exchange - mag')
plt.show()

# MoS2 exchange - fm
new_group = ['O-Mo-O','O-Mo-O_1','O-Mo-O_2','O-Mo-O_3','O-Mo-Zn','O-Mo-Zn_1',
         'O-Mo-Zn_2','O-Mo-Zn_3','Zn-Mo-O','Zn-Mo-O_1','Zn-Mo-O_2',
         'Zn-Mo-O_3','Zn-Mo-Zn','Zn-Mo-Zn_1','Zn-Mo-Zn_2','Zn-Mo-Zn_3']
one_new = one
one_new['Group'] = new_group

color_sequence = ['blue', 'green', 'red', 'orange']  # Define your color sequence
marker_size = 30

# Iterate over each group of four points and plot them with the corresponding color
for i in range(0, len(one_new), 4):
    group_data = one_new.iloc[i:i+4]
    group_color = color_sequence[i//4]  # Pick color from the sequence based on group index
    plt.scatter(group_data['MoS2 exchange'], group_data['fm'], marker='o', s=marker_size, color=group_color)

plt.xlabel('MoS2 exchange (eV)')
plt.ylabel('fm (eV)')
plt.title('MoS2 exchange - fm')
plt.show()

# mag - fm
color_sequence = ['blue', 'green', 'red', 'orange']  # Define your color sequence
marker_size = 30

# Iterate over each group of four points and plot them with the corresponding color
for i in range(0, len(one_new), 4):
    group_data = one_new.iloc[i:i+4]
    group_color = color_sequence[i//4]  # Pick color from the sequence based on group index
    plt.scatter(group_data['mag'], group_data['fm'], marker='o', s=marker_size, color=group_color)
plt.xlabel('mag')
plt.ylabel('fm (ev)')
plt.title('mag - fm')
plt.show()
