import sys
import ctypes
import signal

valid_address = []
invalid_address = []

def segfault_handler(signum, frame):
    raise MemoryError("Segmentation Fault")

signal.signal(signal.SIGSEGV, segfault_handler)

start_addr = 0x400000
end_addr = 0x401000
step = 0x10

for addr in range(start_addr, end_addr, step):
    try:
        ptr = ctypes.POINTER(ctypes.c_int).from_address(addr)
        _ = ptr.contents.value
        valid_address.append(hex(addr))
    except (MemoryError, ValueError):
        invalid_address.append(hex(addr))

print("Valid addresses: ", valid_address)
print("Invalid addresses: ", invalid_address)
