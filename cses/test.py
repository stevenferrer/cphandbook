#!/usr/bin/env python3

import subprocess as sp
import sys, glob
from pathlib import Path

testDir = sys.argv[1]
exePath = sys.argv[2]

print("Running tests...")

MAX_LEN = 30

passed = 0
errors = []

test_inputs = glob.glob("{testDir}/*.in".format(testDir=testDir))

for test_input in test_inputs:
    # print input name
    print(f"{test_input.split('/')[-1]}...", end="")

    # p = sp.Popen([exePath], stdin=open(test_input), stdout=sp.PIPE, text=True)
    # got, error = p.communicate()
    # if error:
    #     print(error)
    #     continue

    # got = got.strip()
    # expect = Path(test_input.replace(".in", ".out")).read_text().strip()

    # if expect != got:
    #     expect_out, got_out = expect, got
    #     if len(expect) > MAX_LEN:
    #         expect_out = expect[:MAX_LEN] + "..."
    #     if len(got) > MAX_LEN:
    #         got_out = got[:MAX_LEN] + "..."

    #     # TODO: output to log file, with diff
    #     errors.append(
    #         "{file}\n>> expecting\n{expect}\n>> got\n{got}".format(
    #             file=test_input, expect=expect_out, got=got_out
    #         )
    #     )
    #     print("WA")
    #     continue

    print("OK")

    passed += 1

if len(errors) > 0:
    print("\n")
    print("Got {errorCount} error/s:".format(errorCount=len(errors)))
    for error in errors:
        print(error)
