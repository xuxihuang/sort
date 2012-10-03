#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10


#ifndef DEBUG
#define DEBUG
#endif


void selection_sort(int* array,int size);
void insertion_sort(int* array,int size);
void quick_sort(int* array,int size);
void Quick_sort(int* array,int size);//optimal quick sort
void shell_sort(int* array,int size);
void merge_sort(int* array,int size);

void print_usage();
void print_array(int* array,int size);

#ifdef DEBUG
void compair(int* array,int size);
#endif

int main(int argc,char** argv)
{
	time_t begin_time,end_time;
	int *array;
#ifdef DEBUG
	int * compairarray; //use an right answer to compair result;
#endif
	int size = MAX_SIZE,count;
	char method;
	if(argc > 1)
	{
		if((size = atoi(argv[1])) < 0)
			size = MAX_SIZE;
	}
	array = malloc(sizeof(int) * size);
	srand(time(NULL));
	for(count = 0;count < size;count++)
	{
#ifdef DEBUG
		array[count] = rand()%100;
#else
		array[count] = rand();
#endif
	}
#ifdef DEBUG
	compairarray = malloc(sizeof(int) * size);
	memcpy(compairarray,array,sizeof(int)*size);
	printf("befor sort\n");
	print_array(array,size);
#endif

	print_usage();
	scanf("%c",&method);
	switch(method)
	{
		case 's':
			begin_time = time(NULL);
			selection_sort(array,size);
			end_time = time(NULL);
			break;
		case 'i':
			begin_time = time(NULL);
			insertion_sort(array,size);
			end_time = time(NULL);
			break;
		case 'q':
			begin_time = time(NULL);
			quick_sort(array,size);
			end_time = time(NULL);
			break;
		case 'Q':
			begin_time = time(NULL);
			Quick_sort(array,size);
			end_time = time(NULL);
			break;
		case 'S':
			begin_time = time(NULL);
			shell_sort(array,size);
			end_time = time(NULL);
			break;
		case 'm':
			begin_time = time(NULL);
			merge_sort(array,size);
			end_time = time(NULL);
			break;
		default:
			printf("not sorted\n");
			break;
	}
#ifdef DEBUG
	printf("after sort\n");
	print_array(array,size);
	compair(compairarray,size);
#endif
	printf("time consume:%d\n",(int)(end_time - begin_time));
	free(array);
	return -1;
}

void merge(int* array,int halfsize,int totalsize)
{
	//array is seperated to two part.one part is from 0 to halfsize-1
	//the other is from halfsize to totalsize-1
	int *temparray = malloc(sizeof(int) * totalsize);
	int i = 0,j = halfsize,index = 0;
	while((i < halfsize) && (j <totalsize))
	{
		if(array[i] > array[j])
			temparray[index++] = array[j++];
		else
			temparray[index++] = array[i++];
	}
	//if the previous part travel over this loop will not excute
	while(i < halfsize)
		temparray[index++] = array[i++];
	//if the rear part travle over this loop will not excute
	while(j < totalsize)
		temparray[index++] = array[j++];
	memcpy(array,temparray,sizeof(int) * totalsize);
	free(temparray);
}

void merge_sort(int* array,int size)
{
	if(size < 2)
		return;
	merge_sort(array,size/2);
	merge_sort(array + size/2,size - size/2);
	merge(array,size/2,size);
}

void shell_sort(int* array,int size)
{
	int increment,i,j,k,temp;
	for(increment = size/2;increment > 0;increment /= 2)
	{
		for(i = 0;i < increment;i++)
		{
			for(j = i + increment;j < size;j += increment)
			{
				k = j;
				while((k > i)&&(array[k-increment] > array[k]))
				{
					temp = array[k-increment];
					array[k-increment] = array[k];
					array[k] = temp;
					k -= increment;
				}
			}
		}
	}
}

int min(int* array,int size)
{
	int i,index = 0,value = array[0];
	for(i = 1;i < size;i++)
	{
		if(array[i] < value)
		{
			value = array[i];
			index = i;
		}
	}
	return index;
}

void selection_sort(int* array,int size)
{
	int i,index,temp;
	for(i = 0;i < size;i++)
	{
		index =i + min(array + i,size - i);
		temp = array[index];
		array[index] = array[i];
		array[i] = temp;
	}
}

void insertion_sort(int* array,int size)
{
	int i,j;
	int temp;
	for(i = 1;i < size;i++)
	{
		j = i - 1;
		while((j >= 0) && array[j + 1] < array[j])
		{
			temp = array[j];
			array[j] = array[j+1];
			array[j+1] = temp;
			j--;
		}
	}
}

void quick_sort(int* array,int size)
{
	int original = array[0],i,j,temp;
	if(size < 2)
		return;
	i = 0;
	j = size - 1;
	while(i < j)
	{
		while((i < j) && (array[j] >= original))
			j--;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;

		while((i < j) && (array[i] < original))
			i++;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;

	}
	if((i > 0) && (i < size -1))
	{
		quick_sort(array,i);
		quick_sort(array + i + 1,size - i - 1);
	}
	else if(i == 0)
		quick_sort(array + 1,size -1);
	else
		quick_sort(array,size-1);
}

void Quick_sort(int* array,int size)
{
	int pivot;
	int i = 0,j = size -1,temp;
	if(size < 2)
		return;
	//put the pivot to the first place,that guarantee the element is pivot
	//when i==j
	pivot = array[size/2];
	array[size/2] = array[0];
	array[0] = pivot;
	while(i < j)
	{
		while((i < j) && (array[j] >= pivot))
			j--;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;

		while((i < j) && (array[i] < pivot))
			i++;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
	if((i > 0)&&(i < size - 1))
	{
		Quick_sort(array,i);
		Quick_sort(array + i,size - i);
	}
	else if(i == 0)
		Quick_sort(array + 1,size -1);
	else
		Quick_sort(array,size-1);
}
void print_array(int* array,int size)
{
	int i = 0;
	while(i < size)
		printf("%d  ",array[i++]);
	putchar('\n');
}

void print_usage()
{
	printf("s\tselection sort\ni\tinsertion sort\nq\tquick sort\n");
	printf("Q\toptimal quick sort\nh\theapsort\nm\tmerge sort\n");
	printf("s\tshell sort\n");
}

#ifdef DEBUG
void compair(int *array,int size)
{
	insertion_sort(array,size);
	printf("for compair\n");
	print_array(array,size);
}
#endif
