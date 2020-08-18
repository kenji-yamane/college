/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 5: Livro              */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Outubro de 2019      */
    
/*  Programa compilado com Code::Blocks 17.12*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>


//--------------------------------------------------
//    node's structure
//--------------------------------------------------

struct tree
{
    char name[21];
    struct tree *father;
    struct tree *son;
    struct tree *brother;
};

typedef struct tree tree;

//--------------------------------------------------
//    TRACES
//--------------------------------------------------

//simply creates a line with 50 hyphens
void traces(FILE *s)
{
    for (int i = 0; i < 50; i++)
        fprintf(s, "-");
    fprintf(s, "\n");
}

//--------------------------------------------------
//    NOT_FOUND
//--------------------------------------------------

//emits message correpondent to an item not being found
void not_found(FILE *s, char reference[])
{
    fprintf(s, "ERRO: nao encontrado item %s\n", reference);
    traces(s);
}

//--------------------------------------------------
//    CREATE_TITLE
//--------------------------------------------------

//creates a root
//if there already exists one, it is created on top of the old one
tree *create_title(tree *t, char command[])
{
    //allocates in heap
    tree *new_node = (tree*)malloc(sizeof(tree));
    
    //sets the parameters
    strcpy(new_node->name, command);
    new_node->father = NULL; //it is a root, so no father
    new_node->son = t; //put on top of the old one
    new_node->brother = NULL; //it is a root, so no brother
    
    return new_node;
}

//--------------------------------------------------
//    SEARCH
//--------------------------------------------------

//searches name in the tree, and inserts the found node in find
void search(tree *t, char name[], tree **find)
{
    if (t != NULL && *find == NULL)
    {
        if (strcmp(t->name, name) == 0) //it was found
            *find = t;
        else //if it wasn't found
        {
            search(t->son, name, find); //searches the sub-tree below it
            search(t->brother, name, find); //searches the other sub-trees
        }
    }
}

//--------------------------------------------------
//    INSERT_SECTION
//--------------------------------------------------

//inserts a new node of name new_name
void insert_section(tree *t, char new_name[], char command[])
{
    //allocates in heap
    tree *new_node = (tree*)malloc(sizeof(tree));
    strcpy(new_node->name, new_name);
    
    if (strcmp(command, "SUB") == 0) //inserted as the greatest son
    {
        new_node->father = t; //it is below t
        new_node->son = NULL; //created initially with no son
        new_node->brother = t->son; //it is greater than the original greatest son
        t->son = new_node; //it is now the greatest son
    }
    else if (strcmp(command, "SEGUINTE_A") == 0) //put after t, as a son of t's father
    {
        new_node->father = t->father; //its father is t's father
        new_node->son = NULL; //created initially with no son
        new_node->brother = t->brother; //t's younger brother is now new node's younger brother
        t->brother = new_node; //new node is now t's younger brother
    }
}

//--------------------------------------------------
//    PRINT_BOOK
//--------------------------------------------------

//prints an indented and indexed representation of the tree
void print_book(tree *t, FILE *s, int depth, int index[])
{
    if (t != NULL)
    {
        //nullifies the indexes of levels that we may visit in pre-ordum
        for (int i = depth; i < 10; i++)
            index[i] = 0;
        //counts how many times we've accessed a given set of sons
        if (depth > 0)
            index[depth - 1]++;
        //prints the indexes of the node's lineage
        for (int i = 0; i < depth; i++)
            fprintf(s, "%d.", index[i]);
        
        //prints the info in pre-ordum
        fprintf(s, "      %s\n", t->name);
        print_book(t->son, s, depth + 1, index);
        print_book(t->brother, s, depth, index);
    }
}

//--------------------------------------------------
//    DELETE_BOOK
//--------------------------------------------------

//frees the memory allocated in heap
void delete_book(tree *t)
{
    if (t != NULL)
    {
        //pos-ordum style
        delete_book(t->son);
        delete_book(t->brother);
        free(t);
    }
}

//--------------------------------------------------
//    REMOVE_SECTION
//--------------------------------------------------

//removes a given branch t of the tree
void remove_section(tree *t)
{
    //if it isn't root, then the pointers have to be rectified
    tree *father = t->father;
    
    if (father != NULL && father->son == t) //if it is the greatest son
        father->son = t->brother; //it isn't anymore
    else if (father != NULL) //if it isn't the greatest son
    {
        //the brother before it now points to the brother after it
        tree *brother = father->son;
        while (brother->brother != t)
            brother = brother->brother;
        brother->brother = t->brother;
    }
    
    //now with the pointers rectified, frees the branch
    delete_book(t->son);
    free(t);
}

//--------------------------------------------------
//    TRANSFER_SECTION
//--------------------------------------------------

//moves a branch from a "from" position to a "to" position
void transfer_section(tree *from, tree *to, char command[])
{
    //rectifing the points for removal
    tree *father = from->father;
    
    if (father != NULL && father->son == from) //if it is the greatest son
        father->son = from->brother; //it isn't anymore
    else if (father != NULL) //if it isn't the greatest son
    {
        //the brother before it points to the brother after it
        tree *brother = father->son;
        while (brother->brother != from)
            brother = brother->brother;
        brother->brother = from->brother;
    }
    
    if (strcmp(command, "SUB") == 0) //below to
    {
        from->father = to; //to is from's father
        from->brother = to->son;
        to->son = from; //from is to's greatest son
    }
    else if (strcmp(command, "SEGUINTE_A") == 0) //after to
    {
        from->father = to->father; //from and to have the same father
        from->brother = to->brother;
        to->brother = from; //from is to's brother
    }
}

void buscaEmLargura(tree *t)
{
    std::queue<tree*> fila;
    
    fila.push(t);
    
    while (!fila.empty())
    {
        if (fila.front()->son != NULL)
        {
            tree *aux = fila.front()->son;
            
            while (aux != NULL)
            {
                fila.push(aux);
                aux = aux->brother;
            }
        }
        
        printf("%s\n", fila.front()->name);
        fila.pop();
    }
}

//--------------------------------------------------
//    MAIN
//--------------------------------------------------

int main()
{
    FILE *e = fopen(/*"C:\\Lab5\\*/"entrada5.txt", "r");
    FILE *s = fopen(/*"C:\\Lab5\\*/"kenjiyamane5.txt", "w");
    tree *t = NULL;
    int index[10], counter = 0;
    char phrase[72], command[15], new_name[21], reference[21];
    
    //first 4 lines won't be processed
    for (int i = 0; i < 4; i++)
        fgets(phrase, 72, e);
    
    //first 3 lines may contain anything
    fprintf(s, "Ow Joao Pedro\n");
    fprintf(s, "A solucao que eu imagino\n");
    fprintf(s, "seria trancar as portas\n");
    //fourth has traces
    traces(s);
    
    do
    {
        fscanf(e, " %s", command);
        
        if (strcmp(command, "TITULO") == 0)
        {
            fscanf(e, " %s", new_name);
            t = create_title(t, new_name); //insert new root
        }
        else if (strcmp(command, "INSERIR") == 0)
        {
            tree *find = NULL;
            fscanf(e, " %s %s %s", new_name, command, reference);
            
            search(t, reference, &find);
            if (find == NULL) //it isn't in the tree
                not_found(s, reference);
            else if (strcmp(command, "SEGUINTE_A") == 0 && find == t) //there is no "next" to root
            {
                fprintf(s, "ERRO: operacao invalida; o noh eh raiz\n");
                traces(s);
            }
            else //with no problems, insert
                insert_section(find, new_name, command);
        }
        else if (strcmp(command, "REMOVER") == 0)
        {
            tree *find = NULL;
            fscanf(e, " %s", reference);
            
            search(t, reference, &find);
            if (find == NULL) //it isn't in the tree
                not_found(s, reference);
            else
                remove_section(find); //with no problems, remove
            
            if (find == t) //if the whole tree was freed, rectify t's target
                t = NULL;
        }
        else if (strcmp(command, "TRANSFERIR") == 0)
        {
            tree *findA = NULL;
            tree *findB = NULL;
            fscanf(e, " %s %s %s", new_name, command, reference);
            
            search(t, new_name, &findA); //find to and from position
            search(t, reference, &findB);
            if (findA == NULL && findB == NULL) //one of them isn't there
            {
                strcat(reference, " nem ");
                strcat(reference, new_name);
                not_found(s, reference);
            }
            else if (findA == NULL) //one of them isn't there
                not_found(s, new_name);
            else if (findB == NULL) //one of them isn't there
                not_found(s, reference);
            else if (strcmp(command, "SEGUINTE_A") == 0 && findB == t) //there is no "next" to the root
            {
                fprintf(s, "ERRO: operacao invalida; o noh eh raiz\n");
                traces(s);
            }
            else //with no problems, transfer
                transfer_section(findA, findB, command);
        }
        else if (strcmp(command, "LISTA") == 0)
        {
            fprintf(s, "LISTA %d\n\n", ++counter);
            //sets index array
            memset(index, 0, sizeof(index));
            //print the tree
            print_book(t, s, 0, index);
            traces(s);
        }
        else if (strcmp(command, "FIM") != 0)
            buscaEmLargura(t);
    } while (strcmp(command, "FIM") != 0);
    
    delete_book(t);
    fclose(e);
    fclose(s);
    
    return 0;
}
