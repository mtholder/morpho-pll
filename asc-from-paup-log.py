#!/usr/bin/env python
import math
import sys
import re
_SITE_PATTERN = re.compile(r'^\s+\d+\s+(\S+)\s*$')
num_states = 2
lnL = []
with open(sys.argv[1], 'r') as inpf:
    for line in inpf:
        m = _SITE_PATTERN.match(line)
        if m:
            lnL.append(-float(m.group(1)))

c = lnL[-1]
sitesLnL = lnL[:-1]
prob_const = num_states*math.exp(c)
prob_var = 1 - prob_const
lnProbVar = math.log(prob_var)
print sum(sitesLnL) - lnProbVar*len(sitesLnL)