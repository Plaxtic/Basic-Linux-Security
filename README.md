# Basic-Linux-Security

Several Basic Ctf Binarys intended to show how the basic Linux/gcc
security protections (such as NX, ASLR, PIE, Relro, and stack canaries) 
may be bypassed.

Each level contains the same two binaries with increasing layers of 
security. The sol folder contains my solution (if I have solved it)
along with rough working notes.
The script aslr.sh should be used to turn off aslr for the first 2
levels, and back on for the others 

```
    ./aslr.sh on/off
```

allsec contains binaries with all basic protections enabled, as the
simple buffer overflow appears to be impossible here, I have included
three more complex, exploitable binaries. 

(more to come)
