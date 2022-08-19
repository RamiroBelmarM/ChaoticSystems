# NIST-STS for eleven chaotic systems used as the entropy source of an encryption algorithm founded in the literature

The results shown in the paper can be found in the ```result.txt``` archive in every subfolder.

## If you want to simulate the results ##
For the NIST-STS and simulation, download and install the following package:

- [NIST-STS](https://github.com/arcetri/sts)
- c++ version 7.5.0 or newer

And then clone this repository. For every subfolder, you will find a ```.cpp``` file that contains the implemented code for the chaotic system, to compile it and get data to test, navigate in the terminal to the desired subfolder, and run:

```terminal
$ g++ Ref#.cpp
$ ./a.out
```
It will generate a ```bitstream.dat``` file, and finally, for the NIST-STS run:
```terminal
$ ./sts -v 1 -i 1000 -w . -F r -s bitstream.dat
```

The results will be in the archive:
```terminal
results.txt
```
