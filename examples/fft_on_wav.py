# generate a fft using numpy on a wav file and plot the result
import numpy as np
import wave
import matplotlib.pyplot as plt
import os

def perform_fft(signal, sample_rate):
    # perform the FFT
    fft = np.fft.fft(signal)
    # calculate the frequency bins
    frequency_bins = np.fft.fftfreq(len(signal), 1 / sample_rate)
    return fft, frequency_bins

files = os.listdir('./audio_samples')
# files = ['badconk2.wav', 'goodconk2.wav']
files_set = set(files)
#create subplots
fig, files_set = plt.subplots(len(files))

# Open wave file
#iterate through files in audio_samples
for i, file  in enumerate(files):
    wav_file = wave.open('./audio_samples/' + file, 'r')

    # Extract Raw Audio from Wav File
    signal = wav_file.readframes(-1)
    frame_rate = wav_file.getframerate()
    signal = np.frombuffer(signal, dtype='int16')

    fft_out, frequency_bins = perform_fft(signal, frame_rate)

    pane = files_set[i]
    #plot the fft
    pane.plot(frequency_bins, fft_out)

    #only show up to 20000Hz
    pane.set_xlim(0, 20000)
    pane.set_ylim(0, 30000000)
    pane.set_title(file)
    plt.xlabel('Frequency')
    plt.ylabel('Amplitude')

plt.subplots_adjust(left=0.1, right=0.9, bottom=0.1, top=0.9, hspace=0.5, wspace=0.5)
#show all the plots
plt.show()
