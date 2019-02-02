#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
using namespace std;


class CBoard {
public:
	explicit CBoard() {}
	CBoard(vector<short> _cells, short _null_pos) :
		cells(_cells),
		null_pos(_null_pos) {}
	CBoard(vector<short> _cells, short _null_pos, vector<char> _way) :
		cells(_cells),
		null_pos(_null_pos),
		way(_way) {}
	~CBoard() {}

	short GetNull() { return null_pos; }
	short GetCount() { return way.size(); }
	vector<short> GetCells() { return cells; }
	vector<char> GetWay() { return way; }

	bool operator<(const CBoard& board) const { return false; }
	bool operator>(const CBoard& board) const { return false; }
	bool operator==(const CBoard& board) const { return false; }
	bool operator!=(const CBoard& board) const { return false; }

	CBoard GoRight() const;
	CBoard GoLeft() const;
	CBoard GoUp() const;
	CBoard GoDown() const;

	bool CanRight() const;
	bool CanLeft() const;
	bool CanUp() const;
	bool CanDown() const;

private:
	vector<short> cells;
	short null_pos;
	vector<char> way;
};

CBoard CBoard::GoRight() const
{
	vector<short> newBoard = cells;
	swap(newBoard[null_pos], newBoard[null_pos + 1]);
	short newNull = null_pos + 1;
	vector<char> newWay = this->way;
	newWay.push_back('L');
	CBoard board(newBoard, newNull, newWay);
	return board;
}

CBoard CBoard::GoLeft() const
{
	vector<short> newBoard = cells;
	swap(newBoard[null_pos], newBoard[null_pos - 1]);
	short newNull = null_pos - 1;
	vector<char> newWay = this->way;
	newWay.push_back('R');
	CBoard board(newBoard, newNull, newWay);
	return board;
}

CBoard CBoard::GoDown() const
{
	vector<short> newBoard = cells;
	swap(newBoard[null_pos], newBoard[null_pos + 4]);
	short newNull = null_pos + 4;
	vector<char> newWay = this->way;
	newWay.push_back('U');
	CBoard board(newBoard, newNull, newWay);
	return board;
}

CBoard CBoard::GoUp() const
{
	vector<short> newBoard = cells;
	swap(newBoard[null_pos], newBoard[null_pos - 4]);
	short newNull = null_pos - 4;
	vector<char> newWay = this->way;
	newWay.push_back('D');
	CBoard board(newBoard, newNull, newWay);
	return board;
}

bool CBoard::CanRight() const
{
	if (null_pos != 3 && null_pos != 7 && null_pos != 11 && null_pos != 15)
		return true;
	else
		return false;
}

bool CBoard::CanLeft() const
{
	if (null_pos != 0 && null_pos != 4 && null_pos != 8 && null_pos != 12)
		return true;
	else
		return false;
}

bool CBoard::CanUp() const
{
	if (null_pos != 0 && null_pos != 1 && null_pos != 2 && null_pos != 3)
		return true;
	else
		return false;
}

bool CBoard::CanDown() const
{
	if (null_pos != 12 && null_pos != 13 && null_pos != 14 && null_pos != 15)
		return true;
	else
		return false;
}

bool Win(CBoard& board)
{
	vector<short> cells = board.GetCells();
	for (int i = 0; i < 16; ++i)
		if (cells[i] != i + 1)
			return false;
	return true;
}

bool correct(CBoard& board)
{
	vector<short> beginState = board.GetCells();
	int correct = board.GetNull() / 4 + 1;
	for (int i = 0; i < 16; ++i)
		for (int j = i; j < 16; ++j)
			if ((beginState[i] > beginState[j]) || j == board.GetNull()) 
				correct++;
	1 + 1;
	if (correct % 2 == 0)
		return true;
	return false;
}

int Heuristic(CBoard& board)
{
	vector<short> cells = board.GetCells();
	vector <pair<int, int> > pos(16);
	for (int i = 0; i < 16; ++i)
		pos[cells[i] % 16] = pair<int, int>(i / 4, i % 4);
	int s = 0;
	for (int i = 1; i < 16; ++i)
		s += abs(pos[i].first - (i - 1) / 4) + abs(pos[i].second - (i - 1) % 4);
	return -s - board.GetCount();
}

CBoard Bfs(CBoard& board)
{
	CBoard newBoard;
	priority_queue<pair<int, CBoard> > q;
	set<vector<short> > s;
	q.push(pair<int, CBoard>(Heuristic(board), board));
	while (!q.empty())
	{
		if (q.size() > 15000)
		{
			priority_queue<pair<int, CBoard> > qeq;
			for (int i = 0; i < 4000; ++i)
			{
				qeq.push(q.top());
				q.pop();
			}
			q = qeq;
		}
		board = q.top().second;
		q.pop();
		if (board.CanRight())
		{
			newBoard = board.GoRight();
			if (!s.count(newBoard.GetCells()))
			{
				if (Win(newBoard))
					return newBoard;
				q.push(pair<int, CBoard>(Heuristic(newBoard), newBoard));
				s.insert(newBoard.GetCells());
			}
		}
		if (board.CanLeft())
		{
			newBoard = board.GoLeft();
			if (!s.count(newBoard.GetCells()))
			{
				if (Win(newBoard))
					return newBoard;
				q.push(pair<int, CBoard>(Heuristic(newBoard), newBoard));
				s.insert(newBoard.GetCells());
			}
		}
		if (board.CanDown())
		{
			newBoard = board.GoDown();
			if (!s.count(newBoard.GetCells()))
			{
				if (Win(newBoard))
					return newBoard;
				q.push(pair<int, CBoard>(Heuristic(newBoard), newBoard));
				s.insert(newBoard.GetCells());
			}
		}
		if (board.CanUp())
		{
			newBoard = board.GoUp();
			if (!s.count(newBoard.GetCells()))
			{
				if (Win(newBoard))
					return newBoard;
				q.push(pair<int, CBoard>(Heuristic(newBoard), newBoard));
				s.insert(newBoard.GetCells());
			}
		}
	}
}

short Solution(CBoard& board, vector<char>& ans)
{
	if (!correct(board))
		return -1;
	if (Heuristic(board) == 0)
		return 0;
	board = Bfs(board);
	for (int i = 0; i < board.GetWay().size(); ++i)
		ans.push_back(board.GetWay()[i]);
	return board.GetCount();
}



int main()
{
	ifstream inp("input.txt");
	ofstream out("output.txt");
	vector<short> input(16);
	short a, null_pos;
	for (int i = 0; i < 16; ++i)
	{
		inp >> a;
		if (a == 0)
		{
			a = 16;
			null_pos = i;
		}
		input[i] = a;
	}
	CBoard board(input, null_pos);

	vector<char> ans;
	out << Solution(board, ans) << endl;
	for (int i = 0; i < (int)ans.size(); ++i)
		out << ans[i];

	inp.close();
	out.close();
	return 0;
}