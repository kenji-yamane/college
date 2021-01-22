#include <bits/stdc++.h>


using namespace std;

int main()
{
    int key[200];
    char aux;
    string phrase;
    
    for (int i = 0; i < 26; i++)
        scanf(" %c", &aux), key[(int)(i + 'a')] = aux;
    cin >> phrase;
    for (int i = 0; i < (int)phrase.size(); i++)
        printf("%c", key[(int)phrase[i]]);
    printf("\n");
    
    return 0;
}
