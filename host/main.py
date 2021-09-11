from audiostream.audiostream import AudioStream
from arduino_comms.arduino_comms import LedDriver, list_devices


#todo integrate pyaudio fork to work in loopback mode
#todo cleanup on exit

RECORD_SECONDS = 10
WAVE_OUTPUT_FILENAME = 'tmp.wav'

stream = AudioStream()
stream.start_stream(stream_time=3)

while stream.streaming:
    pass

#stream.record(3, WAVE_OUTPUT_FILENAME)
#
# while stream.streaming:
#     pass
#
# stream.stop_stream()
#
plot_cnt=0

for f in stream.plot_data:
    left = []
    right = []
    cnt = 0
    print(f)
    for i in range(len(f)-4):
        if cnt % 2 == 0:
            left.append(f[i+2] - f[i])
        else:
            right.append(f[i+2] - f[i])
        cnt+=1

    import numpy as np
    import matplotlib.pyplot as plt
    from scipy.fftpack import fft

    #x = np.linspace(0, len(left)/44100, num=int(len(left)))
    #x = np.linspace(0, len(left) / 44100, len(left))
    left = np.abs(np.fft.rfft(left))
    right = np.abs(np.fft.rfft(right))
    x = list(range(int(len(left))))

    fig, ax = plt.subplots(2)
    ax[0].clear()
    ax[1].clear()
    ax[0].plot(x, left)
    ax[1].plot(x, right)

    ax[0].title.set_text(f'{plot_cnt / 4} s')
    plt.subplots_adjust(bottom=0.20)
    plt.show()
    plot_cnt += 1

# com = list_devices()[0].name.split(' ')[0]
# led = LedDriver(com)

# while True:
#     # todo remove random
#     from random import randint
#     led.send([randint(0, 60), randint(0, 60)])
#     led.receive()

