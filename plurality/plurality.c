#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

typedef struct
{
    string winner_name;
    int winner_votes;
}
winner;

// Array of candidates
candidate candidates[MAX];
winner winners[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
bool isallsame(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner(); // need delete string
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    if (isallsame())
    {
        for (int i = 0; i < candidate_count; i++)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    int max_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > candidates[max_count].votes)
        {
            max_count = i;
        }
    }

//    if (max_count == 0 && (candidates[max_count].votes == candidates[max_count + 1].votes))
//    {
//        for (int i = 0; i < candidate_count; i++)
//        {
//            printf("%s\n", candidates[i].name);
//        }
//    }

    winners[0].winner_name = candidates[max_count].name;
    winners[0].winner_votes = candidates[max_count].votes;

    int count = 1;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (candidates[i].votes == candidates[max_count].votes && !(strcmp(candidates[max_count].name, candidates[i].name) == 0))
        {
            winners[count].winner_name = candidates[i].name;
            winners[count].winner_votes = candidates[max_count].votes;
            count++;
        }
    }

    for (int i = 0; i < count; i++)
    {
        printf("%s\n", winners[i].winner_name);
    }

    return;
}

bool isallsame(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (!(candidates[i].votes == candidates[i + 1].votes))
        {
            return false;
        }
    }
    return true;
}