# NIST-STS for TJF-Unt

## If you want to simulate the results ##
For the NIST-STS and simulation, download and install the following package:

- [NIST-STS](https://github.com/arcetri/sts)
- c++ version 7.5.0 or newer

For every subfolder, you will find a ```.cpp``` file that contains the implemented code for the bitstream generation. To generate data, run

```terminal
$ g++ Nist.cpp
$ ./a.out
```
It will generate a ```bitstream.dat``` file, for the NIST-STS run:
```terminal
$ ./sts -v 1 -i 1000 -w . -F r -s bitstream.dat
```

The results will be in the archive:
```terminal
results.txt
```
