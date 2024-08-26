#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "exam.h"
#include "patient.h"

struct void_queue {
    V_node *front;
    V_node *rear;
};

struct void_node {
    void *data;
    V_node *next;
    V_node *previous;
};


V_queue *create_queue() {
     /** \brief Creates and returns a new queue // Cria e retorna uma nova fila
     *
     * \return Pointer to the newly created queue // Ponteiro para a fila recém-criada
     *
     * \details This function allocates memory for a new queue and initializes its front and rear pointers to NULL.
     * \details Esta função aloca memória para uma nova fila e inicializa seus ponteiros de frente e traseira para NULL.
     *
     */
    V_queue *new_queue = (V_queue *)malloc(sizeof(V_queue));
    if (!new_queue) {
        printf("\nFailed to allocate memory for queue.\n");
        return NULL;
    }
    new_queue->front = new_queue->rear = NULL;
    return new_queue;
}

void enqueue(V_queue *q, void *data) {

    /** \brief Adds data to the end of the queue // Adiciona dados ao final da fila
     *
     * \param queue - Pointer to the queue where data will be added // Ponteiro para a fila onde os dados serão adicionados
     * \param data - Pointer to the data to be enqueued // Ponteiro para os dados a serem enfileirados
     *
     * \details This function creates a new node with the given data and appends it to the end of the queue. If the queue is empty, the new node becomes both the front and rear.
     * \details Esta função cria um novo nó com os dados fornecidos e o adiciona ao final da fila. Se a fila estiver vazia, o novo nó se torna tanto a frente quanto a traseira.
     *
     */
    V_node *new_node = (V_node *)malloc(sizeof(V_node));
    if (!new_node) {
        printf("\nError! Memory allocation failed (enqueue).\n");
        return;
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = q->rear;

    if (q->rear) {
        q->rear->next = new_node;
    } else {
        q->front = new_node;
    }
    q->rear = new_node;

}



Patient *P_denqueue(V_queue *patient_queue) {
     /** \brief Removes and returns the front patient from the queue // Remove e retorna o paciente da frente da fila
     *
     * \param queue - Pointer to the queue from which the patient will be removed // Ponteiro para a fila de onde o paciente será removido
     * \return Pointer to the dequeued patient // Ponteiro para o paciente desenfileirado
     *
     * \details This function removes the front node from the queue and returns the patient data it holds. If the queue becomes empty, the rear pointer is also set to NULL.
     * \details Esta função remove o nó da frente da fila e retorna os dados do paciente que ele contém. Se a fila ficar vazia, o ponteiro traseiro também é definido como NULL.
     *
     */

    if (patient_queue && patient_queue->front) {
        V_node *node_to_remove = patient_queue->front;
        if (!node_to_remove) {
            return NULL;
        }
        Patient *data = (Patient *)node_to_remove->data;


        if (!data) {
            free(node_to_remove);
            return NULL;
        }

        patient_queue->front = node_to_remove->next;
        if (!patient_queue->front) {
            patient_queue->rear = NULL;
        } else {
            patient_queue->front->previous = NULL;
        }


        free(node_to_remove);

        return data;
    }
    return NULL;

}

void E_free_queue(V_queue *queue){
    /** \brief Frees the memory allocated for the exam queue // Libera a memória alocada para a fila de exames
     *
     * \param queue - Pointer to the exam queue to be freed // Ponteiro para a fila de exames a ser liberada
     *
     * \details This function iterates through the exam queue, freeing each node and its associated exam data.
     * \details Esta função percorre a fila de exames, liberando cada nó e seus dados de exames associados.
     *
     */
    V_node *current = queue->front;
    while(current){
        destroy_exam((Exam*)current->data);
        free(current);
        current = current->next;

    }

    free(queue);
    printf("\nExam Queue Deleted!");



}

void P_free_queue(V_queue *queue){
    /** \brief Frees the memory allocated for the patient queue // Libera a memória alocada para a fila de pacientes
     *
     * \param queue - Pointer to the patient queue to be freed // Ponteiro para a fila de pacientes a ser liberada
     *
     * \details This function iterates through the patient queue, freeing each node and its associated patient data.
     * \details Esta função percorre a fila de pacientes, liberando cada nó e seus dados de pacientes associados.
     *
     */
    V_node *current = queue->front;
    while(current){
        destroy_patient(current->data);
        free(current);
        current = current->next;

    }

    free(queue);
    printf("\nPatient Queue Deleted!");



}

int is_queue_empty(const V_queue *queue) {
     /** \brief Checks if the queue is empty // Verifica se a fila está vazia
     *
     * \param queue - Pointer to the queue to be checked // Ponteiro para a fila a ser verificada
     * \return int - Returns 1 if the queue is empty, otherwise returns 0 // Retorna 1 se a fila estiver vazia, caso contrário, retorna 0
     *
     * \details This function checks whether the provided queue pointer is NULL or if the front pointer of the queue is NULL. If either is true, it indicates that the queue is empty, and the function returns 1. Otherwise, it returns 0, indicating that the queue contains elements.
     * \details Esta função verifica se o ponteiro da fila fornecido é NULL ou se o ponteiro da frente da fila é NULL. Se qualquer um dos dois for verdadeiro, isso indica que a fila está vazia, e a função retorna 1. Caso contrário, ela retorna 0, indicando que a fila contém elementos.
     *
     */
    return queue == NULL || queue ->front == NULL;

}

Exam *E_dequeue(V_queue *queue) {
     /** \brief Removes and returns the front exam from the queue // Remove e retorna o exame da frente da fila
     *
     * \param queue - Pointer to the queue from which the exam will be removed // Ponteiro para a fila de onde o exame será removido
     * \return Pointer to the dequeued exam // Ponteiro para o exame desenfileirado
     *
     * \details This function removes the front node from the queue and returns the exam data it holds. If the queue becomes empty, the rear pointer is also set to NULL.
     * \details Esta função remove o nó da frente da fila e retorna os dados do exame que ele contém. Se a fila ficar vazia, o ponteiro traseiro também é definido como NULL.
     *
     */
    if (queue && queue->front) {
        V_node *node_to_remove = queue->front;
        if (!node_to_remove) {
            return NULL;
        }
        Exam *data = (Exam *)node_to_remove->data;


        if (!data) {
            free(node_to_remove);
            return NULL;
        }

        queue->front = node_to_remove->next;
        if (!queue->front) {
            queue->rear = NULL;
        } else {
            queue->front->previous = NULL;
        }

        free(node_to_remove);

        return data;
    }
    return NULL;
}
/**
 * \brief Get the size of the queue.
 *
 * \param fila - Pointer to the queue. // Ponteiro para a fila.
 * \return The number of elements in the queue. // O número de elementos na fila.
 *
 * \details This function iterates through the entire queue, counting the number of nodes
 *          from the front to the rear. It starts from the `front` node and moves to the `next`
 *          node until it reaches the end (NULL), incrementing the `size` counter for each node.
 * \details Esta função percorre toda a fila, contando o número de nós
 *          desde a frente até a traseira. Ela começa a partir do nó `front` e move-se para o nó `next`
 *          até atingir o final (NULL), incrementando o contador `size` para cada nó.
 */
int queue_size(V_queue *fila) {
    int size = 0;
    V_node *current = fila->front;
    while (current) {
        size++;
        current = current->next;
    }
    return size;
}

