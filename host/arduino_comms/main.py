from numpy.core.function_base import linspace
from arduino_comms import LedDriver

ld = LedDriver(com='COM7')

while True:
    try:
        ld.receive(testing=True)
    except KeyboardInterrupt:
        ld.com.close()
        break
