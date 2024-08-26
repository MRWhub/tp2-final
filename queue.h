#ifndef QUEUE_H
#define QUEUE_H
#include "exam.h"
#include"patient.h"
typedef struct void_queue V_queue;
typedef struct void_node V_node;


/**
 * \brief Creates a new queue.
 * \return A pointer to the newly created queue.
 */
V_queue *create_queue();

/**
 * \brief Enqueues data into the queue.
 * \param queue - Pointer to the queue.
 * \param data - Pointer to the data to enqueue.
 */
void enqueue(V_queue *queue, void *data);

/**
 * \brief Dequeues data from the queue (for Patient).
 * \param queue - Pointer to the queue of patients.
 * \return Pointer to the dequeued patient.
 */
Patient *P_denqueue(V_queue *queue);

/**
 * \brief Frees the memory allocated for the queue (for Patient) // Libera a memória alocada para a fila (para pacientes)
 * \param queue - Pointer to the queue of patients to be freed // Ponteiro para a fila de pacientes a ser liberada
 * \details This function iterates through the entire queue, freeing the memory allocated for each node. It then frees the memory allocated for the queue structure itself. After calling this function, the queue pointer should no longer be used. // Esta função itera por toda a fila, liberando a memória alocada para cada nó. Em seguida, libera a memória alocada para a estrutura da fila em si. Após chamar esta função, o ponteiro da fila não deve mais ser usado.
 */
void P_free_queue(V_queue *queue);



/**
 * \brief Frees the memory allocated for the queue (for Exam).
 * \param queue - Pointer to the queue of exams to be freed.
 */
void E_free_queue(V_queue *queue);



/**
 * \brief Checks if the queue is empty // Verifica se a fila está vazia
 * \param queue - Pointer to the queue to be checked // Ponteiro para a fila a ser verificada
 * \return int - Returns 1 if the queue is empty, otherwise returns 0 // Retorna 1 se a fila estiver vazia, caso contrário, retorna 0
 */
int is_queue_empty(const V_queue *queue);


/**
 * \brief Dequeues data from the queue (for Exam).
 * \param queue - Pointer to the queue of exams.
 * \return Pointer to the dequeued exam.
 */
Exam *E_dequeue(V_queue *queue);
/**
 * \brief Gets the size of the queue.
 *
 * \param fila - Pointer to the queue. // Ponteiro para a fila.
 * \return int - Returns the number of elements in the queue. // Retorna o número de elementos na fila.
 */
int queue_size(V_queue *fila);
#endif // QUEUE_H
