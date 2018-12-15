import sys
from nxt.bluesock import BlueSock

bs = BlueSock("00:16:53:12:C0:CA:00")
bs.debug = True
bs.connect()

size_bytes = 256
while True:
    payload = [] # Received data
    print("Main loop")
    while sys.getsizeof(payload) < size_bytes:
        print("Awaiting...")
        t = bs.sock.recv(size_bytes)
        payload.extend(t)
        print("Payload: ", sys.getsizeof(payload))
    strbuf = "".join(payload)
    for i in range(0, size_bytes):
        print(strbuf[i])

