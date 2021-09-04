from audiostream.audiostream import AudioStream
from arduino_comms.arduino_comms import LedDriver, list_devices


#todo integrate pyaudio fork to work in loopback mode
#todo cleanup on exit

RECORD_SECONDS = 10
WAVE_OUTPUT_FILENAME = 'tmp.wav'

stream = AudioStream()
stream.record(3, WAVE_OUTPUT_FILENAME)
# stream.start_stream()
#
# while stream.streaming:
#     pass
#
# stream.stop_stream()
#
# left = []
# right = []
# cnt = 0
# for i in stream.plot_data:
#     if cnt % 2 == 0:
#         left.append(i)
#     else:
#         right.append(i)
#     cnt+=1
#
# import numpy as np
# import matplotlib.pyplot as plt
# x = np.linspace(0, len(left)/44100, num=int(len(left)))
#
# fig, ax = plt.subplots(2)
# ax[0].clear()
# ax[1].clear()
# ax[0].plot(x, left)
# ax[1].plot(x, right)
# plt.subplots_adjust(bottom=0.20)
# plt.show()

# com = list_devices()[0].name.split(' ')[0]
# led = LedDriver(com)

# while True:
#     # todo remove random
#     from random import randint
#     led.send([randint(0, 60), randint(0, 60)])
#     led.receive()

