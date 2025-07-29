#include<algorithm>
#include<iostream>

double quick_sort_for_comparison(int a[], int num){
    clock_t start, finish;
    start = clock();
    std::sort(a + 1, a + 1 + num);
    finish = clock();

    double running_time = (double)(finish - start) / CLOCKS_PER_SEC * (double)1000;

	std::cout<<"[STL] The array used to be compared is quick-sorted out with sorting time: "<<std::endl;
	std::cout<<"    CLOCKS_PER_MILISEC: "<<running_time<<"(ms)"<<std::endl;
	return running_time;
}

double compare_results(int a[], int b[], int num){
    int count = 0;
    for(int i = 1; i <= num; i++)
        if(a[i] == b[i])
            count++;
    return (double)count / (double)num;
}
