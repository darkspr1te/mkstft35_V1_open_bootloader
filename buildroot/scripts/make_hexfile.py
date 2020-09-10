Import("env")

# Custom HEX from ELF
# file saved in buildroot/SDCARD , for bin/elf files see post_copy_update.py for aternate way of doing copy 
# this example show conversion of one type of file to another
env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(" ".join([
        "$OBJCOPY", "-O", "ihex", "-R", ".eeprom",
        "\"$BUILD_DIR\${PROGNAME}.elf\"", "\"$PROJECT_DIR/buildroot/SDCARD/${PROGNAME}.hex\""
    ]), "Building $BUILD_DIR\${PROGNAME}.hex")
)


      
