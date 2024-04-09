
#include <stdio.h>
#include <stdlib.h> // qsrot �Լ��� ����� ��� ���� (������)//�����Լ� ȣ��
#include <time.h>

#define MAX_VERTICES 13
#define INF 1000

typedef struct edge {
    int u, v, w;
} edge;

typedef struct edge_list {
    edge data[MAX_VERTICES];
    int n;
} edge_list;

edge_list elist;

int Graph[MAX_VERTICES][MAX_VERTICES], n;
edge_list spanlist;

void kruskal();
int find(int parent[], int vertexno);
void applyUnion(int parent[], int c1, int c2);
void sort();
void print();
void printGraph(int graph[][MAX_VERTICES]);
void randomTree();

// ũ�罺Į �˰����� �����ϴ� ���� �Լ��Դϴ�.
int main() {
    int i, j, total_cost;
    n = MAX_VERTICES;
    randomTree();

    kruskal();

    print();
    return 0;
}

void printGraph(int graph[][MAX_VERTICES]) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (graph[i][j] != INF) {
                printf(" %4d", graph[i][j]);
            }
            else {
                printf("  INF");
            }

        }
        printf("\n");
    }
}
int randomPoolOk(int randomPool[]) {
    int flag = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (randomPool[i] != -1) {				//��� -1�� �ƴϸ� ���� ������  
            flag = 1;
        }


    }
    //printf("RPO : %d\n", flag);
    //�� �ț����� 1��ȯ 
    //�� ������ 0 ��ȯ  .
    return flag;
}

void randomTree() {
    //��ȭ�迭 �ʱ�ȭ
    int edge1 = 0;
    int x, y;

    //Graph �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            Graph[i][j] = 0;

        }

    }




    srand(time(NULL));//�����Լ� �ʱ�ȭ 
    int randomPool[MAX_VERTICES];//������ Ǯ 

    //���� vertex pool// ��� �������� �ϸ� ������ ���� ������ ����� �ִ�.
    for (int i = 0; i < MAX_VERTICES; i++) {
        randomPool[i] = i;
    }
    //������ ���� ���� ����  MAX~ Max(Max-1)/2�� ~~~~~~~~~~~~~~~/////////////////
    
    int EdgeN = (MAX_VERTICES * (rand() % (MAX_VERTICES - 3) + 2) / 2);//�ּڰ��� MaxVertex���� �̻�����
    printf("���� ���� %d\n", EdgeN);

    while (edge1 < EdgeN) {//������ ���� +1����//���� ���� ���������� n(n-1)/2���̴� �ּ� n


        if (randomPoolOk(randomPool) == 1) {
          
            do {
                x = randomPool[rand() % MAX_VERTICES];
                y = randomPool[rand() % MAX_VERTICES];
               

            } while (x == -1 || y == -1);//�Ѵ� ������� �����͸� ������ ���� 
            if (x == y) {//�̰��� ������ ����
                y = rand() % MAX_VERTICES;
            }
            //printf("debug random (%d, %d) \n",x,y );
        }
        else {//�� ������ �ٛ�����
            x = rand() % MAX_VERTICES;
            y = rand() % MAX_VERTICES;
           // printf("debug random122 (%d, %d) \n", x, y);

        }
        //������ ������ Ȧ���̸� ������ xy �� �������� �����Ҷ� �������� ���� ������ �����̰��� ¦�� �ȸ¾Ƽ�
       
      //  printf("debug x: %d, y: %d , graph(x,y): %d, graph(y,x): %d \n",x,y,Graph[x][y], Graph[y][x]);//
        if (x >= 0 && y >= 0 && Graph[x][y] == 0 && Graph[y][x] == 0 && x != y) {
            int temp = (rand() % 20) + 1;// 1~20 ������ ����ġ
            Graph[x][y] = Graph[y][x] = temp;
            //printf("debug44444\n");// ���� �ȵ���~~~~~~~~~~~~~~~~~~~
            edge1++;
            //random;  pool func
            randomPool[x] = randomPool[y] = -1;

            printf("%d. random edge : ( %d , %d), ( %d , %d ), weight: %d\n", edge1, x, y, y, x, Graph[x][y]);
        }



    }
    printGraph(Graph);
}

// ũ�罺Į �˰����� ������ �Լ��Դϴ�.
void kruskal() {
    int parent[MAX_VERTICES], i, j, cno1, cno2;
    elist.n = 0;//���� ����Ʈ.���� 
    for (i = 1; i < n; i++) {//������ ����Ʈȭ �Ѵ�. �����Ϸ��� 
        for (j = 0; j < i; j++) {
            if (Graph[i][j] != 0) {
                elist.data[elist.n].u = i;
                elist.data[elist.n].v = j;
                //printf("debug (%d, %d) \n", elist.data[elist.n].u, elist.data[elist.n].v);
                elist.data[elist.n].w = Graph[i][j];
                elist.n++;
            }
        }
    }

    sort();

    for (i = 0; i < n; i++) {
        parent[i] = i;
    }

    spanlist.n = 0;
 
    for (i = 0; i < elist.n; i++) {
        cno1 = find(parent, elist.data[i].u);
        cno2 = find(parent, elist.data[i].v);

        if (cno1 != cno2) {
          
            spanlist.data[spanlist.n] = elist.data[i];
            spanlist.n = spanlist.n + 1;
            applyUnion(parent, cno1, cno2);
        }
    }
}

// �������� ����ġ�� ���� �����ϴ� �Լ�
void sort() {
    int i, j;
    edge temp;

    for (i = 1; i < elist.n; i++) {
        for (j = 0; j < elist.n - 1; j++) {
            if (elist.data[j].w > elist.data[j + 1].w) {
                temp = elist.data[j];
                elist.data[j] = elist.data[j + 1];
                elist.data[j + 1] = temp;
            }
        }
    }
}

// ��尡 ���� ������ ã�� �Լ�
int find(int parent[], int vertexno) {
    return (parent[vertexno]);
}

// �� ������ ��ġ�� �Լ�
void applyUnion(int parent[], int c1, int c2) {
    int i;

    for (i = 0; i < n; i++) {
        if (parent[i] == c2) {
            parent[i] = c1;
        }
    }
}

// ����� ����ϴ� �Լ�
void print() {
    int i, cost = 0;

    for (i = 0; i < spanlist.n; i++) {
        printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
        cost = cost + spanlist.data[i].w;//�ּҺ�� ��� �κ� 
    }

    printf("\n�ּ� ���� Ʈ���� ���: %d\n", cost);
}

