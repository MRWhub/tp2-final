#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

#include <time.h>
#include <stddef.h>  // Para NULL e outros tipos úteis

typedef struct patient Patient;

/**
 * \brief Create a new patient.
 *
 * \param id - Patient ID. // ID do paciente.
 * \param name - Patient's name. // Nome do paciente.
 * \param arrival - Pointer to a tm structure with the arrival time. // Ponteiro para uma estrutura tm com o horário de chegada.
 * \return Pointer to the created patient. // Ponteiro para o paciente criado.
 */
Patient *create_patient(int id, const char *name, const struct tm *arrival);

/**
 * \brief Destroy a patient.
 *
 * \param patient - Pointer to the patient to be destroyed. // Ponteiro para o paciente a ser destruído.
 */
void destroy_patient(Patient *patient);

/**
 * \brief Get the patient's ID.
 *
 * \param patient - Pointer to the patient. // Ponteiro para o paciente.
 * \return The patient's ID. // O ID do paciente.
 */
int get_patient_id(Patient *patient);

/**
 * \brief Get the patient's name.
 *
 * \param patient - Pointer to the patient. // Ponteiro para o paciente.
 * \return The patient's name. // O nome do paciente.
 */
char *get_patient_name(Patient *patient);

/**
 * \brief Get the patient's arrival time.
 *
 * \param patient - Pointer to the patient. // Ponteiro para o paciente.
 * \return Pointer to the tm structure containing the patient's arrival time. // Ponteiro para a estrutura tm contendo o horário de chegada do paciente.
 */
struct tm *get_patient_arrival(Patient *patient);
/**
 * \brief Create a new patient with random attributes.
 *
 * \return Pointer to the created patient. // Ponteiro para o paciente criado.
 */
Patient *patient_in();
/**
 * \brief Simulate the arrival of a new patient.
 *
 * \return Pointer to the new patient if arrival is simulated; NULL otherwise. // Ponteiro para o novo paciente se a chegada for simulada; NULL caso contrário.
 */
Patient *patient_arrival();
/**
 * \brief Print patient details to standard output.
 *
 * \param patient - Pointer to the patient to be printed. // Ponteiro para o paciente a ser impresso.
 */
void print_patient(Patient *patient);
/**
 * \brief Print patient details to a file.
 *
 * \param new_patient - Pointer to the patient to be written to the file. // Ponteiro para o paciente a ser gravado no arquivo.
 * \param file - File pointer where the patient details will be written. // Ponteiro para o arquivo onde os detalhes do paciente serão gravados.
 */
void print_patient_db(Patient *new_patient, FILE *file);
#endif // PATIENT_H_INCLUDED
