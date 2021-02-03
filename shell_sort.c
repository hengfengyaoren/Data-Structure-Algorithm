#include <stdio.h>
//思想：先分组再排序  分组后插入排序

#define DATA_ARRAY_LEN 12

//data 数据   length 长度
int shell_sort(int *data, int length)
{
    
    int gap = 0;    //分组的跨度
    int i = 0, j = 0;

    //需要多少次分组
    for(gap = length /2;  gap >= 1; gap  /= 2) {   //分组次数

        for (i = gap; i<length; i++){   //每组的遍历   一组对比次数

            int temp = data[i];
            for (j = i - gap; j >= 0 && temp < data[j]; j = j -gap) {   //组内排序
                
                data[j+gap] = data[j];

            }

            data[j+gap] = temp;


        }

    }

    return 0;

}




int main(){

    int data[DATA_ARRAY_LEN] = {23,64,24,12,9,16,53,57,71,79,87,97};

    shell_sort(data, DATA_ARRAY_LEN);

    for (int i = 0; i < DATA_ARRAY_LEN; i++){
        printf("%4d ", data[i]);
    }

    printf("\n");

    return 0;
}







