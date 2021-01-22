#include <bits/stdc++.h>


using namespace std;

int main()
{
	int N, K, arr[100];
	vector<float> v;
	
	while(scanf("%d %d", &N, &K) != EOF)
	{
	    for (int i = 0; i < N; i++)
		    scanf("%d", &arr[i]);
	    
	    for (int i = 0; i < N; i++)
		    for (int j = i + 1; j < N; j++)
			    for (int k = j + 1; k < N; k++)
				    v.push_back((float)(arr[i] + arr[j] + arr[k])/3);
	    sort(v.begin(), v.end());
	    printf("%.1f\n", *(v.end() - K));
		v.clear();
	}
	
	return 0;
}
