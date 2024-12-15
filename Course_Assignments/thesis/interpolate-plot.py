import numpy as np
from scipy.interpolate import interp1d
import matplotlib.pyplot as plt

# Dữ liệu đầu vào
x_data = np.array([0.8, 0.85, 0.9, 0.95, 1, 1.05])
y_data = np.array([-32.63, -55.73, -66.97, -70.79, -70.13, -66.85])

# Chuyển đổi y_data thành log(y_data)
log_y_data = np.log(-y_data)  # Dùng log của -y_data vì y_data là các giá trị âm

# Nội suy logarit
interp_log = interp1d(x_data, log_y_data, kind='cubic')

# Xác định khoảng giá trị của x để tìm y_min
x_range = np.linspace(min(x_data), max(x_data), 1000)
log_y_range = interp_log(x_range)

# Chuyển đổi ngược từ log(y) thành y
y_range = -np.exp(log_y_range)  # Dùng exp và nhân với -1 để chuyển đổi ngược

# Tìm giá trị y nhỏ nhất
min_y = np.min(y_range)
min_y_x = x_range[np.argmin(y_range)]

print("Giá trị y nhỏ nhất:", min_y)
print("Tại x =", min_y_x)

# Vẽ đồ thị để minh họa
plt.plot(x_data, y_data, 'o', label='Dữ liệu gốc')
plt.plot(x_range, y_range, '-', label='Nội suy log')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.title('Nội suy logarit')
plt.show()
