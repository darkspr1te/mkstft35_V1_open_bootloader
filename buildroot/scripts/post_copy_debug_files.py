Import("env")
import shutil 
print "Post build scripts"

def after_build(source, target, env):
    source_filename = env['PROJECT_BUILD_DIR'] + "/" + env['PIOENV'] + "/" + env['PROGNAME'] + ".elf"
    dst_filename = env['PROJECT_DIR'] + "/buildroot/SDCARD/" + env['PROGNAME'] + ".elf"
    shutil.copyfile(source_filename, dst_filename)
    
env.AddPostAction("buildprog", after_build)
#print(env)