# Encryption and decryption of an arbitrary file
## Test file
Baboon:

![alt text](./BaboonRGB.bmp)

## Compilation
```terminal
$ g++ -o output_file block_cipher.cpp
```

## usage
```terminal
$ ./output_file [option] input_file output_file
```
options:
```terminal
$ -h    help
$ -e    Encryption option
$ -d    Decryption option
```

## Encryption example
```terminal
$ ./output_file -e BaboonRGB.bmp encryption_file
```


## Decryption example
```terminal
$ ./output_file -d encryption_file New_BaboonRGB.bmp
```


# Warning
This cipher implementation is just a demonstration. Please don't use it in production code or in anything you need to secure.
