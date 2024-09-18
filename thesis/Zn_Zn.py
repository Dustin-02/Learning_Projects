import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

one = pd.read_csv('E:/05_Reseach/05_doan/Analysis/Zn_Zn_1603.csv')
columns_to_delete = one.columns[10:14]
one.drop(columns=columns_to_delete, inplace=True)

one.head()
one.rename(columns={one.columns[0]: "name"},inplace=True)

x_elements = ['O_top', 'Zn_top', 'S_top', 'Mo', 'S_bottom', 'Zn_bot', 'O_bot']

# Define names for the clusters
clusters = ['temp', 'O-Mo-O', 'O-Mo-Zn_3', 'Zn-Mo-O_1', 'Zn-Mo-Zn_2']

# Create a color map for clusters
colors = plt.cm.tab10.colors[:len(clusters)]  # Use a colormap with the same number of distinct colors as clusters

# Prepare data for plotting
data = []
for cluster in clusters:
    row = one[one['name'] == cluster]
    values = [row[element].iloc[0] for element in x_elements]
    data.append(values)

# Plotting the clustered bar chart
bar_width = 0.15
index = np.arange(len(x_elements))
plt.figure(figsize=(10, 6))
for i in range(len(clusters)):
    plt.bar(index + i * bar_width, data[i], bar_width, label=clusters[i], color=colors[i])

# Adding labels and title
plt.xlabel('Elements')
plt.ylabel('Values')
plt.title('Clustered Bar Chart of Element Values')

# Adding legend
plt.legend()

# Adjusting x-axis ticks
plt.xticks(index + (len(clusters) - 1) * bar_width / 2, x_elements, rotation=45)

# Show plot
plt.grid(True)
plt.tight_layout()
plt.show()