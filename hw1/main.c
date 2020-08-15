#include <stdio.h>
#include <math.h>

void find_root(); // this fuction part 1

void find_newtonian_root();
int find_multiple_closest(int a, int b);

int main(){
	
	int num1, num2 ,p3_num; // variables for  part3 
	
	find_root();
	find_newtonian_root();
	
	printf("Enter the first integer:\n");
	scanf("%d",&num1);
	printf("Enter the second integer:\n");
	scanf("%d",&num2);
	
	p3_num=find_multiple_closest(num1,num2);
	if(num1==p3_num){
	
		printf("Closest number to %d that is multiple of %d is itself.\n",num1,num2);
	}	
	else{
		printf("Output> Closest number to %d that is multiple of %d is %d.\n",num1,num2,p3_num );
	}
	
}
void find_root(){ // part 1
	int a,b,c,delta,root_delta;
	int f_root,s_root;

	printf("Please Enter the first coefficient:\n");
	scanf("%d",&a);
	printf("Please Enter the second coefficient:\n");
	scanf("%d",&b);
	printf("Please Enter the third coefficient:\n");
	scanf("%d",&c);	

	delta=b*b-4*a*c;
	if(delta<0){
		printf(">Your equation %+dx^2  %+dx  %+d does not have any real roots. The function prototype is:\n",a,b,c );

	}
	else{
		root_delta=sqrt(delta);
		f_root=(-b-root_delta)/2*a;
		s_root=(-b+root_delta)/2*a;
		printf(">Your equation %+dx^2  %+dx  %+d have real roots {%d,%d}.\n",a,b,c,s_root,f_root);



	}


}

 int find_multiple_closest(int a, int b){ // this function  find cloest number
 	int num_large,num_small;
 	int result,dive;

 	dive=a%b;
 	num_small= a-a%b; 
 	num_large=num_small+b;

	if(a-num_small < num_large -a){ 
		return num_small;
	}
	else{
		return num_large;
	}
 	

 }
  void find_newtonian_root(){ // this function 2 part
  	double a,b,c,initial,sumf,sumd,result,delta;
  	double root_delta,f_root,s_root;

 	printf("Please Enter the first coefficient:");
	scanf("%lf",&a);
	printf("Please Enter the second coefficient:");
	scanf("%lf",&b);
	printf("Please Enter the third coefficient:");
	scanf("%lf",&c);
	printf("Please Enter the initial:");
	scanf("%lf",&initial);

	delta=b*b-4*a*c;
	root_delta=sqrt(delta); // this function find root delta
	//printf("root_d:%lf\n",root_delta );
	f_root=(-b-root_delta)/2*a;
	s_root=(-b+root_delta)/2*a;
	
	printf("> Your equation is %+.2lfx^2  %+.2lfx  %+.2lf and iterations are\n",a,b,c );
	printf("Step   x      f(x)   Difference\n");
	
	// start newton methood
	sumf=a*initial*initial+b*initial+c;  
	sumd=2*initial+b;
	result=initial-sumf/sumd;
	initial=result;
	
	int i=0;
	sumf=a*initial*initial+b*initial+c;
	printf("x%d %.4lf %.5lf %.4lf\n",i+1,result,sumf,result - s_root ); //step 1
	sumd=2*initial+b;
	result=initial-sumf/sumd;
	initial=result;

	i++;
	sumf=a*initial*initial+b*initial+c;
	printf("x%d %.4lf %.5lf %.4lf\n",i+1,result,sumf,result - s_root ); // step 2
	sumd=2*initial+b;
	result=initial-sumf/sumd;
	initial=result;
	
	i++;		
	sumf=a*initial*initial+b*initial+c;
	printf("x%d %.4lf %.5lf %.4lf\n",i+1,result,sumf,result - s_root ); // step 3
	sumd=2*initial+b;
	result=initial-sumf/sumd;
	initial=result;
	i++;
	
	sumf=a*initial*initial+b*initial+c;
	printf("x%d %.4lf %.5lf %.4lf\n",i+1,result,sumf,result - s_root ); // step 4
	sumd=2*initial+b;
	result=initial-sumf/sumd;
	initial=result;

	i++;
	sumf=a*initial*initial+b*initial+c;
	printf("x%d %.4lf %.5lf %.4lf\n",i+1,result,sumf,result - s_root ); // step 5
	sumd=2*initial+b;
	result=initial-sumf/sumd;
	initial=result;

  }