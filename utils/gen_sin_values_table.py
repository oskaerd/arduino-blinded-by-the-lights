import matplotlib.pyplot as plt
import numpy as np
import math
import sys

# todo: make it copy string to .ino file

if len(sys.argv) >= 2:
    samples = int(sys.argv[1])
    max     = int(sys.argv[2])
else:
    samples = 100
    max     = 245

x = np.linspace(0, 2*math.pi, samples)
y = [int(max*(math.sin(i) + 1)/2 + 0.5) for i in x]


s='const uint8_t sinus_vals[] = {\n'
tmp = []
for i in range(0, len(y), 5):
    tmp.append(y[i:i+5])

for five in tmp:
    s = f'{s}    {str(five)[1:-1]},\n'
s = f'{s}}};'

print(s)
