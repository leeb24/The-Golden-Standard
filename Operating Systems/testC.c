#include <stdio.h>

// SOLUTION FILE


void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
void reverse(int array[], int array_size)
{
 
    int *pointer1 = array,
 	*pointer2 = array + array_size - 1;
    while (pointer1 < pointer2) {
        swap(pointer1, pointer2);
        pointer1++;
        pointer2--;
    }
}

void print(int* array, int array_size)
{
    int *length = array + array_size/4,
 	*position = array;
    for (position = array; position < length; position++)
        printf("%d ", *position);
}
main()
{
  int var_int;                    // 2

  unsigned char uchar1, uchar2;   // 3
  signed char schar1, schar2;

  int x, y;                       // 4

  char i;                         // 5
  char shift_char;

  int a[10] = {0,10,20,30,40,50,60,70,80,90};    // 6

  int b[10], c[10];               // 7
  int *ip, *ip2;
  int j, k;
  long var_long;

  char AString[] = "HAL";           // 8

  // 1 -- change "World" to your name
  printf("\n\n PART 1 ---------\n");

  printf("\n Hello Byoungsul Lee! \n");

  // 2 -- find sizes of the other C datatypes


  printf("\n\n PART 2 ----------\n");

  printf("\n size of data type int = %d ", sizeof(var_int));
  printf("\n size of data type unsigned char = %d ", sizeof(uchar1));
  printf("\n size of data type char = %d ", sizeof(shift_char));
  printf("\n size of data type long = %d ", sizeof(var_long));
  


  // 3 -- explore signed versus unsigned datatypes and their interactions
  printf("\n\n PART 3 ----------\n");

  // unsigned char data type and signed data type have different value ranges that they can hold.

  uchar1 = 0xFF;
  uchar2 = 0xFE;
  schar1 = 0xFF;
  schar2 = 0xFE;

  printf("\n uchar1 = %d \n", uchar1);
  printf("\n schar1 = %d \n", schar1);
  printf("\n uchar2 = %d \n", uchar2);
  printf("\n schar2 = %d \n", schar2);

  if(uchar1>schar1)
  	printf("uchar1 is bigger !!\n");

  if(uchar1 > uchar2)
  	printf("uchar1 is bigger \n");
  if(uchar2 > uchar1)
  	printf("uchar2 is bigger \n");

  if(schar1 > schar2)
  	printf("schar1 is bigger \n");
  if(schar2 > schar1)
  	printf("schar2 is bigger \n");

  printf("%d\n", schar1 + schar2);

  printf("%d\n", uchar1 + uchar2);

  printf("%d\n", schar1 + uchar1);


  // 4 -- Booleans
  printf("\n\n PART 4 ----------\n");

  x = 1; y = 2;


  printf("The value for TRUE is %d\n",x != y);
  printf("The value for FALSE is %d\n",x == y);

  printf("\n size of data type bool = %d ", sizeof(x == y));

  printf("bit-wise 1&5 = %d \n", 1&5 );

  printf("logical True && FALSE = %d \n", 1&&0);

  printf("bit-wise ~7 = %d \n", ~7 );

  printf("logical !(True && True) = %d \n", !(1&&1));

  // 5 -- shifts
  printf("\n\n PART 5 ----------\n");

  shift_char = 15;
  i = 8;
  int i2 = 1;

  printf("\n shift_char << %d = %d \n", i, shift_char << i);
  printf("\n shift_char >> %d = %d \n", i2, shift_char >> i2);



  // 6 -- pointer basics
  printf("\n\n PART 6 ----------\n");

  ip = a;
  printf("\nstart %d %d %d %d %d %d %d \n",
	 a[0], *(ip), *(ip+1), *ip++, *ip, *(ip+3), *(ip-1));

  printf("\nstart %d %d %d %d %d %d %d \n",
	 a[1], *(ip)++, *(ip--), *ip++, *ip, *(ip+3), *(ip-1));

  printf("\n size of data type int* = %d ", sizeof(int*));


printf("\n value of pointer ip (address) = %x ", ip);

  // 7 -- programming with pointers
  printf("\n\n PART 7 ----------\n");

  int aindex =9;
  for(int reverse1 = 0 ; reverse1 < 10 ; reverse1 ++)
  {
  	b[reverse1] = a[aindex];
  	aindex--;
  }
  for(int n = 0 ; n < 10 ; n++ )
  {
  	printf("%d ",b[n] );
  }

  printf("\n");




  

print(a,sizeof(a));

  // 8 -- strings
  printf("\n\n PART 8 ----------\n");

  printf("\n %s \n", AString);

  printf("\n %d %d %d \n", AString[0], AString[1], AString[2]);

  printf("\n %d \n", AString[3]);

  AString[0] = AString[0]+1;
  AString[1] = AString[1]+1;
  AString[2] = AString[2]+1; //Gets IBM


  printf("\n %s \n", AString);

  AString[3] = AString[3]+60;

  printf("\n %s \n", AString);

  // 9 -- address calculation
  printf("\n\n PART 9 ----------\n");
  for (k = 0; k < 10; k++) 
  {
 	b[k] = a[k];         // direct reference to array element

 	printf("b[k] = %x and a[k] = %x  ", b+k,a+k);
  }

  printf("\n");
  ip = a;
  ip2 = b;
  for (k = 0; k < 10; k++) 
  {
  	*ip2++ = *ip++;     // indirect reference to array element

  	printf("ip2 = %x and ip = %x  ", ip2++,ip++);
  }

  // all done
  printf("\n\n ALL DONE\n");
}
