#include <stdio.h>

int sum (int n, int flag); 
int mult (int n, int flag);

int main(){ 
	int num=0,flag=0,choice=0 ,result=0;
	printf("Enter an integer:");
	scanf("%d",&num);
	printf("Please enter '0' for sum, '1' for multiplication\n");
	scanf("%d",&choice);
	printf("Please enter '0' to work on even numbers,  '1' to work on odd numbers\n");
	scanf("%d",&flag);

	if(flag!=1 && flag!=0){  // if integer is not 0 or 1, exit program
		printf("Invalid value for odd/even selection\n");
		return 0;
	}

	switch (choice) { // user select to menu select sum or mult

		case 0:
		result=sum(num,flag);
		break;

		case 1:
		result=mult(num,flag);
		break;
		
		default :
		printf("Unsuported operation.\n");
		return 0;


	}

	printf("=%d\n",result );
	return 0;



	
} 
int sum(int num, int flag){  // sum odd or even number between num and 0.
	int i=0 ,result=0;

	if(flag==0){
		for(i=1;i<=num;i++){
			if(i%2==0){
				printf("%+d",i );
				result=result+i;

			}

		}
		printf("=%d\n",result );
	}
	else if(flag==1){
		for(i=1;i<num;i++){
			if(i%2==1){
				printf("%+d",i );
				result=result+i;
			}

		}
		
	}
	return result;
}

int mult(int num, int flag){ // multipication odd or even number between num and 1.
	int i=0, result=1;
	if(flag==0){
		for(i=1;i<=num;i++){
			if(i%2==0){
				printf("%d*",i );
				result=result*i;
			}
		}
	}
	else if(flag==1){
		for(i=1;i<=num;i++){
			if(i%2==1){
				printf("%d*",i );
				result=result*i;
			}
		}
	}
	return result;	
}