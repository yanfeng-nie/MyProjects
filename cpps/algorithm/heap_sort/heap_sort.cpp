/***********************************************************
  > File Name: heap_sort.cpp
  > Author: Nie Yanfeng
  > Mail: e83242650@163.com
  > Created Time: Sun 27 Jul 2025 03:45:45 PM CST
  > Last Modified: Sun 27 Jul 2025 05:15:38 PM CST
***********************************************************/

#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>

#include<time.h>

#define PARENT(i) i >> 1
#define LEFT(i) i << 1
#define RIGHT(i) i << 1 | 1

using namespace std;

int input[65537];
int output_1[65537];
const int MOD = 65536;

void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

void max_heapify(int a[], int i, int heap_size){
	if(i <= 0 || i >= heap_size)
		return;

	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;

	if(l <= heap_size && a[l] > a[i])
		largest = l;
	else 
		largest = i;

	if(r <= heap_size && a[r] > a[largest])
		largest = r;
	if(largest != i){
		swap(a[i], a[largest]);
		max_heapify(a, largest, heap_size);
	}
}

void max_heapify_loop(int a[], int i, int heap_size){
	if(i <= 0 || i >= heap_size)
		return;
	while(i < heap_size){
		int l = LEFT(i);
		int r = RIGHT(i);
		int largest;

		if(l <= heap_size && a[l] > a[i])
			largest = l;
		else 
			largest = i;

		if(r <= heap_size && a[r] > a[largest])
			largest = r;

		if(largest != i){
			swap(a[i], a[largest]);
			i = largest;
		}
		else 
			break;
	}
}

void build_max_heap(int *a, int heap_size){
	for(int i = (heap_size >> 1); i >= 1; i--)
		max_heapify_loop(a, i, heap_size);
}

/*
---------------------------------------------------------
SORT OUT THE ARRAY AND COMPARE
---------------------------------------------------------
*/

/*
Quick Sort to evaluate the heap-sort
*/
double quick_sort(int A[], int n){
	clock_t start, finish;
	start = clock();
	sort(A + 1, A + 1 + n);
	finish = clock();

	double running_time = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;

	cout<<"The array used to be compared is quick-sorted out with sorting time: "<<endl;
	cout<<"    CLOCKS_PER_MILISEC: "<<running_time<<"(ms)"<<endl;
	return running_time;
}

double heap_sort(int a[], int num, int heap_size){
	if(num == 0) return -1;
	
	clock_t start, finish;
	start = clock();

	build_max_heap(a, heap_size);

	//heap sort
	for(int i = num; i >= 2; i--){
		swap(a[1], a[i]);
		heap_size--;
		max_heapify_loop(a, 1, heap_size);
	}

	finish = clock();
	double running_time = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;
	cout<<"The array is heap-sorted out with sorting time: "<<endl;
	cout<<"    CLOCKS_PER_MILISEC: "<<running_time<<"(ms)"<<endl;
	return running_time;
}

double compare_results(int a[], int b[], int num){
	int count = 0;
	for(int i = 1; i <= num; i++)
		if(a[i] == b[i])
			count++;
	return (double)count / (double)num;
}

int main(int argc, char* argv[]){
	//generate the length of input array
	srand((unsigned)time(NULL));

	int num = rand() % MOD;
	while(num < 10)
		num = rand() % MOD;//control the length of the generated data
	cout<<"The length of generated random array: "<<num<<endl;

	//initiate
	for(int i = 1; i <= num; i++)
		input[i] = output_1[i] = rand() % MOD;
	
	//Quick Sort
	double time_1 = quick_sort(output_1, num);

	//Heap sort
	double time_2 = heap_sort(input, num, num);

	//Calculate the correction ratio
	cout<<"Correct ratio with Quick Sort: "<<compare_results(input, output_1, num)<<endl;
	cout<<"Heap Sort is "<<(time_2 - time_1) / time_1 * (double)100<<"% Slower than Quick Sort"<<endl;
	return 0;
}
