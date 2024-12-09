#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <queue>
#include <iostream>
using namespace std;

int size1;
int** arr1;
int* dist;

struct Node {
    int n;          // Номер вершины (0..N-1)
    Node* next;
};

Node* LA;          // Массив структур - списков смежности [N]

Node* make_LA() {
    Node* la = (Node*)malloc(sizeof(Node) * size1);
    for (int i = 0; i < size1; i++) {
        la[i].n = i;
        la[i].next = NULL;
        Node* p = &la[i];
        for (int j = 0; j < size1; j++) {
            if (arr1[i][j] == 1) {
                p->next = (Node*)malloc(sizeof(Node));
                p = p->next;
                p->n = j;
                p->next = NULL;
            }
        }
    }
    return la;
}

void print_LA() {
    for (int i = 0; i < size1; i++) {
        printf("%d > ", LA[i].n);
        Node* p = LA[i].next;
        while (p != NULL) {
            printf("%d > ", p->n);
            p = p->next;
        }
        printf("\n");
    }
}

void BFS(int start) {
    queue<int> Q;
    Q.push(start);
    dist[start] = 0;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i = 0; i < size1; i++) {
            if (arr1[v][i] == 1 && dist[i] == -1) {
                dist[i] = dist[v] + 1;
                Q.push(i);
            }
        }
    }
}

void DFS(int v, int count) {
    dist[v] = count;
    for (int i = 0; i < size1; i++) {
        if (arr1[v][i] == 1 && dist[i] == -1) {
            DFS(i, count + 1);
        }
    }
}

void create_matrix() {
    for (int i = 0; i < size1; i++) {
        for (int j = i; j < size1; j++) {
            if (i == j) {
                arr1[i][j] = 0; // главная диагональ == 0
            }
            else {
                arr1[i][j] = rand() % 2;
                arr1[j][i] = arr1[i][j]; // неориентированный граф
            }
        }
    }
}

void print_matrix() {
    printf("     ");
    for (int i = 0; i < size1; i++) {
        printf("%4d ", i);
    }
    printf("\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < size1; i++) {
        printf("%4d|", i);
        for (int j = 0; j < size1; j++) {
            printf("%4d ", arr1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Russian");
    printf("Введите размер матрицы смежности M1: ");
    scanf("%d", &size1);

    dist = (int*)malloc(sizeof(int) * size1);
    arr1 = (int**)malloc(sizeof(int*) * size1);
    for (int i = 0; i < size1; i++) {
        arr1[i] = (int*)malloc(sizeof(int) * size1);
    }

    srand(time(NULL));
    create_matrix();
    printf("Матрица M1:\n");
    print_matrix();

    int start_vertex;
    printf("Введите вершину (от 0 до %d) для начала обхода: ", size1 - 1);
    scanf("%d", &start_vertex);

    // Инициализация расстояний
    for (int i = 0; i < size1; i++) {
        dist[i] = -1;
    }

    // Поиск расстояний с использованием BFS
    BFS(start_vertex);
    for (int i = 0; i < size1; i++) {
        printf("Расстояние от %d вершины до %d вершины = %d\n", start_vertex, i, dist[i]);
    }

    // Сброс расстояний для DFS
    for (int i = 0; i < size1; i++) {
        dist[i] = -1;
    }

    // Создание списка смежности
    LA = make_LA();
    printf("Список смежности S1:\n");
    print_LA();

    // Поиск расстояний с использованием DFS
    DFS(start_vertex, 0);
    for (int i = 0; i < size1; i++) {
        printf("Расстояние от %d вершины до %d вершины = %d\n", start_vertex, i, dist[i]);
    }

    // Освобождение памяти
    for (int i = 0; i < size1; i++) {
        free(arr1[i]);
    }
    free(arr1);
    free(dist);

    return 0;
}
