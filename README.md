# CS50 Projects
CS50 is Harvard University's introduction to computer science and the art of programming. An entry-level course taught by David J. Malan, CS50 teaches students how to think algorithmically and solve problems efficiently. Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, software engineering, and web development. Languages include C, Python, SQL, and JavaScript plus CSS and HTML. Problem sets are inspired by real-world domains of biology, cryptography, finance, forensics, and gaming. 

I completed the course over the course of about a month and a half and here are some of the projects that I've finished.

# Most Notable
- Tideman

# Table of Contents
- [Week 1](https://github.com/tcyang-md/CS50-Projects/edit/main/README.md#pset-1): Intro to C
  - Mario
  - Credit
- [Week 2](https://github.com/tcyang-md/CS50-Projects/edit/main/README.md#pset-2): Arrays in C
  - Scrabble
  - Readability
  - Substitution
- [Week 3](https://github.com/tcyang-md/CS50-Projects/edit/main/README.md#week-3): Algorithms and Recursion
  - Sort
  - Plurality
  - Tideman
- [Week 4](link)
- [Week 5](link)
- [Week 6](link)
- [Week 7](link)
- [Week 8](link)
- [Week 9](link)

## Week 1
Started learning how to program in C. Both of these programs are fairly simple and straight forward.
### Mario
Creates a Mario-like pyramid of # of `n` height where `8 >= n >= 1`.
```
$ ./mario
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
```
### Credit
Program that prompts the user for a credit card number and then reports whether it is a valid American Express, MasterCard, or Visa card number using Luhn's Algorithm.
```
$ ./credit
Number: 4003600000000014
VISA
```

## Week 2
Second week of C where I became more familiar with the language.
### Scrabble
Determines the winner of a short scrabble-like game, where two players each enter their word, and the higher scoring player wins. 
```
$ ./scrabble
Player 1: COMPUTER
Player 2: science
Player 1 wins!
```
### Readability
Implementation of the *Coleman-Liau* index to output the grade level that is needed to understand some text between `"Before Grade 1"` and `"Grade 6+"`.
```
$ ./readability
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
```
### Substitution
Program that implements a substituion cipher where the 26 letter key is passed by a command line argument and each letter in the string is mapped to the matching letter in the normal alphabet. Non-alpha characters are not accepted and the program will only accept a 26 alphabetical key.
```
$ ./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ
plaintext:  HELLO
ciphertext: VKXXN
```

## Week 3
### Sort
