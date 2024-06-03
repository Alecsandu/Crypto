# Encrypto - CryptographyApp

[![Build status](https://github.com/Alecsandu/Crypto/actions/workflows/build.yml/badge.svg)](https://github.com/Alecsandu/Crypto/actions/workflows/build.yml)
[![Latest release](https://img.shields.io/github/release/Alecsandu/Crypto.svg?maxAge=3600)](https://github.com/Alecsandu/Crypto/releases/tag/0.1.0-alpha)

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
  <img src="peppers.bmp">
  <br/>
  Plain image
  <hr />
</p>

<p align="center">
  <img src="examples/encodedpeppers.bmp">
  <br />
  Encrypted image
</p>
