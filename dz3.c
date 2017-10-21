#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DELLTREE(A) free((A)->word);free(A) //макрос для полного удаления элемента дерева(строки и самого указателя)

struct tnode { 
	char *word; 
	struct tnode *left; 
	struct tnode *right;
	};

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *p, char *w)  //добавляет слово в дерево
{	
	int cond;

	if (p == NULL){ //если указатель пустой(мы дошли до конца)
		p = talloc(); //создаем новый узел
		p->word = strdup(w); //выделяем память под слово и кладем его в поле word
		p->left = p->right = NULL; //обнуляем указатели на сыновей
		
	} 
	else if ((cond = strcmp(w, p->word)) == 0){ //иначе если мы нашли слово 
		return p; //выходим
	}
	else if (cond < 0) { //если слово лексикографически меньше идем в левую ветку
		p->left = addtree(p->left, w);
		}
	else //если больше в правую
		p->right = addtree(p->right, w);
	return p;
}

struct tnode* treeprint(struct tnode *p, char *w) //проверяет есть ли слово в дереве
{
	int cond=0;
	if (p == NULL)
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
	int cond;
	if (p == NULL){ //переделать, проверку что корень есть надо делать до
		//printf("NO SUCH WORD\n");
		return p;
	}  
	if ((cond = strcmp(w, p->word)) == 0){
		if (p -> left && p -> right) { //оба сына есть
			if (p -> right -> left == NULL)	{ //у правого сына есть левый сын 
				free(p->word); //освобождаем память от ранее хранившегося слова 
				p -> word =strdup(p -> right -> word);  //перезаписываем слово лежащее в узле
				struct tnode* tmp = p->right;  // копируем адресс правого узла
				p ->right = p -> right -> right; //перезаписываем адресс правого узла на новый
				free(tmp); //удаляем старый адресс правого узла
			}else {
				free(p->word); //освобождаем память от ранее хранившегося слова 
				p -> word = strdup(p -> right -> left -> word);
				p->right->left = removetree(p ->right ->left,p ->right -> left -> word);
			}
		}	
	
		else if (p->left){
			struct tnode* tmp2 = (p->left); //копируем адресс левого узла
			DELLTREE(p); //отчищаем текущей узел
			return tmp2; //отправляем выше по рекурсии(откуда была вызванна данная функция) адресс левого узла(вместо текущего)
		}else if(p->right){
			struct tnode* tmp3 = p->right;
			DELLTREE(p);
			return tmp3;
		}else {
			DELLTREE(p); //если нет ни левого ни правого сына просто отчищаем память
			return NULL; //возвращаем нулл выше по рекурсии
		}
	}		
	else if (cond < 0) 
		p->left = removetree(p->left, w);
	else
		p->right = removetree(p->right, w);
	return p;	
}

void print_all_tree(struct tnode *p)  //печатает всё дерево. Для тестов
{
	if (p != NULL){
		print_all_tree(p->left);
			printf("Word:%s\n",p->word);
		print_all_tree(p->right);
	}
}

void treefree(struct tnode *p) 
{
	if (p != NULL){
		if (p->left == NULL && p->right == NULL)
			free(p);
		else if (p->left != NULL)
			treefree(p->left);
		else if (p->right != NULL)
			treefree(p->right);
	}
}

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("You must input 1 file path\n");
		return 1;
	}
	const char* file_name = *++argv;  //имя файла
	char s[30];
	FILE *f;
	f = fopen(file_name,"r");
	if (errno != 0){							//если возникал ошибка 
			printf("%s:%s\n",file_name, strerror(errno));  //печатаем с каким файлом и что не так
			return errno;  //завершаем работу программы возрващая код ошибки
	}
	struct tnode* root = NULL;
	while(fscanf(f,"%s", s) != EOF){
		if (s[0] =='+'){
			root = addtree(root,s+1);
			//print_all_tree(root);
			//printf("itwas: %s\n\n", s);
		}
		else if (s[0] == '?'){
			root = treeprint(root,s+1);
		//	print_all_tree(root);
		//	printf("itwas: %s\n\n", s);
		}
		else if (s[0] == '-'){
			root = removetree(root, s+1);
		//	print_all_tree(root);
			//printf("itwas: %s\n\n", s);
		}
		else {
			printf("Wrong file format. First letter in word must be +,- or ?\n");
			treefree(root);
			return 2;
		}
	}
	//print_all_tree(root);
	treefree(root);
	fclose(f);
	return 0;
}		