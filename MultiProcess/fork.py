#!/usr/bin/env python3
# _*_ coding: utf-8 _*_

import os

print('Process (%s) start...' % os.getpid())

# Only works on Unix/Linux/Mac:
pid = os.fork()
if pid == 0:
    print('I am child process (%s) and my parent is %s.' % (os.getpid(), os.getppid()))
else:
    print('I (%s) just created a child proecss (%s)' % (os.getpid(), pid))
