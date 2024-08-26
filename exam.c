#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "exam.h"

struct exam{
    int id;
    int rx_id;
    int patient_id;
    char *condition;
    struct tm *exam_time;


};


Exam *create_exam(int id, int rx_id, int patient_id, const char * condition, const struct tm *exam_time) {
    /** \brief This function creates an exam object // Esta função cria um objeto de exame
     *
     * \param id - Unique exam identification // Identificação única do exame
     * \param patient_id - ID of the patient associated with the exam // ID do paciente associado ao exame
     * \param rx_id - ID of the machine used for the exam // ID da máquina usada para o exame
     * \param exam_time - Pointer to a tm structure with the exam time // Ponteiro para uma estrutura tm com o horário do exame
     * \return The created exam object // O objeto de exame criado
     *
     * \details This function allocates memory for a new exam and initializes its fields with the given values.
     *          The tm structure passed as a parameter is copied to the new exam structure.
     *          If memory allocation fails, the function prints an error message and returns NULL.
     * \details Esta função aloca memória para um novo exame e inicializa seus campos com os valores fornecidos.
     *          A estrutura tm passada como parâmetro é copiada para a nova estrutura de exame.
     *          Se a alocação de memória falhar, a função imprime uma mensagem de erro e retorna NULL.
     *
     *
     */

    /* Checks if the time pointer is NULL // Verifica se o ponteiro de time é nulo */
    if (!exam_time) {
        printf("\nError: Exam's time cannot be NULL\n");
        return NULL;
    }

    /* Allocates memory for exam structure and checks whether the allocation was successful
    // Aloca memória para estrutura de exame e verifica se a alocação foi bem-sucedida */
    Exam *new_exam = (Exam*)malloc(sizeof(Exam));
    if (!new_exam) {
        printf("\nFailed to allocate memory for exam's structure\n");
        return NULL;
    }

    /* Allocates memory for exam's time and checks whether the allocation was successful
    // Aloca memória para o horário do exame e verifica se a alocação foi bem-sucedida */
    new_exam->exam_time = (struct tm*)malloc(sizeof(struct tm));
    if (!new_exam->exam_time) {
        printf("\nFailed to allocate memory for time structure\n");
        free(new_exam);
        return NULL;
    }

    /* Assign the exam's id, patient_id, and rx_id // Atribui o id, patient_id e rx_id do exame */
    new_exam->id = id;
    new_exam->patient_id = patient_id;
    new_exam->rx_id = rx_id;

    /* Copy the tm structure // Copia a estrutura tm */
    memcpy(new_exam->exam_time, exam_time, sizeof(struct tm));




    new_exam->condition = (char*)malloc(strlen(condition)+1*sizeof(char));
    if(!new_exam->condition){
        printf("\nFailed to allocate memory for condition str\n");
        free(new_exam);
        return NULL;
    }
    strcpy(new_exam->condition,condition);

    return new_exam;
}

void destroy_exam(Exam *old_exam) {
    /** \brief Free the allocated memory for the exam's structure // Libera a memória alocada para a estrutura do exame
     *
     * \param old_exam - Pointer to the exam structure to be freed // Ponteiro para a estrutura do exame a ser liberada
     *
     * \details This function frees the memory allocated for the exam's time and the exam structure itself.
     * \details Esta função libera a memória alocada para o horário do exame e a própria estrutura do exame.
     *
     * \warning This function does not return any value. If the exam pointer is NULL, it simply returns without doing anything.
     *          Esta função não retorna nenhum valor. Se o ponteiro do exame for NULL, simplesmente retorna sem fazer nada.
     */

    /* Checks if the exam pointer is NULL // Verifica se o ponteiro do exame é nulo */
    if (!old_exam) {
        printf("\nNULL POINTER!!\n");
        return;
    }

    /* Free exam's time if allocated // Libera o horário do exame, se alocado */
    if (old_exam->exam_time) {
        free(old_exam->exam_time);
         // Set to NULL after freeing // Define como NULL após liberar
    }

    if(old_exam->condition){
        free(old_exam->condition);

    }

    /* Free the exam structure itself // Libera a própria estrutura do exame */
    free(old_exam);
    printf("Memory Allocation Freed!(Exam)\n");
}

int get_exam_id(Exam *exam) {
    /** \brief This function gets and returns exam's ID // Esta função obtém e retorna o ID do exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The exam's ID // O ID do exame
     *
     * \details This function checks if the exam pointer is NULL. If it is, it prints an error message to stderr and returns 1. Otherwise, it returns the exam's ID.
     * \details Esta função verifica se o ponteiro do exame é NULL. Se for, imprime uma mensagem de erro em stderr e retorna 1. Caso contrário, retorna o ID do exame.
     *

     */

    /* Checks if the exam pointer is NULL // Verifica se o ponteiro do exame é nulo */
    if (!exam) {
        printf("\nError: NULL exam pointer\n");
        return 1;
    }

    return exam->id;
}

int get_exam_patient_id(Exam *exam) {
    /** \brief This function gets and returns the patient's ID associated with the exam // Esta função obtém e retorna o ID do paciente associado ao exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The patient's ID associated with the exam // O ID do paciente associado ao exame
     *
     * \details This function checks if the exam pointer is NULL. If it is, it prints an error message to stderr and returns 1. Otherwise, it returns the patient's ID associated with the exam.
     * \details Esta função verifica se o ponteiro do exame é NULL. Se for, imprime uma mensagem de erro em stderr e retorna 1. Caso contrário, retorna o ID do paciente associado ao exame.
     *
     *
     */

    /* Checks if the exam pointer is NULL // Verifica se o ponteiro do exame é nulo */
    if (!exam) {
        fprintf(stderr, "Error: NULL exam pointer\n");
        return 1;
    }

    return exam->patient_id;
}

int get_exam_rx_id(Exam *exam) {
    /** \brief This function gets and returns the machine's ID used for the exam // Esta função obtém e retorna o ID da máquina usada para o exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The machine's ID used for the exam // O ID da máquina usada para o exame
     *
     * \details This function checks if the exam pointer is NULL. If it is, it prints an error message to stderr and returns 1. Otherwise, it returns the machine's ID used for the exam.
     * \details Esta função verifica se o ponteiro do exame é NULL. Se for, imprime uma mensagem de erro em stderr e retorna 1. Caso contrário, retorna o ID da máquina usada para o exame.
     *
     *
     */

    /* Checks if the exam pointer is NULL // Verifica se o ponteiro do exame é nulo */
    if (!exam) {
        fprintf(stderr, "Error: NULL exam pointer\n");
        return 1;
    }

    return exam->rx_id;
}
struct tm *get_exam_time(Exam *exam) {
    /** \brief This function gets and returns the exam's time // Esta função obtém e retorna o horário do exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return Pointer to const struct tm representing the exam's time // Ponteiro para const struct tm representando o horário do exame
     *
     * \details This function checks if the exam pointer is NULL. If it is, it prints an error message to stderr and returns NULL. Otherwise, it returns a pointer to the exam's time.
     * \details Esta função verifica se o ponteiro do exame é NULL. Se for, imprime uma mensagem de erro em stderr e retorna NULL. Caso contrário, retorna um ponteiro para o horário do exame.
     *
     *
     */

    /* Checks if the exam pointer is NULL // Verifica se o ponteiro do exame é nulo */
    if (!exam) {
        printf("\nError: NULL exam pointer\n");
        return NULL;
    }

    return exam->exam_time;
}

char *get_exam_condition(struct exam *exam) {
    if (exam == NULL) {
        return NULL; // Retorna NULL se o ponteiro para a estrutura for NULL
    }
    return exam->condition;
}

void print_exam(Exam *exam) {
    /** \brief This function prints the details of the exam // Esta função imprime os detalhes do exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     *
     * \details This function prints the ID, patient ID, machine ID, condition, and date and time of the exam in a formatted manner.
     * \details Esta função imprime o ID, ID do paciente, ID da máquina, condição e data e hora do exame de maneira formatada.
     *
     */
    if (exam) {
        printf("\n\t=============================\n");
        printf("\t          AI EXAM\n");
        printf("\t=============================\n");
        printf("\tExam ID         : %d\n", get_exam_id(exam));
        printf("\tPatient ID      : %d\n", get_exam_patient_id(exam));
        printf("\tX-ray Machine ID: %d\n", get_exam_rx_id(exam));
        printf("\tCondition       : %s\n", exam->condition);

        char buffer[100];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", get_exam_time(exam));
        printf("\tDate and Time   : %s\n", buffer);

        printf("\t=============================\n");
    }
}

void print_exam_db(Exam *current_exam, FILE *exam_file){
    /** \brief This function prints the exam details to a file // Esta função imprime os detalhes do exame em um arquivo
     *
     * \param current_exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \param exam_file - Pointer to the file where the exam details will be printed // Ponteiro para o arquivo onde os detalhes do exame serão impressos
     *
     * \details This function writes the exam details, including ID, RX ID, patient ID, condition, and exam time to a file.
     * \details Esta função escreve os detalhes do exame, incluindo ID, RX ID, ID do paciente, condição e horário do exame em um arquivo.
     *
     * \warning If the exam pointer is NULL or the file pointer is NULL, an error message is printed and the program exits.
     * \warning Se o ponteiro do exame ou o ponteiro do arquivo forem NULL, uma mensagem de erro é impressa e o programa é encerrado.
     */

    if(current_exam && exam_file){

    fprintf(exam_file, "ID: %d\n", get_exam_id(current_exam));
    fprintf(exam_file, "RX ID: %d\n", get_exam_rx_id(current_exam));
    fprintf(exam_file, "Patient ID: %d\n", get_exam_patient_id(current_exam));
    fprintf(exam_file, "Condition: %s\n", get_exam_condition(current_exam));

    const struct tm *exam_time = get_exam_time(current_exam);


    if (exam_time) {

    fprintf(exam_file, "Exam Time: %d-%02d-%02d %02d:%02d:%02d\n",
            exam_time->tm_year + 1900,
            exam_time->tm_mon + 1,
            exam_time->tm_mday,
            exam_time->tm_hour,
            exam_time->tm_min,
            exam_time->tm_sec);

    }

    }else{
    printf("Error saving Exam on DB");
    exit(1);
}


}
