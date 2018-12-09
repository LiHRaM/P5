import struct
from nxt.bluesock import BlueSock

def extract_16_bytes_unsigned(string, i):
    '''
    Extracts two bytes and unpacks them, expecting an unsigned int
    Fails when there are no bytes left to unpack, or when there is only a single byte.
    '''
    try:
        res = struct.unpack("H", string[i:i+2])
        if res > 1023:
            res = struct.unpack("H", string[i-1:i+1])
        return res
    except Exception:
        print("Packet missed!", i)
        return ""