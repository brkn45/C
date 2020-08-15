#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct linklist {
	int data;
	char letter;
	struct linklist *left, *right;
}node;

char* frequency_fun(FILE *fp,int *index); //read character in reference.txt 
int * frequency_int_fun(FILE *fp,int index,char *letters); // I counted how many times it repeats. push let_num array
void print_fun(char *letters, int *let_num,int * index); // if wantto saw letnum and letters array 
void heap_fill_array(node ** heap,char *letters,int *let_num,int index); // do let_num and letters array Heap struct array 
void sort_heap(node **heap,int index); // heap sorted from small to large
node * build_tree(node **heap,int index); //  haufman tree build
node  *add_node(node * heap1,node * heap2); // make node 
void print2D(node *root); // if you want print tree
void print2DUtil(node *root, int space);// helper functiom
void read_text(FILE * fp, node * root,FILE *fp_bin); // read text and traverse binnary
int binnary_fun(char ch,node * root,char* bin_num,int index); //searching for character and converting it into binary system
void array_free(char * array);// helper function read_text fun
void find_message(FILE *fp_encode, node *root,FILE *fp_decode); //convert to bin and charecter
void calulate_file_size(FILE *fp_encode,FILE *fp_decode); // calculate size

int main(){
	char  *letters;
	int *let_num,index=0,i=0;
	
	letters=(char*)malloc(sizeof(char));
	let_num=(int *)malloc(sizeof(int));
	FILE * fp_ref;
	FILE * fp_bin;
	FILE *fp_message;
	FILE * fp_encode;
	FILE * fp_decode;
	
	fp_message=fopen("message.txt","r+");
	fp_encode=fopen("encoded.dat","w+b");
	fp_decode=fopen("decoded.txt","w+");
	fp_bin=fopen("binnary.txt","w+");
	fp_ref=fopen("reference.txt","r");
	
	letters=frequency_fun(fp_ref,&index);
	let_num=frequency_int_fun(fp_ref,index,letters);
	
	//print_fun(letters,let_num,&index);
	
	node **heap,*root;
	heap=(node**)malloc(index*sizeof(node));
	heap_fill_array(heap,letters,let_num,index);
	sort_heap(heap,index);
	
	root=build_tree(heap,index);
	
	
	//print2D(root);
	
	read_text(fp_ref,root,fp_bin);// print binnary.txt
	read_text(fp_message,root,fp_encode); // print encoded.dat

	find_message(fp_encode,root,fp_decode); // print decoded.txt
	calulate_file_size(fp_encode,fp_decode);// print terminale

	fclose(fp_bin);
	fclose(fp_message);
	fclose(fp_encode);
	fclose(fp_decode);
	fclose(fp_ref);


	return 0;

}
void calulate_file_size(FILE *fp_encode,FILE *fp_decode){ // go end file than print
	long int encoded_size,decoded_size;
	fseek(fp_encode,0,SEEK_END);
	fseek(fp_decode,0,SEEK_END);
	
	encoded_size=ftell(fp_encode);
	decoded_size=ftell(fp_decode);
	
	printf("encoded.dat size:%ld\n",encoded_size );
	printf("decoded.txt:%ld\n",decoded_size );
}
void find_message(FILE *fp_encode, node *root,FILE *fp_decode){
	fseek(fp_encode,0,SEEK_SET);
	char bin;
	node *iter;
	iter=root;
	while(!feof(fp_encode)){// go right is 1 , left is zero
		fread(&bin,sizeof(char),1,fp_encode);
		if(feof(fp_encode))
			break;
		if(bin=='1'){
			iter=iter->right;
		}
		else if(bin=='0'){
			iter=iter->left;

		}
		else{
			fprintf(fp_decode,"%c",iter->letter );
			iter=root;
		}
	}
}
int binnary_fun(char ch,node * root,char* bin_num,int index){ 
	int sum=0;
	if(root->letter==ch){ // if find character , than write bin_num array
		return 1;
	}

	if(root->right!=NULL){
		sum = binnary_fun(ch,root->right,bin_num,index+1);
		if(sum==1){
			bin_num[index]='1';
			return 1;
		}
	}
	
	if(root->left!=NULL){
		sum = binnary_fun(ch,root->left,bin_num,index+1);
		if(sum==1){
			bin_num[index]='0';
			return 1;
		}	
	}
	
	bin_num[index]='\0';
	if(root->left==NULL || root->right==NULL)
		return 0;
}
void read_text(FILE * fp, node * root,FILE *fp_bin){
	
	int index=0;
	char * p;
	char ch,bin_num[200];
	p=bin_num;
	fseek(fp,0,SEEK_SET);
	while(!feof(fp)){
		index=0;
		array_free(bin_num);
		fscanf(fp,"%c",&ch);
		if(feof(fp))
			break;
		binnary_fun(ch,root,bin_num,index);
		fprintf(fp_bin, "%s\n",bin_num );
	}
	
}
void array_free(char * array){ // for new code
	int i=0;

	while(i<200){
		array[i]='\0';
		i++;
	}
}
void print2DUtil(node *root, int space) { 
    // Base case 
    if (root == NULL) 
        return; 
  	 space += 10; 
  	print2DUtil(root->right, space); 
  
    
    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 

    printf("%d %c\n", root->data,root->letter);
  	print2DUtil(root->left, space); 
} 
  

void print2D(node *root) 
{ 
	print2DUtil(root, 0); 
}
node * build_tree(node **heap,int index){
	int i=0;
	node * temp,*root;
	temp=(node*)malloc(sizeof(node));	
	while(i<index){
		temp=add_node(heap[0],heap[1]);
		i++;
		
		heap[1]=temp; // shift left and calculete another
		root=temp;
		heap=heap+1;
		sort_heap(heap,index-i);
	}

	return root;		
}

node  *add_node(node * heap1,node * heap2){
	node *root;
	root=(node*)malloc(sizeof(node));

	if(heap1->data > heap2->data){
		root->right=heap1;
		root->left=heap2;
	}
	else{
		root->right=heap2;
		root->left=heap1;

	}

	root->data= heap1->data+heap2->data;
	root->letter='*';

	
	return root;
}

void sort_heap(node **heap,int index){
	int i, j;
	node *temp;
	temp=(node*)malloc(sizeof(node));
   for (i = 0; i <= index; i++){
          
       for (j = 0; j <index-i; j++) { 
           if (heap[j]->data > heap[j+1]->data){
           		temp=heap[j];
           		heap[j]=heap[j+1];
           		heap[j+1]=temp;

           } 
        } 
     }        
}
void heap_fill_array(node ** heap,char *letters,int *let_num,int index){ // make struct array // for sort
	int i=0;
	for(i=0;i<=index;i++){
		heap[i]=(node*)malloc(sizeof(node));
		heap[i]->data=let_num[i];
		heap[i]->letter=letters[i];
		heap[i]->right=NULL;
		heap[i]->left=NULL;
	}
}
void print_fun(char *letters, int *let_num,int * index){
	int i=0;

	while(i<=*index){
		printf("İ :%d letters:%c let_num:%d\n",i,letters[i],let_num[i] );
		i++;
	}
}
int * frequency_int_fun(FILE *fp,int index,char *letters){ // calculate frequence character than puting let_num array
	int i=0,counter=0,*let_num;
	char ch;
	let_num=(int*)malloc(sizeof(int)*index);
	while(i<=index){
		fseek(fp,0,SEEK_SET);
		while(!feof(fp)){	
			fscanf(fp,"%c",&ch);
			if(letters[i]==ch)
				counter++;
		}
		let_num[i]=counter;
		counter=0;
		i++;
	}
	let_num[i-1]=let_num[i-1]-1;
	return let_num;
}
char* frequency_fun(FILE *fp,int *index){ //
	int i=0,k=0,counter=0;
	char ch,let,*letters;
	letters=(char*)malloc(sizeof(char));
	letters[0]='\0';
	
	while(!feof(fp)){
		fscanf(fp,"%c",&ch);
		while(k<i){
			if(ch==letters[k]){
				fscanf(fp,"%c",&ch);
				
				if(feof(fp)){ 
					break;
				}
				k=0;
			}
			k++;	
		}
		if(feof(fp)){ 
			break;
		}	
		letters[i]=ch;

		i++;
		k=0;
		letters = (char *) realloc(letters, (i+1) * sizeof(char));		
	}
	k=0;

	*index=i-1; //last index
	return letters;
}