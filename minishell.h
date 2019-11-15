#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "./get_next_line.h"
#define SH_PROMPT "[Unimaginative prompt] : "
#define TOKEN_MAX 255

void	ft_free_d_tab(void **d_tab);
void	ft_print_prompt(void);
