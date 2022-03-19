#include <iostream>
#include <stack>
#include <queue>
#define INF 2

using namespace std;

int inicial_uni[16];

typedef struct Tabuleiro {                // mantém a matriz e posição do zero juntos
    int m[4][4]; // matriz para guardar tabuleiro de jogo
    int zx, zy;  // posição do zero
} Tab;

typedef struct Node {           // mantém a matriz e posição do zero juntos
    Tab t;  // tabuleiro de jogo
    int d;  // profundidade
    Node *p; //parent
    int c;  // função custo
} N;

void uniArray(int m[4][4]) { // transforma uma matriz bidimensional num array unidimensional
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            inicial_uni[k] = m[i][j];
            k++;
        }
    }
}

bool solvable(Tab t)
{ // verifica de que grupo de suloções o tabuleiro t é
    uniArray(t.m);
    int count = 0;
    for (int i = 0; i < 16; i++)
    {
        if (inicial_uni[i] == 0)
            continue;
        for (int j = i; j < 16; j++)
        {
            if (inicial_uni[i] > inicial_uni[j] && inicial_uni[j] != 0)
                count++; // conta as inversões
        }
    }
    // printf("count = %d\n", count);
    // fórmula do grupo
    if (((4 - t.zx) % 2 == 0 && count % 2 != 0) || ((4 - t.zx) % 2 != 0 && count % 2 == 0))
        return true;
    return false;
}

Tab read() { // lê um tabuleiro do stdin(standard input)
    Tab t;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &t.m[i][j]);
            if (t.m[i][j] == 0) { // guarda a posição do zero
                t.zx = i;
                t.zy = j;
            }
        }
    }
    return t; // devolve o tabuleiro lido
}

Tab moveZero(Tab t, int posicao) { // move a posição do zero
    switch (posicao) {
    case 1: // cima
        if (t.zx > 0) {
            t.m[t.zx][t.zy] = t.m[t.zx - 1][t.zy];
            t.m[t.zx - 1][t.zy] = 0;
            t.zx -= 1;
        }
        break;
    case 2: // baixo
        if (t.zx < 3) {
            t.m[t.zx][t.zy] = t.m[t.zx + 1][t.zy];
            t.m[t.zx + 1][t.zy] = 0;
            t.zx += 1;
        }
        break;
    case 3: // esquerda
        if (t.zy > 0) {
            t.m[t.zx][t.zy] = t.m[t.zx][t.zy - 1];
            t.m[t.zx][t.zy - 1] = 0;
            t.zy -= 1;
        }
        break;
    case 4: // direita
        if (t.zy < 3) {
            t.m[t.zx][t.zy] = t.m[t.zx][t.zy + 1];
            t.m[t.zx][t.zy + 1] = 0;
            t.zy += 1;
        }
        break;
    }
    // printf("2- %d %d\n", t.zx, t.zy);
    return t; // devolve um novo tabuleiro (com a nova posição do zero)
}

void write(Tab t) { // escreve o tabuleiro (matriz e posição do zero) para o stdout(standard output)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", t.m[i][j]);
        }
        printf("\n");
    }
    printf("posicao zero => (%d,%d)\n", t.zx, t.zy);
}

bool areSame(int a[4][4], int b[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

bool not_repeated(N actual, N* parent) { //verifica se o nó não é um nó repetido
    /*printf("REPEATED ACTUAL:\n");
    write(actual.t);
    printf("REPEATED PARENT:\n");
    write(parent->t);*/
    if (areSame(actual.t.m, parent->t.m)) return false;
    else if (parent->d != 0) return false || not_repeated(actual, parent->p);
    return true;
}

// busca em profundidade
void dfs(Tab inicial, Tab final) { // d é a profundidade
    stack<N> s;
    N first = {inicial, 0};
    first.p = (N*)malloc(sizeof(N));
    *first.p = first;   //o primeiro nó é pai de si mesmo
    s.push(first);
    while (!s.empty()) {
        N actual = s.top();
        printf("Actual:\n");
        write(actual.t);
        printf("Parent:\n");
        write(actual.p->t);
        //printf("actual.depth = %d\n", actual.d);
        s.pop();
        if (areSame(actual.t.m, final.m)) {
            printf("--------- SOLUTION ---------\ndepth = %d\n", actual.d);
            write(actual.t);
            return;
        } else if (actual.d==0 || not_repeated(actual, actual.p)) {    
            //printf("not_repeated = %d\n", not_repeated(actual, actual.p));
            // se for um nó que não se repetiu
            for (int i = 1; i <= 4; i++) {
                //printf("Inserted in stack:\n");
                N novo = {moveZero(actual.t,i), actual.d + 1};
                novo.p = (N*)malloc(sizeof(N));
                *novo.p = actual;
                s.push(novo);
                /*write(s.top().t);
                printf("Parent:\n");
                write(s.top().p->t);*/
                
            }
        }
    }
    printf("Solution not found.\n");
    return;
} 

// busca em largura
void bfs(Tab inicial, Tab final) { // d é a profundidade
    queue<N> q;
    Node first = {inicial, 0, &first};
    q.push(first);
     while (!q.empty()) {
        Tab temp = q.front().t;
        Node actual = q.front();
        int d = q.front().d;
        q.pop();
        // write(temp);
        // printf("%d\n", d);
        if (d == 100) return;
        if (areSame(temp.m, final.m)) {
            printf("--------- SOLUTION ---------\ndepth = %d \n", d);
            return;
        }
        else if (not_repeated(actual, actual.p)){
            for (int i = 1; i <= 4; i++) {
                q.push({moveZero(temp, i), d + 1, &actual});
                write(q.back().t);
            }
        }
    }
    printf("Solution not found.\n");
    return;
} 

void idfs(Tab inicial, Tab final) {
    stack<N> s;
    for (int i = 0; i < INF; i++) {
        Node first = {inicial, 0, &first};
        s.push(first);
        while (!s.empty()) {
            Tab temp = s.top().t;
            Node actual = s.top();
            int d = s.top().d;
            s.pop();
            if (areSame(temp.m, final.m)) {
                printf("--------- SOLUTION ---------\ndepth = %d\n", d);
                return;
            }
            else if (not_repeated(actual, actual.p) && d <= i) {
                for (int i = 1; i <= 4; i++) {
                    s.push({moveZero(temp, i), d + 1, &actual});
                    write(s.top().t);
                }
            }
        }
    }
}

int main() {
    Tab inicial, final;

    inicial = read();
    final = read();

    // printf("1- %d %d\n", inicial.zx, inicial.zy);
    // Tab novo = moveZero(inicial, 1);

    write(inicial);
    // write(novo);

    if (solvable(inicial) == solvable(final))
        printf("--------- SOLVABLE ---------\n");
    else
        printf("It is impossible to reach a solution.\n");

    dfs(inicial, final);
    // bfs(inicial, final);
    //idfs(inicial, final);
    return 0;
}
