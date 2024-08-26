# Nome do executável
TARGET = clinic_simulation

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -pthread

# Arquivos fonte
SRCS = main.c queue.c exam.c patient.c medical_check.c rx_machine.c time_control.c
# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regras
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Recompilar o projeto do zero
rebuild: clean all

