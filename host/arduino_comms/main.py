from numpy.core.function_base import linspace
from arduino_comms import LedDriver

ld = LedDriver(com='COM7')

while True:
    try:
        ld.receive(testing=True)
    except KeyboardInterrupt:
        ld.com.close()
        break


# import matplotlib.pyplot as plt
# import numpy as np
# import math

# samples = 100
# max = 245

# x = np.linspace(0, 2*math.pi, samples)
# y = [int(max*(math.sin(i) + 1)/2 + 0.5) for i in x]


# s='const uint8_t sinus_vals[] = {\n'
# tmp = []
# for i in range(0, len(y), 5):
#     tmp.append(y[i:i+5])

# for five in tmp:
#     s = f'{s}    {str(five)[1:-1]},\n'
# s = f'{s}}};'

# print(s)

# # for i in range(1024):
# #     print((50 + int((i*100)/1023)) % 100)

# for i in range(1024):
#     print((100 + int((i*150)/1023)))
