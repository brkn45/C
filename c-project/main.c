#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include <math.h>



int main(){
	Color blue = {0,0,255};
  	Color black = {0,0,0};
  	Color purple = {232, 67, 147};
  	Color yellow ={255,255,0};
  	Color red = {255,0,0};
  	Color green = {0,255,0};
	Figure *fig_cos,*fig_fx1,*fig_fx2,*fig_fx3,*fig_polyline,*fig_polygone,*fig_elips,*fig_tree,*temp;
	Point2D polyline_arr[10],start_roi,end_roi;
	double width=300;
	double height=300;
	// cos
	fig_cos=start_figure(width,height);
	fig_cos->next=NULL;
	set_thickness_resolution(fig_cos,0.1,0.1);
	set_color(fig_cos,blue);
	draw_fx(fig_cos,cos,20,40);
	export_eps(fig_cos,"cos.eps");
	// f(x)= x^2-9
	width=300;
	height=300;
	fig_fx1=start_figure(width,height);
	fig_fx1->next=NULL;
	set_thickness_resolution(fig_fx1,0.1,0.1);
	set_color(fig_fx1,black);
	draw_fx(fig_fx1,fx_fun,10,20);
	export_eps(fig_fx1,"f(x).eps");
	// f(x)=x^3
	width=1000;
	height=1000;
	fig_fx2=start_figure(width,height);
	fig_fx2->next=NULL;
	set_thickness_resolution(fig_fx2,0.1,0.1);
	set_color(fig_fx2,red);
	draw_fx(fig_fx2,f3x_fun,5,10);
	export_eps(fig_fx2,"x^3.eps");
	scale_figure(fig_fx2,1.10,1.10);
	export_eps(fig_fx2,"scale_x^3.eps");

	// F(X)=X^2
	width=300;
	height=300;
	fig_fx3=start_figure(width,height);
	fig_fx3->next=NULL;
	set_color(fig_fx3,yellow);
	set_thickness_resolution(fig_fx3,0.1,0.1);
	
	draw_fx(fig_fx3,my_pow,10,20);
	export_eps(fig_fx3,"x^2.eps");
	

	// Polyline
	

	
	width=300; height=300; 
	fig_polyline=start_figure(width,height);
	fig_polyline->next=NULL;
	set_thickness_resolution(fig_polyline,0.1,0.1);
	set_color(fig_polyline,green);
	draw_polyline(fig_polyline,polyline_arr,10);
	export_eps(fig_polyline,"plyline.eps");
	


	//POLYGONE 
	width=300; height=300; 
	Point2D *polygone;
	polygone=(Point2D*)malloc(sizeof(Point2D));
	polygone->next=NULL;
	fig_polygone=start_figure(width,height);
	fig_polygone->next=NULL;
	set_color(fig_polygone,blue);
	set_thickness_resolution(fig_polygone,0.1,0.1);
	draw_polygon(polygone);
	fig_polygone->point=polygone;
	export_eps(fig_polygone,"plygon.eps");
	scale_figure(fig_polygone,2.0,2.0);
	export_eps(fig_polygone,"plygon_scale.eps");
	scale_figure(fig_polygone,0.5,0.5);
	
	
	
	//ElİPS	
	width=400; height=400; 
	Point2D * centre;
	Point2D * width_height;
	fig_elips=start_figure(width,height);
	fig_elips->next=NULL;
	centre=(Point2D*)malloc(sizeof(Point2D));
	width_height=(Point2D*)malloc(sizeof(Point2D));
	centre->x=0;
	centre->y=0;
	width_height->x=50;
	width_height->y=30;
	set_thickness_resolution(fig_elips,0.1,0.01);
	set_color(fig_elips,green);
	draw_ellipse(centre,width_height);
	fig_elips->point=centre;
	export_eps(fig_elips,"elips.eps");
	scale_figure(fig_elips,2.0,2.0);
	export_eps(fig_elips,"elips_scale.eps");
	
	// resize
	start_roi.x = -100 , start_roi.y = -100;
	end_roi.x = 100 , end_roi.y = 100;
	resize_figure(fig_elips,&start_roi,&end_roi);
	export_eps(fig_elips,"elips_resize.eps");
	
	

	//TREE
	Tree * root;
	root=NULL;
	root=add_num(root,50);
	root=add_num(root,35);
	root=add_num(root,70);
	root=add_num(root,10);
	root=add_num(root,110);
	root=add_num(root,5);
	root=add_num(root,130);
	root=add_num(root,30);
	root=add_num(root,100);
	root=add_num(root,60);
	root=add_num(root,90);
	
	double x=0,y=400;
	width=2000; height=2000;
	fig_tree=start_figure(width,height);
	set_thickness_resolution(fig_tree,0.1,CIRCLE_RESULATION);
	set_color(fig_tree,blue);

	Point2D *point;
	point=(Point2D*)malloc(sizeof(Point2D));
	point->next=NULL;
	point=draw_circle(fig_tree,CIRCLE_R,x,y);
	fig_tree->data=root->data;
	fig_tree->data_flag=TRUE;
	draw_tree_to_point(fig_tree,point,root,x,y);
	export_eps(fig_tree,"tree.eps");
	// resize
	start_roi.x = -500 , start_roi.y = -500;
	end_roi.x = 500 , end_roi.y = 500;
	resize_figure(fig_tree,&start_roi,&end_roi);
	export_eps(fig_tree,"tree_resize.eps");
	
	append_figures(fig_cos,fig_fx1);	
	append_figures(fig_cos,fig_fx2);
	export_eps(fig_cos,"append_figure_fx.eps");
	append_figures(fig_polygone,fig_elips);	
	export_eps(fig_polygone,"append_figure_polygone+elips.eps");


	

}