# TJF plot, attractor reconstruction and stream cipher, using the Hermite function.

# How to compile

## Plot 
```terminal
$ g++ plot.cpp
$ ./a.out >| dat.dat
```
```dat.dat``` contains all the data point for plotting ```t vs f(t)```.

## Attractor
```terminal
$ g++ attractor.cpp
$ ./a.out >| dat.dat
```
```dat.dat``` contains all the data point for plotting ```f(t) vs f(t+tau)```.

## 01-test
```terminal
$ g++ 01-test.cpp
$ ./a.out
```
## Remarks
The results of above, are using random initial conditions, if you want to change it, replace the following line in the ````*.cpp```` file:
```cpp
tjf.init_randomly();
```
by
```cpp
tjf.init_val(alpha, beta, gamma, lambda, a0, b0, d0, l0);
```

## Cipher
The usage of the cipher algorithm implementation is in the cipher folder respectively.

# Warning
The cipher implementation is just a demonstration. Please don't use it in production code or in anything you need to secure.