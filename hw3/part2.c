#include <stdio.h>
#include <math.h>
int isprime(int a);
int main(){
	int flag=0,i=0, num=0;
	printf("Please enteer an integer:");
	scanf("%d",&num);
	for(i=2;i<num;i++){ //  for loop controll  between 2 and num  is prime and not prime
		flag=isprime(i);
		if(flag==0){
			printf("%d is prime number\n\n",i);
		}
		else{
			printf("%d is not prime number, it is dividible by %d\n\n",i,flag );
		}
	}
}

int isprime(int a){ // this function conroll prime or not prime. if number not prime, return divisor number
	int i=0,chance=0;
	chance=(int)sqrt((double)a);
	chance=chance+1;
	for(i=2;i<chance;i++){
		if(a%i==0){
			return i;
		}

	}
	return 0; 

}