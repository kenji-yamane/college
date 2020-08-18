/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>
#include <stdlib.h>


void Follow(int **maze, int *N, int x, int y, int parameter)
{
    maze[x][y] = parameter + 1;
    
    if (parameter == 2)
        printf("%d %d\n", x, y);
    
    if (maze[*N - 1][*N - 1] == parameter && x + 1 < *N && maze[x + 1][y] == parameter)
        Follow(maze, N, x + 1, y, parameter);
    if (maze[*N - 1][*N - 1] == parameter && y + 1 < *N && maze[x][y + 1] == parameter)
        Follow(maze, N, x, y + 1, parameter);
    if (maze[*N - 1][*N - 1] == parameter && y - 1 >= 0 && maze[x][y - 1] == parameter)
        Follow(maze, N, x, y - 1, parameter);
    if (maze[*N - 1][*N - 1] == parameter && x - 1 >= 0 && maze[x - 1][y] == parameter)
        Follow(maze, N, x - 1, y, parameter);
        
    if (maze[*N - 1][*N - 1] != parameter)
    {
        maze[x][y] = parameter + 2;
    }
}

int main()
{
    int N, i, j;
    int *aux = (int*)malloc(sizeof(int));
    int **maze;
    
    if (scanf("%d", &N) != 1)
        exit(-1);
    
    *aux = N;
    maze = (int**)malloc(N*sizeof(int*));
    for (i = 0; i < N; i++)
        maze[i] = (int*)malloc(N*sizeof(int));
        
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            scanf("%d", (*(maze + i) + j));
            
    Follow(maze, aux, 0, 0, 0);
    Follow(maze, aux, 0, 0, 2);
        
    for (i = 0; i < N; i++)
        free(maze[i]);
    free(maze);
    free(aux);
    
    return 0;
}
