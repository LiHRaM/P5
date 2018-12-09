import sys
import helper
from nxt.bluesock import BlueSock

bs = BlueSock("00:16:53:12:C0:CA:00")
bs.debug = True
bs.connect()

size_bytes = 256

with open("sound.csv", "w") as f:
    f.write("AMP\n")
    while True:
        payload = [] # Received data
        received = 0  # Amount of data received in bytes
        while received < size_bytes:
            t = bs.sock.recv(256 - received)
            size = sys.getsizeof(t)
            received += size
            print("Received: ", received)
            payload.extend(t)
        f.write("{0},\n".format([ord(item) for item in payload]))