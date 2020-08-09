DIR_AlG			= ./src/algorithm/
DIR_INPUT		= ./src/input/
DIR_OUTPUT		= ./src/output/
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
				other \
				parse \
				parse_nodes \
				parse_relations \
				relations

FILE_OUTPUT		= \
				choose_ways \
				print_lems

SRC_LEMIN		= \
				$(addprefix $(DIR_AlG), $(addsuffix .c, $(FILE_ALG))) \
				$(addprefix $(DIR_INPUT), $(addsuffix .c, $(FILE_INPUT))) \
				$(addprefix $(DIR_OUTPUT), $(addsuffix .c, $(FILE_OUTPUT))) \
				./src/lemin.c


OBJ_LEMIN 		= \
				$(addsuffix .o, $(FILE_ALG)) \
				$(addsuffix .o, $(FILE_INPUT)) \
				$(addsuffix .o, $(FILE_OUTPUT)) \
				./lemin.o

CC 	   			= gcc
LEMIN 			= lem-in
CHECKER 		= checker
#CFLAGS 	   		= -Wall -Werror -Wextra -O2 -I$(DIR_INC) -I$(DIR_LIB)$(DIR_INC)
CFLAGS 	   		=  -g -O2 -I$(DIR_INC) -I$(DIR_LIB)$(DIR_INC)

all: lemin

lib:
	@make -C $(DIR_LIB)
	@cp libft/libft.a ./

obj_lemin:
	@$(CC) $(CFLAGS) -c $(SRC_LEMIN)

lemin: lib obj_lemin
	@$(CC) $(CFLAGS) -o $(LEMIN) $(OBJ_LEMIN) libft/libft.a
	@mkdir -p $(DIR_OBJ)
	@mv -f $(OBJ_LEMIN) $(DIR_OBJ)

clean:
	@make clean -C $(DIR_LIB)
	@rm -rf $(DIR_OBJ)
	@rm -f libft.a

fclean: clean
	@make fclean -C $(DIR_LIB)
	@rm -f $(LEMIN)

re: fclean all

compile: re
	@clear
	./$(LEMIN)

.PHONY: all clean fclean re compile
