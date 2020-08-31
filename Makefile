DIR_SRC			= ./src/
DIR_AlG			= ./src/algorithm/
DIR_OUTPUT		= ./src/output/
DIR_INPUT		= ./src/input/
DIR_INC			= ./includes/
DIR_LIB			= ./libft/
DIR_OBJ 		= ./obj/

FILE_ALG		= \
				bellman_ford \
				clean_memory \
				refresh_graph_1 \
				refresh_graph_2 \
				suurballe_1 \
				suurballe_2

FILE_INPUT		= \
				error \
				nodes \
				parse \
				parse_nodes \
				parse_relations \
				relations \
				validation \
				array

FILE_OUTPUT		= \
				choose_ways \
				print_lems

OBJ_LEMIN 		= $(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILE_ALG)) $(addsuffix .o, $(FILE_INPUT)) $(addsuffix .o, $(FILE_OUTPUT)) lemin.o)

CC 	   			= gcc
LEMIN 			= lem-in
#CFLAGS 	   		= -Wall -Werror -Wextra -O2 -I$(DIR_INC) -I$(DIR_LIB)$(DIR_INC)
CFLAGS 	   		=  -g -O2 -I$(DIR_INC) -I$(DIR_LIB)$(DIR_INC)

all: lemin

lib:
	@make -C $(DIR_LIB)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_AlG)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)%.o: $(DIR_INPUT)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)%.o: $(DIR_OUTPUT)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

lemin: $(DIR_OBJ) $(OBJ_LEMIN) lib
	@$(CC) $(CFLAGS) -o $(LEMIN) $(OBJ_LEMIN) $(DIR_LIB)libft.a

clean:
	@make clean -C $(DIR_LIB)
	@rm -rf $(DIR_OBJ)
	@rm -f libft.a

fclean: clean
	@make fclean -C $(DIR_LIB)
	@rm -f $(LEMIN)

re: fclean all

.PHONY: all clean fclean re
