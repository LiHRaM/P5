import sys
import struct
import time
from nxt.bluesock import BlueSock

bs = BlueSock("00:16:53:12:C0:CA:00")
bs.debug = True
bs.connect()

size_bytes = 256
received = 0
buffer = []

while received < 256:
    t = bs.sock.recv(size_bytes)
    size = sys.getsizeof(t)
    received += size
    print("Received: ", received)
    buffer.extend(t)
buffer = "".join(buffer)
sound_points = []
for i in range(0, 256, 2):
    try:
        sound_points.extend(struct.unpack("H", buffer[i:i+2]))
    except Exception as e:
        print("Packet missed", e, "Index", i)
print("Points: ", sound_points)
print("Communication finished.")

