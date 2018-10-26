#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>
#include <climits>
using namespace std;

#define INF INT_MAX
const int MAXM = 10000;
int YT[MAXM][MAXM], n, m;
int kase, op;
int a[MAXM], sz;
int min_v;

void YTprint(int op)
{
	if(op == 1){
		printf("Insert ");
		for(int i = 0; i < sz; i++) printf("%d%c", a[i], (i==sz-1)?'\n':' ');
	}else{
		printf("Extract-min %d\n", min_v);
	}
	for(int i = 0 ; i < n; i++)for(int j = 0; j < m ; j++){
		if(YT[i][j] == INF) printf("x");
		else printf("%d", YT[i][j]);
		printf("%c", (j==m-1)?'\n':' ');
	}
}

void YTinit()
{
	string tmp;
	n = 0;
	while(1)
	{
	    if(cin.peek() == '\n') break;
	    m = 0;
	    while(cin >> tmp)
	    {
	        if(tmp == string("x")) YT[n][m++] = INF;
	        else YT[n][m++] = stoi(tmp);
	        if(getchar() == '\n'){
	            n++;
	            break;
	        }
	    }
		//printf("%d %d\n", n, m);
	}
	//YTprint(op);
}

void YTinsert(int x)
{
	int i, j, ti, tj;
	i = n - 1;
	for(j = 0 ; j < m ; j++ ) if(YT[i][j] == INF) {
		YT[i][j] = x;
		break;
	}
	while(1)
	{
		ti = i, tj = j;
		if(i > 0 && YT[i-1][j] > YT[i][j]) ti = i-1;
		if(j > 0 && YT[i][j-1] > YT[ti][j]) tj = j-1, ti = i;
		if(i == ti && j == tj) return;
		int tmp = YT[i][j];
		YT[i][j] = YT[ti][tj];
		YT[ti][tj] = tmp;
		i = ti, j = tj;
	}
}

void YTerase()
{
	int i, j, ti, tj;
	i = n - 1;
	min_v = YT[0][0];
	for(j = 0 ; j < m ; j++ ) if(YT[i][j] == INF) {
		YT[0][0] = YT[i][j-1];
		YT[i][j-1] = INF;
	}

	i = 0, j = 0;
	while(1)
	{
		ti = i, tj = j;
		if(i+1 < n && YT[i+1][j] < YT[i][j]) ti = i+1;
		if(j+1 < m && YT[i][j+1] < YT[ti][j]) tj = j+1, ti = i;
		if(i == ti && j == tj) return;
		int tmp = YT[i][j];
		YT[i][j] = YT[ti][tj];
		YT[ti][tj] = tmp;
		i = ti, j = tj;
	}
}

int main()
{
	scanf("%d", &kase);
	while(kase--)
	{
		scanf("%d", &op);
		string line;
		getline(cin, line); // remove \n
		if(op == 1)
		{
			getline(cin, line);
			istringstream iss(line);
			sz = 0;
			while (iss >> a[sz++]) {}
			--sz; //remove \n
			//for(int i = 0; i < sz; i++) cout << a[i] << ((i == sz-1) ? '\n' : ' ');
			YTinit();
			for(int i = 0 ; i < sz ; i++) YTinsert(a[i]);
		} else {
			YTinit();
			YTerase();
		}
		YTprint(op);
		cout << endl;
	}
}

/*
2 
1 
6 7 
2 3 12 14
4 8 16 x
5 9 x x
x x x x

2
2 3 12 14
4 8 16 x
5 9 x x
x x x x
*/
