#!/usr/bin/env python3

import ctypes
import os
import sys

libc = ctypes.CDLL("libc.so.6")

PTRACE_ATTACH = 16
PTRACE_DETACH = 17

if len(sys.argv) != 4:
    print("Usage: python3 mem_edit.py <pid> <search> <replace>")
    sys.exit(1)

pid = int(sys.argv[1])
search = sys.argv[2].encode()
replace = sys.argv[3].encode()

if len(search) != len(replace):
    print("Search and replace must be same length")
    sys.exit(1)

maps_path = f"/proc/{pid}/maps"
mem_path = f"/proc/{pid}/mem"

print("[*] Attaching to process")

if libc.ptrace(PTRACE_ATTACH, pid, None, None) != 0:
    print("[-] ptrace attach failed")
    sys.exit(1)

os.waitpid(pid, 0)

with open(maps_path, "r") as maps:
    for line in maps:

        if "[heap]" not in line:
            continue

        addr = line.split()[0]
        start, end = [int(x, 16) for x in addr.split("-")]

        print(f"[*] Heap region {hex(start)} - {hex(end)}")

        with open(mem_path, "rb+") as mem:

            mem.seek(start)
            heap = mem.read(end - start)

            pos = heap.find(search)

            if pos == -1:
                print("[-] String not found")
                break

            write_addr = start + pos
            print(f"[*] Found at {hex(write_addr)}")

            mem.seek(write_addr)
            mem.write(replace)

            print("[+] Memory overwritten")

        break

print("[*] Detaching")

libc.ptrace(PTRACE_DETACH, pid, None, None)
