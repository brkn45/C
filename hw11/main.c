#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct linklist{
	int data;
	struct linklist * next;
}node;
typedef struct diff {
	 int n1, n2; 
	 struct diff *next;
	}node_diff;


void part1();
void part2();
int *read_array(char filename[20],int * array);  // read list.txt for array
node *read_linkedlist(char *filename,node * root);	// read  list.txt for linkleist
float * stats_array(int *array,float *mean,float * max,float * min,float *std); // calculate and return mean , max  min standatrd deviation with in array nummbers
float * stats_linkedlist(node* root,float *mean,float *max,float * min,float *std); // calculate and return mean , max  min standatrd deviation with in linklist nummbers
float array_size(int * array); // calculate array size
float linklist_size(node * root); // calculate linklist size
int *input_arr(int * array ,int *num); // take user input for array
node* input_ll(node * root,int *num); // take  user input for linklist
void compare(int * array, node * root, node_diff  * root_diff); // compare diffrent number linklist between array
void write_diff(node_diff * root_diff); // print diffrent number 


int main(){
	part1();
	part2();
}
void part2(){
	printf("\n\nPart 2 Start\n");
	printf("----------------\n");
	printf(" '0' for stop enterig new number \n");
	int num=0;
	node * root;
	node_diff *root_diff;
	root_diff=(node_diff*)malloc(sizeof(node_diff));
	root=(node*)malloc(sizeof(node));	
	int *array;
	array=(int*)malloc(sizeof(int));
	array= input_arr(array,&num);
	input_ll(root,&num);

	compare(array,root,root_diff);
	write_diff(root_diff);
}
void write_diff(node_diff * root_diff){
	node_diff *iter_diff;
	iter_diff=root_diff;
	printf("\nFirst List:\n");
	while(iter_diff->next!=NULL){
		printf("%d ",iter_diff->n1);
		iter_diff=iter_diff->next;
	}
	iter_diff =root_diff;
	printf("\nSecond List\n");
	while(iter_diff->next!=NULL){
		printf("%d ",iter_diff->n2 );
		iter_diff=iter_diff->next;
	}
	printf("\n");
}
void compare(int * array, node * root, node_diff  * root_diff){
	int i=0;
	node * iter;
	node_diff * iter_diff;

	iter=root;
	iter_diff=root_diff;

	while(iter->next!=NULL){
		if(iter->data!=array[i]){
			iter_diff->n1=array[i];
			iter_diff->n2=iter->data;
			iter_diff->next=(node_diff*)malloc(sizeof(node_diff));
			iter_diff=iter_diff->next;
			iter_diff->next=NULL;

		}
		iter=iter->next;
		i++;
	}
}
node * input_ll(node * root,int * num){
	int counter=0;
	node * iter;
	iter=root;
	printf("Please Enter %d Number for LinkList\n",*num);
	while(counter<*num){
		printf("Please Enter  number:");
		scanf("%d",&iter->data);
		iter->next=(node*)malloc(sizeof(node));
		iter=iter->next;
		iter->next=NULL;
		counter++;
	}

} 
int *input_arr(int * array ,int *num){	
	int i=0;
	int input=1;
	printf("Please Enter number for Array List\n");
	while(input!=0){
		printf("Please Enter number:");
		scanf("%d",&input);
		array[i]=input;
		i++;
		array=realloc(array,sizeof(int)*(i+1));

	}
	i--;
	*num=i;
	printf("\nYou are Enter %d\n",*num );
	return array;	
}
void part1(){
	int *array,i=0;
	int num=0;
	char filename[20]="list.txt";
	float *mean, *max, *min, *std;
	clock_t t;
	
	mean=(float*)malloc(sizeof(float));
	max=(float*)malloc(sizeof(float));
	min=(float*)malloc(sizeof(float));
	std=(float*)malloc(sizeof(float));

	node * root;
	root=(node*)malloc(sizeof(node));
	root->next=NULL;						
	array=(int*)malloc(sizeof(int));
	
	array= read_array(filename,array);
	read_linkedlist(filename,root);
	
	

	*std =*stats_array(array,mean,max,min,std);
	printf("Read Array \n");
	printf("-------------\n");
	printf("Array size :%f\n",array_size(array));
	printf("Min        Max           Mean              Standart Deviation\n");
	printf("%.2f     %.2f      %.2f            %.2f\n\n\n",*min , *max , *mean ,*std );
	
	*std = *stats_linkedlist(root,mean,max,min,std);
	printf("Read Linklist\n");
	printf("-----------------\n");
	printf("Linklist Size :%f\n",linklist_size(root) );
	printf("Min        Max          Mean               Standart Deviation\n");
	printf("%.2f     %.2f      %.2f            %.2f\n\n\n",*min , *max , *mean ,*std );
	printf("Time\n");
	printf("----------------------\n");

	t=clock();
	array= read_array(filename,array);
	t=clock() -t;
	printf("1 -Time Array:%f\n",(float)t/CLOCKS_PER_SEC );

	t=clock();
	read_linkedlist(filename,root);
	t=clock() -t;
	printf("1 -Time Linklist:%f\n",(float)t/CLOCKS_PER_SEC );

	t=clock();
	read_linkedlist(filename,root);
	t=clock() -t;
	printf("2 -Time Linklist:%f\n",(float)t/CLOCKS_PER_SEC );

	t=clock();
	array= read_array(filename,array);
	t=clock() -t;
	printf("2- Time Array:%f\n",(float)t/CLOCKS_PER_SEC );

	
	
}
float linklist_size(node * root){
	float sum=0;

	node * iter;
	iter=root;
	while(iter->data!=-1){
		sum=sum + sizeof(iter);
		iter=iter->next;

	}
	return sum;
}
float array_size(int *array){
	float sum=0;
	int i=0;
	while(array[i]!=-1){
		sum=sum + sizeof(array[i]);
		i++;
	}
	return sum;

}
float * stats_linkedlist(node* root,float *mean,float *max,float * min,float *std){
	float sum=0, i=0;

	node * iter;
	iter=root;
	*max=(float)iter->data;
	*min=(float)iter->data;
	while(iter->data!=-1){
		if(iter->data > *max)
			*max=(float)iter->data;
		if(iter->data < *min)		
			*min=(float)iter->data;
		sum=sum+(float)iter->data;
		iter=iter->next;
		i++;
	}
	
 	*mean=(float)sum/(float)i;
	
	sum=0;
	i=0;
	iter=root;
	while(iter->data!=-1){
		sum=sum+ (*mean-iter->data)*(*mean-iter->data);
		iter=iter->next;
		i++;
	}
		
	*std=(float) sqrt(sum/(float)(i-1));


	return std; 
}
float * stats_array(int *array,float *mean,float * max,float * min,float *std){
	int i=0;
	float sum=0;
	*max=(float)array[0];
	*min=(float)array[0]; 

	while(array[i]!=-1){
		if((float)array[i]>*max)
			*max=(float)array[i];
		if((float)array[i]<*min)
			*min=(float)array[i];
		sum=sum+ (float)array[i];
		i++;
	}

	*mean =(float) sum/(float)i;
	sum=0;
	i=0;
	while(array[i]!=-1){
		sum=sum +  (*mean -array[i] )*( *mean-array[i]);
		i++;
	}
	
	*std= (float) sqrt(sum/(float)(i-1));

	return std ;	
}
node *read_linkedlist(char *filename,node * root){
	char c;
	int i=0;
	
	FILE *fp;
	fp=fopen(filename,"r+");
	node *iter;
	iter=root;

	while(1){
		fscanf(fp,"%d",&iter->data);
		i++;
		
		fscanf(fp,"%c",&c);
	
		if(feof(fp)){
			break;
		}
		else{
		iter->next=(node*)malloc(sizeof(node));
		iter=iter->next;
		iter->next=NULL;

		}
	}			
	iter->data=-1;
}
int *read_array(char filename[20],int * array){
	char  c;
	int i=2;
	FILE * fp;
	fp=fopen(filename,"r+");
	while(1){

		fscanf(fp,"%d",&array[i-2]);
		fscanf(fp,"%c",&c);
		if(feof(fp))
			break;
		
		else
			array= realloc(array,sizeof(int)*i);
		
		i++;
	}
	
	array= realloc(array,sizeof(int)*i);
	array[i-2]=-1;
	
	return array;
}