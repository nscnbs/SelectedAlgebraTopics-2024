import numpy as np
import matplotlib.pyplot as plt

theta = np.linspace(-np.pi, np.pi, 1000)
r = np.sin(2*theta)
x = r * np.cos(theta)
y = r * np.sin(theta)

plt.figure(figsize=(6, 6))
plt.plot(x, y, color='red', label='Krzywa czterolistna: r(θ) = sin(2θ)')
plt.title('Wykres krzywej czterolistnej')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True)
plt.legend()
plt.axis('equal')
plt.show()
