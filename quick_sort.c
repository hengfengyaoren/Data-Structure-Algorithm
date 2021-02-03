#include <stdio.h>

#define DATA_ARRAY_LEN 12


////////////////////////////////////////////////////////////////////////////
//调用一次就把哨兵放在固定的位置
int sort(int *data, int left, int right){  //每一次递归就确定一个数据的正确的位置

    if (left >= right) return 0;

    int i = left;
    int j = right;
    int key = data[left];

    while(i < j){

        while(i < j && key < data[j]) {

            j--;

        }
        data[i] = data[j];

        while(i < j && key >= data[i]) {
            i++;
        }
        data[j] = data[i];

    }

    // i==j退出循環
    data[i] = key;

    //递归
    sort(data,left,i-1);
    sort(data, i+1, right);

}

int quick_sort(int *data, int length){

    sort(data, 0, length - 1);

    return 0;
}


int main(){

    int data[DATA_ARRAY_LEN] = {23,64,24,12,9,16,53,57,71,79,87,97};



    quick_sort(data, DATA_ARRAY_LEN);
        for (int i = 0; i < DATA_ARRAY_LEN; i++){
        printf("%4d ", data[i]);
    }

    printf("\n");

    return 0;
}







