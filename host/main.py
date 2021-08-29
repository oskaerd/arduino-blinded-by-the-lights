from audiostream.audiostream import AudioStream


#todo integrate pyaudio fork to work in loopback mode
#todo cleanup on exit

RECORD_SECONDS = 210
WAVE_OUTPUT_FILENAME = 'tmp.wav'

stream = AudioStream()
stream.record(RECORD_SECONDS, WAVE_OUTPUT_FILENAME)


