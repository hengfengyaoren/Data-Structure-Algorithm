#include <stdio.h>

#define DATA_ARRAY_LENGTH 12

//两个集合有序合成一个有序集合
//分割完成后排序 将两个有序合成一个有序的
void sort(int *data, int *temp, int start, int middle, int end){

	int i = start, j = middle + 1,k = start;
	
	while(i <= middle && j <= end){
		
		if (data[i] > data[j]){
			temp[k++] = data[j++];
		}else{
			temp[k++] = data[i++];
		}

	}

	while(i <= middle){
		temp[k++] = data[i++];
	}

	while(j <= end){
		temp[k++] = data[j++];
	}

	for(i = start; i <= end; i++){ //直接用memcpy也是可以的
		data[i] = temp[i];
	}
}

//先分组,直至每组只有两个元素再合并
int merge_sort(int* data, int *temp, int start, int end){

	int middle;

	if (start < end){
		
		middle = start + (end - start) / 2; //分割完后，只有2个元素
		
		merge_sort(data, temp, start, middle);
	        merge_sort(data, temp, middle + 1, end);	

		sort(data, temp, start, middle, end);
	}


	return 0;
}



int main()
{

	int data[DATA_ARRAY_LENGTH] = {1,2,2,4,1,3,18,19,20,1,234,23};
	
	int temp[DATA_ARRAY_LENGTH] = {0};
	merge_sort(data, temp, 0, DATA_ARRAY_LENGTH - 1);

	for(int i = 0; i <DATA_ARRAY_LENGTH;i++){
		printf("%4d",data[i]);
	}	
	printf("\n");


	return 0;
}

