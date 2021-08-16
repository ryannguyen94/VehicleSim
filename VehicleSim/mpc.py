import numpy as np

dt = 0.01
a = 0.99
v = 5
w = 3.449

A = np.array([[1, dt, 0, 0, 0, 0],
              [0, 1, 0, 0, 0, 0],
              [0, 0, 1, dt, 0, 0],
              [0, 0, 0, 0, v, 0],
              [0, 0, 0, 0, 1, dt],
              [0, 0, 0, 0, 0, a]])

B = np.array([[0], [0], [0], [0], [0], [v * (1 - a) / w]])
C = np.array([[0, 0, 1, 0, 0, 0]])
Q = np.array([[10]])
R = np.array([[0.5]])

Np = 10
Nc = 4

CA = C @ A
F = np.array(CA)
for i in range(Np-1):
    CA = CA @ A
    F = np.append(F, CA, 0)

CA = C
phi = np.zeros((Np, Nc))

for i in range(Np):
    for j in range(Nc):
        CAB = CA @ B
        if (i + j + 1) <= phi.shape[0] and (j + 1) <= phi.shape[1]:
            phi[i+j, j] = CAB[0, 0]
        else:
            break
    CA = CA @ A

R_bar = 0.5 * np.eye(Nc)
Rs = np.ones((Np, 1))
x = np.transpose(np.array([[0, 10, 0, 0, 0, 0]]))
delta_u = np.linalg.inv(phi.transpose() @ phi + R_bar) @ phi.transpose() @ (Rs - F @ x)
print(F)
print(phi)
print(delta_u)