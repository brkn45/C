#ifndef lib
#define lib

#define POLYGONE_LINE_NUM 8 // alone pair num 
#define TRUE 1
#define FALSE 0
#define CIRCLE_R 50
#define ELIPS_RESULATION 0.001
#define CIRCLE_RESULATION 0.01
typedef struct color{
	int r;
	int g;
	int b;

}Color;

typedef struct point_ll{
	double x;
	double y;
	int flag;
	struct point_ll *next;
}Point2D;

typedef struct fig_ll{
	double width;
	double height;
	double thickness;
	double resolution;
	Color c;
	int data;
	int data_flag;
	struct point_ll *point;
	struct fig_ll *next;

}Figure;



typedef struct tree{
  int data;
  struct tree *left, *right;
}Tree;

Figure * start_figure(double width, double height);
void set_thickness_resolution(Figure *fig,double thickness, double resolution);
void set_color(Figure * fig, Color c);
void draw_fx(Figure * fig, double f(double x),double end_x,double step_size);

void draw_polygon(Point2D * poly_line);
void draw_ellipse(Point2D * centre, Point2D * width_height);
void draw_binary_tree(Tree * root);

void resize_figure(Figure* fig, Point2D *start_roi, Point2D *end_roi);
void append_figures(Figure * fig1, Figure * fig2);
void export_eps(Figure * fig, char * file_name);
void ll_free(Figure *fig);
void draw_binary_tree(Tree *root);
Figure*  draw_tree_to_point(Figure *fig ,Point2D *point,Tree *root,double x,double y);
double fx_fun(double x);
double f3x_fun(double x);
double my_pow(double x);
Point2D* draw_circle(Figure *fig,double r,double x,double y);
Point2D* new_node_write(Point2D * iter_p,double x,double y);
Tree *add_num(Tree *iter, int num);
void draw_polyline(Figure *fig, Point2D * poly_line, int n);
void scale_figure(Figure *fig, double scale_x, double scale_y);
void append_figures(Figure *fig1,Figure *fig2);

#endif