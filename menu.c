#include <stdio.h>      // для printf, scanf, system
#include <stdlib.h>     // для malloc, free
#include <string.h>     // для strcpy
#include <conio.h>      // для getch() 

// Структура узла очереди
typedef struct Node {
    int a;              
    char b[21];         
    struct Node* next;  // Указатель на следующий элемент в очереди
} Node;

// Структура очереди
typedef struct Queue {
    Node* front;        // Указатель на первый элемент
    Node* rear;         // Указатель на последний элемент
    int size;           // Кол-во элементов в очереди
    int created;        // Флаг
} Queue;

// Очистка очереди
void clearQueue(Queue* q) {
    // Проходим по всем узлам и освобождаем память
    while (q->front != NULL) {
        Node* temp = q->front;        // Сохраняем текущий узел
        q->front = q->front->next;    // Перемещаем указатель на следующий
        free(temp);                   // Освобождаем память узла
    }
    q->rear = NULL;   
    q->size = 0;      
}

// Удаление очереди
void deleteQueue(Queue* q) {
    clearQueue(q);        
    q->created = 0;      
}

// Добавление элемента
void enqueue(Queue* q, int a, char* b) {
    // Выделяем память под новый узел
    Node* newNode = (Node*)malloc(sizeof(Node));

    // Заполняем данные нового узла
    newNode->a = a;                
    strcpy(newNode->b, b);         
    newNode->next = NULL;          // Новый узел — последний, поэтому next = NULL

    // Если очередь пуста — новый узел становится и первым, и последним
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        // Иначе добавляем в конец
        q->rear->next = newNode;   // Предыдущий последний теперь ссылается на новый
        q->rear = newNode;         // Новый узел становится последним
    }
    q->size++; // Увеличиваем счётчик элементов
}

// Удаление элемента из начала очереди (dequeue)
void dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Очередь пуста!\n");
        return;
    }

    // Сохраняем указатель на удаляемый узел
    Node* temp = q->front;
    printf("Удалён: %d %s\n", temp->a, temp->b);

    // Перемещаем начало очереди на следующий элемент
    q->front = q->front->next;

    // Если после удаления очередь стала пустой — обнуляем хвост
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // Освобождаем память удалённого узла
    free(temp);
    q->size--; // Уменьшаем счётчик
}

// Вывод количества элементов в очереди
void countElements(Queue* q) {
    if (!q->created) {
        printf("Очередь не создана!\n");
    } else {
        printf("Элементов в очереди: %d\n", q->size);
    }
}

void printQueue(Queue* q) {
    if (!q->created || q->size == 0) {
        printf("Очередь: (пусто)\n\n");
        return;
    }

    printf("Очередь:");
    Node* cur = q->front; // Начинаем с первого элемента
    while (cur != NULL) {
        printf(" %d %s", cur->a, cur->b); 
        if (cur->next != NULL) {
            printf(" →"); // Стрелка между элементами
        }
        cur = cur->next; // Переходим к следующему
    }
    printf("\n\n");
}

int main() {
    system("chcp 65001 > nul");
    Queue myQueue = {NULL, NULL, 0, 0};
    int choice = 0;

    // Основной цикл программы
    while (1) {
        system("cls"); // Очищаем экран

        // Всегда отображаем текущее состояние очереди сверху
        printQueue(&myQueue);

        // Меню с 7 пунктами
        const char* menu[] = {
            "1. Создать очередь",
            "2. Очистить очередь",
            "3. Запись элемента в очередь",
            "4. Удалить элемент из очереди",
            "5. Удалить очередь",
            "6. Количество элементов",
            "7. Выход"
        };

        printf("=== МЕНЮ ===\n");
        for (int i = 0; i < 7; i++) {
            if (i == choice)
                printf(">>> %s\n", menu[i]); 
            else
                printf("    %s\n", menu[i]); 
        }
        printf("\nСтрелки — перемещение, Enter — выбрать\n");

        char key = getch();

        // Обработка стрелок (72 — вверх, 80 — вниз)
        if (key == 0 || key == -32) {
            key = getch();
            if (key == 72) { 
                if (choice == 0) choice = 6; 
                else choice--;
            }
            if (key == 80) {
                if (choice == 6) choice = 0;
                else choice++;
            }
        }
        // Обработка нажатия Enter
        else if (key == 13) {
            switch (choice) {
                case 0: // создать очередь
                    if (myQueue.created) {
                        deleteQueue(&myQueue); // Если уже создана — удаляем старую
                    }
                    myQueue.created = 1; 
                    printf("Очередь создана.\n");
                    getch(); 
                    break;

                case 1: // Очистить очередь
                    clearQueue(&myQueue);
                    printf("Очищено.\n");
                    getch();
                    break;

                case 2: // Добавить элемент
                    if (!myQueue.created) {
                        printf("Сначала создайте очередь!\n");
                        getch();
                        continue;
                    }
                    int a;
                    char b[21];
                    printf("Число: ");
                    scanf("%d", &a);
                    printf("Строка: ");
                    scanf("%20s", b);
                    enqueue(&myQueue, a, b);
                    printf("Добавлено.\n");
                    getch();
                    break;

                case 3: // Удалить элемент
                    if (!myQueue.created) {
                        printf("Очередь не создана!\n");
                    } else {
                        dequeue(&myQueue);
                    }
                    getch();
                    break;

                case 4: // Удалить очередь полностью
                    if (!myQueue.created) {
                        printf("Очередь не создана!\n");
                    } else {
                        deleteQueue(&myQueue);
                        printf("Очередь удалена.\n");
                    }
                    getch();
                    break;

                case 5: // Показать количество элементов
                    countElements(&myQueue);
                    getch();
                    break;

                case 6: // Выход
                    return 0;
            }
        }
    }
}