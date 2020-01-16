#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<math.h>

typedef struct Block {
  int block_size;           // # of bytes in the data section
  struct Block *next_block; // pointer to the next block
}Block;

//Function signatures
void my_initialize_heap(int size);
void* my_alloc(int size);
void my_free(void *data);
float standard_deviation(int arr[], int x); //actually calculates the standard deviation
//test cases(1 - 5) for program
void test1();
void test2();
void test3();
void test4();
void test5();
void sd(); //driver program for standard deviation problem

//Global Variables
int overhead_size = sizeof(Block*); // 8, overhead accounts for the block before each space of memory
Block *free_head;
int bufferLength = 1000;
int voidSize = sizeof(void*); //8

int main(){
  my_initialize_heap(bufferLength);
  // printf("Shifted address of freehead: %p\n", (free_head + sizeof(int) ) );
  // test1();
  //test2();
  //test3();
  // test4();
  //test5();
  sd();

  return 0;
}

void test1(){
  // TEST 1
  printf("Test 1\n\n");
  //  printf("Address of free head: %p", free_head);
  int *x = (int *)my_alloc(sizeof(int));
  printf("Overhead size: %d\n", overhead_size);
  printf("Size of int x in bytes: %d\n", sizeof(x));
  printf("Address of int x: %p\n\n",(void *) x);
  my_free(x);
  int *y = (int *)my_alloc(sizeof(int));
  printf("Size of int y in bytes: %d\n", sizeof(y));
  printf("Address of int y: %p\n\n",(void *) y);
  my_free(y);
}

void test2(){
  //TEST2
  printf("Test 2\n\n");
  int *x = (int*)my_alloc(sizeof(int));
  int *y = (int*)my_alloc(sizeof(int));
  printf("Address of x: %p\n", (void*)x);
  printf("Address of y: %p\n", (void*)y);
  my_free(x);
  my_free(y);
}

void test3(){
  //TEST 3
  printf("Test 3\n\n");
  printf("Size of double: %d\n", sizeof(double));
  int *x = (int*)my_alloc(sizeof(int));
  int *y = (int*)my_alloc(sizeof(int));
  int *z = (int*)my_alloc(sizeof(int));
  printf("Address of int x: %p\n", (void*)x);
  printf("Address of int y: %p\n", (void*)y);
  printf("Address of int z: %p\n", (void*)z);
  my_free(y);
  double *a = (double*)my_alloc(sizeof(double));
  printf("Address of double a: %p\n", (void*)a);
  my_free(a);
  my_free(x);
  my_free(z);
}

void test4(){
  //TEST 4
  printf("Test 4\n\n");
  int *x = (int*)my_alloc(sizeof(int));
  char *y = (int*)my_alloc(sizeof(char));
  printf("Address of int x: %p\n", (void*)x);
  printf("Address of char y: %p\n", (void*)y);
  my_free(x);
  my_free(y);
}

void test5(){
  //TEST 5
  printf("Test 5\n\n");
  // int *arr = (int*)my_alloc(100 * sizeof(int));
  // int *x = (int*)my_alloc(sizeof(int));
  // // int *arr = (int*)malloc(100 * sizeof(int));
  // // int *x = (int*)malloc(sizeof(int));
  // printf("Address of array: %p\n", (void*)arr);
  // printf("Address of int x: %p\n", (void*)x);
  // printf("Address of x - array: %p\n", (void*)(x - arr));
  int arr[100];
  int *x = my_alloc(sizeof(int));
  int xSize = x;
  int *y = my_alloc(sizeof(arr));
  int ySize = y;
  // int *x = my_alloc(sizeof(int));
  // int xSize = x;
  int diff = xSize - (100*sizeof(int) + overhead_size);
  printf("Address of freehead: %p\n", (void*)free_head);
  printf("Address of y(array): %p\n", (void*)y);
  printf("Address size of y(array): %d\n", ySize);
  printf("Address of x: %p\n", (void*)x);
  printf("Address size of x: %d\n", xSize);
  printf("100 * sizeof(int) + overhead_size: %d\n", (100*sizeof(int) + overhead_size));
  printf("Address size of x - 100 * sizeof(int) + overhead_size: %d\n", diff );
  my_free(x);
  my_free(y);
}

void sd(){
    //STANDARD DEVIATION
    //ask user to enter pos int n.
    //allocate space for an array of n intoread n integers from standard in,
    //into the array you allocated.
    //calculate and print the standard deviation of the integers entered,
    // using the standard dev formula.
    printf("STANDARD DEVIATION\n\n");
    int arr_size, a, i; //x is size, a is for random number generator, i is for loops
    printf("Please enter a positive integer for array size: ");
    scanf("%d",&arr_size); //get user input
    printf("value of arr_size: %d\n", arr_size);
    int *arr = (int*)my_alloc(arr_size * sizeof(int));

    // printf("Generating random numbers for array\n");
    // for(i = 0; i < arr_size; i++){ //fill up array with random numbers
    //   a = rand()%20 + 1;
    //   arr[i] = a;
    //   printf("%d\n", a);
    // }

    for(i = 0; i < arr_size; i++){
      printf("Arr[%i] = ", i);
      if(scanf("%d", &arr[i]) != 1){
        fprintf(stderr, "bad array value - exiting \n");
        return 1;
      }
    }


    printf("Address of free_head: %p\n");
    printf("Printing out the addresses of each element\n");
    printf("Address of array arr: %p\n", (void*)arr);
    for(i = 0; i < arr_size ; i++){
      printf("Address of element %d: %p\n", i,  (void*)&arr[i] );
    }

    // printf("Printing content of array: ");
    // for(i = 0; i < x; i++){
    //   printf(" %d ", arr[i]);
    // }
    // printf("\n");

    float sd = standard_deviation(arr, arr_size);

    printf("Standard deviation: %.2f\n", sd);

    my_free(arr);
}

float standard_deviation(int arr[], int x){
    int a;
    float mean, sd;
    float sum = 0;
    float variance = 0;
    for(a = 0; a < x; a++){
      sum += arr[a];
      printf("arr[%d]: %d\n",a, arr[a]);
    }
    printf("sum: %.2f\n", sum);
    mean = sum / x;
    printf("Mean: %.2f\n", mean);

    for(a=0; a<x; a++){
      variance += pow((arr[a] - mean), 2 );
      printf("Calculating variance: %.2f\n", variance);
    }
    printf("Variance sum: %.2f\n", variance);
    variance = variance / (float)x;
    printf("Variance after dividing by x: %.2f\n", variance);

    sd = sqrt(variance);
    //  printf("Standard deviation in function: %.2f\n", sd);

    return sd;
}

void my_initialize_heap(int size){
  printf("Got into my_initialize_heap\n");
  free_head = malloc(size);
  free_head -> block_size = (size) - overhead_size;
  free_head -> next_block = NULL;
  printf("Address of freehead: %p\n", free_head);
  printf("Size of free head data block: %d\n\n", free_head -> block_size);

}

//note: have to allocate in blocks of 8 bytes(size of void)
void* my_alloc(int size){
  printf("Got into my_alloc\n");
  // free_head = (char *) free_head + overhead_size + size;
  //allocate space for user
  //start from the end of buffer
  Block *currentBlock = free_head;
  Block *previousBlock = NULL;

  //make sure you allocate in blocks of voidSize, which is 8
  if( (size%voidSize) != 0){ //allocating for an int or long
    // size = voidSize;
    while(1){//increment size until its a multiple of void
      if( (size%voidSize) == 0){
        break;
      }
      else{
        size++;
      }
    }
  }

  while(1){ //iterate through the link list to check every block


    if( (currentBlock -> block_size) >= size && ((currentBlock -> block_size)%voidSize == 0) ){ //to create a new block, you need 8 bytes for overhead and 8 bytes for data
        // printf("Address of free_head: %p\n", free_head);
        // printf("Address of currentBlock: %p\n", currentBlock);
        if((currentBlock->block_size)==size){
            printf("Exact fit\n\n");
            if(previousBlock == NULL){ //free head
              //free_head = currentBlock -> next_block;
              return ((unsigned char*)currentBlock + overhead_size);
            }
            else if( (previousBlock != NULL) && (currentBlock -> next_block == NULL) ) { //not free head
              //free_head = previousBlock;
              previousBlock -> next_block = NULL;
              return ((unsigned char*)currentBlock + overhead_size);
            }
            else{ //previous and next are not NULL
              previousBlock -> next_block = currentBlock -> next_block;
              return ((unsigned char*)currentBlock + overhead_size);

            }
          }
          else{
            printf("Block is bigger than required size\n");
            Block *nb = (unsigned char*)currentBlock + ( (currentBlock -> block_size) - (size + overhead_size) ); //place new block at the end of the buffer
            // printf("Size of nb: %d\n", sizeof(nb));
            nb -> block_size = size;
            // printf("Nb block size: %d\n", nb -> block_size);
            nb -> next_block = NULL;
            // printf("Size of free_head block before change: %d\n", free_head ->block_size);
            // printf("Size of currentBlock before change: %d\n", currentBlock ->block_size);
            currentBlock -> block_size = ( (currentBlock -> block_size) - (nb->block_size + overhead_size) ); // size of free head is now its original size minus the space allocated
            // printf("Address of new block: %p\n", nb);
            // printf("Address of new block shifted 1: %p\n", ((char*)nb + 1) );
            // printf("New Size of currentBlock block: %d\n", currentBlock->block_size);
            printf("New size of free head block: %d\n\n", free_head->block_size);

            return ((unsigned char*)nb + overhead_size);
          }

    }
    else{
      if( (currentBlock -> next_block != NULL) ){
        previousBlock = currentBlock;
        currentBlock = currentBlock ->  next_block;
      }
      else{ //this means your reached the end of free list
        printf("There is not enough space\n\n");
        return NULL; //return NULL since there is no free space
      }
    }

  }

}

void my_free(void *data){
  // printf("\nGot into my_free\n");
  Block *bp = (Block*)data; //bp is block pointer
  //bp--;
  //add block to linked list of free blocks
  bp = ((unsigned char*)bp - overhead_size);
  //bp -> next_block = free_head;
  // printf("Address of data: %p\n", data);
  // printf("Address of bp: %p\n",bp);
  // printf("Block size of bp: %d\n", bp -> block_size);
  //bp -> block_size = (bp -> block_size) + (free_head -> block_size) + overhead_size; //use to test with one allocation/deallocation
  // printf("Block size of free_head in my_free: %d\n\n", free_head->block_size);
  //printf("Block size of bp after my_free: %d\n\n", bp -> block_size);
  //bp -> next_block = free_head -> next_block;
  //free_head -> next_block = bp;
  bp -> next_block = free_head;
  free_head = bp;
  //printf("Address of freehead in my_free: %p\n", free_head);
}
