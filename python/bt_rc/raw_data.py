import sys
from nxt.bluesock import BlueSock

bs = BlueSock("00:16:53:12:C0:CA:00")
bs.debug = True
bs.connect()

size_bytes = 256
while True:
    print(str(ord(bs.sock.recv(size_bytes)[0])))

