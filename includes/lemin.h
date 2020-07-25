#ifndef FT_LEMIN_H
# define FT_LEMIN_H

# include <limits.h>
# include "libft.h"
# include "vector.h"

# define START 			"##start"
# define END 			"##end"
# define COMMENT 		'#'

# define ERR 			"ERROR"

# define F_START 		(1 << 0)
# define F_END			(1 << 1)
//# define F_FIRST		(1 << 2)

# define N_NAME 		0
# define N_X 			1
# define N_Y 			2
# define N_SIZE			3
# define N_SEP 			' '

# define R_FROM			0
# define R_TO			1
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
    t_uc 				active;
    t_uc 				need_delete;
    int					relation_weight;
    struct s_nodes 		*to;
    struct s_relations	*next;
    struct s_relations	*start;

}						t_relations;

typedef struct			s_nodes
{
	char 				*name;
    t_uc				is_start;
    t_uc				is_finish;
    t_uc 				in;
    t_uc 				out;
    t_uc				need_delete;
    int					weight;
	t_point 			point;
	int					lem_num;

    struct s_nodes		*next;
    struct s_nodes		*tmp;
    struct s_relations	*relations;
	struct s_nodes		*prev;
	struct s_nodes 		*start;				
}						t_nodes;

typedef struct			s_options
{
	int					paths_count;
	struct s_paths		*paths;
	struct s_options	*start;
	struct s_options	*next;
}						t_options;

typedef struct 			s_paths
{
	int					nodes_count;
	struct s_paths		*start;
	struct s_paths		*next;
	struct s_nodes		**path;
}						t_paths;

//typedef struct 			s_path
//{
//	char 				*name;
//	struct s_path		*start;
//	struct s_path		*next;
//}						t_path;

int 					g_ants;


/*---------------------- PARSE --------------------------------------------------*/

int 			parse_title(char *line);
void 			parse_number_ants(int fd);
void 			parse_section_node(char *line, t_nodes **nodes);
void 			parse_file(char* file_name, t_nodes **nodes);
void 			parse_switch(char* file_name, t_nodes **nodes);
void 			parse_section_relation(char *line, t_nodes **nodes);
void			parse_line_node(char *line, char *w_node[]);
void 			parse_line_relation(char *line, char *w_relation[]);

/*----------------------- ERROR -------------------------------------------------*/

void 			print_error(int line);

/*----------------------- NODES --------------------------------------------------*/

void 			nodes_front(t_nodes **list, t_nodes *node);
void 			nodes_second(t_nodes **list, t_nodes *node);
void 			nodes_back(t_nodes **list, t_nodes *node);
void 			nodes_insert(t_nodes **list, t_nodes *node, size_t num);

void 			node_init(t_nodes *node, char *w_node[], t_title name_title);
t_nodes			*node_search(t_nodes *node, char *name);

/*----------------------- RELATIOINS ----------------------------------------------*/

void 			relations_front(t_nodes *nodes, t_relations *relation);
void			relations_second(t_nodes *nodes, t_relations *relation);
void 			relations_back(t_nodes *nodes, t_relations *relation);

/*----------------------- OTHER ----------------------------------------------------*/

void 			print_nodes(t_nodes *head);

/*----------------------- ALGORITHM ------------------------------------------------*/

void 			suurballe(t_nodes *nodes, t_options *options);
void			bellman_ford(t_nodes *nodes);
void 			refresh(t_nodes *nodes);
void 			clean_path(t_nodes *nodes);
void 			delete_tmp_links(t_nodes *nodes);
void			clean_memory(t_options **options, t_nodes **nodes);

/*------------------------- OUTPUT --------------------------------------------------*/

t_options	*choose_ways(t_options *options);

/*					need delete							*/
void	add_option(t_options **options);
void 	print_lems(t_paths *ways);
void	print_shortest_way(t_nodes *nodes);

#endif
