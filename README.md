# Basic-Linux-Security

Several Basic Ctf binaries intended to show how the basic Linux/gcc
security protections (such as NX, ASLR, PIE, Relro, and stack canaries) 
may be bypassed.

To build the binaries, run:
```
./build.sh
```
Try not to look at the source code initially. The goal in every case is
to pop a shell.

Each level contains the same two binaries with increasing layers of 
security. The sol folder contains my solution, exploit.py, (if I have solved it)
along with rough working notes. The working notes are also executable
tutorials, to execute these or the solutions please install pwntools
(you will probably need it anyway).
```
pip install pwn
```
The script aslr.sh should be used to turn off aslr for the first 2
levels, and back on for the others.

```
./aslr.sh on/off
```

allsec contains binaries with all basic protections enabled. As the
simple buffer overflow appears to be impossible here, I have included
four more complex, exploitable binaries. The best stuff is in allsec.

(more to come)
