# Encrypto - CryptographyApp
## Idea
Encrypt and decrypt your photos using a CLI tool, to *make* sure that no one sees your peppers.
## Features
The source code for the program in [crypto.c](crypto.c) has the following features:
- encrypt and decrypt an image, using a secret key(composed of two values)
- show the results of the CHI-SQUARED test of the plain image and encrypted image
- help option
## Building
To build use:
```
make install
```
## Results
<p align="center">
  <img src="https://github.com/Alecsandu/CryptographyApp/blob/main/peppers.bmp">
  <br/>
  Plain image
  <hr />
</p>

<p align="center">
  <img src="https://github.com/Alecsandu/CryptographyApp/blob/main/examples/encodedpeppers.bmp">
  <br />
  Encrypted image
</p>
