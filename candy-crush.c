#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define NUM_COLORS 5

// Print the game board
void printBoard(int board[][BOARD_SIZE])
{
    printf("  ");
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Initialize the game board with random colors
void initBoard(int board[][BOARD_SIZE])
{
    srand(time(NULL));
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = rand() % NUM_COLORS + 1;
        }
    }
}

// Swap two elements on the game board
void swap(int board[][BOARD_SIZE], int row1, int col1, int row2, int col2)
{
    int temp = board[row1][col1];
    board[row1][col1] = board[row2][col2];
    board[row2][col2] = temp;
}

// Check if there are any matches on the board
int checkMatches(int board[][BOARD_SIZE])
{
    int matchFound = 0;
    // Check horizontal matches
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE - 2; j++)
        {
            if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
            {
                matchFound = 1;
                board[i][j] = board[i][j + 1] = board[i][j + 2] = 0;
            }
        }
    }
    // Check vertical matches
    for (int i = 0; i < BOARD_SIZE - 2; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j])
            {
                matchFound = 1;
                board[i][j] = board[i + 1][j] = board[i + 2][j] = 0;
            }
        }
    }
    return matchFound;
}

// Collapse the board after matches have been removed
void collapseBoard(int board[][BOARD_SIZE])
{
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        int k = BOARD_SIZE - 1;
        for (int i = BOARD_SIZE - 1; i >= 0; i--)
        {
            if (board[i][j] != 0)
            {
                swap(board, i, j, k, j);
                k--;
            }
        }
        for (int i = 0; i <= k; i++)
        {
            board[i][j] = 0;
        }
    }
}

// Main function to play the game
int main()
{
    int board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board);
    printBoard(board);
    while (checkMatches(board))
    {
        collapseBoard(board);
        printf("Matches found! Board after collapse:\n");
        printBoard(board);
    }
    printf("Nothing\n");
    return 0;
}
