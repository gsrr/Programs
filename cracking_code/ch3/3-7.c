
/*
 * Animal Shelter 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


struct Animal
{
        int order;
        int tag;
};

typedef struct Animal Animal;

struct Queue
{
        Animal* ani;
        int front;
        int rear;
        int num;
};

typedef struct Queue Queue;


Queue* createQuene(int num)
{
        Queue* tmp = (Queue*)malloc(sizeof(Queue));
        tmp->ani = (Animal*)malloc(sizeof(Animal) * num);
        tmp->front = 0;
        tmp->rear = 0;
        tmp->num = num;
}


void enQueue(Queue** q, Animal ani)
{
        Queue* tmp = *q;
        int num = tmp->num;
        if((tmp->rear + 1) % num == tmp->front)
        {
                printf("Queue is Full\n");
                return;
        }
        tmp->ani[tmp->rear] = ani;
        tmp->rear += 1;
}

void initialQueue(Queue** q)
{
        sleep(1);
        srand(time(NULL));
        Queue* tmp = *q;
        int num = tmp->num;
        int i;
        for( i = 0 ; i < num ; i++)
        {
                int tag = rand() % 100;
                int order = rand() % 20;
                Animal ani;
                ani.order = order;
                ani.tag = tag;
                enQueue(q, ani);
                order = order + 1;
        }

}


int deQueue(Queue** q)
{
        Queue* tmp = *q;
        int num = tmp->num;
        if((tmp->front)%num == tmp->rear)
        {
                printf("Queue is empty\n");
                return;
        }
        Animal ani = tmp->ani[tmp->front];
        tmp->front += 1;
        return ani.tag;

}


void print_queue(Queue* q)
{
        int num = q->num;
        int i = q->front;
        for(i ; i%num != q->rear ; i++)
        {
                printf("tag:%d, order:%d\n", q->ani[i].tag, q->ani[i].order);
        }
}

void releaseQueue(Queue* q)
{
        Animal* a = q->ani;
        free(a);
        free(q);
}

struct Animals
{
        Queue* cq;
        Queue* dq;
};
typedef struct Animals Animals;


void releaseAnimals(Animals* anis)
{
        
        releaseQueue(anis-> cq);
        releaseQueue(anis-> dq);
        free(anis);
}

void deQueueCat(Animals** anis)
{
        Animals* tmp = *anis;
        Queue* cq = tmp->cq;
        printf("deQueueCat:%d\n",deQueue(&cq));
}
void deQueueDog(Animals** anis)
{
        Animals* tmp = *anis;
        Queue* dq = tmp->dq;
        printf("deQueueCat:%d\n",deQueue(&dq));

}

Animal watchItem(Queue* q)
{
        if(q->front == q->rear)
        {
                printf("Queue is empty\n");
        }
        return q->ani[q->front];
}

void deQueueAnimals(Animals** anis)
{
        Animals* tmp = *anis;
        Queue* cq = tmp->cq;
        Queue* dq = tmp->dq;
        Animal c = watchItem(cq);
        Animal d = watchItem(dq);
        if (c.order > d.order)
        {
                printf("deQueueAnimal from cat:%d\n",deQueue(&cq));
        }
        else
        {
                printf("deQueueAnimal from dog:%d\n",deQueue(&dq));
        }

}
int main()
{
        
        Queue* cq = createQuene(10);
        Queue* dq = createQuene(10);
        initialQueue(&cq);              
        initialQueue(&dq);      
        print_queue(cq);
        printf("\n");
        print_queue(dq);
        Animals* anis = (Animals*)malloc(sizeof(Animals));   
        anis->cq = cq;
        anis->dq = dq;     
        deQueueCat(&anis);
        deQueueDog(&anis);
        deQueueAnimals(&anis);
        return 0;
}

