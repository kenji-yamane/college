#include <bits/stdc++.h>


using namespace std;

//construindo o tabuleiro coluna a coluna
int test_case;

bool valid_queen(vector<pair<int, int> > &queens, int row, int column)
{
	pair<int, int> difference_vector;
	for (int i = 0; i < (int)queens.size(); i++)
	{
		difference_vector.first = abs(queens[i].first - row);
		difference_vector.second = abs(queens[i].second - column);
		if (difference_vector.first == difference_vector.second) //diagonal
			return false;
		else if (!difference_vector.first || !difference_vector.second) //row|column
			return false;
	}
	
	return true;
}

void build_board(vector<pair<int, int> > &queens, int column)
{
	if (queens.front().second == column) build_board(queens, column + 1);
	if (column == 8)
	{
		int answer[8];
		for (int i = 0; i < (int)queens.size(); i++)
			answer[queens[i].second] = queens[i].first;
		
		printf("%2d      ", ++test_case);
		for (int i = 0; i < 8; i++)
			printf("%d%c", answer[i] + 1, i == 7 ? '\n' : ' ');
	}
	
	for (int i = 0; i < 8; i++)
		if (valid_queen(queens, i, column))
		{
			queens.push_back(make_pair(i, column));
			build_board(queens, column + 1);
			queens.pop_back();
		}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int datasets, row, column;
	vector<pair<int, int> > queens;	
	
	cin >> datasets;
	while (datasets--)
	{
		test_case = 0;
		cin >> row >> column;
		queens.push_back(make_pair(row - 1, column - 1));
		printf("SOLN       COLUMN\n");
		printf(" #      1 2 3 4 5 6 7 8\n\n");
		build_board(queens, 0);
		queens.pop_back();
		if (datasets) printf("\n");
	}
	
	return 0;
}
