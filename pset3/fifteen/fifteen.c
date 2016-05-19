/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }
    
    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // calculate the max tile number listed on the tiles
    int max = (d * d) - 1;
    // create a counter variable in order to label each tile from largest to smallest for initialization
    int n = 0;
    // each tile will be labeled consecutively in descending order
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            printf("%d", max-n);
            board[i][j] = (max - n);
            n++;
        }
    }
    
    // if the board has even dimensions(d) and an odd number of tiles(max), the positions of tiles numbered 1 and 2 should start off swapped 
    if(d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
        
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // loop through the rows
    for(int i = 0; i < d; i++)
    {
        // loop through each value in the row
        for(int j = 0; j < d; j++)
        {
            //print all tiles except the 0 tile
            if(board[i][j] > 0)
            {
                printf("  %2d  ", board[i][j]);  
            }
            // print a blank space instead of a zero
            if(board[i][j] == 0)
            {
                printf("  __  ");
            }
            
        }
        printf("\n");
    }
    return;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 * This function accepts the number of the tile the user wants to move as its argument
 */
bool move(int tile)
{
    // first check if the tile number is part of the game
    if(tile >= 0 || tile <= ((d * d) - 1))
    {
        // search through board to find the tile the user wishes to move
        for(int i = 0; i < d; i++)
        {
            for(int j = 0; j < d; j++)
            {
                // if the tile is found, check if it can legally make a move
                if(board[i][j] == tile)
                {
                    // if tile to the left exists and is the blank space
                    if(board[i - 1][j] == 0 && i != 0)
                    {   
                        // swap tile for blank space
                        board[i - 1][j] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                    // if tile to the right exists and is the blank space
                    else if(board[i + 1][j] == 0 && (i + 1) < d)
                    {
                        // swap tile for blank space
                        board[i + 1][j] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                    // if tile above exists and is the blank space
                    else if(board[i][j - 1] == 0 && j != 0)
                    {
                        // swap tile for blank space
                        board[i][j - 1] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                    // if tile below exists and is the blank space
                    else if(board[i][j + 1] == 0 && (j + 1) < d)
                    {
                        // swap tile for blank space
                        board[i][j + 1] = tile;
                        board[i][j] = 0;
                        return true;
                    }

                }
                
            }
        }
    }
    // if the tile does not border an empty space, return false
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // create variable that will increment from 1 to the max number tile in the game
    int n = 1;
    // check each tile
    for(int i = 0; i < d; i++) 
    {
        for(int j = 0; j < d; j++)
        {
            // each square should match the current count in order to win, otherwise return false
            // need to specify the value is not zero in order to not count the last blank space
            if (board[i][j] != n && board[i][j] != 0)
            {
                return false;
            }
            n++;
        }
    }
    // if each tile has been checked and the tile value decreases consecutively, the user has won
    return true;
}