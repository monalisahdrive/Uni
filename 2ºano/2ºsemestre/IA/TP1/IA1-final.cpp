#include <iostream>
#include <stack>
#include <queue>
#include <math.h>
#include <vector>
#include <bits/stdc++.h>
#define INF 10000000
using namespace std;


class Node {
    int t[4][4]; //matriz para guardar o tabuleiro
    int zx, zy;  //posição do 0
    int uni_array[16];

    //d-> profundidade
    //g-> guarda o quanto um nó já andou
    //h-> guarda o resultado da heurística usada no algoritmo greedy e A*
    public:
        int d,g,h,f;
        Node* p;

        //construtor para a configuração inicial e final
        Node() {
          p = NULL;
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              scanf("%d", &t[i][j]);

              if (t[i][j] == 0) {
                zx = i;
                zy = j;
              }
            }
          }

          g = 0;
          d = 0;
          f = 0;
        }

        //construtor para sucessores(depois de movimentar o 0)
        Node(Node* parent, int dir) {
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) t[i][j] = parent->t[i][j];
          }

          zx = parent->zx;
          zy = parent->zy;
          d = parent->d + 1;

          switch (dir) {
            case 1: // cima
              if (zx > 0) {
                t[zx][zy] = t[zx - 1][zy];
                t[zx - 1][zy] = 0;
                zx -= 1;
              }
              break;

            case 2: // baixo
              if (zx < 3) {
                t[zx][zy] = t[zx + 1][zy];
                t[zx + 1][zy] = 0;
                zx += 1;
              }
              break;

            case 3: // esquerda
              if (zy > 0) {
                t[zx][zy] = t[zx][zy - 1];
                t[zx][zy - 1] = 0;
                zy -= 1;
              }
              break;

            case 4: // direita
              if (zy < 3) {
                t[zx][zy] = t[zx][zy + 1];
                t[zx][zy + 1] = 0;
                zy += 1;
              }
              break;
            }

          p = parent;
          g = 0;
          h = 0;
          f = 0;
        }

        //escreve a matriz
        void write() {
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              printf("%2d ", t[i][j]);
            }
            printf("\n");
          }
          printf("\n");
        }

        //transforma o tabuleiro num array unidimensional
        void uniArray() {
          int k = 0;

          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              uni_array[k] = t[i][j];
              k++;
            }
          }
        }

        //verifica se a matriz inicial consegue chegar à final
        bool solvable(){
          uniArray();
          int count = 0;

          for (int i = 0; i < 16; i++) {
            if (uni_array[i] == 0) continue;
            for (int j = i; j < 16; j++) {
              if (uni_array[i] > uni_array[j] && uni_array[j] != 0) count++; // conta as inversões
            }
          }

          return (((4 - zx) % 2 == 0 && count % 2 != 0) || ((4 - zx) % 2 != 0 && count % 2 == 0));
        }

        //verifica se duas matrizes são iguais
        bool equals(Node* n) {
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              if (t[i][j] != n->t[i][j]) return false;
            }
          }

          return true;
        }

        //somatório do número de peças fora do lugar comparando com a configuração final
        int outOfPlace(Node* final) {
          int r = 0; //somatório das peças fora do lugar
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              if (t[i][j] != final->t[i][j]) r++;
            }
          }

          return r;
        }

        //somatório das distâncias de cada peça ao seu lugar na configuração final
        int manhattanDistance(Node* final) {
          int r = 0;
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                  if (t[i][j] == final->t[k][l]) r+= abs(k-i)+abs(l-j);
                }
              }
            }
          }

          return r;
        }
};


//verifica se um nó não é repetido
bool notRepeated(Node* actual, Node* parent) {
  if (parent == NULL) return true;
  if (actual->equals(parent)) return false;
  return false || notRepeated(actual, parent->p);
}

//busca em profundidade
void dfs(Node* first, Node* final) {
  stack<Node*> s;
  s.push(first);

  while(!s.empty()) {
    Node* actual = s.top();
    s.pop();

    if(actual->equals(final)) { //verifica se é igual ao tabuleiro final
      printf("--------- SOLUTION ---------\ndepth = %d\n", actual->d);
      actual->write();
      return;
    }

    if (notRepeated(actual, actual->p)) { //verifica se não é um tabuleiro repetido
      for (int i = 1; i <= 4; i++) {
        Node* successor = new Node(actual,i);
        s.push(successor);
        }

      } else free(actual);
  }

  printf("Solution not found.\n");
}

//busca em largura
void bfs(Node* first, Node* final) {
  queue<Node*> q;
  q.push(first);

  while(!q.empty()) {
    Node* actual = q.front();
    q.pop();

    if (actual->d == 100) return; //profundidade de paragem

    if(actual->equals(final)) { //verifica se é igual ao tabuleiro final
      printf("--------- SOLUTION ---------\ndepth = %d\n", actual->d);
      actual->write();
      return;
    }

    if (notRepeated(actual, actual->p)) { //verifica se o tabuleiro não é reperido
      for (int i = 1; i <= 4; i++) {
        Node* successor = new Node(actual,i);
        q.push(successor);
      }

    } else free(actual);
  }

  printf("Solution not found.\n");
}

//busca iterativa em profundidade
void idfs(Node* first, Node* final) {
  stack<Node*> s;
  for (int i = 0; i < INF; i++) {
    s.push(first);

    while(!s.empty()) {
      Node* actual = s.top();
      s.pop();

      if (actual->equals(final)) { //verifica se é igual ao tabuleiro final
        printf("--------- SOLUTION ---------\ndepth = %d\n", actual->d);
        actual->write();
        return;
      }

      if (actual->d <= i && notRepeated(actual, actual->p)) { //verifica se o tabuleiro não é reperido
        for (int j = 1; j <= 4; j++) {
          Node* successor = new Node(actual,j);
          s.push(successor);
        }

      } else free(actual);
    }
  }

  printf("Solution not found.\n");
}

//comparador do algoritmo A*
//verifica que nó têm o menor f
//põem os nós por ordem crescente
struct ASearchComparator {
  bool operator()(const Node* n1, const Node* n2) {
    return n1->f > n2->f;
  }
};

//algoritmo A*
void a_search(Node* first, Node* final, int alg) {
  priority_queue<Node*, vector<Node*>, ASearchComparator> q;
  q.push(first);

  //inicializa o h para o tabuleiro inicial
  if (alg == 1) first->f = first->outOfPlace(final);
  else first->f = first->manhattanDistance(final);

  while (!q.empty()) {
    Node* least_f = q.top();
    q.pop();

    for (int i = 1; i <= 4; i++) {
      Node* successor = new Node(least_f,i);
      successor->g = least_f->g + least_f->d;

      if (alg == 1) successor->h = successor->outOfPlace(final);
      else successor->h = successor->manhattanDistance(final);

      if (successor->h == 0) { //verifica se é igual ao tabuleiro final
        printf("--------- SOLUTION ---------\ndepth = %d\n", successor->d);
        successor->write();
        return;
      }

      successor->f = successor->g + successor->h;

      if (notRepeated(successor, successor->p)) q.push(successor);
    }
  }

  printf("Solution not found.\n");
}

//comparador do algoritmo greedy
//verifica que nó têm o menor h
//põem os nós por ordem crescente
struct GreedyComparator {
  bool operator()(const Node* n1, const Node* n2) {
    return n1->h > n2->h;
  }
};

//algoritmo Greedy
void greedy(Node* first, Node* final, int alg) {
  priority_queue<Node*, vector<Node*>, GreedyComparator> q;
  q.push(first);

  while (!q.empty()) {
    Node* actual = q.top();
    q.pop();

    if (actual->equals(final)) {
      printf("--------- SOLUTION ---------\ndepth = %d\n", actual->d);
      actual->write();
      return;
    }

    if (notRepeated(actual, actual->p)) {
      for (int i = 1; i <= 4; i++) {
        Node* successor = new Node(actual,i);

        if (alg == 1) successor->h = successor->outOfPlace(final);
        else successor->h = successor->manhattanDistance(final);
        
        q.push(successor);
      }
    } else free(actual);
  }

  printf("Solution not found.");
}


int main() {
  Node* first = new Node();
  Node* final = new Node();

  if (first->solvable() == final->solvable()) {

    if (first->equals(final)) printf("Boards are identical.");

    else {
      printf("--------- SOLVABLE ---------\n");

      /*printf("=> dfs");
      dfs(first,final);*/

      /*printf("=> bfs");
      bfs(first,final);*/

      /*printf("=> idfs");
      idfs(first,final);*/

      printf("=> A*-1");
      a_search(first,final,1);

      /*printf("=> A*-2");
      a_search(first,final,2);*/

      /*printf("=> greedy-1");
      greedy(first,final,1);*/

      /*printf("=> greedy-2");
      greedy(first,final,2);*/
    }
  } else printf("It is impossible to reach a solution.\n");

  return 0;
}
