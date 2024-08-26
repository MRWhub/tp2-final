#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "patient.h"
#define MAX_LEN 100
struct patient {
    int id;
    char *name;
    struct tm *arrival;
};


Patient *create_patient(int id, const char *name, const struct tm *arrival){
    /** \brief This function builds a patient object // Esta função constrói um objeto paciente
     *
     * \param id - Unique patient identification // Identificação única do paciente
     * \param name - Pointer to patient name // Ponteiro para o nome do paciente
     * \param arrival - TM object with patient's arrival // Objeto TM com a hora de chegada do paciente
     * \return The patient object created // O objeto paciente criado
     *
     * \details This function allocates memory for a new patient and initializes its fields with the given values.
     *          The TM structure passed as a parameter is copied to the new patient structure.
     *          If the name or arrival pointers are NULL, the function prints an error message to stderr and returns NULL.
     *          If memory allocation fails, the function prints an error message to stderr and returns NULL.
     *
     * \details Esta função aloca memória para um novo paciente e inicializa seus campos com os valores fornecidos.
     *          A estrutura TM passada como parâmetro é copiada para a nova estrutura do paciente.
     *          Se os ponteiros para name ou arrival forem NULL, a função imprime uma mensagem de erro em stderr e retorna NULL.
     *          Se a alocação de memória falhar, a função imprime uma mensagem de erro em stderr e retorna NULL.
     *
     * \warning If the name or arrival pointers are NULL, the function prints an error message to stderr and returns NULL.
     *          Se os ponteiros para name ou arrival forem NULL, a função imprime uma mensagem de erro em stderr e retorna NULL.
     *
     */

     /* Checks if name or arrival is NULL // Verifica se name ou arrival é nulo */
     if (!name) {
        printf("\nError: Patient's name cannot be NULL");
        return NULL;
     } else if (!arrival){
         printf("\nError: Patient's arrival cannot be NULL");
         return NULL;
     }

    /* Allocates memory for patient structure and checks whether the allocation was successful
    // Aloca memória para estrutura paciente e verifica se a alocação foi bem-sucedida */
    Patient *patient = (Patient *)malloc(sizeof(Patient));


    if(!patient){
        printf("\nFailed to allocate memory for patient's structure");
        return NULL;
    }

    /* Assign the patient's id(Type INT) // Atribui o id(INT) do paciente */
    patient->id = id;

    /* Allocates memory for patient's name and checks whether the allocation was successful
    // Aloca memória para o nome do paciente e verifica se a alocação foi bem-sucedida */
    patient->name = (char *) malloc(sizeof(char) * strlen(name) + 1);

    if(!patient->name) {
        printf("\nFailed to allocate memory for name");
        free(patient);
        return NULL;
    }

    /* Copy the name // Copia o nome */
    strcpy(patient->name, name);

    /* Allocates memory for patient's arrival and checks whether the allocation was successful
    // Aloca memória para a hora de chegada do paciente e verifica se a alocação foi bem-sucedida */
    patient->arrival = (struct tm *) malloc(sizeof(struct tm));

    if (!patient->arrival){
        printf("\nFailed to allocate memory for arrival");
        free(patient->name);
        free(patient);
        return NULL;
    }

    /* Copy the tm structure // Copia a estrutura tm */
    memcpy(patient->arrival, arrival, sizeof(struct tm));

    return patient;
}

void destroy_patient(Patient *patient){
    /** \brief Free the allocated memory for the patient's structure // Libera memória alocada para a estrutura do paciente
     *
     * \param patient - Pointer to patient's structure for free // Ponteiro para estrutura do paciente a ser liberada
     *
     * \details This function checks if the patient pointer is NULL. If not, it frees the memory allocated for the patient's name and arrival, if they were allocated, and then frees the patient structure itself.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se não for, libera a memória alocada para o nome e data de nascimento do paciente, se estiverem alocados, e então libera a própria estrutura do paciente.
     *
     * \warning This function does not return any value. If the patient pointer is NULL, it simply returns without doing anything.
     *          Esta função não retorna nenhum valor. Se o ponteiro do paciente for NULL, simplesmente retorna sem fazer nada.
     */

    /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
    if (!patient){
        printf("\nNULL POINTER!!");
        return;
    }

    /* Free patient's name if allocated // Libera o nome do paciente, se alocado */
    if (patient->name) {
        free(patient->name);

            }

    /* Free patient's arrival if allocated // Libera a data de nascimento do paciente, se alocada */
    if (patient->arrival) {
        free(patient->arrival);

    }

    /* Free the patient structure itself // Libera a estrutura do paciente */
    free(patient);
    printf("\nMemory Allocation Freed!(Patient)\n");
}

int get_patient_id(Patient *patient) {
    /** \brief This function gets and returns patient's ID // Esta função obtém e retorna o ID do paciente
     *
     * \param patient - Pointer to patient's structure // Ponteiro para a estrutura do paciente
     * \return The patient's ID // O ID do paciente
     *
     * \details This function checks if the patient pointer is NULL. If it is, it prints an error message to stderr and returns 1. Otherwise, it returns the patient's ID.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se for, imprime uma mensagem de erro em stderr e retorna 1. Caso contrário, retorna o ID do paciente.
     *
     *
     */

     /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        printf("\nError: NULL patient pointer");
        return 1;
     }

    return patient->id;
}

char *get_patient_name(Patient *patient){
    /** \brief This function gets and returns patient's name // Esta função obtém e retorna o nome do paciente
     *
     * \param patient - Pointer to patient's structure // Ponteiro para a estrutura do paciente
     * \return The patient's name // O nome do paciente
     *
     * \details This function checks if the patient pointer is NULL. If it is, it prints an error message to stderr and returns NULL. Otherwise, it returns the patient's name.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se for, imprime uma mensagem de erro em stderr e retorna NULL. Caso contrário, retorna o nome do paciente.
     *
     *
     */

     /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        printf("\nError: NULL patient pointer");
        return NULL;
     }

    return patient->name;
}


Patient *patient_in(){
/** \brief Create a new patient with random details // Cria um novo paciente com detalhes aleatórios
 *
 * \return Pointer to the newly created Patient structure // Ponteiro para a estrutura Patient recém-criada
 *
 * \details This function generates a new patient with a random name, surname, and ID.
 *          It also assigns the current time as the patient's arrival time.
 * \details Esta função gera um novo paciente com um nome, sobrenome e ID aleatórios.
 *          Também atribui o horário atual como o horário de chegada do paciente.
 */


    time_t tempoAtual;
    time(&tempoAtual);
    struct tm *tempoLocal = localtime(&tempoAtual);

    int geradorNome = rand()%30;
    int geradorSobrenome= rand()%30;
    int geradorID = rand()%1000+1;

    char nomeCompleto[MAX_LEN];



    const char *nomes[30] = {
        "Ana", "Bruno", "Carlos", "Diana", "Eduardo",
        "Fernanda", "Gabriel", "Helena", "Igor", "Julia",
        "Karine", "Lucas", "Mariana", "Nelson", "Olga",
        "Pedro", "Quiteria", "Rafael", "Sofia", "Tiago",
        "Ursula", "Vanessa", "William", "Xuxa", "Yara",
        "Zé", "Alice", "Bob", "Clara", "Daniel",
        "Elena", "Francisco"
    };

    // Array com 30 sobrenomes
    const char *sobrenomes[30] = {

        "Almeida", "Barros", "Carvalho", "Dias", "Ferreira",
        "Gonçalves", "Henrique", "Inácio", "Junqueira", "Klein",
        "Lima", "Machado", "Nascimento", "Oliveira", "Pereira",
        "Queiroz", "Rodrigues", "Silva", "Teixeira", "Ueda",
        "Vasquez", "Wanderley", "Ximenes", "Yoshida", "Zanetti",
        "Andrade", "Barros", "Campos", "Duarte", "Freitas",
        "Gomes", "Haddad"
    };

    snprintf(nomeCompleto, MAX_LEN, "%s %s", nomes[geradorNome], sobrenomes[geradorSobrenome]);



    return create_patient(geradorID,nomeCompleto,tempoLocal);
    }




struct tm *get_patient_arrival(Patient *patient){
    /** \brief This function gets and returns patient's arrival // Esta função obtém e retorna a hora de chegada do paciente
     *
     * \param patient - Pointer to patient's structure // Ponteiro para a estrutura do paciente
     * \return Pointer to const struct tm representing the patient's arrival // Ponteiro para const struct tm representando a da de chegada do paciente
     *
     * \details This function checks if the patient pointer is NULL. If it is, it prints an error message to stderr and returns NULL. Otherwise, it returns a pointer to the patient's arrival.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se for, imprime uma mensagem de erro em stderr e retorna NULL. Caso contrário, retorna um ponteiro para a data de nascimento do paciente.
     *
     *
     */

     /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){

        printf("\nError: NULL patient pointer");
        return NULL;
     }

    return patient->arrival;
};


Patient *patient_arrival(){

/** \brief Simulate the arrival of a patient // Simula a chegada de um paciente
 *
 * \return Pointer to a newly created Patient structure or NULL if no patient is created // Ponteiro para a nova estrutura Patient ou NULL se nenhum paciente for criado
 *
 * \details This function simulates the arrival of a patient with a 20% probability.
 *          If a patient is created, it returns a pointer to the new patient; otherwise, it returns NULL.
 * \details Esta função simula a chegada de um paciente com uma probabilidade de 20%.
 *          Se um paciente for criado, retorna um ponteiro para o novo paciente; caso contrário, retorna NULL.
 */

     int geradorP = rand()%100 +1;
     if(geradorP<=20){
        Patient *new_patient = patient_in();
        if(!new_patient){
            printf("\nError creating patient!!!");
            exit(1);
        }
        return new_patient;
     }else{

     return NULL;

     }



}
void print_patient(Patient *p) {
/** \brief Print the details of a patient to the standard output // Imprime os detalhes de um paciente na saída padrão
 *
 * \param p - Pointer to the Patient structure to be printed // Ponteiro para a estrutura Patient a ser impressa
 *
 * \details This function prints the ID, name, and arrival time of a patient to the standard output.
 *          The arrival time is formatted as "dd/mm/yyyy hh:mm:ss".
 * \details Esta função imprime o ID, nome e horário de chegada de um paciente na saída padrão.
 *          O horário de chegada é formatado como "dd/mm/yyyy hh:mm:ss".
 */
    if (p) {
        printf("\n\t=============================\n");
        printf("\t       NEW PATIENT ARRIVED\n");
        printf("\t=============================\n");
        printf("\tPatient ID      : %d\n", get_patient_id(p));
        printf("\tPatient Name    : %s\n", get_patient_name(p));

        char buffer[100];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", get_patient_arrival(p));
        printf("\tArrival Time    : %s\n", buffer);

        printf("\t=============================\n");
    }
}


void print_patient_db(Patient *new_patient, FILE *patient_file){
/** \brief Print the details of a patient to a file // Imprime os detalhes de um paciente em um arquivo
 *
 * \param new_patient - Pointer to the Patient structure to be written to the file // Ponteiro para a estrutura Patient a ser gravada no arquivo
 * \param patient_file - File pointer to the file where the patient details will be written // Ponteiro para o arquivo onde os detalhes do paciente serão gravados
 *
 * \details This function writes the ID, name, and arrival time of a patient to the specified file.
 *          The arrival time is formatted as "yyyy-mm-dd hh:mm:ss".
 * \details Esta função grava o ID, nome e horário de chegada de um paciente no arquivo especificado.
 *          O horário de chegada é formatado como "aaaa-mm-dd hh:mm:ss".
 *
 * \warning If the patient pointer or file pointer is NULL, or if there is an error writing to the file, an error message is printed and the program exits.
 *          Se o ponteiro do paciente ou o ponteiro do arquivo for NULL, ou se houver um erro ao gravar no arquivo, uma mensagem de erro é impressa e o programa é encerrado.
 */
    if (new_patient && patient_file) {
    fprintf(patient_file, "ID: %d\n", get_patient_id(new_patient));
    fprintf(patient_file, "Name: %s\n", get_patient_name(new_patient));
    const struct tm *arrival_time = get_patient_arrival(new_patient);

    if (arrival_time) {
    fprintf(patient_file, "Arrival Time: %d-%02d-%02d %02d:%02d:%02d\n",
            arrival_time->tm_year + 1900,
            arrival_time->tm_mon + 1,
            arrival_time->tm_mday,
            arrival_time->tm_hour,
            arrival_time->tm_min,
            arrival_time->tm_sec);
    }else{
    printf("Error Saving Patient on DB\n");
    exit(1);

    }



    }else{
    printf("Error Saving Patient on DB(new_patient)\n");
    exit(1);
    }

}


