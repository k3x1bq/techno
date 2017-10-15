#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100 // максимальный размер слова 


struct tnode { /* узел дерева */
	char *word; /* указатель на текст */
	struct tnode *parent;
	struct tnode *left; /* левый сын */
	struct tnode *right; /* правый сын */
}; 

/* talloc: создает tnode */
struct tnode *talloc(void)
{
	struct tnode* p = (struct tnode *) malloc(sizeof(struct tnode));
	p->word = NULL;
	return p;
}



struct tnode *addtree(struct tnode *p, char *w)
{
	int cond=0;
	//printf("oke");
	if (p->word == NULL){
		p->word = strdup(w);
		p->left = talloc();
		p->right = talloc();
		p->left->parent = p->right->parent = p;
		//printf("%p %s\n", p->parent,p->word);
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		return  p; 
	else if (cond < 0) /* меньше корня левого поддерева */
		p->left = addtree(p->left, w);
	else /* больше корня правого поддерева */
		p->right = addtree(p->right, w);
	return p;
}

struct tnode* treeprint(struct tnode *p, char *w)
{
	int cond=0;
	if (p->word == NULL)
		printf("%s NO\n", w);
	else if((cond=strcmp(w,p->word)) == 0)
		printf("%s YES\n", w);
	else if (cond < 0)
		p->left = treeprint(p->left,w);
	else 
		p->right = treeprint(p->right,w);	
	return p;
}

void freetree(struct tnode* p){
	free(p->word);
	free(p);
}

struct tnode* remove_tree(struct tnode *p, char *w){
	int cond = 0;
	//printf("oke\n");
	if (p->word == NULL)
		return p;
	else if ((cond=strcmp(w,p->word)) == 0){
		//printf("oke1\n");
		if ((p->left->word == NULL) && (p->right->word == NULL)){
			//printf("oke\n");
			freetree(p->left);
			freetree(p->right);
			freetree(p);
		}
		else if (p->right->word == NULL){
			if (p->parent->left == p)
				p->parent->left = p->left;
			else if(p->parent->right == p)
				p->parent->right = p->left;
			freetree(p);
		}
		else if (p->left->word == NULL){
			if (p->parent->left == p)
				p->parent->left = p->right;
			else if(p->parent->right == p)
				p->parent->right = p->right;
			freetree(p);
		}
	}
	else if (cond < 0){
		//printf("oke1\n");
		p->left = remove_tree(p->left,w);
		//printf("oke1\n");
	}
	else if (cond > 0){
		//printf("oke1\n");
		p->right = remove_tree(p->right,w);
	}
	return p;
}

void treeprinting(struct tnode *p)
{
	if (p->word != NULL){
		treeprinting(p->left);
			printf("Word:%s\n",p->word);
		treeprinting(p->right);
	}
}

int main(int argc, char *argv[]){
	char s[MAXWORD];
	FILE *f;
	//printf("sd");
	f = fopen("file2","r");
	struct tnode* root = talloc();
	//printf("okeM" );
	while(fscanf(f,"%s", s) != EOF){
		if (s[0] =='+')
			root = addtree(root,s+1);
		else if(s[0]=='-')
			remove_tree(root,s+1); //пока не смотри
		else if (s[0]=='?')
			treeprint(root,s+1);
			//printf("%s QUASTION MARK\n", s+1); // пока не смотри */
	}
	treeprinting(root);
	fclose(f);
	return 0;
}