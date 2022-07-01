# CS50 Projects
CS50 is Harvard University's introduction to computer science and the art of programming. An entry-level course taught by David J. Malan, CS50 teaches students how to think algorithmically and solve problems efficiently. Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, software engineering, and web development. Languages include C, Python, SQL, and JavaScript plus CSS and HTML. Problem sets are inspired by real-world domains of biology, cryptography, finance, forensics, and gaming. 

I completed the course over the course of about a month and a half and here are some of the projects that I've finished.

# Most Notable
- Tideman

# Table of Contents
- [Week 1](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#pset-1): Intro to C
  - Mario
  - Credit
- [Week 2](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#pset-2): Arrays in C
  - Scrabble
  - Readability
  - Substitution
- [Week 3](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-3): Algorithms and Recursion
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
During lecture, lab, and this week's problem set, I became more familiar with time and space complexity. Furthermore, I also became more familiar with algorithms and recursion during my implementation of the plurality and tideman voting systems.
### Sort
These were already-compiled C programs where each implemented a different sorting algorithm and I had to determine which algorithm was which based on compile time of a text file that each contained a different number of numbers arranged in a reversed, shuffled, or sorted order.
```
$ time ./[program_name] [filename.txt]

Sort1: bubblesort
sorted50000:   0.4450s
reversed50000: 5.7412s
random50000:   7.3580s

Sort2: mergesort
sorted50000:   0.3490s
reversed50000: 0.3320s
random50000:   0.3460s

Sort3: selectionsort
sorted50000:   3.0230s
reversed50000: 2.9510s
random50000:   3.1190s
```
### Plurality
The program is an implementation of a simple plurality election that takes 9 votes in total.
```
$ ./plurality Alice Bob
Number of voters: 3
Vote: Alice
Vote: Bob
Vote: Alice
Alice
```
### Tideman
Implementation of a Tideman voting system which is also known as a ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate. Instead of just voting for their top-choice, they can rank the candidates in order of preference. In situations that previously would have ended in a tied election could now have a "condorcet winner": the personw ho would have won any head-to-head matchup against another candidate. 
Generally, Tideman method works by constructing a "graph" of candidates, where an arrow from A to B indicates that A beats B in a head-to-head matchup and A beats C in a head-to-head matchup. The winner would then be A, the "source" of the graph. 
The issue arises when there's no Condorcet winner in this case A beats B, B beats C, and C beats A. This would result in a draw. To handle this, the algorithm locks in the strongest wins first, or the wins that win by the largest margins. Then adds the rest to the graph. Wins that would have created no Condorcet winner would not occur because the strength of the victory would not create an edge.
#### Breakdown
- Tally: determines who preferred the candidate over another and by what margin are they preferred
- Sort: sorts the pairs of candidates in decreasing order by margin of victory
- Lock: starting with the strongest pair, go through all pairs of candidates and lock in the pair so long as the pair does not create a cycle in the graph.
#### Methods
- `vote`: takes `rank` and `name` then inserts the name into `ranks` array where `ranks[i]` represents the user's `i`th preference.
- `record_preferences`: function is called once for each voter, takes argument `ranks` array. Function updates a global `preferences[i][j]` array to add the current voter's preferences where each cell represents the number of votes who prefer candidate `i` over candidate `j`
- 
#### Example
```
./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie
```
