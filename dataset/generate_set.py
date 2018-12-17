from __future__ import print_function
from receiver import NXTReceiver, unpack_u16
from datetime import datetime

rc = NXTReceiver()

def get_line(data):
    return str(datetime.now()) + "," + ",".join([str(1023 - unpack_u16(data[i:i+2])) for i in range(0, data.__len__(), 2)]) + "\n"

with open("cries.log", "w") as f:
    while True:
        time = unicode(datetime.now())
        data = get_line(rc.recv(256))
        f.write(data)
