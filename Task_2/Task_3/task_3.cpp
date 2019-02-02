#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
using namespace std;


class CBoard {
public:
    explicit CBoard() {}
    CBoard(int _cells, short _null_pos, vector<char> _way) :
            cells(_cells),
            null_pos(_null_pos),
            way(_way) {}
    ~CBoard() {}

    void FillBoard(int input, short _null_pos);
    int GetCells() { return cells; }
    short GetCount() { return way.size(); }
    vector<char> GetWay() { return way; }

    CBoard GoRight() const;
    CBoard GoLeft() const;
    CBoard GoUp() const;
    CBoard GoDown() const;

    bool CanRight() const;
    bool CanLeft() const;
    bool CanUp() const;
    bool CanDown() const;

private:
    int cells;
    short null_pos;
    vector<char> way;
};

void CBoard::FillBoard(int input, short _null_pos)
{
    cells = input;
    null_pos = _null_pos;
}

short getDigit(int number, short digit)
{
    if (number == 0)
        return number % 10;
    int x = number / pow(10, digit);
    return x % 10;
}

CBoard CBoard::GoRight() const
{
    int newBoard = cells + pow(10, (8 - null_pos)) * (getDigit(cells, 7 - null_pos) - 9) - pow(10, (7 - null_pos)) * (getDigit(cells, 7 - null_pos) - 9);
    short newNull = null_pos + 1;
    vector<char> newWay = way;
    newWay.push_back('R');
    CBoard board(newBoard, newNull, newWay);
    return board;
}

CBoard CBoard::GoLeft() const
{
    int newBoard = cells - pow(10, (9 - null_pos)) * (getDigit(cells, 9 - null_pos) - 9) + pow(10, (8 - null_pos)) * (getDigit(cells, 9 - null_pos) - 9);
    short newNull = null_pos - 1;
    vector<char> newWay = way;
    newWay.push_back('L');
    CBoard board(newBoard, newNull, newWay);
    return board;
}

CBoard CBoard::GoDown() const
{
    int newBoard = cells + pow(10, (8 - null_pos)) * (getDigit(cells, 5 - null_pos) - 9) - pow(10, (5 - null_pos)) * (getDigit(cells, 5 - null_pos) - 9);
    short newNull = null_pos + 3;
    vector<char> newWay = way;
    newWay.push_back('D');
    CBoard board(newBoard, newNull, newWay);
    return board;
}

CBoard CBoard::GoUp() const
{
    int newBoard = cells - pow(10, (11 - null_pos)) * (getDigit(cells, 11 - null_pos) - 9) + pow(10, (8 - null_pos)) * (getDigit(cells, 11 - null_pos) - 9);
    short newNull = null_pos - 3;
    vector<char> newWay = way;
    newWay.push_back('U');
    CBoard board(newBoard, newNull, newWay);
    return board;
}

bool CBoard::CanRight() const
{
    if (null_pos != 2 && null_pos != 5 && null_pos != 8)
        return true;
    else
        return false;
}

bool CBoard::CanLeft() const
{
    if (null_pos != 0 && null_pos != 3 && null_pos != 6)
        return true;
    else
        return false;
}

bool CBoard::CanUp() const
{
    if (null_pos != 0 && null_pos != 1 && null_pos != 2)
        return true;
    else
        return false;
}

bool CBoard::CanDown() const
{
    if (null_pos != 6 && null_pos != 7 && null_pos != 8)
        return true;
    else
        return false;
}



bool correct(int cells)
{
    vector<short> beginState;
    beginState.resize(9);
    for (int i = 0; i < 9; ++i)
    {
        beginState[8 - i] = cells % 10;
        cells = cells / 10;
    }
    int current_num_nine;
    for (int i = 0; i < 9; ++i)
    {
        if (beginState[i] == 9)
            current_num_nine = i;
    }
    int correct = 0;
    for (int i = 0; i < 9; ++i)
        for (int j = i; j < 9; ++j) {
            if ((beginState[i] > beginState[j])) {
                correct += 1;
            }
        }
    correct += current_num_nine;
    if (correct % 2 == 0)
        return true;
    return false;
}

CBoard Bfs(CBoard& board)
{
    CBoard newBoard;
    queue<CBoard> q;
    unordered_set<int> s;
    q.push(board);
    while (!q.empty())
    {
        board = q.front();
        q.pop();
        if (board.CanRight())
        {
            newBoard = board.GoRight();
            if (!s.count(newBoard.GetCells()))
            {
                if (newBoard.GetCells() == 123456789)
                    return newBoard;
                q.push(newBoard);
                s.insert(newBoard.GetCells());
            }
        }
        if (board.CanLeft())
        {
            newBoard = board.GoLeft();
            if (!s.count(newBoard.GetCells()))
            {
                if (newBoard.GetCells() == 123456789)
                    return newBoard;
                q.push(newBoard);
                s.insert(newBoard.GetCells());
            }
        }
        if (board.CanDown())
        {
            newBoard = board.GoDown();
            if (!s.count(newBoard.GetCells()))
            {
                if (newBoard.GetCells() == 123456789)
                    return newBoard;
                q.push(newBoard);
                s.insert(newBoard.GetCells());
            }
        }
        if (board.CanUp())
        {
            newBoard = board.GoUp();
            if (!s.count(newBoard.GetCells()))
            {
                if (newBoard.GetCells() == 123456789)
                    return newBoard;
                q.push(newBoard);
                s.insert(newBoard.GetCells());
            }
        }
    }
}

short Solution(CBoard& board, vector<char>& ans)
{
    if (!correct(board.GetCells()))
        return -1;
    board = Bfs(board);
    for (int i = 0; i < board.GetWay().size(); ++i)
        ans.push_back(board.GetWay()[i]);
    return board.GetCount();
}



int main()
{
    ifstream inp("puzzle.in");
    ofstream out("puzzle.out");
    CBoard board;
    int input = 0;
    short a, null_pos;
    for (int i = 0; i < 9; ++i)
    {
        inp >> a;
        if (a == 0)
        {
            a = 9;
            null_pos = i;
        }
        input = input * 10 + a;
    }

    board.FillBoard(input, null_pos);
    vector<char> ans;
    out << Solution(board, ans) << endl;
    for (int i = 0; i < ans.size(); ++i)
        out << ans[i];

    inp.close();
    out.close();
    return 0;
}