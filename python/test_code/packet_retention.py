import sys
from nxt.bluesock import BlueSock

bs = BlueSock("00:16:53:12:C0:CA:00")
bs.debug = True
bs.connect()

size_bytes = 4
iterations = 128
t_list = []
received = 0


for i in range(0, iterations):
    try:
        t = bs.sock.recv(size_bytes)
        received += 1
        if (t[0] == 999):
            break
        t_list.extend([c for c in t])
    except Exception as e:
        print(e)
        break
print("Communication finished.")
print("Packets expected: ", iterations, "Packets received: ", received)

