CakesSpiderROP
========

Installs the mset rop using spider.

Usage
========
## Basic usage
Copy code.bin to the root of your sdcard and point your spider to :

* On 4.x firm :  
  http://dukesrg.no-ip.org/3ds/rop/?LoadCode4.dat  
  ![qr](https://chart.googleapis.com/chart?cht=qr&chs=220x220&chl=http://dukesrg.no-ip.org/3ds/rop/?LoadCode4.dat)

* On 9.0~9.2 firm :  
http://dukesrg.no-ip.org/3ds/rop/?LoadCode.dat  
![qr](https://chart.googleapis.com/chart?cht=qr&chs=220x220&chl=http://dukesrg.no-ip.org/3ds/rop/?LoadCode.dat)

The bottom screen should flash with a random pattern. Press home menu to exit spider.

This will install the rop for for loading Cakes.dat by default.

## Custom rop
To install a rop for a custom file, put ropCustom.txt in the root of the sdcard. The first line inside the file will be used as the custom dat filename.
The custom filename is limited to 12 characters.
See example/ropCustom.txt for an example.

Credits
========
* Anonymous contributor for the code
* zoogie for the patch format