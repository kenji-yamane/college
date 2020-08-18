/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 1: Torre de Controle  */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Agosto de 2019      */
    
/*  Programa compilado com o compilador g++ e a flag -fsanitize=leak,address,undefined*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct list
{
    int flight_number;
    char origin[32];
    bool urgency;
    struct list *next;
};

typedef struct list linked_list;

/*--------------------------------------------------*/
linked_list *new_list()
{
    return NULL;
}

/*--------------------------------------------------*/
//node creation
linked_list *create_node(int flight_number, char origin[], bool urgency, linked_list *next)
{
    linked_list *l = (linked_list*)malloc(sizeof(linked_list));
    
    if (l != NULL) //if there is enough memory
    {
        //set the parameters to the node
        l->flight_number = flight_number;
        strcpy(l->origin, origin);
        l->urgency = urgency;
        l->next = next;
    }
    
    return l;
}

/*--------------------------------------------------*/
//inserts a node in the end of the queue
linked_list *push(linked_list *l, int flight_number, char origin[], bool urgency)
{
    if (l == NULL)
        l = create_node(flight_number, origin, urgency, NULL);
    else
    {
        linked_list *aux = l;
        
        //reaching the end of my list
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = create_node(flight_number, origin, urgency, NULL);
    }
    
    return l;
}

/*--------------------------------------------------*/
//removes a node from the top of the queue
linked_list *pop(linked_list *l, FILE *s)
{
    //checking if the queue is empty
    if (l == NULL)
        fprintf(s, "0000    Nenhum aviao pousando\n");
    else //if the queue isn't empty
    {
        fprintf(s, "%.4d    %s", l->flight_number, l->origin);
        
        linked_list *aux = l;
        l = l->next;
        free(aux);
    }
    
    return l;
}

/*--------------------------------------------------*/
//reallocates a node to the first position of the queue not in urgency
linked_list *urgency_request(linked_list *l, int flight_number)
{
    linked_list *to_replace = l;
    linked_list *urge = l;
    linked_list *prior_to_urge;
    linked_list *prior_to_replace = NULL;
    
    //urge is going to point to the plane which made the distress call
    while (urge->flight_number != flight_number)
    {
        prior_to_urge = urge;
        urge = urge->next;
    }
    /*if the plane had already made a distress call,  */
    /*or if it is already the first in the queue,     */
    /*nothing is to be changed                        */
    if (urge->urgency == false && l != urge)
    {
        //remove urge from the list
        prior_to_urge->next = urge->next;
        
        //to_replace is the first element of the list not marked as urgent
        while (to_replace != NULL && to_replace->urgency == true)
        {
            prior_to_replace = to_replace;
            to_replace = to_replace->next;
        }
        //inserts urge right before to_replace
        urge->next = to_replace;
        if (prior_to_replace != NULL)    //if the one to replace isn't the first in the list
            prior_to_replace->next = urge;
        else                             //if the one to replace is
            l = urge;
    }
    urge->urgency = true;
    return l;
}

/*--------------------------------------------------*/
//frees the queue and shows the final situation of it
void delete_list(linked_list *l, FILE *s)
{
    linked_list *aux;
    
    while (l != NULL)
    {
        //showing the situation of the queue
        fprintf(s, "%.4d    %s", l->flight_number, l->origin);
        aux = l;
        l = l->next;
        free(aux);
    }
}

/*--------------------------------------------------*/
int main()
{
    FILE *e = fopen("entrada1.txt", "r");
    FILE *s = fopen("kenjiyamane1.txt", "w");
    
    linked_list *l = new_list();
    char command[16], origin[32], phrase[72];
    int flight_number;
    bool end = false;
    
    //first 7 lines of input which won't be processed
    for (int i = 0; i < 7; i++)
        fgets(phrase, 72, e);
    //first 4 lines wich shows stars forming a parabola
    for (int i = 0; i < 4; i++)
        fprintf(s, "%*c\n", (i + 1)*(i + 1)*2, '*');
    fprintf(s, "FLIGHT FROM\n\n");
    while (end == false)
    {
        fscanf(e, "%s %d ", command, &flight_number);
        fgets(origin, 32, e);
        
        //analyzing which command was demanded
        if (strcmp(command, "pede_pouso") == 0)
            l = push(l, flight_number, origin, false);
        else if (strcmp(command, "pista_liberada") == 0)
            l = pop(l, s);
        else if (strcmp(command, "URGENCIA") == 0)
            l = urgency_request(l, flight_number);
        else if (strcmp(command, "FIM") == 0)
            end = true;
    }
    fprintf(s, "\nSituacao da fila\n\n");
    if (l == NULL) //in case the queue is empty
        fprintf(s, "Sundjerbob kokalone!!\n");
    else
        delete_list(l, s);
    
    fclose(e);
    fclose(s);
    return 0;
}
