/***********************************************************
  > File Name: bucket_sort.cpp
  > Author: Nie Yanfeng
  > Mail: e83242650@163.com
  > Created Time: Mon 28 Jul 2025 05:58:14 PM CST
  > Last Modified: Mon 28 Jul 2025 05:58:16 PM CST
***********************************************************/

#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>

#include<time.h>
#include<cstring>
#include<vector>

#define MOD 65535 * 16

using namespace std;

int input[MOD + 2], output[MOD + 2];
vector<int> bucket[MOD + 1];

double quick_sort_for_comparison(int[], int);
double compare_results(int[], int[], int);

void insertion_sort(vector<int>& A) {
    for (int i = 1; i < A.size(); ++i) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

double bucket_sort(int a[], vector<int> bucket[], int num, int w){
    clock_t start, finish;
    start = clock();

    //bucket sort
    int bucket_size = w / num + 1;
    for(int i = 0; i < num; i++)
        bucket[i].clear();
    for(int i = 1; i <= num; i++)
        bucket[a[i] / bucket_size].push_back(a[i]);
    int idx = 0;
    for(int i = 0; i < num; i++){
        insertion_sort(bucket[i]);
        for(int j = 0; j < bucket[i].size(); j++){
            a[++idx] = bucket[i][j];
        }
    }

    finish = clock();    
    
    double running_time = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;

	cout<<"[STL] The array used to be compared is bucket-sorted out with sorting time: "<<endl;
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

    //bucket sort
    int maxn = -1;
    for(int i = 1; i <= num; i++)
        if(input[i] > maxn)
            maxn = input[i];
    double time_2 = bucket_sort(input, bucket, num, maxn);

    double ratio = compare_results(input, output, num);
    cout<<"Correct ratio with STL Quick Sort: "<<ratio<<endl;
    cout<<"Bucket Sort is "<<(time_1 - time_2) / time_1 * (double)100<<"% faster than STL Quick Sort"<<endl;
    return 0;
}
