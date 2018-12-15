from __future__ import print_function
from receiver import NXTReceiver, unpack_u16
from matplotlib.pyplot import plot, show

rc = NXTReceiver()

data = ""
for i in range(0, 128):
    data += rc.recv(256)
length = data.__len__()
translated = [1023 - unpack_u16(data[i:i+2]) for i in range(0, length, 2)]
plot(translated)
show()