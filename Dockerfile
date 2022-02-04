FROM gcc:4.9

COPY . /CryptoApp

WORKDIR /CryptoApp/

RUN gcc -std=c99 -o CryptoApp crypto.c

CMD ["./CryptoApp"]