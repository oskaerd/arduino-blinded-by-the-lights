import pyaudio
import wave
import librosa.display
from datetime import datetime
import matplotlib.pyplot as plt
import numpy as np

CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 2
RATE = 44100
RAW_DATA = False


#todo implement switching of the device
class AudioStream:
    def __init__(self, format=FORMAT, channels=CHANNELS, rate=RATE, chunk=CHUNK):
        self.audio = pyaudio.PyAudio()
        self.frames = []
        self.streaming = False

        # search for loopback device
        devices = [self.audio.get_device_info_by_index(i) for i in range(self.audio.get_device_count())]
        # todo check for that
        self.input_dev_idx = 0xff
        for d in devices:
            if 'voicemeeter aux output' in d['name'].lower():
                self.input_dev_idx = d['index']
                break

        self.stream = self.audio.open(format=format,
                                      channels=channels,
                                      rate=rate,
                                      input=True,
                                      input_device_index=self.input_dev_idx,
                                      frames_per_buffer=chunk)

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
    def start_stream(self, seconds):
        pass

    def stop_stream(self):
        self.streaming = False

    def record(self, seconds, output_filename):
        if seconds <= 0:
            return

        print("* recording")
        self.frames = []

        for i in range(0, int(RATE / CHUNK * seconds)):
            data = self.stream.read(CHUNK)
            self.frames.append(data)

        print('* done recording')
        self.stream.stop_stream()

        # todo make librosa working with raw data instead of this scuffed POS
        # time_series, sample_rate = librosa.load(output_filename)
        # stft = np.abs(librosa.stft(time_series, hop_length=512, n_fft=2048))

        if RAW_DATA:
            with open('dump.raw', 'w') as rawfile:
                rawdata = self.frames
                rawdata = [str(r) + '\n' for r in rawdata]
                rawfile.writelines(rawdata)

        then = datetime.now()
        wf = wave.open(output_filename, 'wb')
        wf.setnchannels(CHANNELS)
        wf.setsampwidth(self.audio.get_sample_size(FORMAT))
        wf.setframerate(RATE)
        wf.writeframes(b''.join(self.frames))
        wf.close()
        now = datetime.now()
        print(now.second-then.second)
        print(now.microsecond-then.microsecond)

