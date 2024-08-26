#include "rx_machine.h"
#include <stdlib.h>
#include <stdio.h>
#include "time_control.h"
#include "patient.h"
#include "exam.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAX_EXECUTION 43.200
struct rx_machine {
    int id;
    bool avaible;
    int patient_id;
};

Rx **create_machines() {
/**
 * @brief Creates a list of X-Machines with initial settings.
 * @details Allocates memory for a fixed number of X-Machines and initializes each one.
 * @return Pointer to an array of pointers to Rx (X-Machines).
 */

    Rx **machines_list = (Rx**)malloc(5 * sizeof(Rx*)); // Alocar memória para 5 máquinas
    if (!machines_list) {
        printf("\nError: Memory allocation failed (Machines Vector)");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        machines_list[i] = (Rx*)malloc(sizeof(Rx));
        if (!machines_list[i]) {
            printf("\nError: Memory allocation failed (Machine %d)", i);
            exit(1);
        }

        machines_list[i]->id = i + 1;
        machines_list[i]->avaible = true;
        machines_list[i]->patient_id = 0;
    }

    return machines_list;
}

void destroy_machines(Rx **machines_list) {

/**
 * @brief Verifies the availability of X-Machines and occupies one for the given patient.
 * @details Searches through the list of X-Machines to find an available machine, assigns the patient to it,
 *          and performs an exam using the machine. If no machine is available, prints a message.
 * @param machines_list - Pointer to the array of pointers to X-Machines.
 * @param patient - Pointer to the patient for whom the exam is to be performed.
 * @return Pointer to the created Exam or NULL if no machine is available.
 */

    if (machines_list) {
        for (int i = 0; i < 5; i++) {
            if (machines_list[i]) {
                free(machines_list[i]);
            }
        }
        free(machines_list);
    }
}

Exam *verify_and_ocupate(Rx **machines_list, Patient *patient) {
/**
 * @brief Verify and occupy an available X-Machine for the given patient // Verifica e ocupa uma Máquina X disponível para o paciente dado
 *
 * @param machines_list - Pointer to the array of X-Machines // Ponteiro para o array de Máquinas X
 * @param patient - Pointer to the patient who needs an exam // Ponteiro para o paciente que precisa de um exame
 * @return Pointer to the created Exam if a machine is available, NULL otherwise // Ponteiro para o exame criado se uma máquina estiver disponível, NULL caso contrário
 */
    if (machines_list && patient) {
        for (int i = 0; i < 5; i++) {
            if (machines_list[i] && machines_list[i]->avaible) {
                machines_list[i]->patient_id = get_patient_id(patient);
                machines_list[i]->avaible = false;
                Exam *new_exam = do_exam_with_AI(machines_list[i]);
                return new_exam;
            }
        }

        printf("\nThere is no X-MACHINE avaible, please wait.");
    }
    return NULL;
}



char *diagnostic_by_ai() {
/**
 * @brief Generate a random diagnostic based on AI
 * @details This function creates a diagnostic based on probability. The probabilities for each diagnostic are as follows:
 * - "Normal Health": 30%
 * - "Bronchitis": 20%
 * - "Pneumonia": 10%
 * - "COVID": 10%
 * - "Pulmonary Embolism": 5%
 * - "Pleural Effusion": 5%
 * - "Pulmonary Fibrosis": 5%
 * - "Tuberculosis": 5%
 * - "Lung Cancer": 10%
 * The thresholds array defines cumulative probability thresholds to determine the diagnostic.
 * @return Pointer to a string representing the diagnostic
 */

        char *diagnostics[] = {
        "Normal Health",
        "Bronchitis",
        "Pneumonia",
        "COVID",
        "Pulmonary Embolism",
        "Pleural Effusion",
        "Pulmonary Fibrosis",
        "Tuberculosis",
        "Lung Cancer"
    };

    static const int thresholds[] = {30, 50, 60, 70, 75, 80, 85, 90, 100};

    int geradorP = rand() % 100 + 1;

    for (int i = 0; i < 9; i++) {
        if (geradorP <= thresholds[i]) {
            return diagnostics[i];
        }
    }
    return diagnostics[8];
}

Exam *do_exam_with_AI(Rx *machine) {
/**
 * \brief Perform an exam using the AI diagnostic and mark the machine as available.
 * \details This function simulates performing an exam on a patient using an AI-generated diagnostic.
 *          It assigns a unique exam ID, generates a diagnostic based on AI, and marks the X-Machine as available after the exam is completed.
 *          The exam is conducted with a simulated delay to mimic real-world processing time.
 *
 * \param machine - Pointer to the X-Machine performing the exam. It should be a valid pointer to a machine that is currently in use.
 *                  The function will check if the machine is available and perform the exam if it is.
 *
 * \return Pointer to the created Exam. If the machine is valid and the exam is successfully created,
 *         a pointer to the new Exam is returned. If the machine is NULL, indicating an invalid machine, the function returns NULL.
 */
    if (machine) {
        int exam_id = rand() % 1000;
        printf("\nExam started for (ID): %d", machine->patient_id);

        time_t tempoAtual;
        time(&tempoAtual);
        struct tm *tempoLocal = localtime(&tempoAtual);

        const char *ai_diagnostic = diagnostic_by_ai();
        Exam *new_exam = create_exam(exam_id, machine->id, machine->patient_id, ai_diagnostic, tempoLocal);
        my_sleep(MAX_EXECUTION/4320);

        printf("\nExam finished for (ID): %d", machine->patient_id);

        machine->avaible = true;
        machine->patient_id = 0;

        return new_exam;
    }
    return NULL;
}

