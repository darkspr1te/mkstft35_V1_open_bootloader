Import("env")
import shutil 
from os.path import basename, isdir, join
print("Post build scripts")

def after_build(source, target, env):
    source_filename = env['PROJECT_BUILD_DIR'] + "/" + env['PIOENV'] + "/" + env['PROGNAME'] + ".bin"
    dst_filename = env['PROJECT_DIR'] + "/buildroot/SDCARD/" + env['PROGNAME'] + ".bin"
    shutil.copyfile(source_filename, dst_filename)
      
env.AddPostAction("buildprog", after_build)
#print(env)