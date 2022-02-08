#!/bin/sh

function build() {

    BASE=`basename $1 .c`

    # fully vulnerable: executable stack, no canary no relocations, no PIE, no aslr
    gcc -w -o "level1/$BASE/vuln" $1 -fno-stack-protector -Wl,-z,norelro -no-pie -z execstack

    # non-executable stack
    gcc -w -o "level2/$BASE/vuln" $1 -fno-stack-protector -Wl,-z,norelro -no-pie

    # non-executable stack, address space layout randomisation (ASLR) 
    gcc -w -o "level3/$BASE/vuln" $1 -fno-stack-protector -Wl,-z,norelro -no-pie
    
    # non-executable stack, ASLR, PIE
    gcc -w -o "level4/$BASE/vuln" $1 -fno-stack-protector -Wl,-z,norelro
    
    # non-executable stack, ASLR, PIE, relocations
    gcc -w -o "level5/$BASE/vuln" $1 -fno-stack-protector
    
    # all protection, including canary: I can't hack this (yet)
    gcc -w -o "allsec/$BASE/vuln" $1 
}

build easy.c
build normal.c

# extra allsec binaries to show its possible (no need to disable warnings!)
gcc -o "allsec/server/vulnserv" server.c
gcc -o "allsec/forker/vulnfork" forker.c

