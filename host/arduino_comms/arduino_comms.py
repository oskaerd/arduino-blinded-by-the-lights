import serial
from serial.tools import list_ports


def list_devices():
    comdevices = list(list_ports.comports())
    for com in comdevices:
        print(com)
    return comdevices


class ArduinoSerial:
    def __init__(self, com, baudrate):
        #todo close on exit
        self.uart = serial.Serial(port=com, baudrate=baudrate)


class LedDriver:
    def __init__(self, com, baudrate=115200):
        self.arduino = ArduinoSerial(com, baudrate)

    def send(self, amplitude):
        tmp = bytes(amplitude)
        self.arduino.uart.write(tmp)

    def receive(self):
        #received = self.arduino.uart.readline().decode('utf-8')
        received = self.arduino.uart.read(1)
        print(received)
