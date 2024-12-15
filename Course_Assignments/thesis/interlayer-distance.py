import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

# Data for (a) | O-O
interlayer_distance_a = np.array([2, 2.4, 2.8, 3.2, 3.6])
E_f_a = np.array([6.27, 1.28, -2.27, -2.91, -2.63])

# Data for (b) | Zn-O
interlayer_distance_b = np.array([2, 2.4, 2.8, 3.2, 3.6])
E_f_b = np.array([10.42, -0.69, -2.40, -2.07, -1.29])

# Data for (c) | Zn - Zn
interlayer_distance_c = np.array([2, 2.4, 2.8, 3.2, 3.6])
E_f_c = np.array([12.95, -1.99, -3.82, -3.56, -3.04])

# Interpolation functions
interp_func_a = interp1d(np.log(interlayer_distance_a), E_f_a, kind='cubic')
interp_func_b = interp1d(np.log(interlayer_distance_b), E_f_b, kind='cubic')
interp_func_c = interp1d(np.log(interlayer_distance_c), E_f_c, kind='cubic')

# Generate more points for smooth curves
x_new = np.linspace(interlayer_distance_a.min(), interlayer_distance_a.max(), 500)
y_new_a = interp_func_a(np.log(x_new))
y_new_b = interp_func_b(np.log(x_new))
y_new_c = interp_func_c(np.log(x_new))

# Find exact minimum values
min_index_a = np.argmin(y_new_a)
min_index_b = np.argmin(y_new_b)
min_index_c = np.argmin(y_new_c)

min_x_a = x_new[min_index_a]
min_y_a = y_new_a[min_index_a]

min_x_b = x_new[min_index_b]
min_y_b = y_new_b[min_index_b]

min_x_c = x_new[min_index_c]
min_y_c = y_new_c[min_index_c]

# Plotting
fig, axs = plt.subplots(1, 3, figsize=(18, 6), sharey=True)

# Plot (a)
axs[0].plot(interlayer_distance_a, E_f_a, 'o', markersize=8)
axs[0].plot(x_new, y_new_a, '-', linewidth=2.5)
axs[0].scatter(interlayer_distance_a, E_f_a, color='black', zorder=5)
axs[0].scatter(min_x_a, min_y_a, color='red', s=100, zorder=6)
axs[0].set_xlabel('Interlayer Distance (Å)', fontname='Times New Roman', fontsize=20)
axs[0].set_ylabel('E$_f$ (eV)', fontname='Times New Roman', fontsize=20)
axs[0].text(0.5, 0.95, '(a)', horizontalalignment='center', verticalalignment='top', transform=axs[0].transAxes, fontname='Times New Roman', fontsize=20)
axs[0].tick_params(axis='both', which='major', labelsize=14)

# Plot (b)
axs[1].plot(interlayer_distance_b, E_f_b, 'o', markersize=8)
axs[1].plot(x_new, y_new_b, '-', linewidth=2.5)
axs[1].scatter(interlayer_distance_b, E_f_b, color='black', zorder=5)
axs[1].scatter(min_x_b, min_y_b, color='red', s=100, zorder=6)
axs[1].set_xlabel('Interlayer Distance (Å)', fontname='Times New Roman', fontsize=20)
axs[1].text(0.5, 0.95, '(b)', horizontalalignment='center', verticalalignment='top', transform=axs[1].transAxes, fontname='Times New Roman', fontsize=20)
axs[1].tick_params(axis='both', which='major', labelsize=14)

# Plot (c)
axs[2].plot(interlayer_distance_c, E_f_c, 'o', markersize=8)
axs[2].plot(x_new, y_new_c, '-', linewidth=2.5)
axs[2].scatter(interlayer_distance_c, E_f_c, color='black', zorder=5)
axs[2].scatter(min_x_c, min_y_c, color='red', s=100, zorder=6)
axs[2].set_xlabel('Interlayer Distance (Å)', fontname='Times New Roman', fontsize=20)
axs[2].text(0.5, 0.95, '(c)', horizontalalignment='center', verticalalignment='top', transform=axs[2].transAxes, fontname='Times New Roman', fontsize=20)
axs[2].tick_params(axis='both', which='major', labelsize=14)

plt.tight_layout()
plt.show()
