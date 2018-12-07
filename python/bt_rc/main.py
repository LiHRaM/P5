import sys
from nxt.bluesock import BlueSock

bs = BlueSock("00:16:53:12:C0:CA:00")
bs.debug = True
bs.connect()

size_bytes = 2
t_list = []
f = open("data.txt", "w")


for i in range(0, 256):
    t = bs.sock.recv(size_bytes)
    t_list.append([c for c in t])
f.write(" ".join([[str(d) for d in c] for c in t_list]))
f.write("\n")
f.close()
print("done")

