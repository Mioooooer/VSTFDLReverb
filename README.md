# FDLReverb
A VST3 Plugin convolutional reverb.
It's basicly a simplified convolutional reverb which contains IR data itself.
The IR is converted directly from .wav file to float by python scripts.

TODO:
1. can't work now....
2. There may be some problems in the STFT algorithm, and it leads to audio click when buffer size is not a multiple of shift number.
   Probably because of the 'adding zero' code in STFT algorithm or something wrong in the 'overlap', 'shift' code or maybe any other place.
3. Don't know if there's already perfect reconstruction in code or not. If not, should upgrade it.
4. Up or down sampling function and drag to substitude IR function.