#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

int nivel[40], marc[40];
vector<int> exig_por[40];
vector<string> resp;
string a, b, c;
map<string, int> num;
map<int, string> nome;

void dfs(int x){
     marc[x]=1;
     resp.push_back(nome[x]);
     for(int p=0; p<exig_por[x].size( ); p++){
           int k=exig_por[x][p];
           nivel[k]--;
           if(nivel[k]==0 && marc[k]!=1) dfs(k);
     }
}

int main( ){
    int n, r=1;
    while(1){
        scanf("%d", &n);
        if(n==0) break;
        for(int i=0; i<n; i++){
            cin >> a;
            num[a]=i;
            nome[i]=a;
            if(!exig_por[i].empty( )) exig_por[i].clear( );
        }
        for(int i=0; i<n; i++){
            cin >> b;
            scanf("%d", &nivel[num[b]]);
            for(int j=0; j<nivel[num[b]]; j++){
                 cin >> c;
                 exig_por[num[c]].push_back(num[b]);
            }
        }
        for(int i=0; i<n; i++) if(nivel[i]==0 && marc[i]!=1) dfs(i);
        printf("Teste %d\n", r++);
        if(resp.size( )!=n) printf("impossivel");
        else{
            for(int i=0; i<resp.size( ); i++){
                  cout << resp[i] << " ";
            }
        }
        cout << "\n\n";
        num.clear( );
        nome.clear( );
        memset(marc, 0, sizeof marc);
        if(!resp.empty( )) resp.clear( );
    }
    return 0;
}
