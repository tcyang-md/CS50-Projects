# CS50 Projects
CS50 is Harvard University's introduction to computer science and the art of programming. An entry-level course taught by David J. Malan, CS50 teaches students how to think algorithmically and solve problems efficiently. Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, software engineering, and web development. Languages include C, Python, SQL, and JavaScript plus CSS and HTML. Problem sets are inspired by real-world domains of biology, cryptography, finance, forensics, and gaming. 

I completed the course over the course of about a month and a half and here are some of the projects that I've finished.

# Most Notable
- Tideman

# Table of Contents
- [Week 1:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-1) Intro to C
  - Mario
  - Credit
- [Week 2:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-2) Arrays in C
  - Scrabble
  - Readability
  - Substitution
- [Week 3:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-3) Algorithms and Recursion
  - Sort
  - Plurality
  - Tideman
- [Week 4:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-4) Memory
  - Volume
  - Filter
  - Recover
- [Week 5:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-5) Data Structures
  - Inheritance
  - Speller
- [Week 6:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-6) Intro to Python
  - World Cup
  - DNA
  - Remake of old exercises
      - Hello
      - Mario
      - Credit
      - Readability
- [Week 7:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-7) SQL, SQLite
  - Songs
  - Movies
  - Fiftyville
- [Week 8:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-8) HTML, CSS, JavaScript, Bootstrap
  - Trivia
  - Homepage
- [Week 9:](https://github.com/tcyang-md/CS50-Projects/blob/main/README.md#week-9) Flask
  - Birthday
  - Finance

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

## Week 7
This week was mainly focused on getting comfortable writing SQL queries and being able to quickly obtain correct information from a database. All of the projects this week were "worksheet" like where I had to answer questions by querying/creating a database.
### Songs
Contains a database with the top 100 streamed songs on Spotify in 2018. Here are some examples of questions that I had to answer by querying the `songs.db` database.
#### Schema
``` SQL
CREATE TABLE songs (
    id INTEGER,
    name TEXT,
    artist_id INTEGER,
    danceability REAL,
    energy REAL,
    key INTEGER,
    loudness REAL,
    speechiness REAL,
    valence REAL,
    tempo REAL,
    duration_ms INTEGER
);
CREATE TABLE artists (
    id INTEGER,
    name TEXT
);
```
#### Examples
1. Write a SQL query that lists the names of songs that are by Post Malone
``` SQL
SELECT name FROM songs WHERE artist_id == (SELECT id FROM artists WHERE name = 'Post Malone');
```
2. Write a SQL query that returns the average energy of songs that are by Drake.
``` SQL
SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists Where name = 'Drake');
```
### Movies
SQL queries to answer questions about a database of movies. Each of these tables store distinct information and in order to answer more complicated questions such as "Who starred in the movie Toy Story 2", the SQL query must cross reference the `movies` table to obtain the movie `id`, then get the actors' `person_id` from the `stars` table, then bring up the `name` of the actors and actresses by referencing the `id` or `person_id` in the `people` table.
#### Schema
``` SQL
CREATE TABLE movies (
                    id INTEGER,
                    title TEXT NOT NULL,
                    year NUMERIC,
                    PRIMARY KEY(id)
                );
CREATE TABLE stars (
                movie_id INTEGER NOT NULL,
                person_id INTEGER NOT NULL,
                FOREIGN KEY(movie_id) REFERENCES movies(id),
                FOREIGN KEY(person_id) REFERENCES people(id)
            );
CREATE TABLE directors (
                movie_id INTEGER NOT NULL,
                person_id INTEGER NOT NULL,
                FOREIGN KEY(movie_id) REFERENCES movies(id),
                FOREIGN KEY(person_id) REFERENCES people(id)
            );
CREATE TABLE ratings (
                movie_id INTEGER NOT NULL,
                rating REAL NOT NULL,
                votes INTEGER NOT NULL,
                FOREIGN KEY(movie_id) REFERENCES movies(id)
            );
CREATE TABLE people (
                id INTEGER,
                name TEXT NOT NULL,
                birth NUMERIC,
                PRIMARY KEY(id)
            );
CREATE INDEX idx_year ON movies(year);
```
#### Examples
1. Write a SQL query to list the names of all people who starred in Toy Story.
``` SQL
SELECT name FROM people 
JOIN stars ON people.id = stars.person_id 
JOIN movies ON stars.movie_id = movies.id 
WHERE title = 'Toy Story';
```
2. Write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
``` SQL
SELECT title, rating FROM movies 
JOIN ratings ON movies.id = ratings.movie_id 
WHERE movies.year = 2010 
ORDER BY ratings.rating 
DESC, movies.title;
```
3. Write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
``` SQL
SELECT DISTINCT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.id in
(SELECT movies.id FROM movies
join people on stars.person_id=people.id
join stars on stars.movie_id=movies.id
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958)
AND people.name != "Kevin Bacon";
```
### Fiftyville
An extremely elaborate mystery/scavenger hunt created by the team of CS50 where you must query the town's security footage, atm transaction, flight, and other databases to find out who stole the CS50 Duck, where they escaped to, and who helped them escape. This was a really fun task that took a couple hours and definitely helped me become more familar with SQL queries.
### Breakdown
- `answers.txt`: logs my answers to CS50 mystery
- `fiftyville.db`: database including tables for `crime_scene_reports`, `interviews`, `atm_transactions`, `bank_accounts`, `airports`, `flights`, `passengers`, `phone_calls`, `people`, and `bakery_security_logs`.
#### Examples
1. First, I have to find what I can from police interviews
``` SQL
SELECT year, month, day, description FROM crime_scene_reports WHERE description LIKE '%duck%';
SELECT name, transcript FROM interviews WHERE year = 2021 and month = 7 and day = 28 and transcript LIKE '%bakery%';
```
2. Then based on the time and location of the crime from the interviews, I was able to get the names of the individuals that were at the scene of the crime plus or minus 15 minutes.
``` SQL
SELECT DISTINCT name, bakery_security_logs.hour, bakery_security_logs.minute, people.license_plate FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE people.license_plate in
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 and month = 7 and day = 28 and activity = 'exit' and hour <= 11 and hour >=10
) and bakery_security_logs.hour = 10 ORDER BY name;
```

## Week 8
This week was an introduction to web development starting with HTML, CSS, and JavaScript. 
### Trivia
A basic trivia questions web page implemented in HTML with CSS as well as JavaScript to make it more dynamic.
#### Instructions
`$ http-server index.html`
#### Example
![image](https://user-images.githubusercontent.com/70073219/177054156-7aef5852-a1cb-44cf-a2d8-ccd7ce4b2f78.png)
### Homepage
For this assignment, we were tasked to create a homepage with whatever content we wanted. I decided to make a webpage using a Bootstrap framework that displayed local ski resort information such as snow forecast, trails open, lift status, etc... I also added a couple of extra webpages about myself with a BootStrap carousel containing pictures of ski resorts I've been to as well a contact me form with a dynamic thank you page that personalizes the thank you displayed depending on form submission. There's also a current weather tab on the NavBar that will redirect the user to a webpage displaying the user's location and weather.
![image](https://user-images.githubusercontent.com/70073219/177054600-aafe2df1-81af-4544-8672-0d8686aad82e.png)

## Week 9
This week we were able to bring together our SQL, Python, and HTML/CSS/JavaScript/Bootstrap knowledge to create a couple of dynamic web applications.
### Birthdays
A web application using HTML/CSS/JavaScript to run the front end of the web application and Python/SQL to handle the back end that stores birthday information. List automatically updates a SQL database and dynamically changes the webpage to reflect a change in the database.
