# Encrypto - CryptographyApp
## Idea
Encrypt and decrypt your photos using a private key, to be sure that no one sees your peppers
## Features
The program from [crypto.c](crypto.c) has the following features:
- encrypt and decrypt an image, using a secret key(composed of two values)
- show the results of the CHI-SQUARED test of the plain image and encrypted image
- show instructions of how to use the program
## Building
To build on windows use:
```
gcc -std=c99 crypto.c -o crypto
```
## Results
<p align="center">
  <img src="https://github.com/Alecsandu/CryptographyApp/blob/main/peppers.bmp">
  <br/>
  Plain image
  <hr />
</p>

<p align="center">
  <img src="https://github.com/Alecsandu/CryptographyApp/blob/main/encodedpeppers.bmp">
  <br />
  Encrypted image
</p>
