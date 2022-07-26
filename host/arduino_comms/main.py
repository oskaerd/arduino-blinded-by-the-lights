from numpy.core.function_base import linspace
from arduino_comms import LedDriver
from random import randint
import time

ld = LedDriver(com='COM7')

while True:
    try:
        ld.send(red=randint(50, 200), green=10, blue=randint(100, 200))
        time.sleep(0.150)
        ld.receive(testing=True)
    except KeyboardInterrupt:
        ld.com.close()
        break
