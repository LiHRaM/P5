from nxt.bluesock import BlueSock
from struct import unpack
from sys import getsizeof

class NXTReceiver(object):
    "Slave to the NXT"
    bs = None
    sock = None

    def __init__(self):
        self.bs = BlueSock("00:16:53:12:C0:CA:00")
        self.bs.debug = True
        self.bs.connect()
        self.sock = self.bs.sock

    def recv(self, len):
        "Iteratively waits for input until the desired size is achieved"
        received = 0
        payload = ""
        while received < len:
            t = self.sock.recv(len - received)
            received += t.__len__()
            payload += t
        return payload

    def send(self, isCrying):
        if isCrying:
            self.sock.send("1")


def unpack_u16(vector):
    if vector.__len__() == 2:
        (val,) = unpack("H", vector)
        return val
    else:
        return None

def get_line(data):
    return ",".join([str(unpack_u16(data[i:i+2])) for i in range(0, data.__len__(), 2)]) + "\n"