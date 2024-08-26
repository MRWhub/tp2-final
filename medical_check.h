#ifndef MEDICAL_CHECK_INCLUDED
#define MEDICAL_CHECK_INCLUDED
#include "exam.h"
#include <pthread.h>



typedef struct examPriority  ExamPriorityQueue;

typedef struct report Report;

/**
 * \brief Create a new priority queue for exams // Cria uma nova fila de prioridade para exames
 *
 * \return A pointer to the newly created priority queue // Um ponteiro para a nova fila de prioridade criada
 */
ExamPriorityQueue *new_priority_queue();

/**
 * \brief Free the memory allocated for a priority queue // Libera a memória alocada para uma fila de prioridade
 *
 * \param any - Pointer to the priority queue to be freed // Ponteiro para a fila de prioridade a ser liberada
 */
void free_priority_queue(ExamPriorityQueue *any);

/**
 * \brief Insert an exam into the appropriate priority queue // Insere um exame na fila de prioridade apropriada
 *
 * \param any - Pointer to the priority queue where the exam will be inserted // Ponteiro para a fila de prioridade onde o exame será inserido
 * \param exam - Pointer to the exam to be inserted // Ponteiro para o exame a ser inserido
 */
void insert_in_priority_queue(ExamPriorityQueue *any, Exam *exam);

/**
 * \brief Retrieve an exam from the highest priority queue // Recupera um exame da fila de maior prioridade
 *
 * \param any - Pointer to the priority queue from which to retrieve the exam // Ponteiro para a fila de prioridade da qual recuperar o exame
 * \return Pointer to the retrieved exam or NULL if all queues are empty // Ponteiro para o exame recuperado ou NULL se todas as filas estiverem vazias
 */
Exam *get_priority_exams(ExamPriorityQueue *any);

/**
 * \brief Get the AI-assigned priority for an exam // Obtém a prioridade atribuída pela IA para um exame
 *
 * \param exam - Pointer to the exam for which to get the priority // Ponteiro para o exame para o qual obter a prioridade
 * \return The priority level assigned by the AI (1-6) or 0 if the condition is not recognized // O nível de prioridade atribuído pela IA (1-6) ou 0 se a condição não for reconhecida
 */
int get_ai_priority(Exam *exam);

/**
 * \brief Get the ID of a report // Obtém o ID de um relatório
 *
 * \param report - Pointer to the report from which to get the ID // Ponteiro para o relatório do qual obter o ID
 * \return The ID of the report // O ID do relatório
 */
int get_report_id(Report *report);

/**
 * \brief Get the exam ID associated with a report // Obtém o ID do exame associado a um relatório
 *
 * \param report - Pointer to the report from which to get the exam ID // Ponteiro para o relatório do qual obter o ID do exame
 * \return The exam ID associated with the report // O ID do exame associado ao relatório
 */
int get_report_exam_id(Report *report);

/**
 * \brief Get the time when the report was created // Obtém o horário em que o relatório foi criado
 *
 * \param report - Pointer to the report from which to get the time // Ponteiro para o relatório do qual obter o horário
 * \return Pointer to the report creation time // Ponteiro para o horário de criação do relatório
 */
struct tm *get_report_time(const Report *report);

/**
 * \brief Create a new report for an exam // Cria um novo relatório para um exame
 *
 * \param exam_id - ID of the exam associated with the report // ID do exame associado ao relatório
 * \param condition - Condition reported // Condição relatada
 * \param report_time - Time when the report was created // Horário em que o relatório foi criado
 * \return Pointer to the newly created report // Ponteiro para o novo relatório criado
 */
Report *create_report(int exam_id, const char *condition, const struct tm *report_time);

/**
 * \brief Get the condition reported in a report // Obtém a condição relatada em um relatório
 *
 * \param report - Pointer to the report from which to get the condition // Ponteiro para o relatório do qual obter a condição
 * \return The condition reported in the report // A condição relatada no relatório
 */
char *get_report_condition(Report *report);

/**
 * \brief Print the details of a report to the console // Imprime os detalhes de um relatório no console
 *
 * \param report - Pointer to the report to be printed // Ponteiro para o relatório a ser impresso
 */
void print_report(Report *report);

/**
 * \brief Free the memory allocated for a report // Libera a memória alocada para um relatório
 *
 * \param report - Pointer to the report to be freed // Ponteiro para o relatório a ser liberado
 */
void free_report(Report *report);

/**
 * \brief Check if all priority queues are empty // Verifica se todas as filas de prioridade estão vazias
 *
 * \param new_queue - Pointer to the priority queue to check // Ponteiro para a fila de prioridade a ser verificada
 * \return 1 if all priority queues are empty, 0 otherwise // 1 se todas as filas de prioridade estiverem vazias, 0 caso contrário
 */
int is_priority_queue_empty(ExamPriorityQueue *new_queue);

/**
 * \brief Generate a medical report for an exam, possibly altering the diagnostic // Gera um relatório médico para um exame, possivelmente alterando o diagnóstico
 *
 * \param exam - Pointer to the exam for which to generate the report // Ponteiro para o exame para o qual gerar o relatório
 * \return Pointer to the generated report // Ponteiro para o relatório gerado
 */
Report *do_medical_report(Exam *exam);

/**
 * \brief Print a report to a file // Imprime um relatório em um arquivo
 *
 * \param report - Pointer to the report to be printed // Ponteiro para o relatório a ser impresso
 * \param report_file - File pointer to the file where the report will be printed // Ponteiro para o arquivo onde o relatório será impresso
 */
void print_report_db(Report *report, FILE *report_file);

/**
 * \brief Get the total number of reports waiting in the priority queue // Obtém o número total de relatórios esperando na fila de prioridade
 *
 * \param queue - Pointer to the priority queue to check // Ponteiro para a fila de prioridade a ser verificada
 * \return Total number of reports waiting // Número total de relatórios esperando
 */
int priority_queue_waiting(ExamPriorityQueue *queue);

/**
 * \brief Get the AI-assigned priority for a report // Obtém a prioridade atribuída pela IA para um relatório
 *
 * \param report - Pointer to the report for which to get the priority // Ponteiro para o relatório para o qual obter a prioridade
 * \return The priority level assigned by the AI (1-6) or 0 if the condition is not recognized // O nível de prioridade atribuído pela IA (1-6) ou 0 se a condição não for reconhecida
 */
int get_report_priority_condition(Report *report);

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
 */
void print_status(double tempo_total, double time_reports, int pacientes_totais,
                 int waiting, int reports_finalizados,
                 int reports_tempo_ok, int ia_exames_realizados,
                 double *priority_time_sum, int *priority_count);
#endif // MEDICAL_CHECK_INCLUDED
