#ifndef EXAM_H_INCLUDED
#define EXAM_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>  // Para definir NULL e outros tipos úteis

typedef struct exam Exam;

/**
 * Creates a new exam.
 *
 * @param id Exam ID.
 * @param rx_id Associated RX ID.
 * @param patient_id Patient ID.
 * @param condition Patient's condition.
 * @param exam_time Exam date and time.
 * @return Pointer to the created exam.
 */
Exam *create_exam(int id, int rx_id, int patient_id, const char* condition, const struct tm *exam_time);

/**
 * Destroys an exam.
 *
 * @param exam Pointer to the exam to be destroyed.
 */
void destroy_exam(Exam *exam);

/**
 * Retrieves the exam ID.
 *
 * @param exam Pointer to the exam.
 * @return Exam ID.
 */
int get_exam_id(Exam *exam);

/**
 * Obtém o ID do paciente associado ao exame.
 *
 * @param exam Ponteiro para o exame.
 * @return ID do paciente.
 */
int get_exam_patient_id(Exam *exam);
/**
 * Retrieves the RX ID associated with the exam.
 *
 * @param exam Pointer to the exam.
 * @return RX ID.
 */
int get_exam_rx_id(Exam *exam);

/**
 * Retrieves the date and time of the exam.
 *
 * @param exam Pointer to the exam.
 * @return Pointer to the tm structure containing the date and time of the exam.
 */
struct tm *get_exam_time(Exam *exam);
/**
 * Retrieves the patient's condition associated with the exam.
 *
 * @param exam Pointer to the exam.
 * @return Pointer to the string containing the patient's condition.
 */

char *get_exam_condition(Exam *exam);

/**
 * Prints the detailed information of an exam.
 *
 * @param e Pointer to the exam to be printed.
 */
void print_exam(Exam *e);

/**
 * Prints the exam information to a file.
 *
 * @param current_exam Pointer to the exam to be printed.
 * @param exam_file Pointer to the file where the information will be printed.
 */

void print_exam_db(Exam *current_exam, FILE *exam_file);
#endif // EXAM_H_INCLUDED
