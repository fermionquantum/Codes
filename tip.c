#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// auxliary function to maipulate HEAP properties
#define father(i) ((i-1)/2)
#define left(i) (2*i+1)
#define right(i) (2*i+2)

#define MAX 1000 // Maximun elements in FILE

typedef struct heap {
   int *inf;   // node pointer
   int nelem;  // number of elements in HEAP
   int tmax;   // max number of elements in HEAP
} Heap;
/*-------------------------------------------------------*/
void swap(int *x, int *y) //auxiliary function: exchange pointers
{
   int aux;
   aux = *x;
   *x = *y;
   *y = aux;
}
/*-------------------------------------------------------*/
Heap * createMinHeap(int tmax) // HEAP inicialization
{
   Heap * H = (Heap*)calloc(1,sizeof(Heap));

   H->tmax = tmax;
   H->nelem = 0;
   H->inf = (int*)calloc(H->tmax,sizeof(int));
}
/*-------------------------------------------------------*/
int emptyHeap(Heap * H)
{
   if(H->nelem <= 0)
      return 1;
   else
      return 0;
}
/*-------------------------------------------------------*/
int fullHeap(Heap *H)
{
   if(H->nelem >= H->tmax)
      return 1;
   else
      return 0;
}
/*-------------------------------------------------------*/
void freeMemory(Heap **H)
{
   free((*H)->inf);
   free(*H);
   *H = NULL;
}
/*-------------------------------------------------------*/
void downMinHeap(Heap * H, int i)  // HEAPFY i-th element to down
{
   int smaller, lef, rig;

   lef = left(i);
   rig = right(i);

   if((lef < H->nelem) && (H->inf[lef]) < H->inf[i])
      smaller = lef;
   else
      smaller = i;

   if((rig < H->nelem) && (H->inf[rig] < H->inf[smaller]))
      smaller = rig;

   if(smaller != i)
   {
      swap(&H->inf[i],&H->inf[smaller]);
      downMinHeap(H, smaller);
   }
}
/*-------------------------------------------------------*/
void upMinHeap(Heap * H, int i) // HEAPFY i-th element to up
{
   int dad;

   dad = father(i);

   while((dad >=0) && (H->inf[dad] > H->inf[i]))
   {
      swap(&H->inf[i], &H->inf[dad]);
      i = dad;
      dad = father(i);
   }
}
/*-------------------------------------------------------*/
void insertMinHeap(Heap * H, int i) // insetiotn to HEAPFY
{
   if(!fullHeap(H))
   {
      H->nelem += 1;
      H->inf[H->nelem-1] = i;
      upMinHeap(H, H->nelem-1);
   }
}
/*-------------------------------------------------------*/
int removeMinHeap(Heap *H) // remotion to HEAPFY
{
   int aux;

   if(!emptyHeap(H))
   {
      aux = H->inf[0];
      H->inf[0] = H->inf[H->nelem-1];
      H->nelem--;
      downMinHeap(H,0);
   }
   return aux;
}
/*-------------------------------------------------------*/
void readArq(char *arqName, Heap *H) // reading from archive and inserting in min HEAP
{
   FILE *arq;
   int num;

   arq = fopen(arqName, "r");
   if(arq == NULL) printf("ERROR_readArq");

   while(fscanf(arq,"%d",&num) != EOF)
      insertMinHeap(H,num);

   fclose(arq);
}
/*-------------------------------------------------------*/
void saveArq(char *arqName, Heap *H) // writing in the new archive from the min HEAP
{
   FILE *arq;
   int out;

   arq = fopen(arqName, "w");
   if(arq == NULL) printf("ERRO_saveArq");

   while(!emptyHeap(H))
   {
      out = removeMinHeap(H); // The min HEAP always ensure the min from the readArq function
      fprintf(arq, "%d\n", out);
   }
   fclose(arq);
}
/*-------------------------------------------------------*/
int main()
{
   Heap *H = NULL;
   char arqName[50], outputName[50];
   H = createMinHeap(MAX);

   printf("Insert Input Archive Name: ");
   scanf("%s", arqName);

   readArq(arqName, H); // Worst case time: O(log n)

   printf("Create Output Archive Name: ");
   scanf("%s", outputName);

   saveArq(outputName, H); // Worst case time: O(log n)

   freeMemory(&H);

   return 0;
}
