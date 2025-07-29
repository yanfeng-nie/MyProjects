/***********************************************************
  > File Name: counting_sort.cpp
  > Author: Nie Yanfeng
  > Mail: e83242650@163.com
  > Created Time: Mon 28 Jul 2025 05:57:51 PM CST
  > Last Modified: Mon 28 Jul 2025 05:57:56 PM CST
***********************************************************/

#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>

#include<time.h>
#include<cstring>

#define MOD 65535 * 16

using namespace std;
int input[MOD + 2], output[MOD + 2];
int b[MOD + 2], c[MOD + 2];

double quick_sort_for_comparison(int[], int);
double compare_results(int[], int[], int);

double counting_sort(int a[], int b[], int c[], int num, int k){
    clock_t start, finish;
    start = clock();
    //init
    memset(c, 0, sizeof(c));

    //count
    for(int i = 1; i <= num; i++) c[a[i]]++;
    for(int i = 1; i <= k; i++) c[i] += c[i - 1];
    for(int i = num; i >= 1; i--){
        b[c[a[i]]] = a[i];
        c[a[i]] --;
    }
    finish = clock();

    double running_time = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;

	cout<<"[COUNT] The array used to be compared is counting-sorted out with sorting time: "<<endl;
	cout<<"    CLOCKS_PER_MILISEC: "<<running_time<<"(ms)"<<endl;
    return running_time;
}

int main(int argc, char* argv[]){
    //generate the data
    srand((unsigned)time(NULL));

    int num = rand() % MOD;
    while(num < 10) num = rand() % MOD;

    for(int i = 1; i <= num; i++)
        input[i] = output[i] = rand() % MOD;
    cout<<"The length of generated array is: "<<num<<endl;

    //quick sort
    double time_1 = quick_sort_for_comparison(output, num);

    //counting sort
    double time_2 = counting_sort(input, b, c, num, MOD);

    double ratio = compare_results(b, output, num);
    cout<<"Correct ratio with STL Quick Sort: "<<ratio<<endl;
    cout<<"Counting Sort is "<<(time_1 - time_2) / time_1 * (double)100<<"% faster than STL Quick Sort"<<endl;
    return 0;
}
