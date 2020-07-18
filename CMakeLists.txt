cmake_minimum_required(VERSION 3.1...3.10)

project(lemin LANGUAGES C)


add_library(libft STATIC
			libft/conversion/ft_atoi.c
			libft/conversion/ft_lltoa.c
			libft/conversion/ft_tolower.c
			libft/conversion/ft_toupper.c
			libft/conversion/ft_itoa.c
			libft/conversion/ft_uitoa_base.c
			libft/conversion/ft_ulltoa_base.c

			libft/ctype/ft_isalnum.c
			libft/ctype/ft_isalpha.c
			libft/ctype/ft_isascii.c
			libft/ctype/ft_isdigit.c
			libft/ctype/ft_isescape.c
			libft/ctype/ft_isprint.c

			libft/display/ft_putchar.c
			libft/display/ft_putchar_fd.c
			libft/display/ft_putendl.c
			libft/display/ft_putendl_fd.c
			libft/display/ft_putnbr.c
			libft/display/ft_putnbr_fd.c
			libft/display/ft_putstr.c
			libft/display/ft_putstr_fd.c

			libft/gnl/get_next_line.c

			libft/math/ft_abs.c
			libft/math/ft_bpow.c
			libft/math/ft_max.c
			libft/math/ft_min.c
			libft/math/ft_random.c

			libft/memory/ft_bzero.c
			libft/memory/ft_memset.c
			libft/memory/ft_memalloc.c
			libft/memory/ft_memccpy.c
			libft/memory/ft_memchr.c
			libft/memory/ft_memcmp.c
			libft/memory/ft_memcpy.c
			libft/memory/ft_memdel.c
			libft/memory/ft_memmove.c
			libft/memory/ft_memswap.c
			libft/memory/ft_swap.c

			libft/strings/ft_strcat.c
			libft/strings/ft_strchr.c
			libft/strings/ft_strchri.c
			libft/strings/ft_strclr.c
			libft/strings/ft_strcmp.c
			libft/strings/ft_strcpy.c
			libft/strings/ft_strdup.c
			libft/strings/ft_strequ.c
			libft/strings/ft_striter.c
			libft/strings/ft_striteri.c
			libft/strings/ft_strjoin.c
			libft/strings/ft_strlcat.c
			libft/strings/ft_strlen.c
			libft/strings/ft_strmap.c
			libft/strings/ft_strmapi.c
			libft/strings/ft_strncat.c
			libft/strings/ft_strncmp.c
			libft/strings/ft_strncpy.c
			libft/strings/ft_strnequ.c
			libft/strings/ft_strnew.c
			libft/strings/ft_strnstr.c
			libft/strings/ft_strrchr.c
			libft/strings/ft_strsplit.c
			libft/strings/ft_strstr.c
			libft/strings/ft_strsub.c
			libft/strings/ft_strtrim.c

			libft/vector/vector_byte_capacity.c
			libft/vector/vector_byte_size.c
			libft/vector/vector_chr.c
			libft/vector/vector_clear.c
			libft/vector/vector_copy.c
			libft/vector/vector_destroy.c
			libft/vector/vector_erase.c
			libft/vector/vector_free_size.c
			libft/vector/vector_get_element.c
			libft/vector/vector_init.c
			libft/vector/vector_insert_data.c
			libft/vector/vector_is_empty.c
			libft/vector/vector_is_initialized.c
			libft/vector/vector_memmove.c
			libft/vector/vector_move_array.c
			libft/vector/vector_move_back_array.c
			libft/vector/vector_move_back_data.c
			libft/vector/vector_move.c
			libft/vector/vector_offset.c
			libft/vector/vector_pop_back.c
			libft/vector/vector_pop_front.c
			libft/vector/vector_push_back_array.c
			libft/vector/vector_push_back_data.c
			libft/vector/vector_push_front_data.c
			libft/vector/vector_qsort.c
			libft/vector/vector_reallocate.c
			libft/vector/vector_resize.c
			libft/vector/vector_set_element.c

			libft/stack/stack_byte_capacity.c
			libft/stack/stack_byte_size.c
			libft/stack/stack_destroy.c
			libft/stack/stack_get_element.c
			libft/stack/stack_init.c
			libft/stack/stack_is_empty.c
			libft/stack/stack_is_initialized.c
			libft/stack/stack_move_array.c
			libft/stack/stack_move.c
			libft/stack/stack_move_data.c
			libft/stack/stack_pop.c
			libft/stack/stack_push.c
			libft/stack/stack_second.c
			libft/stack/stack_top.c)

set(LEMIN_SRC
    src/lemin.c
    src/error.c
    src/nodes.c
    src/relations.c
    src/parse.c
	src/other.c)


include_directories("includes/" "libft/includes/")

add_executable(lemin ${LEMIN_SRC})
target_link_libraries(lemin PUBLIC libft)
