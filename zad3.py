import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Funkcje opisujące rozmaitości algebraiczne
def variety1(x, y):
    return x**2 + y**2

def variety2(x, y):
    return np.sqrt(x**2 + y**2)
# -sqrt 

def variety3(x, y):
    return x**2 - y**2

def variety4(x, y):
    return x*y

def variety5(x, y):
    z = np.zeros_like(x)
    z[(x == 0) | (y == 0)] = 0
    return z

# Tworzenie siatki punktów w przedziale [-5, 5]
x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
x, y = np.meshgrid(x, y)

# Wykresy rozmaitości algebraicznych
fig = plt.figure(figsize=(12, 10))

# Rozmaitość 1: V(z - x^2 - y^2)
ax1 = fig.add_subplot(221, projection='3d')
ax1.plot_surface(x, y, variety1(x, y), cmap='viridis')
ax1.set_title('V(z - x^2 - y^2)')

# Rozmaitość 2: V(z^2 - x^2 - y^2)
ax2 = fig.add_subplot(222, projection='3d')
ax2.plot_surface(x, y, variety2(x, y), cmap='plasma')
ax2.set_title('V(z^2 - x^2 - y^2)')

# Rozmaitość 3: V(z - x^2 + y^2)
ax3 = fig.add_subplot(223, projection='3d')
ax3.plot_surface(x, y, variety3(x, y), cmap='magma')
ax3.set_title('V(z - x^2 + y^2)')

# Rozmaitość 4: V(xz, yz)
ax4 = fig.add_subplot(224, projection='3d')
#ax4.plot_surface(x, y, variety4(x, y), cmap='viridis')
ax4.plot_surface(x, y, variety4(x, y), cmap='viridis')
ax4.set_title('V(xz, yz)')

plt.show()
