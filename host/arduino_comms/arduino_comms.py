import serial
from serial.tools import list_ports


def list_devices():
    comdevices = list(list_ports.comports())
    for com in comdevices:
        print(com)
    return comdevices

# todo add timestamps
class LedDriver:
    def __init__(self, com, baudrate=115200):
        # todo close on exit
        self.com = serial.Serial(port=com, baudrate=baudrate)

    def send(self, red, green, blue):
        rgb = [red, green, blue, 0]
        rgb = bytearray(rgb)
        print(rgb)
        self.com.write(rgb)

    def receive(self, testing=False):
        if testing:
            received = self.com.readline().decode('utf-8')
        else:
            received = self.com.read(1)
        print(received)
