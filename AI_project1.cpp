//Jinhao Chen
#include <iostream>
using namespace std;

const int maxnum = 100;
const int maxint = 999999;


int dist[maxnum];     
int prev[maxnum];     
int c[maxnum][maxnum];   
int n, line;             
// n -- n nodes
// v -- the source node
// dist[] -- the distance from the ith node to the source node
// prev[] -- the previous node of the ith node
// c[][] -- every two nodes' distance
void Dijkstra(int n, int v, int *dist, int *prev, int c[maxnum][maxnum])
{
	bool s[maxnum];   
	for (int i = 1; i <= n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     
		if (dist[i] == maxint)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;

	for (int i = 2; i <= n; ++i)
	{
		int tmp = maxint;
		int u = v;
		for (int j = 1; j <= n; ++j)
			if ((!s[j]) && dist[j]<tmp)
			{
				u = j;              
				tmp = dist[j];
			}
		s[u] = 1;   

		for (int j = 1; j <= n; ++j)
			if ((!s[j]) && c[u][j]<maxint)
			{
				int newdist = dist[u] + c[u][j];
				if (newdist < dist[j])
				{
					dist[j] = newdist;
					prev[j] = u;
				}
			}
	}
}


void searchPath(int *prev, int v, int u)
{
	int que[maxnum];
	int tot = 1;
	que[tot] = u;
	tot++;
	int tmp = prev[u];
	while (tmp != v)
	{
		que[tot] = tmp;
		tot++;
		tmp = prev[tmp];
	}
	que[tot] = v;
	for (int i = tot; i >= 1; --i)
		if (i != 1)
			cout << que[i] << " -> ";
		else
			cout << que[i] << endl;
}

int main()
{

	int dist[maxnum];   
	int prev[maxnum];     
	int c[maxnum][maxnum];   
	int n, line;
	int vv[maxnum];
	
	cout << "please enter how many vertexs" << endl;

	cin >> n;

	for (int i = 1; i <= n; i++){
	cout << "please enter  vertexs " << i << endl;
	cin >> vv[i];

	}





	
	int pp, qq;
	int p, q, len;        
	int j, k;
	int ss, end;
	cout << "please enter which start vertex and end vertex" << endl;
	cin >> j >> k;
	for (int e = 1; e <= n; e++)
	{
			if (j == vv[e]) 
				ss = e;
			
		if (k == vv[e])
			end = e;

	}
	j= ss;
	k = end;
	
	cout << "please enter how many edge" << endl;
	cin >> line;
	



	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			c[i][j] = maxint;

	for (int i = 1; i <= line; ++i)
	{
		cout << " please enter vertex vertex edge_weight" << endl;
		cin >> p >> q >> len;
		for (int e = 1; e <= n; e++)
		{
			if (p == vv[e])
				pp = e;

			if (q == vv[e])
				qq = e;
		}
		
		
		c[pp][qq] = len;
	}

	for (int i = 1; i <= n; ++i)
		dist[i] = maxint;

	Dijkstra(n, j, dist, prev, c);

	cout << "the total distance(weight) is " << dist[n] << endl;


	cout << "the shortest path is ";
	searchPath(prev, j, k);
	for (int i = 1; i <= n; i++)
	{
		cout << " the number " << i << " is refer to vertex " << vv[i] << endl;
	}
	}