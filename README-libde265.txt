libde265 DirectShow filters
-------------------------------------

Based on LAVFilters
https://github.com/Nevcairiel/LAVFilters

Uses libde265 for H.265/HEVC decoding
https://github.com/strukturag/libde265

Further information are available at http://www.libde265.org

Copyright (c) 2014-2015 struktur AG
Portions Copyright (C) 2010-2015 Hendrik Leppkes


Build instructions
-------------------------------------

We provide a Vagrant file that can be used to setup a complete build
environment and compile the filters in there:

- git submodule update --init
- ./bootstrap.sh
- vagrant up

The resulting installer will be copied to the host system after everything is
finished.
