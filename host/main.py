from audiostream.audiostream import AudioStream
from arduino_comms.arduino_comms import LedDriver, list_devices


#todo integrate pyaudio fork to work in loopback mode
#todo cleanup on exit

RECORD_SECONDS = 210
WAVE_OUTPUT_FILENAME = 'tmp.wav'

#stream = AudioStream()
#stream.record(RECORD_SECONDS, WAVE_OUTPUT_FILENAME)

com = list_devices()[0].name.split(' ')[0]
led = LedDriver(com)

# while True:
#     # todo remove random
#     from random import randint
#     led.send([randint(0, 60), randint(0, 60)])
#     led.receive()

