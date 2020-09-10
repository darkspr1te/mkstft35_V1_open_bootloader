Import("env")
from os.path import basename, isdir, join

build_flags = env.ParseFlags(env['BUILD_FLAGS'])
#print build_flags.get("CPPDEFINES")
flags = {k: v for (k, v) in build_flags.get("CPPDEFINES")}
#print flags
filename = flags.get("HARDWARE") + "." + flags.get("SOFTWARE_VERSION")
filename = flags.get("OUTPUTNAME")
#print filename
env.Replace(PROGNAME=filename)
