import pyaudio
import wave
import librosa.display
from datetime import datetime
import matplotlib.pyplot as plt
import numpy as np

CHUNK = 2048
FORMAT = pyaudio.paInt16
CHANNELS = 2
RATE = 44100
RAW_DATA = False


def tmp_wav_fft(filename):
    from scipy.io import wavfile as wav
    from scipy.fftpack import fft
    rate, data = wav.read(filename)
    fft_out = fft(data)
    plt.plot(data, np.abs(fft_out))
    plt.show()


#todo implement switching of the device
class AudioStream:
    def __init__(self, channels=CHANNELS, rate=RATE, chunk=CHUNK, non_blocking=True):
        self.audio = pyaudio.PyAudio()
        self.then = datetime.now()
        self.frames = []
        self.plot_data = []
        self.plot_left_channel = []
        self.plot_right_channel = []
        self.streaming = False

        # search for loopback device
        devices = [self.audio.get_device_info_by_index(i) for i in range(self.audio.get_device_count())]
        # todo check for that
        self.input_dev_idx = 0xff
        for d in devices:
            if 'voicemeeter aux output' in d['name'].lower():
                self.input_dev_idx = d['index']
                break

        self.stream = self.audio.open(format=pyaudio.paInt16,
                                      channels=channels,
                                      rate=rate,
                                      input=True,
                                      input_device_index=self.input_dev_idx,
                                      frames_per_buffer=chunk)
                                      # stream_callback=self.stream_callback)

    def __del__(self):
        print('* closing stream')
        self.stream.close()

    def list_devices(self, key=None, value=None):
        devices = [self.audio.get_device_info_by_index(i) for i in range(self.audio.get_device_count())]
        for d in devices:
            if key is None:
                print(d)
            else:
                if value in d[key]:
                    print(d)

    # TODO: add the one with callback
    # todo implement actual streaming start/stop and remove seconds
    def start_stream(self):
        print('* starting stream')
        self.streaming = True
        self.then = datetime.now()
        self.stream.start_stream()

    def stop_stream(self):
        self.streaming = False
        now = datetime.now()
        print(f'end: {now.second * 1000000 + now.microsecond - (self.then.second * 1000000 + self.then.microsecond)}')

    def stream_callback(self, in_data, frame_count, time_info, status):
        #now = datetime.now()
        #print(f'cb: {now.second * 1000000 + now.microsecond - (self.then.second * 1000000 + self.then.microsecond)}')
        #self.then = datetime.now()
        self.plot_data = self.plot_data + list(np.frombuffer(in_data, np.int16))

        if len(self.plot_data) >= 2 * 3 * 44100:
            print('complete')
            self.streaming = False
            return in_data, pyaudio.paComplete
        else:
            return in_data, pyaudio.paContinue

    def record(self, seconds, output_filename):
        if seconds <= 0:
            return

        print("* recording")
        self.frames = []

        for s in range(1):
            self.frames = []
            for i in range(0, int(RATE / CHUNK * 3)):
                data = self.stream.read(CHUNK)
                self.frames.append(data)

            print('* done recording')

            # todo make it working with raw data instead of this scuffed POS
            # time_series, sample_rate = librosa.load(output_filename)
            # stft = np.abs(librosa.stft(time_series, hop_length=512, n_fft=2048))

            if RAW_DATA:
                with open('dump.raw', 'w') as rawfile:
                    rawdata = self.frames
                    rawdata = [str(r) + '\n' for r in rawdata]
                    rawfile.writelines(rawdata)

            then = datetime.now()
            wf = wave.open(f'{output_filename[:-4]}_{s}.wav', 'wb')
            wf.setnchannels(CHANNELS)
            wf.setsampwidth(self.audio.get_sample_size(FORMAT))
            wf.setframerate(RATE)
            wf.writeframes(b''.join(self.frames))
            #tmp_wav_fft(f'{output_filename[:-4]}_{s}.wav')
            wf.close()
            now = datetime.now()
            print(now.second-then.second)
            print(now.microsecond-then.microsecond)
        self.stream.stop_stream()
