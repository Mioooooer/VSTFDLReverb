import librosa
import numpy as np
y, sr = librosa.load("modified.wav",sr = 48000, mono = True)
#table = 'f,'.join([str(i) for i in y])
with open("modified.txt", "w") as fp:
    for i in range(y.size):
        if i%100 == 0:
            fp.writelines('\n'+str(y[i])+'f,')
        else:
            fp.writelines(str(y[i])+'f,')
