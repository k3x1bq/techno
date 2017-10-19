#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELLTREE(A) {free((A)->word);free(A);}

struct tnode { 
	char *word; 
	struct tnode *left; 
	struct tnode *right;
	};

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *p, char *w)
{	
	int cond;

	if (p == NULL){
		p = talloc();
		p->word = strdup(w);
		p->left = p->right = NULL;
		
	} 
	else if ((cond = strcmp(w, p->word)) == 0){
		return p; 
	}
	else if (cond < 0) {
		p->left = addtree(p->left, w);
		}
	else 
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

struct tnode *removetree(struct tnode *p, char *w)
{
	if (p == NULL) 
	{
		printf("%s", "NO WORD\n");
		return p;
	}
	int cond;
	if ((cond = strcmp(w, p->word)) == 0){
		if (p -> left && p -> right) {
			if (p -> right -> left == NULL)	{
				p -> word = p -> right -> word;
				struct tnode* tmp = p->right;
				p ->right = p -> right -> right;
				//DELLTREE(tmp);
			}
			else {
				p -> word = p -> right -> left -> word;
				removetree(p ->right ->left,p ->right -> left -> word);
			}
		}

		else{
			if (p->left){
				struct tnode* tmp2 = (p->left); 
				//DELLTREE(p);
				return tmp2;
			}
			else if(p->right){
					struct tnode* tmp3 = p->right;
					//DELLTREE(p);
					return tmp3;
			}
		}
		return p; 
	}
	else if (cond < 0) 
		p->left = removetree(p->left, w);
	else 
		p->right = removetree(p->right, w);
	return p;	
}

int main(void){
	char s[30];
	FILE *f;
	printf("oke\n" );
	f = fopen("file","r");
	struct tnode* root = NULL;
	while(fscanf(f,"%s", s) != EOF){
		if (s[0] =='+')
			root = addtree(root,s+1);
		else if (s[0] == '?')
			root = treeprint(root,s+1);
		else if (s[0] == '-')
			root = removetree(root, s+1);
	}
	//treeprinting(root);
	fclose(f);
	return 0;
}		