#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -gdwarf-4 -pthread -fsanitize=thread
#=================== NAME ===================#
NAME = philo
#============ MINISHELL SOURCES =============#
SRCS = main.c \
	eat.c \
	utils.c \
	action.c \
	routine.c \
	philo_utils.c \
	philos_handle.c \
	time_handle.c \
	thread_utils.c
#============ TRANSFORM .c TO .o ============#
OBJ_DIR = obj/
SRCS_DIR = srcs/
INCLUDE_DIR = includes
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

INCLUDES = -I$(INCLUDE_DIR)

all : $(NAME)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(OBJ) $(OBJBUILTINS)
	@ $(CC) $(FLAGS) -lreadline $(OBJ) $(OBJBUILTINS) $(INCLUDES) -o $(NAME)

clean :
	@ rm -rf $(OBJ_DIR)

fclean :
	@ rm -rf $(NAME) $(OBJ_DIR)

re : fclean all

.PHONY : all clean fclean re
