# CS50 Projects
CS50 is Harvard University's introduction to computer science and the art of programming. An entry-level course taught by David J. Malan, CS50 teaches students how to think algorithmically and solve problems efficiently. Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, software engineering, and web development. Languages include C, Python, SQL, and JavaScript plus CSS and HTML. Problem sets are inspired by real-world domains of biology, cryptography, finance, forensics, and gaming. 

I completed the course over the course of about a month and a half and here are some of the projects that I've finished.

# Most Notable
- Tideman

# Table of Contents
- [Week 1](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-1): Intro to C
  - Mario
  - Credit
- [Week 2](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-2): Arrays in C
  - Scrabble
  - Readability
  - Substitution
- [Week 3](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-3): Algorithms and Recursion
  - Sort
  - Plurality
  - Tideman
- [Week 4](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-4): Memory
  - Volume
  - Filter
  - Recover
- [Week 5](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-5): Data Structures
  - Inheritance
  - Speller
- [Week 6](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-6): Intro to Python
  - World Cup
  - DNA
  - Remake of old exercises
      - Hello
      - Mario
      - Credit
      - Readability
- [Week 7](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-7)
- [Week 8](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-8)
- [Week 9](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-9)

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
- `add_pairs`: function adds all pairs of candidates where one candidate is preferred to the `pairs` array. A pair of candidates who are tied are not added to the array.
- `sort_pairs`: function sorts the `pair` array in decreasing order of strength/margin of victory. If there are multiple pairs with the same strength of victory the order does not matter.
- `lock_pairs`: creates a `locked[][]` graph adding all edges in decreasing order of victory strength and recursively checks if a new locked pair would create a cycle.
- `print_winner`: prints the name of the candidate who is the source of the graph/winner of the voting.
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

## Week 4
Learned much more about how computers allocate memory as well as how to edit and access memory of `.wav`, `.bmp`, and `.jpeg` files.
### Volume
Changes volume of a sound file by a given factor. Reads data from the `.wav` file on 16-bit sample at a time and multiplies by `factor` to a new output file.
```
$ ./volume [INPUT.wav] [OUTPUT.wav] [factor]
```
### Filter
Program applies filter such as grayscale `g`, reflection `r`, box blur `b`, and edge detection `e` (Sobel Filter) to `.bmp` files.
```
$ ./filter -g images/yard.bmp out.bmp
$ ./filter -r images/yard.bmp out.bmp
$ ./filter -b images/yard.bmp out.bmp
$ ./filter -e images/yard.bmp out.bmp
```
### Recover
When photos are deleted on a computer, they are usually just "forgotten" rather than deleted, which means that you can recover JPEGs from computer memory since they start with a specific signature. This exercise uses `fread` to read in a raw file and recovers the images that have been "deleted" from the computer's memory.
```
$ ./recover card.raw
```

## Week 5
This week was an introduction to data structures including linked lists, hash tables, and tries as well as their benefits and drawbacks.
### Inheritance
This program uses pointers to simulate blood type inheritance similar to that of a Punnett Square.
```
$ ./inheritance
Child (Generation 0): blood type OO
    Parent (Generation 1): blood type AO
        Grandparent (Generation 2): blood type OA
        Grandparent (Generation 2): blood type BO
    Parent (Generation 1): blood type OB
        Grandparent (Generation 2): blood type AO
        Grandparent (Generation 2): blood type BO
```
### Speller
An implementation of a spell checker that uses a hash table to store a dictionary of words from disk into memory. My hash function just puts each word into a different bucket depending on what letter the word starts with.
#### Breakdown
- `dictionary.c`: loads in a dictionary from a text file, reads each word, hashes it, and places it into the hash table, creating a dictionary in `C`.
- `speller.c`: essentially creates the "interface" that is shown in the console, records the benchmarks for loading in the file, how many words are in the dictionary or text, etc...
- `dictionaries/`: directory with dictionary `.txt` files.
-  `speller50.c`: a correct implementation of the program that I used to check my work.
-  `texts/`: directory with text files with mispellings that `speller.c` or `speller50.c` can check for.
-  `keys/`: text file that has all the correct console outputs that would come from a specific text file from `texts/`
#### Usage
When implemented correctly both `$ ./speller texts/lalaland.txt` and `$ ./speller50 texts/lalaland.txt` should output the same thing.
``` C
$ ./speller texts/lalaland.txt
Chazelle
L
TECHNO
L
...
WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.02
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.06
```
It's also possible to check the output with a key of the console output. To do this, you must first redirect the output to a file and then compare.
```
$ ./speller texts/lalaland.txt > file.txt
$ diff -y file.txt keys/lalaland.txt
```
Lastly, any text file can be spell checked so long as the text file is added to the `texts/` directory by calling `$ ./speller texts/yourfile.txt`

## Week 6
This week was mainly spent getting used to coding in Python. The different syntax definitely is a big change from C, but there are many quality of life changes in Python that make it much easier to code.
### World Cup
Simulates a FIFA World Cup with 16 teams. Outcome is determined through 1000 simulations where the probability of the winner for each match is determined by the FIFA rating of each team.
```
$ python tournament.py 2018m.csv
Belgium: 20.9% chance of winning
Brazil: 20.3% chance of winning
Portugal: 14.5% chance of winning
Spain: 13.6% chance of winning
Switzerland: 10.5% chance of winning
Argentina: 6.5% chance of winning
England: 3.7% chance of winning
France: 3.3% chance of winning
Denmark: 2.2% chance of winning
Croatia: 2.0% chance of winning
Colombia: 1.8% chance of winning
Sweden: 0.5% chance of winning
Uruguay: 0.1% chance of winning
Mexico: 0.1% chance of winning
```
### DNA
Identifies a person based on their DNA. A person's DNA has repeating sequences called Short Tandem Repeasts (STRs) and each person's STR, their composition and occurence, varies drastically. Therefore, STRs are the key to identifying a person based on their DNA. The program reads in a `.csv` of individuals with their STR counts and counts the unique STRs as seen in the header. It also reads in a `.txt` file with a sequence of data that has not been identified and counts the unique STRs as identified in the heading. Lastly, it compares to see if there's an individual in the `.csv` that has a matching number of STRs.
```
$ python dna.py databases/file.csv sequences/file.txt
Joe
```
### Remakes
- Hello: simple hello world program
- Mario: exactly the same as the Mario program from week 1 but written in Python
- Credit: same as `credit.c` from week 1 but written in Python
- Readability: same as `readability.c` from week 2 but written in Python
