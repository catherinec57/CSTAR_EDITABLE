# python script that performs an FFT on an input audio signal
import numpy as np
import matplotlib.pyplot as plt

FREQUENCY = 440
PHASE = 0
AMPLITUDE = 1
SAMPLE_RATE = 10000
DURATION = 1

# generate a generic input signal based on frequency, phase and amplitude parameters
def generate_signal(frequency, phase, amplitude, sample_rate, duration):
    # generate a time vector
    time = np.linspace(0, duration, sample_rate * duration)
    # generate a signal vector
    signal = amplitude * np.sin(2 * np.pi * frequency * time + phase)
    return signal

# perform an FFT on the signal
def perform_fft(signal, sample_rate):
    # perform the FFT
    fft = np.fft.fft(signal)
    # calculate the frequency bins
    frequency_bins = np.fft.fftfreq(len(signal), 1 / sample_rate)
    return fft, frequency_bins

# generate a signal
signal = generate_signal(FREQUENCY, PHASE, AMPLITUDE, SAMPLE_RATE, DURATION)
# take the FFT of the signal
fft, frequency_bins = perform_fft(signal, SAMPLE_RATE)

# plot both the input singal and the FFT on separate plots
plt.figure(1)
plt.subplot(211)
plt.plot(signal)
plt.title('Input Signal')
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.subplot(212)
# print(frequency_bins)
plt.plot(frequency_bins, fft)
plt.title('FFT')
plt.xlabel('Frequency')
plt.ylabel('Amplitude')
# adjust the x axis to only show the positive frequencies and only up to 10kHz
plt.xlim(0, 1000)
plt.show()

