from __future__ import print_function
from nxt.bluesock import BlueSock
from struct import unpack

bs = BlueSock("00:16:53:12:C0:CA:00")
bs.debug = True
bs.connect()
sock = bs.sock

for i in range(0, 2):
    for j in range(0, 128):
        try:
            t = sock.recv(2)
            (val,) = unpack("H", t)
            print(val, end=",")
        except Exception:
            pass