#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -gdwarf-4 -pthread -fsanitize=thread
#=================== NAME ===================#
NAME = philo
#============ MINISHELL SOURCES =============#
SRCS = \
	utils.c \
	init/main.c \
	init/philo_utils.c \
	init/philos_handle.c \
	routine/eat.c \
	routine/action.c \
	routine/routine.c \
	routine/time_handle.c \
	routine/thread_utils.c \
	ft_printf/ft_printf.c \
	ft_printf/printf_hex_print.c \
	ft_printf/printf_nbr_print.c \
	ft_printf/printf_char_print.c \
	error/error.c \
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
