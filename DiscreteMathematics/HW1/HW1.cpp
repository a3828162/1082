#include<iostream>
#include<algorithm>
using namespace std;

void determine(bool ch[],int vh[],int** path,int max,int path2,int dote)
{
	if (dote == path2)
		return;

	for (int i = 0; i < path2; i++)
	{
		if ((max == path[i][0] || max == path[i][1]) && ch[i] == false)
		{
			ch[i] = true;
			int a = 0;
			if (max == path[i][0])
				a = path[i][1];
			else
				a = path[i][0];
			vh[path[i][0]]++, vh[path[i][1]]++;
			dote++;
			determine(ch, vh, path, a, path2, dote);
		}
	}
}

bool decide(int vh[], int node)
{
	for (int i = 0; i < node; i++)
		if (vh[i] == 0)
			return false;

	return true;
}

int main() {
	int line;
	cin >> line;
	int* lines = new int[line]();
	for (int i = 0; i < line; i++)
	{
		int node, path;
		cin >> node;
		cin >> path;
		int* nodes = new int[node]();
		int** paths = new int* [path]();
		for (int j = 0; j < path; j++)
			paths[j] = new int[2]();
		for (int j = 0; j < path; j++)
		{
			cin >> paths[j][0] >> paths[j][1];
			nodes[paths[j][0]]++, nodes[paths[j][1]]++;
		}

		int max = 0;
		for (int x = 0; x < node; x++)
			if (nodes[x] > max)
				max = x;
		bool* ch = new bool[path]();
		int* vh = new int[node]();
		int dote = 0;

		determine(ch, vh, paths, max, path, dote);

		if (decide(vh, node))
			lines[i] = 1;
		else
			lines[i] = 0;
			
		delete[]nodes;
		for (int j = 0; j < path; j++)
			delete[]paths[j];
		delete[]paths;
		delete[]ch;
		delete[]vh;
	}


	for (int i = 0; i < line; i++)
	{
		if (lines[i])
			cout << "connected" << endl;
		else
			cout << "disconnected" << endl;
	}
	delete[]lines;

	return 0;
}