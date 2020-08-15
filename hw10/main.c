#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME "commands.txt"
#define STR_LEN 1000

typedef struct point{
	char name[5];
	double x;
	double y;
	struct point *next;
}p_node;

typedef struct line{
	char name[5];
	struct point * p1;
	struct point * p2;
	struct line  *next;
}l_node;

typedef struct plygon{
	char name[5];
	char pl_obje[20][5];
	struct plygon * next;
	
}pl_node;

void file_name_fun(FILE *fp, char str[100]); // file name end  has '\n' this function delede last character
void action_fun(FILE *fp,p_node *iter_p, l_node *iter_l,pl_node *iter_pl); // read file action and push work
double distance_fun(char name1[5],char name2[5],p_node *iter_p,l_node *iter_l);// calculate distance
double one_pointline(char name1[5],char name2[5],p_node *iter_p,l_node *iter_l); // calculate distance 
double angle_fun(char name1[5],char name2[5],l_node *iter_l);// calculate angle
double find_point(l_node *iter_l1,l_node *iter_l2); // calculate point
double length_fun(char name1[1],p_node *iter_p, l_node *iter_l,pl_node *iter_pl); // calculate lengt
double area_fun(char name1[5],p_node *iter_p, l_node *iter_l,pl_node *iter_pl,double *x,double *y); // calculate area
double recuv_area(char obje[20][5],char name1[5],p_node *iter_p); // calculate area
void take_point(char objelist[20][5],char obje[20][5],l_node *iter_l); // take plygon every point
int what_obje(FILE *fp,char str[100]); // return obje number
void read_obje(FILE *fp,p_node *iter_p, l_node *iter_l,pl_node *iter_pl ); // read obje and push anthing read function
p_node *read_point(FILE *fp,p_node * iter  ,char str[1000]); //  write point struct 
l_node * read_line(FILE *fp,l_node *iter_l,p_node * iter_p,char str[100]); // write line struct and linked point line
pl_node * plygon(FILE *fp, char str[1000],pl_node *iter_pl); // write plygon struct 

int main(){
 	char str[STR_LEN];
	FILE * fp;
	fp=fopen(FILENAME,"r+");

	p_node *root_p;
	l_node *root_l;
	pl_node * root_pl;
	

	root_pl=(pl_node*)malloc(sizeof(pl_node));
	root_p=(p_node*)malloc(sizeof(p_node));
	root_l=(l_node*)malloc(sizeof(l_node));	

	fgets(str,100,fp);
	//printf("str11:%s\n",str );	
	read_obje(fp,root_p,root_l,root_pl);
	//printf("pl1:%s\n",root_pl->next->next->next->name );
	action_fun(fp,root_p,root_l,root_pl);

}
void action_fun(FILE *fp,p_node *iter_p, l_node *iter_l,pl_node *iter_pl){
	char moved[4][15]={"Distance","Angle","Length","Area"};
	char name1[5],name2[5] ,cmp_name[20];
	char str[STR_LEN];
	int counter=0 ,i=0;
	double *x,*y;
	FILE *fp_out;
	fgets(str,sizeof(str),fp);
	//printf("str:%s\n",str );
	fgets(str,sizeof(str),fp);
	//printf("str:%s\n",str );
	file_name_fun(fp,str); // 
	fp_out=fopen(str,"w+");
	fgets(str,sizeof(str),fp);
	//printf("ne:%s\n",str );	
	sscanf(str,"%d",&counter);
	//printf("conter:%d\n",counter );

	while(i<counter){
		fgets(str,sizeof(str),fp);
		sscanf(str,"%s %s %s",cmp_name,name1,name2);
		//printf("str:%s\n",str );
		if(!strcmp(cmp_name,moved[0])){
			//printf("bura:str:%s\n",str );
			fprintf(fp_out,"Distance(%s,%s)=%lf\n",name1,name2,distance_fun(name1,name2,iter_p,iter_l));
		}
		else if(!strcmp(cmp_name,moved[1])){
			//printf("name1:%s name2:%s\n",name1,name2 );
			fprintf(fp_out,"Angle(%s,%s)=%lf\n",name1,name2,angle_fun(name1,name2,iter_l));
		}
		else if(!strcmp(cmp_name,moved[2])){
			//printf("burada:%s\n",cmp_name	);
			fprintf(fp_out,"Length(%s)=%lf\n",name1, length_fun(name1,iter_p,iter_l,iter_pl));
		}
		else if(!strcmp(cmp_name,moved[3])){
			fprintf(fp_out,"Area(%s) =%lf\n",name1, area_fun(name1,iter_p,iter_l,iter_pl,x,y));
		}
		i++;

	}


}
double area_fun(char name1[5],p_node *iter_p, l_node *iter_l,pl_node *iter_pl,double *x,double *y){  // area fun
	char objelist[20][5];
	pl_node * root_pl;
	p_node * root_p;
	l_node * root_l;
	root_pl=iter_pl;
	root_p=iter_p;
	root_l=iter_l;

	while(strncmp(iter_pl->name,name1,3)){
		iter_pl=iter_pl->next;
		//printf("name1:%s\n",name1 );
		//printf("iter->name:%s\n",iter_pl->name );
	}
	take_point(objelist,iter_pl->pl_obje,iter_l); //  line translate 2 point  
			//printf("oke\n");
	
		return fabs(recuv_area(objelist,iter_p->name,root_p)/2);

	

}
void take_point(char objelist[20][5],char obje[20][5],l_node *iter_l){
	int i=0;
	l_node *root_l;
	root_l =iter_l;
	while(obje[i][0]!='\0'){
		if(obje[i][0]=='L'){
			while(strcmp(iter_l->name,obje[i])){
				iter_l=iter_l->next;
			}
			strcpy(objelist[i],iter_l->p1->name);
		}
		else if(obje[i][0]='P'){
			strcpy(objelist[i],obje[i]);
		}
		i++;
		iter_l=root_l;
	}
}
double recuv_area(char obje[20][5],char name1[5],p_node *iter_p){ // calculate area every point 
		int i=0;
		double sum=0;
		p_node *root_p;
		root_p=iter_p;
		p_node *iter_p1;
		p_node *iter_p2;
		//printf("obje:%s\n",obje[0] );

		if(obje[1][0]=='\0'){  // stop Null character recuv function
			while(strcmp(name1,iter_p->name)){
				iter_p=iter_p->next;
			}
			iter_p1=iter_p;
			iter_p=root_p;
			while(strcmp(obje[0],iter_p->name)){
				iter_p=iter_p->next;
			}
			iter_p2=iter_p;
			//printf("%lf %lf %lf %lf\n",iter_p1->x,iter_p2->y , iter_p1->y,iter_p2->x );
			sum =(iter_p2->x*iter_p1->y - iter_p2->y*iter_p1->x);
			//printf("çıktı:%lf\n",sum );
			return sum;
		}
		if(obje[0][0]=='P'){
			while(strcmp(obje[0],iter_p->name)){
				iter_p=iter_p->next;
			}
			iter_p1=iter_p;
			iter_p=root_p;
			if(obje[1][0]=='P'){
				while(strcmp(obje[1],iter_p->name)){
				iter_p=iter_p->next;
		//printf("buraya gelen varmı\n");
			}
				iter_p2=iter_p;
				sum =(iter_p1->x*iter_p2->y - iter_p1->y*iter_p2->x);
				//printf("sum:%lf\n",sum );
				return sum  + recuv_area(obje+1,name1,root_p);
			}
		}
		return 0;
}
double length_fun(char name1[1],p_node *iter_p, l_node *iter_l,pl_node *iter_pl){ 
	int i=0,sum=0;
	pl_node * root_pl;
	root_pl=iter_pl;
	l_node * root_l;
	root_l =iter_l;
	if(name1[0]=='L'){ // if lenght is line, translate two point then push distance function
		while(strcmp(iter_l->name,name1)){
			iter_l=iter_l->next;
		}
		 return distance_fun(iter_l->p1->name,iter_l->p2->name,iter_p,iter_l);

	}
	while(strncmp(iter_pl->name,name1,3)){ // else find lygon name
		iter_pl=iter_pl->next;
		//printf("iter_pl->name:%s\n",iter_pl->name);
		//printf("name1:%s\n",name1 );

	}
	//printf("iter->name:%s\n",iter_pl->name );
	//printf("name:%s\n",name1 );

	while(iter_pl->pl_obje[i][0]!='\0'){ // every point lenght calculate
		//printf("pl->obje:%s\n",iter_pl->pl_obje[i] );
		if(iter_pl->pl_obje[i][0]=='P'){
			//printf("i:%d objekk:%s\n",i,iter_pl->pl_obje[i]);
			if(iter_pl->pl_obje[i+1][0]=='\0'){
				//printf("break\n");
				break;
			}
			else if(iter_pl->pl_obje[i+1][0]=='P'){
				sum=sum+ distance_fun(iter_pl->pl_obje[i],iter_pl->pl_obje[i+1],iter_p,iter_l);
				//printf("sum1:%d\n",sum );
			}
			else if(iter_pl->pl_obje[i+1][0]=='L'){
				while(strcmp(iter_l->name,iter_pl->pl_obje[i+1])){
				iter_l=iter_l->next;
			}
				sum=sum+ distance_fun(iter_pl->pl_obje[i],iter_l->name,iter_p,iter_l);
				//printf("sum2:%d\n",sum );
			}
		}
		else if(iter_pl->pl_obje[i][0]=='L'){

			//printf("i:%d obje_else:%s\n",i,iter_pl->pl_obje[i]);
			while(strcmp(iter_l->name,iter_pl->pl_obje[i])){
				iter_l=iter_l->next;
				
		}
			sum=sum+ distance_fun(iter_l->p1->name,iter_l->p2->name,iter_p,iter_l);
				//printf("sum3:%d\n",sum );
		}
		iter_l=root_l;
		i++;
	}
	iter_l=root_l;	
	//printf("iiiiiiiiiiiiiiiiiiiii:%d\n",i );
	if(iter_pl->pl_obje[i][0]=='P' && iter_pl->pl_obje[0][0]=='P' ){

		sum= sum+ distance_fun(iter_pl->pl_obje[i],iter_pl->pl_obje[0],iter_p,root_l); // last korner and first korner
				//printf("iter->pl:%lf\n",iter_pl-> );
				//printf("sum4:%d\n",sum );
	}
	else if(iter_pl->pl_obje[i][0]=='P' && iter_pl->pl_obje[0][0]=='L' ){
		//printf("line1:%s\n",iter_pl->pl_obje[i] );
		while(strcmp(iter_l->name,iter_pl->pl_obje[0])){
				iter_l=iter_l->next;
			}
			sum=sum + distance_fun(iter_l->p1->name,iter_pl->pl_obje[i],iter_p,root_l);
				//printf("sum5:%d\n",sum );
	}
	return sum ;
}
double angle_fun(char name1[5],char name2[5],l_node *iter_l){
	int distance=0;
	l_node *root_l;
	l_node * iter_l1, *iter_l2;
	root_l=iter_l;
	while(strcmp(iter_l->name,name1)){
		iter_l=iter_l->next;
	}
	iter_l1=iter_l;
	iter_l=root_l;
	
	while(strcmp(iter_l->name,name2)){
		iter_l=iter_l->next;
	}
	iter_l2=iter_l;
	
	return find_point(iter_l1,iter_l2);
}
double find_point(l_node *iter_l1,l_node *iter_l2){ // calcule te angle with dot product
	l_node *same_p;
	double x1,x2,x3,x4,y1,y2,y3,y4,m1,distance1,distance2,angle;
	
	x1=iter_l1->p1->x;
	y1=iter_l1->p1->y;
	x2=iter_l1->p2->x;
	y2=iter_l1->p2->y;

	x3=iter_l2->p1->x;
	y3=iter_l2->p1->y;
	x4=iter_l2->p2->x;
	y4=iter_l2->p2->y;
	//printf("x1:%lf y1:%lf x2:%lf y2:%lf x3:%lf y3:%lf x4:%lf y4:%lf n",x1,y1,x2,y2,x3,y3,x4,y4 );
		m1=(x1-x2)*(x3-x4) +(y1-y2)*(y3-y4);
		distance1=sqrt((x1-x2)*(x1-x2) +(y1-y2)*(y1-y2));
		distance2=sqrt((x3-x4)*(x3-x4)+(y3-y4)*(y3-y4));

		angle=acos(m1/(distance1*distance2))*180/M_PI;
		if(angle==180)
			return 0;
		else 
			return angle;
	
	

}
double distance_fun(char name1[5],char name2[5],p_node *iter_p,l_node *iter_l){ // calculate distance
	//printf("geldi\n");
	if(name1[0]=='P' && name2[0]=='P'){ // desired distance is point and point 
		//printf("name1:%s\n",name1);
		//printf("name2:%s\n",name2);
		double x1=0,y1=0,x2=0,y2=0;
		p_node *root_p;
		root_p=iter_p;

		while(strcmp(iter_p->name,name1)){
			iter_p=iter_p->next;
		}
		x1=iter_p->x;
		y1=iter_p->y;
		//printf("x1:%f y1:%f\n",iter_p->x ,iter_p->y);
		iter_p=root_p;
		while(strcmp(iter_p->name,name2)){
			iter_p=iter_p->next;
		}
		x2=iter_p->x;
		y2=iter_p->y;
		//printf("x2:%f y2:%f\n",iter_p->x ,iter_p->y);
		return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		}

	else if(name1[0]=='L' && name2[0]=='P'){ //  desired distance line and point
		one_pointline(name1,name2,iter_p, iter_l);
	}
	else if(name1[0]=='P' && name2[0]=='L'){
			one_pointline(name2,name1,iter_p, iter_l);
	
	}


}
double one_pointline(char name1[5],char name2[5],p_node *iter_p,l_node *iter_l){ // first name is Line second name is point 
	double distance=0,slope=0,c=0;
	l_node * root_l;
	p_node * root_p;

	root_l=iter_l;
	root_p=iter_p;

	while(strcmp(iter_l->name,name1)){
		iter_l=iter_l->next;
	}
	//printf("iter-name:%s \n",iter_l->name );
	//printf("name:%s \n",name1 );
	while(strcmp(iter_p->name,name2)){
		iter_p=iter_p->next;
	}
	//printf("iter->name:%s\n",iter_p->name );
	//printf("name:%s\n",name2 );

	slope=(iter_l->p1->y - iter_l ->p2->y )/(iter_l->p1->x - iter_l->p2->x);
	//printf("slope:%f\n",slope );
	c = iter_l->p1->y - (slope*iter_l->p1->x);
	return distance = (fabs (iter_p->y - (slope * iter_p->x - c))) / (sqrt (1 + slope * slope));;

}
void file_name_fun(FILE *fp, char str[100]){ // last character delete
	int i=0;
	char filename[20],c='k';
	while(c!='\n'){	
		fscanf(fp,"%c",&c);
		//printf("c:%c\n",c );
		str[i]=c;
		i++;
	}
	//printf("i:%d\n",i );
	str[i-1]='\0';
	//printf("str:%s\n",str );

		
}

void read_obje(FILE *fp,p_node *iter_p, l_node *iter_l,pl_node *iter_pl  ){ // read obje 
	int counter=0,i=0,obje=0;
	
	char str[1000];
	fgets(str,sizeof(str),fp);
	sscanf(str,"%d",&counter);
	//printf("counter:%d\n",counter );
	p_node *root_p;
	l_node *root_l;
	pl_node * root_pl;
	

	root_p =iter_p;
	root_l=iter_l;
	root_pl=iter_pl;


	while(i<counter){
		
		obje=what_obje(fp,str); // return obje
	

		if(obje==1)
			iter_p= read_point(fp,iter_p,str);
		
		else if(obje==2)
			iter_l=read_line(fp,iter_l,root_p,str);
		
		else if(obje==3)
			iter_pl=plygon(fp,str,iter_pl);
		
		
		i++;
		
	}
	
}
int what_obje(FILE *fp,char str[1000]){ // function return point 1 Line 2 other 3 
	int i=0 ,num_l=0,num_p=0,flag=0;
	char l='L',p='P';
	fgets(str,1000,fp);
	//printf("obje:%s\n",str );
	for(i=0;i<20;i++){
		if(p==str[i]){
			num_p++;
		}
		if(l==str[i]){
			num_l++;
		}
	}
	//printf("l:%d p:%d\n",num_l,num_p );
	if(num_l==0 && num_p==1)
		flag=1;
	else if(num_p==2 && num_l ==1)
		flag=2;
	else
		flag=3;

	//printf("flag:%d\n",flag );
	return flag;
}
pl_node * plygon(FILE *fp, char str[1000],pl_node *iter_pl){ // write struct plygon 
	char *obje,flag=0;
	int i=0;
	pl_node *root_pl;
	root_pl=iter_pl;
	
	obje=strtok(str," ");
	strcpy(iter_pl->pl_obje[i],obje);
	//printf("1obje:%s\n",iter_pl->pl_obje[i]);
	i++;
	while(1){
			
		obje=strtok(NULL," ");
		if(!strncmp(obje,"PG",2)){
			break;
		}
		strcpy(iter_pl->pl_obje[i],obje);
		i++;
		//printf("obje:%s\n",obje );
	}
	//obje[strlen(obje)]='\0';
	strncpy(iter_pl->name,obje,4);
	//printf("objepl:%s\n",iter_pl->name);

	iter_pl->next=(pl_node*)malloc(sizeof(pl_node));
	iter_pl=iter_pl->next;
	iter_pl->next=NULL;
	return iter_pl;


}

p_node *read_point(FILE *fp,p_node * iter,char str[1000]  ){ // write point struct
	
	double num1,num2;
	char dene[100];	
	
	//printf("str2:%s\n",str);
	sscanf(str,"%lf %lf %s",&iter->x,&iter->y,iter->name);
	
	//	printf("x:%.1lf  y:%.1lf %s\n",iter->x,iter->y,iter->name);

	iter->next=(p_node*)malloc(sizeof(p_node));
	iter=iter->next;
	iter->next=NULL;
	return iter;
}
l_node *read_line(FILE *fp, l_node *iter_l,p_node * iter_p,char str[1000]){ // write line struct
	char point1[5],point2[5],line_name[5] ,line_str[12];
	int i=0;
	p_node * root_p;
	root_p =iter_p;
	l_node *root_l;
	root_l=iter_l;
	strncpy(line_str,str,10);
		
		//printf("try:%d %s\n",try++,line_str );	
		sscanf(line_str,"%s %s %s",point1,point2,line_name);
		//printf("point 1:%s\n",line_name );
		while(strcmp(point1,iter_p->name)!=0){
			iter_p=iter_p->next;
		}
		//printf( "iter_p1:%s\n",iter_p->name );
		iter_l->p1=iter_p;

		iter_p=root_p;
		while(strcmp(point2,iter_p->name)){
			iter_p= iter_p->next;
		}
		iter_l->p2=iter_p;
		//printf( "iter_p2:%s\n",iter_p->name );
		iter_p=root_p;
		strcpy(iter_l->name,line_name);
		

		iter_l->next=(l_node*)malloc(sizeof(l_node));
		iter_l=iter_l->next;
		iter_l->next=NULL;
		return iter_l;


}