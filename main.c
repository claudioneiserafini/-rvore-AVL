// |------------------------------------------------ Bibliotecas 
#include <stdio.h>
#include <stdlib.h>

// |-------------------------------------------------- Struct 
typedef struct Node{
  int number;
  struct Node *left, *right;
  int height;
}Node;

// |------------------------------------------------ Prototipação
Node* createNode(int);
// Interface
void menu(Node*);
void order(Node*);
// Ações
Node* insert(Node*,int);
Node* del(Node*,int);
void search(Node*, int);
// Ordens
void preOrder(Node*);
void inOrder(Node*);
void posOrder(Node*);
// Auxiliadores
int bigger(int ,int );
int height(Node*);
int balancingFactor(Node*);
Node* balancing(Node*);
// Rotações
Node* rightRotate(Node*);
Node* leftRotate(Node*);
Node* rightLeftRotate(Node*);
Node* leftRightRotate(Node*);

// |----------------------------------------------- Implementação MAIN
int main(){
  struct Node *root = NULL;

  // Valores de exemplo
  root = insert(root, 1);
  root = insert(root, 2);
  root = insert(root, 3);
  root = insert(root, 8);
  root = insert(root, 10);
  root = insert(root, 11);
  root = insert(root, 12);
  root = insert(root, 20);
  root = insert(root, -5);
  root = insert(root, 3);
  root = insert(root, 10);
  root = insert(root, 9);
 
  // Chama Menu
  menu(root);

  return 0;
}

// |----------------------------------------------- Implementação MENU
void menu(Node* root){
  int value;
  int choice;
  system("tput reset");

  while (6) {
    printf("|========== |MENU| ==========|\n");
    printf("| 1. Inserir Livro\n");
    printf("| 2. Remover Livro\n");
    printf("| 3. Buscar Livro\n");
    printf("| 4. Ordenação\n");
    printf("| 5. Limpar console\n");
    printf("| 6. Sair\n");
    printf("|\n");
    printf("| Escolha uma opção: ");
    scanf("%d", &choice);
    printf("|============================|\n");

    switch (choice) {
      case 1: /*Inserir*/
        printf("| Insira o código ISBN: ");
        scanf("%d", &value);
        root = insert(root, value);
        system("tput reset");
      break;

      case 2: /*Remover*/
        printf("| Insira o código ISBN: ");
        scanf("%d", &value);
        root = del(root, value);
        //system("tput reset");
      break;

      case 3: /*Buscar*/
        printf("| Insira o código ISBN: ");
        scanf("%d", &value);
        search(root, value);
      break;
        
      case 4: /*Ordenar*/
        order(root);
      break;

      case 5: /*Limpar*/
        system("tput reset");
      break;

      case 6: /*Finalizar*/
        system("tput reset");
        printf("|==========| AVL |===========|\n");
        printf("|\t\t\tALUNO\n");
        printf("| \tClaudionei L. Serafini.\n");
        printf("|============================|\n");
        exit(6);
      break;
          
      default:
        printf("|\n| [!] Escolha uma opção valida. [!]\n|\n");
      break;
    }
  }
}

// |----------------------------------------------- Implementação ORDENAÇÃO
void order(Node* root){
  int choice;
  system("tput reset");
  printf("\n|========== |Ordenação| ==========|\n");
  printf("| 1. Em Ordem\n");
  printf("| 2. Pós Ordem\n");
  printf("| 3. Pré Ordem\n");
  printf("| 4. Todas Ordens\n");
  printf("| 5. Voltar\n");
  printf("|\n");
  printf("| Escolha uma opção: ");
  scanf("%d", &choice);
  printf("|============================|\n");

  switch (choice) {
    case 1: 
      printf("|\n| Livros - Em Ordem: \n| ");
      inOrder(root);
      printf("\n|\n");
    break;

    case 2: 
      printf("|\n| Livros - Pós Ordem: \n| ");
      posOrder(root);
      printf("\n|\n");
    break;

    case 3: 
      printf("|\n| Livros - Pré Ordem: \n| ");
      preOrder(root);
      printf("\n|\n");
    break;

    case 4: 
      system("tput reset");
      printf("|============================|\n");
      printf("|\n| Livros - Em Ordem: \n| ");
      inOrder(root);
      printf("\n|\n| Livros - Pós Ordem: \n| ");
      posOrder(root);
      printf("\n|\n| Livros - Pré Ordem: \n| ");
      preOrder(root);
      printf("\n|\n");
    break;

    case 5:
      system("tput reset");
    break;

    default:
      printf("|\n| [!] Opção invalida, voltando para MENU. [!]\n|\n");
    break;
  } 
}

// |----------------------------------------------- Implementação CRIAR NODE

/*
Função que cria um novo nó 
value -> valor a ser inserido no nó 
Retorna: o endereço do nó criado;
*/

Node *createNode(int value) {
  Node *root = (struct Node *)malloc(sizeof(struct Node));

  root->number = value; // Recebe valor a ser inserido;
  root->left = NULL;    // Define como NULL;
  root->right = NULL;   // Define como NULL;
  root->height = 0;     // Folha;

  return root;          // Endereço;
}

// |----------------------------------------------- Implementação insert
/*
Insere um novo nó na árvore 
root -> nó da árvore 
number -> valor a ser inserido 
Retorna: endereço do novo nó ou nova raiz após o balanceamento
*/
Node* insert(Node* root, int number) {
  if (root == NULL) // Árvore vazia
    return (createNode(number));
  else{
  // Inserção será à esquerda ou à direita
  if (number <= root->number)
    root->left = insert(root->left, number);
  else if (number >= root->number)
    root->right = insert(root->right, number);
  else
    return root;
  }
  
  // Recalcula a height de todos os nós entre a raiz e o novo nó inserido
  root->height = bigger(height(root->left), height(root->right)) + 1;

  // Verifica a necessidade de rebalancear a árvore
  root = balancing(root);

  return root;
}
 // |----------------------------------------------- Implementação DELETE
Node* del(Node *root, int number){
  if (root == NULL){ // Se o valor não existir
    printf("|\n| [!] Codigo ISBN invalido. [!]\n|\n");
    return NULL;
  }else{ 
    // Removendo nó folha;
    if(root->number == number){
      if(root->left == NULL && root->right == NULL){
        free(root);
        return NULL;
      } 
      else{
        // Removendo nó que possui dois filhos;
        if(root->left != NULL && root->right != NULL){
          Node *aux = root->left;
            while(aux->right != NULL){
              aux = aux->right;
            }
            root->number = aux->number;
            aux->number= number; // Elemento trocado
            root->left = del(root->left, number);
            return root;
        }
      else{
        // Removendo nó que possui apenas um filho;
        Node *aux;
        if(root->left != NULL)
          aux= root->left;
        else
          aux= root->right;
          free(root);
        return aux;
      } 
    } 
  } else {
    if(number < root->number){
      root->left = del(root->left, number);
    }else{
      root->right = del(root->right, number);
    }
  }
  // Recalcula a height de todos os nós entre a raiz e o novo nó inserido
  root->height = bigger(height(root->left), height(root->right)) + 1;

  // Verifica a necessidade de rebalancear a árvore
  root = balancing(root);

  return root;
  }
}

// |----------------------------------------------- Implementação BALANCING
Node* balancing(Node *root){
  int bf = balancingFactor(root); 

  // Rotação ESQUERDA
  if (bf < -1 && balancingFactor(root->right) <= 0){
    root = leftRotate(root);
    //printf("\nEnntrou1\n");
  }

  // Rotação DIREITA
  else if(bf > 1 && balancingFactor(root->left) >= 0){
    root = rightRotate(root);
    //printf("\nEnntrou2\n");
  }

  // Rotação DUPLA ESQUERDA
  else if (bf > 1 && balancingFactor(root->left) < 0){
    root = leftRightRotate(root); 
    //printf("\nEnntrou3\n");
  }

  // Rotação DUPLA DIREITA
  else if (bf < -1 && balancingFactor(root->right) > 0 ){
    root = rightLeftRotate(root);
    //printf("\nEnntrou4\n");
  } 

 return root;
}

// |----------------------------------------------- Implementação BUSCAR
void search(Node *root, int value){
  printf("|\n| Caminho até o elemento [%d]:\n| ", value);
  while (1){
    printf("[%i] -> ", root->number);
    if (value == root->number){
      printf("[Encontrado]\n|\n");
      return;
    }
    if (value > root->number){
      if (root->right == NULL)
      {
        printf("[?]\n| [!] Elemento não encontrado. [!]\n|\n");
        return;
      }
      root = root->right;
    }
    else
    {
      if (root->left == NULL)
      {
        printf("[?]\n| [!] Elemento não encontrado. [!]\n|\n");
        return;
      }
      root = root->left;
    }
  }
}

// |----------------------------------------------- Implementação height
/*
Retorna a height de um nó ou 0 caso ele seja null
*/

int height(Node *N) {
  if (N == NULL){
    return 0;
  }  
  return N->height;
}

// |----------------------------------------------- Implementação bigger

/*
Retorna o bigger dentre dois valores 
a, b -> height de dois nós da árvore
*/

int bigger(int a, int b) {
  return (a > b) ? a : b; // Operador ternario
}


// |----------------------------------------------- Implementação FATOR BALANCEAMENTO

/*
Calcula e retorna o fator de balancenceamento de um nó
caso for -2 ou 2, significa que a árvore está desbalanceada
*/

int balancingFactor(Node* N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// |----------------------------------------------- Implementação PRÉ ORDEM
// R/E/D ou P.Esquerda

void preOrder(Node* root) {
  if (root != NULL) {
    printf("[%i] ", root->number);
    preOrder(root->left);
    preOrder(root->right);
  }
}

// |----------------------------------------------- Implementação EM ORDEM
// E/R/D ou P. Baixo

void inOrder(Node* root){
  if (root != NULL) {
    inOrder(root->left);
    printf("[%i] ", root->number);
    inOrder(root->right);
  }
}

// |----------------------------------------------- Implementação PÓS ORDEM
// E/D/R ou P. Direita
void posOrder(Node* root){
  if (root != NULL) {
    posOrder(root->left);
    posOrder(root->right);
    printf("[%i] ", root->number);
  }
}

// |----------------------------------------------- Implementação ROTAR PRA DIREITA


Node* rightRotate(Node *r) {
  //y e f são ponteiros auxiliares para guardar os filhos.
  struct Node *y = r->left;
  struct Node *f = y->right;
  
  y->right = r;
  r->left = f;

  //recarrega height
  r->height = bigger(height(r->left), height(r->right)) + 1;
  y->height = bigger(height(y->left), height(y->right)) + 1;

  return y;
}

// |----------------------------------------------- Implementação ROTAR PARA ESQUERDA

Node* leftRotate(Node *r) {
  //y e f são ponteiros auxiliares para guardar os filhos.
  struct Node *y = r->right;
  struct Node *f = y->left;
  
  y->left = r;
  r->right = f;

  //recarrega height
  r->height = bigger(height(r->left), height(r->right)) + 1;
  y->height = bigger(height(y->left), height(y->right)) + 1;

  return y;
}

// |----------------------------------------------- Implementação ROTAÇÃO DUPLA DIREITA
Node* leftRightRotate(Node *n) {
  n->left = leftRotate(n->left);
  return rightRotate(n);
}

// |----------------------------------------------- Implementação ROTAÇÃO DUPLA ESQUERDA
Node* rightLeftRotate(Node *n) {
  n->right = rightRotate(n->right);
  return leftRotate(n);;
}

// |----------------------------------------------- FIM DO PROGRAMA