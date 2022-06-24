# TJF-self-driving plot, attractor reconstruction using the Hermite function.

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
tjf.init_val(alpha, a0, b0, d0, l0);
```