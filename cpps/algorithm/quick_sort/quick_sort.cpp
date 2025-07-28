/***********************************************************
  > File Name: quick_sort.cpp
  > Author: Nie Yanfeng
  > Mail: e83242650@163.com
  > Created Time: Sun 27 Jul 2025 10:52:52 PM CST
  > Last Modified: Sun 27 Jul 2025 10:52:56 PM CST
***********************************************************/

#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>

#include<time.h>
#include<algorithm>

#define MOD 65535 * 16

using namespace std;
int input[MOD + 2], output[MOD + 2];

void swap(int &a, int &b){int t = a; a = b; b = t;}

int partition(int a[], int p, int r){
    int x = a[r];
    int i = p - 1;
    for(int j = p; j <= r - 1; j++){
        if(a[j] <= x){
            i ++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quick_sort(int a[], int p, int r){
    if(p < r){
        int q = partition(a, p, r);
        quick_sort(a, p, q - 1);
        quick_sort(a, q + 1, r);
    }
}

double quick_sort_for_comparison(int a[], int num){
    clock_t start, finish;
    start = clock();
    sort(a + 1, a + 1 + num);
    finish = clock();

    double running_time = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;

	cout<<"[STL] The array used to be compared is quick-sorted out with sorting time: "<<endl;
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
    //randomize the data
    srand((unsigned)time(NULL));

    int num = rand() % MOD;
    while(num < 10)
        num = rand() % MOD;
    cout<<"The length of generated array is: "<<num<<endl;

    for(int i = 1; i <= num; i++)
        input[i] = output[i] = rand() % MOD;

    //quick sort for comparison
    double time_1 = quick_sort_for_comparison(output, num);

    //quick sort
    clock_t start, finish;
    start = clock();

    quick_sort(input, 1, num);

    finish = clock();
    double time_2 = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;

	cout<<"[MANUAL] The array is quick-sorted out with sorting time: "<<endl;
	cout<<"    CLOCKS_PER_MILISEC: "<<time_2<<"(ms)"<<endl;

    //Calculate the correction ratio
	cout<<"Correct ratio with STL Quick Sort: "<<compare_results(input, output, num)<<endl;
	cout<<"Manual Quick Sort is "<<(time_1 - time_2) / time_1 * (double)100<<"% faster than STL Quick Sort"<<endl;

    return 0;
}

