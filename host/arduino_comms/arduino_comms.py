import serial
from serial.tools import list_ports


def list_devices():
    comdevices = list(list_ports.comports())
    for com in comdevices:
        print(com)
    return comdevices


class LedDriver:
    def __init__(self, com, baudrate=115200):
        # todo close on exit
        self.com = serial.Serial(port=com, baudrate=baudrate)

    def send(self, amplitude):
        tmp = bytes(amplitude)
        self.com.write(tmp)

    def receive(self):
        #received = self.arduino.uart.readline().decode('utf-8')
        received = self.com.read(1)
        print(received)
