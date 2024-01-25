#!/usr/bin/env python3

# Generate tests based on meta data in log.py and log_data.py
# MUST BE RUN BY log_auto-test-gen.sh ONLY!

import os
from log import *

S = '\\'
NN = '\\n'
TT = '\\t'
N = '\n'
T = '\t'

print('''
#ifndef LOG_AUTO_C


#include "../../test/packing/log_auto_mirror.h"

''')

for optype in log_data.optypes:
    print('''#define __wt_logop_%(name)s_pack __wt_logop_%(name)s_pack__mirror''' % {'name' : optype.name})
    print('''#define __wt_logop_%(name)s_unpack __wt_logop_%(name)s_unpack__mirror''' % {'name' : optype.name})

print('''
#endif
''')
