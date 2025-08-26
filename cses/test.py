#!/usr/bin/env python3

import subprocess as sp
import sys, glob
from pathlib import Path

exePath = sys.argv[1]
testDir = sys.argv[2]

print("Running tests for {exePath}".format(exePath=exePath), end="")

MAX_LEN = 30

passed = 0
errors = []
for file in glob.glob("{testDir}/*.in".format(testDir=testDir)):
    p = sp.Popen([exePath], stdin=open(file), stdout=sp.PIPE, text=True)
    got, error = p.communicate()
    if error:
        print(error)
        continue
    
    got = got.strip()
    expect = Path(file.replace(".in", ".out")).read_text().strip()
    print(".", end="")
    if expect != got:
        expect_out, got_out = expect, got
        if len(expect) > MAX_LEN:
            expect_out = expect[:MAX_LEN] + "..."
        if len(got) > MAX_LEN:
            got_out = got[:MAX_LEN] + "..."

        errors.append("{file}\n>> expecting\n{expect}\n>> got\n{got}".format(file=file, expect=expect_out, got=got_out))
        continue
    
    passed+=1

if len(errors) > 0:
    print("\n")
    print("Got {errorCount} error/s:".format(errorCount=len(errors)))
    for error in errors:
        print(error)
else:
    print("done.")
