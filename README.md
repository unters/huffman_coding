# Huffman coding

## Description

This repository contains implementation of huffman coding algorithm in C made in educational purposes.

The algorithm is implemented as a cmd application capable of compressing and decompressing arbitrary files.

## How it works

### Overview

1. Read file byte by byte and count character frequences.

2. Build huffman tree using discovered character frequences.

3. Traverese the huffman tree and provide each character with its code length.

4. Using calculated code lengths provide each character with corresponding canonical huffman code.

5. Compress file using built canonical huffman codes.

### Step 1 - 2

* <mark>TODO</mark>: describe.

### Steps 3 - 4, building canonical codes

The normal Huffman coding algorithm assigns a variable length code to every symbol in the alphabet. More frequently used symbols will be assigned a shorted code. Suppose we have the following *non*-canonical codebook:

```textile
A = 11
B = 0
C = 101
D = 100
```

To make the code a *canonical* Huffman code, the codes are renumbered. The bit lengths stay the same with the code book being sorted **first** **by** codeword **length** and **secondly** **by** **alphabetical value** of the letter:

```textile
B = 0
A = 11
C = 101
D = 100
```

Each of the existing codes is replaced with a new one of the same length, using the following algorithm:

* The *first* symbol in the list gets assigned a codeword which is the same length as the symbol's original codeword but all zeros.

* Each subsequent symbol is assigned the next binary number in sequence, ensuring that folowing codes are always higher in value.

* When a longer codeword is reached, then *after* incrementing, zeroes are appended to codeword on its right until the length of the new codeword is reached (this can be done via left shift).

By following these three rules, the *canonical* version of the code book produced will be:

```textile
B = 0
A = 10
C = 110
D = 111
```

The advantage of a canonical Huffman tree is that it can be encoded in fewer bits than an arbitrary tree. <mark>TODO</mark>: describe.

## Step 5

* <mark>TODO</mark>: describe.

## Links

* [Canonical Huffman code - Wikipedia](https://en.wikipedia.org/wiki/Canonical_Huffman_code)


