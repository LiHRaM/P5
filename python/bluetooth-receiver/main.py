import sys
from nxt.bluesock import BlueSock

sock = BlueSock("00:16:53:12:C0:CA:00")
sock.debug = True
sock.connect()

size_bytes = 256
f = open("data.txt", "w")

for i in range(0, 128):
    t = sock.sock.recv(size_bytes)
    t_s = sys.getsizeof(t)

    if t_s < 128:
        continue
    print(t_s)

    # for j in range(0, 128):
    #     f.write(t[j])
    # f.write("\n")
print("Done")

