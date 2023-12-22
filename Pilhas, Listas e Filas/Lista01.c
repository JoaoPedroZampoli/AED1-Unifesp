#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Erro na aloca��o de mem�ria\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node** head) {
    Node* temp = *head;
    Node* nextNode;
    while(temp != NULL) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    *head = NULL;
}

int main() {
    Node* head = NULL;
    int i, N, data;

    printf("Digite o n�mero de elementos que voc� deseja adicionar � lista: ");
    scanf("%d", &N);

    for(i=0; i<N; i++) {
        printf("Digite o %d� n�mero: ", i+1);
        scanf("%d", &data);
        insertAtEnd(&head, data);
    }

    printList(head);

    freeList(&head);

    return 0;
}
