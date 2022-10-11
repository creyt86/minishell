/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:44:12 by creyt             #+#    #+#             */
/*   Updated: 2022/10/11 16:49:06 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include "../utils/ft_printf/ft_printf.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>	// readline, rl*
# include <readline/history.h>	// readline, rl*
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <sys/stat.h>			// stat, lstat, fstat
# include <sys/ioctl.h>			// ioctl
# include <sys/types.h>			// read
# include <sys/uio.h>			// read
# include <signal.h>			// signal, sigaction, sig*, kill
# include <dirent.h>			// *dir
# include <string.h>			// strerror
# include <termios.h>			// tc*
# include <curses.h>			// tg*
# include <term.h>				// tg*
# include <fcntl.h>				// open

/* DEFINE COLORS */
# define PURP "\e[35m"
# define GREEN "\e[32m"
# define RED "\e[31m"
# define WHITE "\e[39m"
# define YELLOW "\033[33m"
# define ORANGE "$(shell tput setaf 208)"
# define RESET "\e[0"
# define BLUE "\033[34m"
# define CYAN "\033[36m"

# define MAX_PATH 1024
# define NO_RESULT -1

# define ERR_PERM 126
# define ERR_404 127
# define ERR_SIGN 128
# define ERR_EXIT 255
# define ERR_REDIR 258

# define ERROR "Error\n"
# define OPT_IGN "Option(s) ignored\n"
# define ERR_ARG "Argument invalid in this scope\n"
# define ERR_NO_ARG "No argument(s) provided\n"
# define CMD_404 "command not found\n"
# define TM_ARG "too many arguments\n"
# define HOMELESS "HOME not set\n"
# define NOT_EVEN "Quotes are not closed\n"
# define NOT_NUM "numeric argument required\n"
# define ERR_MALL "malloc error\n"
# define ERR_CHEVRON "redirection error\n"
# define ERR_PIPE "pipe error\n"
# define ERR_FILE "file error\n"
# define ERR_EXE "execution error\n"
# define ERR_TOKEN "syntax error near unexpected token\n"

int		g_exit_stat;

// structure des listes chaînées afin de pouvoir stocker les arguments
//et de pouvoir les utiliser de manière optimisée
typedef struct s_elem
{
	char	**cont;
}	t_elem;

typedef struct s_redir
{
	char	*file;
	char	*chevron;
}	t_redir;

typedef struct s_fd
{
	int		in;
	int		out;
}	t_fd;

typedef struct s_input
{
	pid_t	pid;
	char	*cont;
	int		n_elem;
	t_elem	*elem;
	t_redir	*red;
	int		n_redir;
	int		pos_red;
	t_fd	fd;
}	t_input;

typedef struct s_data
{
	char				**env;
	int					n_env;
	char				*path;
	int					n_cmd;
	t_input				*in;
}	t_data;

//prompt.c
void	prompt(char **envp);
int		termios_line(t_data *dt);
void	the_closer(t_data *dt);
void	prompt_quotes(t_data *dt);
void	ft_wait(t_data *dt, int i);

//builtins.c
int		b_pwd(t_data *dt);
int		b_exit(t_data *dt, int in);
int		b_env(t_data *dt);
void	free_all(t_data *dt);

//cmd_selector.c
void	cmd_selector(t_data *dt, int i);
int		builtins_selector(t_data *dt, int i);
void	bs_fd(t_data *dt, int i, t_fd *fdk);
int		is_bs(t_data *dt, int i);
char	*ft_strtolower(char *s);

//parsing.c
int		parsing_init(char *args, t_data *dt);
int		each_elem(t_input *in, char *s, int i, int n);
void	parsing_elem(t_data *dt, char *s, int in);
int		parsing_misc(t_data *dt, int i, char **input);

//parsing_utils.c
int		check_quotes(t_input *input, char *s);
int		skip_spaces(char *s, int i);
void	space_counter(t_input *input, char *s);
int		skip_quotes(t_input *in, int i);
int		skip_n(t_input *in, int i);

//parsing_elem_utils.c
int		malloc_elem(t_input *in, char *s, int i, int n);
int		into_elem_quotes(t_input *in, char *s, int i, int n);
int		nb_cmd(t_data *dt, char *args, int i);

//quotes_mgmt.c
int		d_quotes_mgmt(t_input *input, char *s, int i, int n);
int		s_quotes_mgmt(t_input *input, char *s, int i, int n);
int		no_quote_mgmt(t_input *input, char *s, int i, int n);

//env_utils.c
char	**parse_env(char *s);
void	sort_env(t_data *dt, int in);
void	print_env(t_data *dt, int in, char **elem);
void	the_sorter(t_data *dt, char *tempura, char *a, char *b);
void	dup_array_to_env(t_data *dt, char **array);

//b_cd.c
int		b_cd(t_data *dt, int in);
int		where_in_env(t_data *dt, char *key, int len);
void	update_env(t_data *dt, char *dir);
int		print_cd(char *s, int n);
int		no_place_like_home(t_data *dt);

//b_export.c
int		b_export(t_data *dt, int in);
void	add_key(t_data *dt, char *key, char *val);
char	*define_val(char *key, char *val);
void	update_arr(t_data *dt, char **new_array, int add_key, char *new_val);
void	update_key(t_data *dt, char *key, char *val, char **new_array);

//b_unset.c
int		b_unset(t_data *dt, int in);
void	remove_key(t_data *dt, char *key);

//b_echo.c
int		b_echo(t_data *dt, int in);
void	print_echo_n(t_input *in, int i);

//b_init.c
void	b_init(t_data *dt, char *envp[]);
void	malloc_checker(char *s);
void	freearray(char **m, int n);

//var.c
void	conv_var(t_data *dt, int in, int i);
char	*check_doll(t_input *in, int j, char *tmp, int i);

//quotes_utils.c
int		trimquotes(t_data *dt, char *s, int in, int i);

//redir_utils.c
int		count_redir(t_data *dt, int in);
void	init_redir(t_data *dt, int in);
int		pop_redir(t_data *dt, int in, int i);
int		checker_redir(t_data *dt, int in, int i);

//redir.c
void	exec_redir(t_data *dt);
void	redir_output(t_data *dt, int i, int j);
void	redir_input(t_data *dt, int i, int j);
void	append_in(t_data *dt, int i, int j);
void	heredoc(t_data *dt, int i, int j);

//redir_again.c
void	mgmnt_fd(t_data *dt);
void	open_fd(t_data *dt, int i, int j);
void	init_fd(t_data *dt);
void	reset_fd(t_fd *fdk);

//execve.c
void	exec_boarders(t_data *dt, int in);
int		exec_middle(t_data *dt, int in, int ok, int i);
int		on_my_way(t_data *dt, int ok, char *cmd_path, int in);
void	execution(t_data *dt, int in, int i, int ok);
int		len_array(char **array);

//signals.c
void	sig_int(int c);
void	sig_double(int c);
char	*ft_set_signal(void);

//error.c
int		the_end(char *msg, int status, int print);
int		msg_cmd_404(t_data *dt, int i);

//free.c
void	free_data(t_data *dt);
void	free_redir(t_data *dt, int i);

//ft_split_exception_utils.c
int		check_qts_split(char *s, int i, char c);

#endif
