#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

void print_preferences(void);
void print_pairs(void);
bool check_cycle(int head, int next);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    // print_preferences();

    add_pairs();
    //print_pairs();

    sort_pairs();
    print_pairs();

    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // over all of candidates[]
    for (int i = 0; i < candidate_count; i++)
    {
        // if there's a match of the name
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }

    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO

    // loops through all of ranks[]
    for (int i = 0; i < candidate_count; i++)
    {
        // rank[i] should be the row in pref and rank[i+1] should be the column in pref
        // once you're there increase the victory matchup by one
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    // through all the preferences
    for (int r = 0; r < candidate_count; r++)
    {

        for (int c = 0; c < candidate_count; c++)
        {
            // if statement helps avoid overlap of results
            if (c > r)
            {
                // create a pair to store into pairs array
                pair matchup;

                // checks and assigns winners
                if (preferences[r][c] > preferences[c][r])
                {
                    matchup.winner = r;
                    matchup.loser = c;
                    pairs[pair_count] = matchup;
                    pair_count++;
                }
                else if (preferences[r][c] < preferences[c][r])
                {
                    matchup.winner = c;
                    matchup.loser = r;
                    pairs[pair_count] = matchup;
                    pair_count++;
                }
                // tie
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // create temp array to copy from
    pair temp[pair_count];

    for (int j = 0; j < pair_count; j++)
    {
        // create temp array to copy from
        for (int i = 0; i < pair_count; i++)
        {
            temp[i].winner = pairs[i].winner;
            temp[i].loser = pairs[i].loser;
        }

        int highest_win = 0;
        int highest_index = 0;

        for (int i = j; i < pair_count; i++)
        {
            // winner minus the loser set to margins array
            int margins = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            if ((margins) >= highest_win)
            {
                highest_win = margins;
                highest_index = i;
            }
        }

        pairs[j] = pairs[highest_index];
        pairs[highest_index] = temp[j];

    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {

        // check cycle for false
        // checks the locked to see if there are any repeat
        // if there are no repeat, then nothing
        // if there are repeat, then remove the locked pair that you just added, move onto the next
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        // check cycle false
        // nothing
    }

    return;
}

bool check_cycle(int w, int l)
{
    // hold the head, if the loser i'm looking at isn't myself
    // hold onto the head, check if loser beat anyone
    // if what i'm looking at is myself
    // return true

    // return false

    // base case where you do find something that cycles so you gotta stop it
    if (w == l)
    {
        return true;
    }

    // checks all the pairs
    for (int i = 0; i < candidate_count; i++)
    {
        // if the loser beats someone
        if (locked[l][i])
        {
            // is the person that loser beats the winner?
            if (check_cycle(w, i))
            {
                // will only be in here if the winner == loser
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int loses = 0;
        // check each loser to the candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // if all the candidates don't beat our candidate, then this is our winner
            if (locked[j][i] == false)
            {
                loses++;
                if (loses == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }

    return;
}

void print_preferences(void)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("[%i] ", preferences[i][j]);
        }
        printf("\n");
    }
}

void print_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("winner: %i, loser: %i\n", pairs[i].winner, pairs[i].loser);
    }
}

