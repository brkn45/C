#include <stdio.h>
#include <math.h>

int andop (int a, int b);
int control_digit(int a,int b);
int control_number(int a,int b);

int main(){
	int num1=0, num2=0,result=0 ,flag=0,controll=0;
	do{		// if 2 contoll is true, out the loop.  
		controll=0;
		printf("First Integer:");
		scanf("%d",&num1);
		printf("Secound Integer:");
		scanf("%d",&num2);
		flag=control_digit(num1,num2);
		if(flag==1){
			printf("Integer should have the length, please enter 2 new integer\n");
			
		}
		else{
			controll++;
		}
		flag=control_number(num1,num2);
		if(flag==2){
			printf("Integer should be binnary, please enter 2 new integer\n");
		}
		else{
			controll++;
		}


	}while(controll!=2);

	result=andop(num1,num2); // this function make  logical AND operation than return the result. 
	printf("%d AND %d = %d\n",num1,num2,result );
}

int control_digit(int num1,int num2){ // controll digit length
	int digit1=0,digit2=0,counter=0;
	do{
		num1=num1/10;
		counter++;
	}while(num1>=10);
	
	digit1=counter;
	counter=0;
	
	do{
		num2=num2/10;
		counter++;
	}while(num2>=10);
	
	digit2=counter;
	if(digit1==digit2){
		return 0;
	}
	else{
		return 1;
	}
}

int control_number(int num1,int num2){ // this function controll binnary or not binnarry
	int control=0;
	do{
		control=num1%10;
		if(control>1){
			return 2;		
		}
		num1=num1/10;
	}while(num1>=10);

	do{
		control=num2%10;
		if(control>1){
			return 2;		
		}
		num2=num2/10;
	}while(num2>=10);
	return 0;
}

int andop(int num1,int num2){ // function make  logical AND operation num1 and num2 then return result
	int result=0,control1=0,control2=0,end=0;
	int counter=0;

	do{
		
		control1=num1%10;
		control2=num2%10;
		if(control1==1 && control2==1){
			result=1;
		}
		else{
			result=0;
		}
		end= end+result*pow(10,counter);
		num1=num1/10;
		num2=num2/10;
		counter++;
	}while(num1>0);
	return end;
}