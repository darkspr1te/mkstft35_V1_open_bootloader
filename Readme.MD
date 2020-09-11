# MKS 3.5" TFT Bootloader 
 
Supporting MKSTFT35 V1_0 original firmware (mks robin encryption) or 
vanilla firmware from other vendors 

 place firmware file on sdcard , 
 different names for different type of firmware, 
  Original MKS firmware use *mkstft35.bin* for filename
  for vanilla (non encrypted firmware ) use *mkslcd.bin* 

  still early beta, lots of debug code slowing it down, 
pre built bin and hex files flashable via st-link / open ocd and other found in 

https://github.com/darkspr1te/mkstft35_V1_open_bootloader/tree/master/buildroot/SDCARD



##Few bugs/warnings 
system does not rename firmware file so it will reflash on reboot. yet!
system does not copy fonts/icons onto system(spi flash). yet!
OTA updates via esp2866 feature disabled until i can find a good vector for activation. 


darkspr1te 

