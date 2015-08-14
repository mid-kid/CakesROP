CakesROP
========

A modified rop installer for CakesFW.

Credits to zoogie for creating this.
https://gbatemp.net/threads/homebrew-development.360646/page-182#post-5461751

Building
========
Requires devkitPro with libnds. Run make to compile.

Custom rop and banner
========
 * Define ```DATNAME``` when calling the makefile to specify the dat name to be used as the default when installing NVRAM ROP.
 * Define ```DISPNAME``` when calling the makefile to specify the name to be displayed
 * Define ```GRAPHICS``` when calling the makefile to specify the graphics folder containing your grit and png files to be used as the custom banner.
e.g.

```
make DATNAME=dat.dat GRAPHICS=data -C CakesROP  
or  
make DATNAME=whatever/dat.dat DISPNAME=dat.dat GRAPHICS=data -C CakesROP
```

License
========
This project is licensed under BSD 2-Clause. See LICENSE for details.  
By contributing to the repo either through pull requests or comments you're agreeing to have your content to be under the same license.
If you require another license for your content please explicitly mention so in the pull request or comment.

Credits
========
* zoogie for the the original patches and the patch format
* Reisyukaku for N3DS entry
* GW for the original ROP