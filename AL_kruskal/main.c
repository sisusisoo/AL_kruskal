
#include <stdio.h>
#include <stdlib.h> // qsrot 함수가 선언된 헤더 파일 (퀵정렬)//랜덤함수 호출
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

// 크루스칼 알고리즘을 실행하는 메인 함수입니다.
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
        if (randomPool[i] != -1) {				//모두 -1이 아니면 아직 덜쓴것  
            flag = 1;
        }


    }
    //printf("RPO : %d\n", flag);
    //다 안썻으면 1반환 
    //다 썻으면 0 반환  .
    return flag;
}

void randomTree() {
    //기화배열 초기화
    int edge1 = 0;
    int x, y;

    //Graph 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            Graph[i][j] = 0;

        }

    }




    srand(time(NULL));//랜덤함수 초기화 
    int randomPool[MAX_VERTICES];//정점의 풀 

    //랜덤 vertex pool// 모두 랜덤으로 하면 간선이 없는 정점이 생길수 있다.
    for (int i = 0; i < MAX_VERTICES; i++) {
        randomPool[i] = i;
    }
    //간선수 고르기 위한 변수  MAX~ Max(Max-1)/2개 ~~~~~~~~~~~~~~~/////////////////
    
    int EdgeN = (MAX_VERTICES * (rand() % (MAX_VERTICES - 3) + 2) / 2);//최솟값이 MaxVertex보다 이상으로
    printf("간선 갯수 %d\n", EdgeN);

    while (edge1 < EdgeN) {//간선은 정점 +1개만//간선 갯수 정점갯수의 n(n-1)/2개이다 최소 n


        if (randomPoolOk(randomPool) == 1) {
          
            do {
                x = randomPool[rand() % MAX_VERTICES];
                y = randomPool[rand() % MAX_VERTICES];
               

            } while (x == -1 || y == -1);//둘다 사용하지 않은것만 썻을때 가능 
            if (x == y) {//이경우는 어차피 못씀
                y = rand() % MAX_VERTICES;
            }
            //printf("debug random (%d, %d) \n",x,y );
        }
        else {//한 정점씩 다썻을때
            x = rand() % MAX_VERTICES;
            y = rand() % MAX_VERTICES;
           // printf("debug random122 (%d, %d) \n", x, y);

        }
        //문제점 정점이 홀수이면 위에서 xy 점 랜덤으로 배정할때 마지막에 같은 정점만 배정이가능 짝이 안맞아서
       
      //  printf("debug x: %d, y: %d , graph(x,y): %d, graph(y,x): %d \n",x,y,Graph[x][y], Graph[y][x]);//
        if (x >= 0 && y >= 0 && Graph[x][y] == 0 && Graph[y][x] == 0 && x != y) {
            int temp = (rand() % 20) + 1;// 1~20 까지의 가중치
            Graph[x][y] = Graph[y][x] = temp;
            //printf("debug44444\n");// 여기 안들어옴~~~~~~~~~~~~~~~~~~~
            edge1++;
            //random;  pool func
            randomPool[x] = randomPool[y] = -1;

            printf("%d. random edge : ( %d , %d), ( %d , %d ), weight: %d\n", edge1, x, y, y, x, Graph[x][y]);
        }



    }
    printGraph(Graph);
}

// 크루스칼 알고리즘을 구현한 함수입니다.
void kruskal() {
    int parent[MAX_VERTICES], i, j, cno1, cno2;
    elist.n = 0;//간선 리스트.갯수 
    for (i = 1; i < n; i++) {//간선을 리스트화 한다. 정렬하려고 
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

// 간선들을 가중치에 따라 정렬하는 함수
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

// 노드가 속한 집합을 찾는 함수
int find(int parent[], int vertexno) {
    return (parent[vertexno]);
}

// 두 집합을 합치는 함수
void applyUnion(int parent[], int c1, int c2) {
    int i;

    for (i = 0; i < n; i++) {
        if (parent[i] == c2) {
            parent[i] = c1;
        }
    }
}

// 결과를 출력하는 함수
void print() {
    int i, cost = 0;

    for (i = 0; i < spanlist.n; i++) {
        printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
        cost = cost + spanlist.data[i].w;//최소비용 계산 부분 
    }

    printf("\n최소 신장 트리의 비용: %d\n", cost);
}

