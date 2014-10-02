import sys
import re


REMAP = {
        'number' : '^\d+$',
        'hr:min' : '^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$',
        'hr:min:sec' : '^([0-1]?[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$'
}

def isHourMinSec(arg):
        return bool(re.match(REMAP['hr:min:sec'], arg))

def isHourMin(arg):
        return bool(re.match(REMAP['hr:min'], arg))

def isNumber(arg):
        return bool(re.match(REMAP['number'], arg))


if __name__ == "__main__":
        func = getattr(sys.modules[__name__], sys.argv[1])
        print func(sys.argv[2])

