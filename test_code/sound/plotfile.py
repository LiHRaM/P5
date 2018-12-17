from matplotlib.pyplot import figure, title, plot, show
from soundfile import read

data, samplerate = read("sample.ogg")

figure(1)
title("Original file")
plot(data)
show()