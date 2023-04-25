import numpy as np
import librosa
import soundfile
from scipy.interpolate import interp2d

cname = input('carrier name')
mname = input('modulator name')

# Load the carrier and modulator audio signals
carrier, sr_carrier = librosa.load(cname)
modulator, sr_modulator = librosa.load(mname)

# Ensure that the sampling rates of the two signals are the same
if sr_carrier != sr_modulator:
    modulator = librosa.resample(modulator, sr_modulator, sr_carrier)
    sr_modulator = sr_carrier

# Set the number of mel bands and hop length
n_bands = 16
hop_length = 512

# Compute the STFTs of the carrier and modulator signals
stft_carrier = librosa.stft(carrier, hop_length=hop_length)
stft_modulator = librosa.stft(modulator, hop_length=hop_length)

# Compute the magnitudes and phases of the STFTs
mag_carrier, phase_carrier = librosa.magphase(stft_carrier)
mag_modulator, phase_modulator = librosa.magphase(stft_modulator)

# Compute the mel spectrograms of the carrier and modulator signals
mel_carrier = librosa.feature.melspectrogram(carrier, sr=sr_carrier, n_fft=hop_length*2, hop_length=hop_length, n_mels=n_bands)
mel_modulator = librosa.feature.melspectrogram(modulator, sr=sr_modulator, n_fft=hop_length*2, hop_length=hop_length, n_mels=n_bands)

# Normalize the magnitudes of the modulator spectrogram
#mel_modulator -= mel_modulator.min()
mel_modulator /= mel_modulator.max()

# Upsample the modulator mel spectrogram to match the dimensions of the carrier STFT magnitudes
interp_func = interp2d(np.linspace(0, 1, mel_modulator.shape[1]), np.linspace(0, 1, mel_modulator.shape[0]), mel_modulator)
interp_freq = np.linspace(0, 1, mag_carrier.shape[0])
interp_time = np.linspace(0, 1, mel_modulator.shape[1])
mel_modulator = interp_func(interp_time, interp_freq)

# Apply the modulator magnitudes to the carrier phases
new_mag_carrier = mag_carrier * mel_modulator

# Combine the new magnitudes and original phases to obtain the modified STFT
new_stft_carrier = new_mag_carrier * phase_carrier

# Invert the STFT to obtain the modified audio signal
new_carrier = librosa.istft(new_stft_carrier, hop_length=hop_length)

# Write the modified audio signal to a file
soundfile.write(mname+'output.wav', new_carrier, sr_carrier)
