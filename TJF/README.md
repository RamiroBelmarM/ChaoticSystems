# TJF function
This repository contains all the code for the TJ-function implementation and its application in a cipher algorithm.
# Requiriments
- c++ version 7.5.0 or newer

If you dont have it, for windows try to install it [from here](https://www.mingw-w64.org/) and for linux [from here](https://gist.github.com/hugoledoux/2e91ed3efbfa8ca5da1ea27e522d2b34)

# Organization

## Core folder
- ### TJF headers folder
This folder contains all the code required for TJ-function implementation.
- ### Cipher headers folder
This folder contains all the code required for the cipher algorithm.
- ### Polynomials headers folder
This folder contains the code of the four used polynomials as the DCF.
- ### Plot headers
This folder contains the code for the attractor reconstruction and for the 01-test for chaos.


## TJF-variations folder
You will find the code for plotting the function, attractor reconstruction and for the encryption implementation, using the Legendre polynomials (```TJF-Pnt```), Chebyshev polynomials of the first kind  (```TJF-Tnt```), Chebyshev polynomials of the second kind  (```TJF-Unt```) and for the Hermite function (```TJF-Hnt```)

# Warning
The cipher implementation is just a demonstration. Please don't use it in production code or in anything you need to secure.


# License
```terminal

“Commons Clause” License Condition v1.0

The Software is provided to you by the Licensor under the License, as defined below, 
subject to the following condition.

Without limiting other conditions in the License, the grant of rights under the License 
will not include, and the License does not grant to you, the right to Sell the Software.

For purposes of the foregoing, “Sell” means practicing any or all of the rights granted 
to you under the License to provide to third parties, for a fee or other consideration 
(including without limitation fees for hosting or consulting/ support services related 
to the Software), a product or service whose value derives, entirely or substantially, 
from the functionality of the Software. Any license notice or attribution required by 
the License must also include this Commons Clause License Condition notice.

Software: TJF_ARX_cipher library

License: BSD 3-Clause License

Licensor: Ramiro Belmar Monterrubio.


```
