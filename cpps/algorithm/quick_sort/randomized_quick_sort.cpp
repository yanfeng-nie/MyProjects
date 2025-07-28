/***********************************************************
  > File Name: randomized_quick_sort.cpp
  > Author: Nie Yanfeng
  > Mail: e83242650@163.com
  > Created Time: Mon 28 Jul 2025 02:10:19 PM CST
  > Last Modified: Mon 28 Jul 2025 02:10:22 PM CST
***********************************************************/

#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>

#include<time.h>
#include<algorithm>

#define MOD 65535 * 16

using namespace std;
int input[MOD + 2], output[MOD + 2], rinput[MOD + 2];

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

int randomized_partition(int a[], int p, int r){
    int i = rand() % (r - p + 1) + p;
    swap(a[r], a[i]);
    return partition(a, p, r);
}

void quick_sort(int a[], int p, int r, bool flag){
    if(p < r){
        int q;
        if(flag == true)
            q = randomized_partition(a, p, r);
        else 
            q = partition(a, p, r);
        quick_sort(a, p, q - 1, flag);
        quick_sort(a, q + 1, r, flag);
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


/*
flag = true -> use randomized_partition
flag = false -> use partition
*/
double quick_sort_test(int a[], int num, bool flag){
    clock_t start, finish;
    start = clock();

    quick_sort(a, 1, num, flag);

    finish = clock();
    double running_time = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;

    if(flag == true)
	    cout<<"[RANDOMIZED] The array is quick-sorted out with sorting time: "<<endl;
	else
        cout<<"[MANUAL] The array is quick-sorted out with sorting time: "<<endl;
    cout<<"    CLOCKS_PER_MILISEC: "<<running_time<<"(ms)"<<endl;
    return running_time;
}

void compare_results(int a[], int b[], int c[], int num, double time_1, double time_2, double time_3){
    /*
    a - input - time3 - count1
    b - rinput - time2 - count2
    c - output - time1
    */
    
    int count1 = 0, count2 = 0;
    for(int i = 1; i <= num; i++){
        if(b[i] == c[i])//manual
            count1++;
        if(b[i] == a[i])//randomized
            count2++;
    }
        
    double ratio1 = (double)count1 / (double)num;
    double ratio2 = (double)count2 / (double)num;

    //compare
    cout<<endl<<"##########   START COMPARISON   ##########"<<endl<<endl;
    cout<<"[RANDOMIZED with STL]:"<<endl;
    cout<<"    Correct ratio with STL Quick Sort: "<<ratio1<<endl;
    if(time_1 > time_2)
	    cout<<"    Randomized Quick Sort is "<<(time_1 - time_2) / time_1 * (double)100<<"% faster than STL Quick Sort"<<endl;
    else
        cout<<"    Randomized Quick Sort is "<<(time_2 - time_1) / time_1 * (double)100<<"% slower than STL Quick Sort"<<endl;

    cout<<"[RANDOMIZED with MANUAL]:"<<endl;
    cout<<"    Correct ratio with MANUAL Quick Sort: "<<ratio2<<endl;
    if(time_3 > time_2)
	    cout<<"    Randomized Quick Sort is "<<(time_3 - time_2) / time_3 * (double)100<<"% faster than MANUAL Quick Sort"<<endl;
    else
        cout<<"    Randomized Quick Sort is "<<(time_2 - time_3) / time_3 * (double)100<<"% slower than MANUAL Quick Sort"<<endl;
    cout<<endl<<"##########   START COMPARISON   ##########"<<endl<<endl;
}

int main(int argc, char* argv[]){
    //randomize the data
    srand((unsigned)time(NULL));

    int num = rand() % MOD;
    while(num < 10)
        num = rand() % MOD;
    cout<<"The length of generated array is: "<<num<<endl;

    for(int i = 1; i <= num; i++)
        input[i] = rinput[i] = output[i] = rand() % MOD;

    //quick sort for comparison
    double time_1 = quick_sort_for_comparison(output, num);

    //quick sort
    double time_2 = quick_sort_test(rinput, num, true);
    double time_3 = quick_sort_test(input, num, false);

    //compare results
    compare_results(input, rinput, output, num, time_1, time_2, time_3);

    return 0;
}
