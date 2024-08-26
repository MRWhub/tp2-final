#include "medical_check.h"
#include <time.h>
#include "exam.h"
#include <string.h>
#include "queue.h"
#include "rx_machine.h"
#define MAX_EXECUTION 43.200
#define MAX_CONDITION_SIZE 100

struct report {
    int id;
    int exam_id;
    char *condition;  // Definido como um array para armazenar a string
    struct tm* report_time;
} ;

struct examPriority{

        int total_exams_enqueued;

        V_queue *priority_6;
        V_queue *priority_5;
        V_queue *priority_4;
        V_queue *priority_3;
        V_queue *priority_2;
        V_queue *priority_1;

};

ExamPriorityQueue *new_priority_queue(){

/**
 * \brief Create a new priority queue for managing exams // Cria uma nova fila de prioridade para gerenciar exames
 *
 * \param void - This function does not take any parameters // Esta função não recebe parâmetros
 *
 * \details This function allocates memory for a new priority queue structure and initializes six different queues for storing exams based on their priority levels (1 to 6). // Esta função aloca memória para uma nova estrutura de fila de prioridade e inicializa seis filas diferentes para armazenar exames com base em seus níveis de prioridade (1 a 6).
 * \details The queues are used to manage exams based on their urgency, with priority levels from 1 (lowest) to 6 (highest). // As filas são usadas para gerenciar exames com base em sua urgência, com níveis de prioridade de 1 (mais baixo) a 6 (mais alto).
 *
 * \warning If memory allocation fails, an error message is printed and the program exits. // Se a alocação de memória falhar, uma mensagem de erro é impressa e o programa é encerrado.
 *
 * \return ExamPriorityQueue* - Pointer to the newly created priority queue structure // Ponteiro para a nova estrutura de fila de prioridade criada
 */
    ExamPriorityQueue *new_queue = (ExamPriorityQueue*)malloc(sizeof(ExamPriorityQueue));
    if(!new_queue){
        printf("\nError :: Memory Allocation Failed (Exam Priority Queue)!!");
        exit(1);
    }

    new_queue->priority_6 = create_queue();
    new_queue->priority_5 = create_queue();
    new_queue->priority_4 = create_queue();
    new_queue->priority_3 = create_queue();
    new_queue->priority_2 = create_queue();
    new_queue->priority_1 = create_queue();

    return new_queue;
}

void free_priority_queue(ExamPriorityQueue *any){
/**
 * \brief Free the memory allocated for the priority queue and its associated queues // Libera a memória alocada para a fila de prioridade e suas filas associadas
 *
 * \param any - Pointer to the ExamPriorityQueue structure that needs to be freed // Ponteiro para a estrutura ExamPriorityQueue que precisa ser liberada
 *
 * \details This function deallocates memory for each priority queue within the ExamPriorityQueue structure and then frees the memory for the priority queue itself. // Esta função desaloca a memória para cada fila de prioridade dentro da estrutura ExamPriorityQueue e, em seguida, libera a memória para a própria fila de prioridade.
 * \details It ensures that all associated queues are properly freed before the main structure is deallocated. // Garante que todas as filas associadas sejam devidamente liberadas antes que a estrutura principal seja desalocada.
 *
 * \warning The function assumes that the pointer provided is valid and non-NULL. // A função assume que o ponteiro fornecido é válido e não é NULL.
 */
    E_free_queue(any->priority_6);
    E_free_queue(any->priority_5);
    E_free_queue(any->priority_4);
    E_free_queue(any->priority_3);
    E_free_queue(any->priority_2);
    E_free_queue(any->priority_1);

    free(any);

    printf("\nPriority Queue Destroyed.");

}

void insert_in_priority_queue(ExamPriorityQueue *any, Exam *exam){
/**
 * \brief Insert an exam into the appropriate priority queue based on its diagnostic priority // Insere um exame na fila de prioridade apropriada com base em sua prioridade diagnóstica
 *
 * \param any - Pointer to the ExamPriorityQueue structure where the exam will be inserted // Ponteiro para a estrutura ExamPriorityQueue onde o exame será inserido
 * \param exam - Pointer to the Exam structure that needs to be inserted into the queue // Ponteiro para a estrutura Exam que precisa ser inserida na fila
 *
 * \details This function determines the priority of an exam using the get_ai_priority function and enqueues it into the corresponding priority queue. // Esta função determina a prioridade de um exame usando a função get_ai_priority e o coloca na fila de prioridade correspondente.
 * \details The priority is used to manage the urgency of exam processing, with higher priorities processed first. // A prioridade é usada para gerenciar a urgência do processamento dos exames, com prioridades mais altas sendo processadas primeiro.
 *
 * \warning If the exam pointer is NULL, an error message is printed, and the function does not insert the exam into the queue. // Se o ponteiro do exame for NULL, uma mensagem de erro é impressa e a função não insere o exame na fila.
 */

     int ia_diagnostic_priority = get_ai_priority(exam);
     switch(ia_diagnostic_priority){
    case 6 :
        enqueue(any->priority_6,exam);
        printf("\nExam inserted on priority 6(Urgent) queue\n");
        break;
    case 5:
        enqueue(any->priority_5,exam);
        printf("\nExam inserted on priority 5(High) queue\n");
        break;
    case 4:
        enqueue(any->priority_4,exam);
       printf("\nExam inserted on priority 4(Medium) queue\n");
        break;
    case 3:
        enqueue(any->priority_3,exam);
        printf("\nExam inserted on priority 3(Medium) queue\n");
        break;
    case 2:
        enqueue(any->priority_2,exam);
        printf("\nExam inserted on priority 2(Low) queue\n");
        break;
    case 1:
        enqueue(any->priority_1,exam);
        printf("\nExam inserted on priority 1(Low) queue\n");
        break;
    default:
        printf("\nError Inserting Exam on priority queue\n");

        break;
     }




}



int is_priority_queue_empty(ExamPriorityQueue *new_queue){
/**
 * \brief Check if all priority queues are empty // Verifica se todas as filas de prioridade estão vazias
 *
 * \param new_queue - Pointer to the ExamPriorityQueue structure to be checked // Ponteiro para a estrutura ExamPriorityQueue a ser verificada
 *
 * \details This function checks each priority queue within the ExamPriorityQueue structure to determine if all are empty. // Esta função verifica cada fila de prioridade dentro da estrutura ExamPriorityQueue para determinar se todas estão vazias.
 *
 * \warning The function assumes that the pointer provided is valid and non-NULL. // A função assume que o ponteiro fornecido é válido e não é NULL.
 *
 * \return int 1 if all priority queues are empty, 0 otherwise // int - 1 se todas as filas de prioridade estiverem vazias, 0 caso contrário
 */

    if(is_queue_empty(new_queue->priority_1) && is_queue_empty(new_queue->priority_2) && is_queue_empty(new_queue->priority_3) && is_queue_empty(new_queue->priority_4) && is_queue_empty(new_queue->priority_5)&& is_queue_empty(new_queue->priority_6)){

        return 1;
    }
    return 0;


}

Exam *get_priority_exams(ExamPriorityQueue *any) {
/**
 * \brief Retrieve the highest priority exam from the priority queue // Recupera o exame de maior prioridade da fila de prioridade
 *
 * \param any - Pointer to the ExamPriorityQueue structure from which to retrieve an exam // Ponteiro para a estrutura ExamPriorityQueue da qual recuperar um exame
 *
 * \details This function dequeues an exam from the highest priority queue that is not empty, starting from priority 6 (highest) to priority 1 (lowest). // Esta função remove um exame da fila de maior prioridade que não está vazia, começando pela prioridade 6 (mais alta) até a prioridade 1 (mais baixa).
 * \details If all queues are empty, it returns NULL and prints a message indicating that there are no exams waiting. // Se todas as filas estiverem vazias, retorna NULL e imprime uma mensagem indicando que não há exames esperando.
 *
 * \warning The function assumes that the pointer provided is valid and non-NULL. // A função assume que o ponteiro fornecido é válido e não é NULL.
 *
 * \return Exam* - Pointer to the exam retrieved from the highest priority queue, or NULL if all queues are empty // Ponteiro para o exame recuperado da fila de maior prioridade, ou NULL se todas as filas estiverem vazias
 */
    // Verifique a fila de maior prioridade primeiro
    if (is_queue_empty(any->priority_6) == 0) { // A fila não está vazia

        return E_dequeue(any->priority_6);
    } else if (is_queue_empty(any->priority_5) == 0) {

        return E_dequeue(any->priority_5);
    } else if (is_queue_empty(any->priority_4) == 0) {

        return E_dequeue(any->priority_4);
    } else if (is_queue_empty(any->priority_3) == 0) {

        return E_dequeue(any->priority_3);
    } else if (is_queue_empty(any->priority_2) == 0) {

        return E_dequeue(any->priority_2);
    } else if (is_queue_empty(any->priority_1) == 0) {

        return E_dequeue(any->priority_1);
    } else {
        printf("\nThere is no Exam waiting for Doctor");
        return NULL;
    }
}



int priority_queue_waiting(ExamPriorityQueue *queue) {
/**
 * \brief Calculate the total number of exams waiting in all priority queues // Calcula o número total de exames esperando em todas as filas de prioridade
 *
 * \param queue - Pointer to the ExamPriorityQueue structure to be checked // Ponteiro para a estrutura ExamPriorityQueue a ser verificada
 *
 * \details This function sums up the number of exams in each priority queue within the ExamPriorityQueue structure to determine the total number of waiting exams. // Esta função soma o número de exames em cada fila de prioridade dentro da estrutura ExamPriorityQueue para determinar o número total de exames esperando.
 * \details The total number of waiting exams is obtained by adding the sizes of all priority queues. // O número total de exames esperando é obtido somando os tamanhos de todas as filas de prioridade.
 *
 * \warning The function assumes that the pointer provided is valid and non-NULL. // A função assume que o ponteiro fornecido é válido e não é NULL.
 *
 * \return int - Total number of exams waiting in all priority queues // Número total de exames esperando em todas as filas de prioridade
 */
    int waiting = 0;
    waiting += queue_size(queue->priority_1) + queue_size(queue->priority_2) +
               queue_size(queue->priority_3) + queue_size(queue->priority_4) +
               queue_size(queue->priority_5) + queue_size(queue->priority_6);



    return waiting;
}


int get_ai_priority(Exam *exam) {
/**
 * \brief Determine the priority of an exam based on its condition // Determina a prioridade de um exame com base em sua condição
 *
 * \param exam - Pointer to the Exam structure whose priority needs to be determined // Ponteiro para a estrutura Exam cuja prioridade precisa ser determinada
 *
 * \details This function assigns a priority to an exam based on its condition using predefined criteria. // Esta função atribui uma prioridade a um exame com base em sua condição usando critérios predefinidos.
 * \details Priorities are assigned as follows:
 *          - 1 for Normal Health
 *          - 2 for Bronchitis
 *          - 3 for Pneumonia
 *          - 4 for COVID, Pulmonary Embolism, and Pleural Effusion
 *          - 5 for Pulmonary Fibrosis and Tuberculosis
 *          - 6 for Lung Cancer
 * \details If the condition is not recognized, it returns 0. // Se a condição não for reconhecida, retorna 0.
 *
 * \warning If the exam pointer or condition string is NULL, an error message is printed and a priority of -1 is returned. // Se o ponteiro do exame ou a string da condição for NULL, uma mensagem de erro é impressa e uma prioridade de -1 é retornada.
 *
 * \return int - Priority assigned to the exam based on its condition // Prioridade atribuída ao exame com base em sua condição
 */
    if (!exam) {
        printf("\nNull Pointer to Exam!");
        return -1; // Retorna um valor de erro se o exame for NULL
    }

    char *condition = get_exam_condition(exam);
    if (!condition) {
        printf("\nError  getting AI Condition\n");
        return -1; // Retorna um valor de erro se a condição do exame for NULL
    }

    // Define as prioridades com base na condição do exame
        if (strcmp(condition, "Normal Health") == 0) {
        return 1;
        } else if (strcmp(condition, "Bronchitis") == 0) {
        return 2;
        } else if (strcmp(condition, "Pneumonia") == 0) {
        return 3;
        } else if (strcmp(condition, "COVID") == 0) {
        return 4;
        } else if (strcmp(condition, "Pulmonary Embolism") == 0) {
        return 4;
        } else if (strcmp(condition, "Pleural Effusion") == 0) {
        return 4;
        } else if (strcmp(condition, "Pulmonary Fibrosis") == 0) {
        return 5;
        } else if (strcmp(condition, "Tuberculosis") == 0) {
        return 5;
        } else if (strcmp(condition, "Lung Cancer") == 0) {
        return 6;
        }

        return 0;
        }



int get_report_priority_condition(Report *report){
/**
 * \brief Determine the priority of a report based on its condition // Determina a prioridade de um relatório com base em sua condição
 *
 * \param report - Pointer to the Report structure whose priority needs to be determined // Ponteiro para a estrutura Report cuja prioridade precisa ser determinada
 *
 * \details This function assigns a priority to a report based on its condition using predefined criteria. // Esta função atribui uma prioridade a um relatório com base em sua condição usando critérios predefinidos.
 * \details Priorities are assigned as follows:
 *          - 1 for Normal Health
 *          - 2 for Bronchitis
 *          - 3 for Pneumonia
 *          - 4 for COVID, Pulmonary Embolism, and Pleural Effusion
 *          - 5 for Pulmonary Fibrosis and Tuberculosis
 *          - 6 for Lung Cancer
 * \details If the condition is not recognized, it returns 0. // Se a condição não for reconhecida, retorna 0.
 *
 * \warning If the report pointer or condition string is NULL, an error message is printed and a priority of -1 is returned. // Se o ponteiro do relatório ou a string da condição for NULL, uma mensagem de erro é impressa e uma prioridade de -1 é retornada.
 *
 * \return int - Priority assigned to the report based on its condition // Prioridade atribuída ao relatório com base em sua condição
 */

    char *condition = get_report_condition(report);
    if (!condition) {
        printf("\nError  getting Report Condition\n");
        return -1; // Retorna um valor de erro se a condição do exame for NULL
    }

    // Define as prioridades com base na condição do report
        if (strcmp(condition, "Normal Health") == 0) {
        return 1;
        } else if (strcmp(condition, "Bronchitis") == 0) {
        return 2;
        } else if (strcmp(condition, "Pneumonia") == 0) {
        return 3;
        } else if (strcmp(condition, "COVID") == 0) {
        return 4;
        } else if (strcmp(condition, "Pulmonary Embolism") == 0) {
        return 4;
        } else if (strcmp(condition, "Pleural Effusion") == 0) {
        return 4;
        } else if (strcmp(condition, "Pulmonary Fibrosis") == 0) {
        return 5;
        } else if (strcmp(condition, "Tuberculosis") == 0) {
        return 5;
        } else if (strcmp(condition, "Lung Cancer") == 0) {
        return 6;
        }

        return 0;
        }





int get_report_id(Report *report){
/**
 * \brief Retrieve the ID of a report // Recupera o ID de um relatório
 *
 * \param report - Pointer to the Report structure from which the ID will be retrieved // Ponteiro para a estrutura Report da qual o ID será recuperado
 *
 * \details This function returns the ID of the specified report. // Esta função retorna o ID do relatório especificado.
 *
 * \warning If the report pointer is NULL, an error message is printed and a special error value of -999 is returned. // Se o ponteiro do relatório for NULL, uma mensagem de erro é impressa e um valor de erro especial de -999 é retornado.
 *
 * \return int - ID of the report // ID do relatório
 */
    if(!report){
        printf("\nError:: report pointer cannot be NULL");
        return  -999;

    }

    return report->id;


}


int get_report_exam_id(Report *report){
/**
 * \brief Retrieve the exam ID associated with a report // Recupera o ID do exame associado a um relatório
 *
 * \param report - Pointer to the Report structure from which the exam ID will be retrieved // Ponteiro para a estrutura Report da qual o ID do exame será recuperado
 *
 * \details This function returns the exam ID associated with the specified report. // Esta função retorna o ID do exame associado ao relatório especificado.
 *
 * \warning If the report pointer is NULL, an error message is printed and a special error value of -999 is returned. // Se o ponteiro do relatório for NULL, uma mensagem de erro é impressa e um valor de erro especial de -999 é retornado.
 *
 * \return int - Exam ID associated with the report // ID do exame associado ao relatório
 */
    if(!report){
        printf("\nError:: report pointer cannot be NULL");
        return -999;


    }

    return report->exam_id;

}


char *get_report_condition(Report *report){
/**
 * \brief Retrieve the condition string of a report // Recupera a string de condição de um relatório
 *
 * \param report - Pointer to the Report structure from which the condition string will be retrieved // Ponteiro para a estrutura Report da qual a string de condição será recuperada
 *
 * \details This function returns the condition string of the specified report. // Esta função retorna a string de condição do relatório especificado.
 *
 * \warning If the report pointer is NULL, an error message is printed and NULL is returned. // Se o ponteiro do relatório for NULL, uma mensagem de erro é impressa e NULL é retornado.
 *
 * \return char* - Condition string of the report // String de condição do relatório
 */
    if(!report){
        printf("\nError:: report pointer cannot be NULL");
        return NULL;


    }

    return report->condition;
}

struct tm *get_report_time(const Report *report) {
/**
 * \brief Retrieve the report time // Recupera o horário do relatório
 *
 * \param report - Pointer to the Report structure from which the report time will be retrieved // Ponteiro para a estrutura Report da qual o horário do relatório será recuperado
 *
 * \details This function returns the time associated with the specified report. // Esta função retorna o horário associado ao relatório especificado.
 *
 * \warning If the report pointer is NULL, an error message is printed and NULL is returned. // Se o ponteiro do relatório for NULL, uma mensagem de erro é impressa e NULL é retornado.
 *
 * \return const struct tm* - Time associated with the report // Horário associado ao relatório
 */
    if (!report) {
        printf("\nError: report pointer cannot be NULL");
        return NULL;
    }

    return report->report_time;
}


Report *do_medical_report(Exam *exam) {
/**
 * \brief Generate a medical report based on an exam // Gera um relatório médico com base em um exame
 *
 * \param exam - Pointer to the Exam structure for which the medical report is to be generated // Ponteiro para a estrutura Exam para a qual o relatório médico será gerado
 *
 * \details This function generates a medical report based on the provided exam. It decides whether to keep the original diagnostic or update it with a new one based on a random chance.
 *          The decision is made with an 80% chance to maintain the original diagnostic and a 20% chance to generate a new one.
 *          The report's timestamp is set to the current local time.
 * \details Esta função gera um relatório médico com base no exame fornecido. Ela decide se mantém o diagnóstico original ou o atualiza com um novo, com base em uma chance aleatória.
 *          A decisão é feita com uma chance de 80% de manter o diagnóstico original e 20% de gerar um novo.
 *          O horário do relatório é definido como o horário local atual.
 *
 * \warning If the diagnostic or new diagnostic pointer is NULL, an error message is printed and NULL is returned. // Se o ponteiro do diagnóstico ou o novo diagnóstico for NULL, uma mensagem de erro é impressa e NULL é retornado.
 * \warning If it is not possible to generate a new diagnostic after 10 attempts, a warning message is printed. // Se não for possível gerar um novo diagnóstico após 10 tentativas, uma mensagem de aviso é impressa.
 *
 * \return Report* - Pointer to the newly created report // Ponteiro para o novo relatório criado
 */
    time_t tempoAtual;
    time(&tempoAtual);
    struct tm *tempoLocal = localtime(&tempoAtual);

    int geradorP = rand() % 100 + 1;
    Report *new_report = NULL;

    if (geradorP <= 80 ) {
        new_report = create_report(get_exam_id(exam), get_exam_condition(exam), tempoLocal);
        printf("\nIA Decision Maintained\n");
    } else {
        char *diagnostic = get_exam_condition(exam);
        char *new_diagnostic = diagnostic_by_ai();

        // Verificação de ponteiros NULL
        if (diagnostic == NULL || new_diagnostic == NULL) {
            fprintf(stderr, "Error: Diagnostic or New Diagnostic is NULL.\n");
            return NULL;
        }else{

        int attempts = 0;
        while (strcmp(diagnostic, new_diagnostic) == 0 && attempts < 10) {
            new_diagnostic = diagnostic_by_ai();
            attempts++;
        }

        if (attempts >= 10) {
            printf("\nWarning: Wasn't possible to create a new diagnostic...\n");
        }

        printf("\nOld diagnostic for patient: %s\n", diagnostic);
        printf("\nNew diagnostic for patient: %s\n", new_diagnostic);

        new_report = create_report(get_exam_id(exam), new_diagnostic, tempoLocal);
    }
    }

    return new_report;
}



Report *create_report(int exam_id, const char *condition, const struct tm *report_time) {

/**
 * \brief Create a new medical report // Cria um novo relatório médico
 *
 * \param exam_id - ID of the associated exam // ID do exame associado
 * \param condition - Diagnostic condition to be recorded in the report // Condição diagnóstica a ser registrada no relatório
 * \param report_time - Pointer to the time when the report was created // Ponteiro para o horário em que o relatório foi criado
 *
 * \details This function allocates memory for a new Report structure, initializes its fields with provided values, and copies the examination condition and report time.
 *          The report ID is randomly generated between 1 and 1000.
 * \details Esta função aloca memória para uma nova estrutura de Relatório, inicializa seus campos com valores fornecidos e copia a condição do exame e o horário do relatório.
 *          O ID do relatório é gerado aleatoriamente entre 1 e 1000.
 *
 * \warning If memory allocation fails for any of the fields, an error message is printed and the program exits. // Se a alocação de memória falhar para qualquer um dos campos, uma mensagem de erro é impressa e o programa é encerrado.
 *
 * \return Report* - Pointer to the newly created report // Ponteiro para o novo relatório criado
 */
        Report *new_report = (Report*)malloc(sizeof(Report));
        if(!new_report){
            printf("\nError : Memory Allocation Failed (Create_report)\n");
            exit(1);
        }
        new_report->id = rand()%1000+1;
        new_report->exam_id = exam_id;
        new_report->report_time = (struct tm*)malloc(sizeof(struct tm));
        if(!new_report->report_time){
            printf("\nError : Memory Allocation Failed (Report time)\n");
            exit(1);
        }

         memcpy(new_report->report_time, report_time, sizeof(struct tm));

        new_report->condition = (char*)malloc(strlen(condition)+1 *sizeof(char));
        if(!new_report->condition){
            printf("\nError : Memory Allocation Failed\n");
            exit(1);
        }

        strcpy(new_report->condition,condition);
        return new_report;
}
void free_report(Report *report) {
/**
 * \brief Free the memory allocated for a medical report // Libera a memória alocada para um relatório médico
 *
 * \param report - Pointer to the Report structure to be freed // Ponteiro para a estrutura Report a ser liberada
 *
 * \details This function releases the memory allocated for the condition, report time, and the Report structure itself.
 * \details Esta função libera a memória alocada para a condição, horário do relatório e a própria estrutura Report.
 *
 * \warning If the report pointer is NULL, the function does nothing. // Se o ponteiro do relatório for NULL, a função não faz nada.
 */
    if (report) {
        free(report->condition);
        free(report->report_time);
        free(report);
    }
}



void print_report(Report *report) {
/**
 * \brief Print the details of a medical report to the standard output // Imprime os detalhes de um relatório médico na saída padrão
 *
 * \param report - Pointer to the Report structure to be printed // Ponteiro para a estrutura Report a ser impressa
 *
 * \details This function prints the report ID, exam ID, condition, and report time to the standard output in a formatted manner.
 *          The report time is formatted as "dd/mm/yyyy hh:mm:ss".
 * \details Esta função imprime o ID do relatório, ID do exame, condição e horário do relatório na saída padrão de forma formatada.
 *          O horário do relatório é formatado como "dd/mm/aaaa hh:mm:ss".
 *
 * \warning If the report pointer is NULL, a message indicating that the pointer is NULL is printed. // Se o ponteiro do relatório for NULL, uma mensagem indicando que o ponteiro é NULL é impressa.
 */
    if (report) {
        printf("\n\t===============================\n");
        printf("\t    DOCTOR'S REPORT DETAILS\n");
        printf("\t===============================\n");
        printf("\tReport ID      : %d\n", get_report_id(report));
        printf("\tExam ID        : %d\n", get_report_exam_id(report));
        printf("\tCondition      : %s\n", get_report_condition(report));

        char buffer[100];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", get_report_time(report));
        printf("\tReport Time    : %s\n", buffer);

        printf("\t=============================\n");
    } else {
        printf("Report pointer is NULL.\n");
    }
}


void print_report_db(Report *report,FILE *report_file){
/**
 * \brief Print the details of a medical report to a file // Imprime os detalhes de um relatório médico em um arquivo
 *
 * \param report - Pointer to the Report structure to be printed // Ponteiro para a estrutura Report a ser impressa
 * \param report_file - File pointer to the file where the report details will be written // Ponteiro para o arquivo onde os detalhes do relatório serão gravados
 *
 * \details This function writes the report ID, exam ID, condition, and report time to the specified file.
 *          The report time is formatted as "yyyy-mm-dd hh:mm:ss".
 * \details Esta função grava o ID do relatório, ID do exame, condição e horário do relatório no arquivo especificado.
 *          O horário do relatório é formatado como "aaaa-mm-dd hh:mm:ss".
 *
 * \warning If the report pointer or file pointer is NULL, or if there is an error writing to the file, an error message is printed and the program exits. // Se o ponteiro do relatório ou o ponteiro do arquivo for NULL, ou se houver um erro ao gravar no arquivo, uma mensagem de erro é impressa e o programa é encerrado.
 */
if(report){
    fprintf(report_file, "ID: %d\n", get_report_id(report));
    fprintf(report_file, "Exam ID: %d\n", get_report_exam_id(report));
    fprintf(report_file, "Condition: %s\n", get_report_condition(report));

    const struct tm *report_time = get_report_time(report);
    if (report_time) {
        fprintf(report_file, "Report Time: %d-%02d-%02d %02d:%02d:%02d\n",
                report_time->tm_year + 1900,
                report_time->tm_mon + 1,
                report_time->tm_mday,
                report_time->tm_hour,
                report_time->tm_min,
                report_time->tm_sec);
    } else {
        printf("\nReport time is NULL\n");
    }

}else{
    printf("\nError  Saving Report on DB(new_patient)\n");
    exit(1);
}

}

void print_status(double tempo_total, double time_reports, int pacientes_totais,
                 int waiting, int reports_finalizados,
                 int reports_tempo_ok, int ia_exames_realizados,
                 double *priority_time_sum, int *priority_count) {

/**
 * \brief Print a status report with various metrics // Imprime um relatório de status com várias métricas
 *
 * \param tempo_total - Total execution time of the program in seconds // Tempo total de execução do programa em segundos
 * \param time_reports - Total time spent generating reports in seconds // Tempo total gasto na geração de relatórios em segundos
 * \param pacientes_totais - Total number of patients arrived // Número total de pacientes que chegaram
 * \param waiting - Number of patients currently in the priority queue // Número de pacientes atualmente na fila de prioridade
 * \param reports_finalizados - Number of reports finalized // Número de relatórios finalizados
 * \param reports_tempo_ok - Number of reports completed within the acceptable time (> 7,200 seconds) // Número de relatórios concluídos dentro do tempo aceitável (> 7.200 segundos)
 * \param ia_exames_realizados - Number of IA exams performed // Número de exames de IA realizados
 * \param priority_time_sum - Array of cumulative report times for each priority level // Array com os tempos acumulados de relatório para cada nível de prioridade
 * \param priority_count - Array of counts of reports for each priority level // Array com a contagem de relatórios para cada nível de prioridade
 *
 * \details This function prints a status report summarizing various metrics related to the execution of the program, including total execution time, patient data, report metrics, and priority-based report times.
 *          The average report time for each priority level is calculated and displayed if there are reports for that priority.
 * \details Esta função imprime um relatório de status resumindo várias métricas relacionadas à execução do programa, incluindo tempo total de execução, dados dos pacientes, métricas de relatórios e tempos de relatório baseados em prioridade.
 *          O tempo médio de relatório para cada nível de prioridade é calculado e exibido se houver relatórios para essa prioridade.
 *
 * \warning Ensure that `priority_time_sum` and `priority_count` arrays are properly initialized and have at least 6 elements. // Certifique-se de que os arrays `priority_time_sum` e `priority_count` estão devidamente inicializados e têm pelo menos 6 elementos.
 */

    printf("\n========== Status Report ==========\n");
    printf("Total Execution Time:          %.2lf seconds\n", tempo_total);
    printf("Total Patients Arrived:        %d\n", pacientes_totais);
    printf("Patients in Priority Queue:    %d\n", waiting);
    printf("IA Exams Performed:            %d\n", ia_exames_realizados);
    printf("Patients with Doctor's report: %d%%\n", reports_finalizados * 100 / ia_exames_realizados);
    printf("Mean Report Time:              %.2lf seconds\n", time_reports / reports_finalizados);
    printf("Reports Finalized:             %d\n", reports_finalizados);
    printf("Reports out of time (delayed) (>7.200): %d\n", reports_tempo_ok);

    printf("\nPriority Report Times:\n");
    for (int i = 0; i < 6; i++) {
        if (priority_count[i] > 0) {
            printf("Mean Report Time for priority %d, appereances(%d): %.2lf seconds\n", i + 1, priority_count[i],priority_time_sum[i] / priority_count[i]);
        } else {
            printf("Priority %d: No reports\n", i + 1);
        }
    }

    printf("===================================\n");
}

