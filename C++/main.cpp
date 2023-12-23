#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <array>
#include <chrono>
#include <random>

using namespace std;

const int N = 9;

using SudokuArray = array<array<int, N>, N>;

void printSudoku(const SudokuArray &sudoku)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

void printSudokuSolver(const SudokuArray &sudoku)
{
    cout << "Sudoku Puzzle Solution:" << endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

void shuffleDigits(array<int, N> &digits)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(digits.begin(), digits.end(), default_random_engine(seed));
}

bool isSafe(const SudokuArray &sudoku, int row, int col, int num)
{

    for (int x = 0; x < N; ++x)
    {
        if (sudoku[row][x] == num || sudoku[x][col] == num || sudoku[row - row % 3 + x / 3][col - col % 3 + x % 3] == num)
        {
            return false;
        }
    }
    return true;
}

bool solveSudoku(SudokuArray &sudoku)
{
    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            if (sudoku[row][col] == 0)
            {
                array<int, N> possibleNumbers{1, 2, 3, 4, 5, 6, 7, 8, 9};
                shuffleDigits(possibleNumbers);

                for (int num : possibleNumbers)
                {
                    if (isSafe(sudoku, row, col, num))
                    {
                        sudoku[row][col] = num;

                        if (solveSudoku(sudoku))
                        {
                            return true;
                        }

                        sudoku[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void generateRandomSudoku(SudokuArray &sudoku, int numToRemove)
{

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    for (int i = 0; i < 5; ++i)
    {
        shuffle(sudoku.begin(), sudoku.end(), default_random_engine(seed));
        for (int j = 0; j < N; ++j)
        {
            shuffle(sudoku[j].begin(), sudoku[j].end(), default_random_engine(seed));
        }
        array<int, N> digits{1, 2, 3, 4, 5, 6, 7, 8, 9};
        shuffleDigits(digits);
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                if (sudoku[j][k] != 0)
                {
                    sudoku[j][k] = digits[sudoku[j][k] - 1];
                }
            }
        }
    }

    solveSudoku(sudoku);

    while (numToRemove > 0)
    {
        int row = rand() % N;
        int col = rand() % N;

        if (sudoku[row][col] != 0)
        {
            sudoku[row][col] = 0;
            numToRemove--;
        }
    }
}

void generateSudoku(int numToRemove)
{
    SudokuArray sudoku{};

    generateRandomSudoku(sudoku, numToRemove);

    cout << "Generated Sudoku Puzzle:" << endl;
    printSudoku(sudoku);

    SudokuArray solution = sudoku;
    solveSudoku(solution);

    cout << "\n";
    printSudokuSolver(solution);
    cout << "\n";
}

int main()
{

    int numToRemoveEasy = 30;
    int numToRemoveMedium = 40;
    int numToRemoveHard = 50;

    generateSudoku(numToRemoveEasy);
    cout << "\n---\n";
    generateSudoku(numToRemoveMedium);
    cout << "\n---\n";
    generateSudoku(numToRemoveHard);

    return 0;
}
