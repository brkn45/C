#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"


void resize_figure(Figure *fig, Point2D *start_roi, Point2D *end_roi){ // fisrt fig node chance 
	fig->width = end_roi->x - start_roi->x;
	fig->height = end_roi->y - start_roi->y;
}

void append_figures(Figure *fig1,Figure *fig2){ // function print the pictures 
	while(fig1->next!=NULL){
		fig1=fig1->next;
	}
	fig1->next=fig2;
	while(fig1->next!=NULL){
		fig1=fig1->next;
	}
	fig1->next=NULL;
}

void scale_figure(Figure *fig, double scale_x, double scale_y){ // multiplication of distance
	Point2D *iter_p;

	while(fig!=NULL){
		iter_p=fig->point;
		while(iter_p!=NULL){
			iter_p->x=iter_p->x*scale_x;
			iter_p->y=iter_p->y*scale_y;
			iter_p=iter_p->next;
		}
		fig=fig->next;
	}
}
Figure* draw_tree_to_point(Figure *fig ,Point2D *iter_p,Tree *root,double x,double y){ // draw tree
	if(root->left==NULL && root->right ==NULL){
		return fig;
	}
	Point2D *temp;
	Figure * lastfig;
	temp=(Point2D*)malloc(sizeof(Point2D));

	
	temp->flag=FALSE;
	temp->x=iter_p->x;
	temp->y=iter_p->y;
	temp->next=NULL;

	
	if(root->left!=NULL){
		
		iter_p=new_node_write(iter_p,-40,-30);
		iter_p->next=NULL;
		fig->next=start_figure(2000,2000);
		set_color(fig->next,fig->c);
		fig=fig->next;
		set_thickness_resolution(fig,0.1,CIRCLE_RESULATION);
		fig->data_flag=TRUE;
		iter_p=draw_circle(fig,CIRCLE_R,iter_p->x,iter_p->y);
		iter_p->next=NULL;
		fig->data=root->left->data;
		
		draw_tree_to_point(fig,iter_p,root->left,x,y);
	
		

	}
	while(fig->next!=NULL){
		fig=fig->next;
	}
	while(iter_p->next!=NULL){
		iter_p=iter_p->next;
	}
	if(root->right !=NULL){
		
		iter_p->next=temp;
		temp=new_node_write(temp,40,-30);
		temp->next=NULL;
		fig->next=start_figure(2000,2000);
		set_color(fig->next,fig->c);
		fig=fig->next;
		set_thickness_resolution(fig,0.1,CIRCLE_RESULATION);
		fig->data_flag=TRUE;
		iter_p=draw_circle(fig,CIRCLE_R,temp->x,temp->y);
		fig->data=root->right->data;
		iter_p->next=NULL;
		
		return draw_tree_to_point(fig,iter_p,root->right,x,y);
	}
	
	
}
Point2D* new_node_write(Point2D * iter_p,double x,double y){ // tree circle between jump
	Point2D *root;
	root=iter_p;
	iter_p->next=(Point2D*)malloc(sizeof(Point2D));
	

	iter_p->next->x=iter_p->x +x;
	iter_p->next->y=iter_p->y +y;
	iter_p->next->flag=FALSE;

	iter_p=iter_p->next;

	iter_p->next=(Point2D*)malloc(sizeof(Point2D));
	iter_p->next-> x= iter_p->x + x;
	iter_p->next-> y= iter_p->y + y;
	iter_p->next->flag=TRUE;

	iter_p=iter_p->next;
	iter_p->next=(Point2D*)malloc(sizeof(Point2D));
	iter_p->next->x=iter_p ->x + x;
	iter_p->next->y=iter_p ->y + y;
	iter_p->next->flag=FALSE;	
	iter_p=iter_p->next;
	iter_p->next=NULL;

	return  iter_p;
}

Point2D* draw_circle(Figure *fig,double r,double x,double y){ // draw circle for tree
	Point2D * iter_p;
	iter_p=(Point2D*)malloc(sizeof(Point2D));
	double end_x=x+r ;
	double start_x=x-r;
	fig->point=iter_p;
	iter_p->x=start_x;
	iter_p->flag=TRUE;
	iter_p->y=y;
	

	while(start_x<=end_x){
		iter_p->next=(Point2D*)malloc(sizeof(Point2D));
		iter_p->next->flag=TRUE;
		iter_p->next->x=iter_p->x + fig->resolution;
		iter_p->next->y=sqrt(abs(r*r -(start_x - x)*(start_x - x)))+y;
		
		start_x=start_x + fig->resolution;
		iter_p=iter_p->next;
		iter_p->next=NULL;
		

	}
	start_x=start_x -2*r;
	iter_p->x=start_x;
	iter_p->flag=FALSE;
	iter_p->y=-sqrt(abs(r*r -(start_x - x)*(start_x - x)))+y;

	while(start_x<=end_x){
		iter_p->next=(Point2D*)malloc(sizeof(Point2D));
		iter_p->next->flag=TRUE;
		iter_p->next->x=iter_p->x + fig->resolution;
		iter_p->next->y=-sqrt(abs(r*r -(start_x - x)*(start_x - x)))+y;
		start_x=start_x + fig->resolution;
		iter_p=iter_p->next;
		iter_p->next=NULL;
		

	}

	iter_p->x=x;
	iter_p->y=y;
	
	
	
	iter_p->flag=FALSE;
	iter_p->next=NULL;
	return iter_p;
}

Tree *add_num(Tree *iter, int num){ // build tree
	if(iter == NULL){
		iter=(Tree*)malloc(sizeof(Tree));
		iter->left=NULL;
		iter->right=NULL;
		iter->data=num;
	}
		
	if(num < iter->data)
		iter->left = add_num(iter->left, num);
	else if(num > iter->data)
		iter->right = add_num(iter->right, num);
	return iter;

}

	

void draw_ellipse(Point2D * centre, Point2D * width_height){ // funcition draw elips first up than come back draw down
	double start_y=centre->y;
	double start_x=centre->x -width_height->x/2;
	double end_x=centre->x+width_height->x/2;
	double y=centre->y;
	double controll;
	controll=start_x;
	while(controll < end_x){
		centre->x=controll;
		
		centre->y=(width_height->y/2)*sqrt(1.0 - (controll*controll) / ((width_height->x/2)*(width_height->x/2))) + y;
		centre->flag=1;
		centre->next=(Point2D*)malloc(sizeof(Point2D));
		centre=centre->next;
		centre->next=NULL;
		controll=controll +ELIPS_RESULATION;
	}
	
	centre->x=start_x;
	centre->y=start_y;
	centre->flag=FALSE;
	centre->next=(Point2D*)malloc(sizeof(Point2D));
	centre=centre->next;
	controll=start_x;


	
	

	while(controll < end_x){
		centre->x=controll;
		centre->y=y -(width_height->y/2)*sqrt(1.0 - (controll*controll) / ((width_height->x/2)*(width_height->x/2)));
		centre->flag=1;
		centre->next=(Point2D*)malloc(sizeof(Point2D));
		centre=centre->next;
		centre->next=NULL;

		controll=controll +ELIPS_RESULATION;
	}

	
		
	

}
void draw_polygon(Point2D * poly_line){ // draw plygone  funcition draw elips first up than come back draw down // function can't draw odd number line poylgone
	double i=0, line_num=POLYGONE_LINE_NUM;  // plynom line num
	double x=-20,y=0.0;
	double r=20.0;
	
	while(i<(line_num/2)+1){
		poly_line->x=x;

		poly_line->y=sqrt((r*r)- x*x);
		poly_line->flag=TRUE;
		poly_line->next=(Point2D*)malloc(sizeof(Point2D));
		poly_line=poly_line->next;
		x=x +(2*r)/(line_num/2);
		i++;
		
	}
	x=x - (2*r)/(line_num/2);
	x=x - (2*r)/(line_num/2);
 	
	while(i<line_num+1){
		poly_line->x=x;
		poly_line->y=-sqrt(r*r- x*x);
		poly_line->flag=TRUE;
		poly_line->next=(Point2D*)malloc(sizeof(Point2D));
		poly_line=poly_line->next;
		x=x - (2*r)/(line_num/2);
		i++;
	}
	poly_line->flag=FALSE;
	poly_line->x=0;
	poly_line->y=0;
	poly_line->next=NULL;
		
}
void draw_polyline(Figure *fig, Point2D * poly_line, int n){ // first build line 
	int i=0;
	Point2D *iter,*root;
	//iter=poly_line;
	iter=(Point2D*)malloc(sizeof(Point2D));
	iter->next=NULL;
	root=iter;
	
	
	for(i=0 ; i<n ; i++)
	{
		poly_line[i].x=i;
		poly_line[i].y=i*i*i;
		
		
	}
	for(i=0;i<n-1;i++){
		iter->x=poly_line[i].x;
		iter->y=poly_line[i].y;
		iter->flag=TRUE;
		iter->next=(Point2D*)malloc(sizeof(Point2D));
		iter= iter->next;
		iter->next=NULL;
		
	}
	iter->next=NULL;
	iter->flag=FALSE;
	iter->x=0;
	iter->y=0;
	fig->point=root;
	fig->next=NULL;	
}
double my_pow(double x){ 
	return x*x;
}
double f3x_fun(double x){
	return x*x*x;
}
double fx_fun(double x){
	return x*x -9; 
}
void export_eps(Figure* fig,char *file_name){ // print eps format
	FILE *fp;
	int i=0;
	double start_x, end_x,most_big_y,most_small_y;
	start_x=fig->point->x;
	most_small_y=fig->point->y;
	most_big_y=fig->point->y;
	Point2D * iter_p;
	Figure *root;
	root=fig;
	fp=fopen(file_name,"w+");
	fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
 	fprintf(fp,"%%%%BoundingBox:%f %f %f %f\n",-fig->width/2,-fig->height/2,fig->width/2,fig->height/2);
 	
 	
 	while(fig!=NULL){ 
		iter_p =fig->point;
			fprintf(fp,"%f setlinewidth\n",fig->thickness);
			fprintf(fp, "%d %d %d setrgbcolor\n",root->c.r,root->c.g,root->c.b );
 			fprintf(fp,"%f %f moveto\n",fig->point->x,fig->point->y);
		if(fig->data_flag==TRUE){
			fprintf(fp, "%f  %f moveto\n",iter_p->x +40,iter_p->y -5);
			fprintf(fp, "/Times-Roman findfont 20 scalefont setfont\n");
			fprintf(fp, "(%d) show\n",fig->data );
			fprintf(fp, "%f  %f moveto\n",iter_p->x,iter_p->y );
		}	
 		while(iter_p!=NULL){
 		if(iter_p->flag==1){
 			fprintf(fp,"%lf %lf lineto\n",iter_p->x, iter_p->y );
 			if(most_big_y < iter_p->y){
 				most_big_y=iter_p->y;
 				end_x=iter_p->x;
 				
 			}
 			if(most_small_y > iter_p->y)
 				most_small_y=iter_p->y;
 		}
 		else{
 			fprintf(fp,"%f  %f moveto\n",iter_p->x,iter_p->y );
 		}
 		
 		iter_p=iter_p->next;
 		
		i++;
 	}
		fprintf(fp, "stroke\n");
		fig=fig->next;
 	}
 	
	
 	fclose(fp);
}		
void draw_fx(Figure * fig, double f(double x),double end_x,double step_size){ // functions draw; example f(x) cos
	Figure *iter;
	iter =fig;
	Point2D * iter_p;
	fig->point=(Point2D*)malloc(sizeof(Point2D));
	iter_p=fig->point;
	double start_x=end_x-step_size;
	iter_p->next=NULL;
	int i=0;
	while(start_x<end_x){
		iter_p->x=start_x;
		iter_p->y=f(iter_p->x);
		iter_p->flag=1;
		iter_p->next=(Point2D*)malloc(sizeof(Point2D));
		iter_p=iter_p->next;
		iter_p->next=NULL;
		start_x=start_x + fig->resolution;
		
	}
	iter_p->x=start_x;
	iter_p->y=f(iter_p->x);
	iter_p->flag=1;
	iter_p->next=NULL;

}
void set_color(Figure *fig,Color c){
	if(fig==NULL) return;
	fig->c=c;
}
void set_thickness_resolution(Figure *fig,double thickness, double resolution){ // set resulation and thickness
	
	fig->resolution=resolution;
	fig->thickness=thickness;
}

Figure * start_figure(double width, double height){ // start figure , make fig node
	Figure * root;
	Figure * iter;
	root=(Figure*)malloc(sizeof(Figure));
	iter=root;
	root->width=width;
	root->height=height;
	root->next=NULL;
	return root;



}


