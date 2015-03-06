import os
import sys
import traceback

def main(argv):
    cmds = os.listdir("./commands/")
    try:
        cmd = argv[1]
        if cmd in cmds:
            op = argv[2]
            moduleName = [cmd]
            sys.path.append("./commands/%s"%cmd)
            modules = map(__import__ , moduleName)
            func = getattr(modules[0], op)
            if len(argv) > 3:
                func(argv[3:])
            else:
                func()
        else:
            print "command is incorrect!"
    except:
        print "Need:command operation"
        print traceback.format_exc()

if __name__ == "__main__":
    main(sys.argv)
