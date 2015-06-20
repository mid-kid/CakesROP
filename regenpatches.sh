xxd -i patches | sed -e "s/patches_len/fSIZE/g" -e "s/patches/rawData/g" > source/patches.h
