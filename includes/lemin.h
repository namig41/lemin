#ifndef FT_LEMIN_H
# define FT_LEMIN_H

# include <limits.h>
# include "libft.h"
# include "vector.h"

# define START 			"##start"
# define END 			"##end"
# define COMMENT 		'#'

# define ERR 			"ERROR"

# define F_START 		0
# define F_END			1
# define F_FIRST		2

# define N_NAME 		0
# define N_X 			1
# define N_Y 			2
# define N_SIZE			3
# define N_SEP 			' '

# define R_NODE_1		0
# define R_NODE_2		1
# define R_SIZE 		2
# define R_SEP 			'-'

typedef enum 			e_title {
      TITLE_START,
      TITLE_END,
      NODE,
      RELATION
} 						t_title;

typedef struct 			s_point
{
    int 				x;
    int 				y;
}						t_point;

typedef struct			s_relations
{
    int					relation_weight;
    struct s_nodes 		*to;
    struct s_relations	*next;
    struct s_relations	*start;

}						t_relations;

typedef struct			s_nodes
{
	char 				*name;
	int					weight;
    t_uc				is_start;
    t_uc				is_finish;
    t_uc 				we_used_it;
    struct s_relations 	*next_relations;
	struct s_relations	*relations;
	struct s_nodes		*prev;
	struct s_nodes 		*start;				
	struct s_nodes		*next;
    t_point 			point;
}						t_nodes;

int 					g_ants;


/*---------------------- PARSE --------------------------------------------------*/

int 			parse_title(char *line);
void 			parse_number_ants(int fd);
void 			parse_file(char* file_name, t_nodes **nodes, t_relations **relations);
void 			parse_switch(char* file_name, t_nodes **nodes, t_relations **relations);
void 			parse_section_node(char *line, t_nodes **nodes);
void 			parse_section_relation(char *line, t_nodes *nodes, t_relations **list);
void			parse_line_node(char *line, char *w_node[]);
void 			parse_line_relation(char *line, char *w_relation[]);


/*----------------------- ERROR --------------------------------------------*/

void 			print_error(void);

/*----------------------- NODES --------------------------------------------------*/

void 			nodes_front(t_nodes **list, t_nodes *node);
void 			nodes_second(t_nodes **list, t_nodes *node);
void 			nodes_back(t_nodes **list, t_nodes *node);
void 			nodes_insert(t_nodes **list, t_nodes *node, size_t num);

/*----------------------- RELATIOINS ----------------------------------------------*/

void 			relations_front(t_relations **list, t_relations *relation);
void			relations_second(t_relations **list, t_relations *relation);
void 			relations_back(t_relations **list, t_relations *relation);

void 			print_nodes(t_nodes *head);
void 			print_relations(t_relations *head);

/*----------------------- OTHER -------------------------------------------------*/

void 			node_init(t_nodes *node, t_title name_title);
t_nodes			*node_search(t_nodes *node, char *name);

#endif
