#ifndef FT_LEMIN_H
# define FT_LEMIN_H

# include <limits.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

# define START 			"##start"
# define END 			"##end"
# define COMMENT 		'#'

# define ERR 			"ERROR"

# define F_START 		(1 << 0)
# define F_END			(1 << 1)
# define F_REL			(1 << 2)
# define F_DD			(1 << 3)
# define F_COMMENT		(1 << 4)

# define N_NAME 		0
# define N_X 			1
# define N_Y 			2
# define N_SIZE			3
# define N_SEP 			' '

# define R_FROM			0
# define R_TO			1
# define R_SIZE 		2
# define R_SEP 			'-'

typedef enum 			e_title
{
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
	int					lem_num;
	t_point 			point;

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


/*----------------------- PARSE --------------------------------------------------------*/

void 			parse_ants(t_nodes **nodes);
void 			parse_file(t_nodes **nodes);
void 			parse_switch(char* line, t_nodes **nodes, t_title *title, t_uc *f);
int 			parse_title_1(char *line, t_nodes **nodes, t_title *title, t_uc *f);
int 			parse_title_2(char *line, t_nodes **nodes, t_title *title, t_uc *f);

/*---------------------- PARSE NODES --------------------------------------------------*/

void 			parse_section_node(char *line, t_nodes **nodes, t_title *title, t_uc *f);

/*---------------------- PARSE RELATIONS --------------------------------------------------*/

void 			parse_section_relation(char *line, t_nodes **nodes);


/*---------------------- VALIDATION --------------------------------------------------*/

char			**valid_line_node(char *line);
char			**valid_line_relation(char *line, t_nodes *nodes);
int				valid_start_end(t_nodes *nodes);
int				valid_node_cmp(t_nodes *nodes, t_nodes *node);

/*----------------------- ERROR ------------------------------------------------------*/

void 			print_error(t_nodes **nodes);

/*----------------------- NODES ------------------------------------------------------*/

void 			node_init(t_nodes **nodes, t_nodes *node, char *w_node[], t_title *title);

void 			nodes_front(t_nodes **nodes, t_nodes *node);
void 			nodes_back(t_nodes **nodes, t_nodes *node);
void 			nodes_insert(t_nodes **nodes, t_nodes *node, size_t num);

t_nodes			*node_search(t_nodes *node, char *name);

/*----------------------- RELATIOINS -------------------------------------------------*/

void 			relations_back(t_nodes **nodes, t_nodes *node, t_relations *relation);

/*----------------------- OTHER ------------------------------------------------------*/

void			print_nodes(t_nodes *head);
size_t			word_count(char **ar);

/*----------------------- ALGORITHM --------------------------------------------------*/

void 			suurballe(t_nodes *nodes, t_options *options);
void			bellman_ford(t_nodes *nodes);
void 			refresh(t_nodes *nodes);

/*------------------------- CLEAR MEMORY ----------------------------------------------*/

void 			clean_path(t_nodes *nodes);
void 			delete_tmp_links(t_nodes *nodes);
void			clean_memory(t_options **options, t_nodes **nodes);
void 			free_nodes(t_nodes **nodes);

/*------------------------- OUTPUT --------------------------------------------------*/

t_options		*choose_ways(t_options *options);

/*					need delete							*/
void	add_option(t_options **options);
void 	print_lems(t_paths *ways);
void	print_shortest_way(t_nodes *nodes);
void	delete_relations(t_nodes **nodes);
int		is_cross(t_nodes *nodes);
void	add_in_out(t_nodes *nodes);
void	change_direction(t_nodes *nodes);

int g_fd;

#endif
