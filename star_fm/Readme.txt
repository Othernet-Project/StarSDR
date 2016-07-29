rm -f ./libstarsdr.so; ln -s ../out/libstarsdr_rtlsdr.so ./libstarsdr.so ; sudo LD_LIBRARY_PATH=./:../out/ ./star_fm -f 98.3e6  -s 200000 -r 32000 - | aplay -r 32k -f S16_LE 
rm -f ./libstarsdr.so; ln -s ../out/libstarsdr_mirics.so ./libstarsdr.so ; sudo LD_LIBRARY_PATH=./:../out/ ./star_fm -f 98.3e6  -s 200000 -r 32000 - | aplay -r 32k -f S16_LE 
