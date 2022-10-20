/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_partage_taches.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:44:12 by creyt             #+#    #+#             */
/*   Updated: 2022/10/20 11:33:20 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./utils/libft/libft.h"
# include "./utils/ft_printf/ft_printf.h"

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
# define HOME_SET "HOME not set\n"
# define NOT_CLOSE "Quotes are not closed\n"
# define NOT_NUM "numeric argument required\n"
# define ERR_MALL "malloc error\n"
# define NOT_RDIR "redirection error\n"
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

typedef struct s_shell
{
	char				**env;
	int					n_env;
	char				*path;
	int					n_cmd;
	t_input				*in;
}	t_shell;

//prompt.c - Verena - OK
void	prompt(char **envp);
int		ft_new_prompt(t_shell *sh);
void	ft_close(t_shell *sh);
void	prompt_quotes(t_shell *sh);
void	ft_wait(t_shell *sh, int i);

//builtins.c - Claire
int		b_pwd(t_shell *sh);
int		b_exit(t_shell *sh, int in);
int		b_env(t_shell *sh);
void	free_all(t_shell *sh);

//cmd_selector.c - Claire
void	cmd_selector(t_shell *sh, int i);
int		builtins_selector(t_shell *sh, int i);
void	bs_fd(t_shell *sh, int i, t_fd *fdk);
int		is_bs(t_shell *sh, int i);
char	*ft_strtolower(char *s);

//parsing.c - Verena - OK
int		parsing_init(char *args, t_shell *sh);
int		each_elem(t_input *in, char *s, int i, int n);
void	parsing_elem(t_shell *sh, char *s, int in);
int		parsing_misc(t_shell *sh, int i, char **input);

//parsing_utils.c- Verena - OK
int		check_quotes(t_input *input, char *s);
int		avoid_spaces(char *s, int i);
void	count_spaces(t_input *input, char *s);
int		avoid_quotes(t_input *in, int i);
int		avoid_n(t_input *in, int i);

//parsing_elem_utils.c - Verena
int		malloc_elem(t_input *in, char *s, int i, int n);
int		into_elem_quotes(t_input *in, char *s, int i, int n);
int		nbr_cmd(t_shell *sh, char *args, int i);

//quotes_mgmt.c - Claire
int		d_quotes_mgmt(t_input *input, char *s, int i, int n);
int		s_quotes_mgmt(t_input *input, char *s, int i, int n);
int		no_quote_mgmt(t_input *input, char *s, int i, int n);

//env_utils.c - Claire
char	**parse_env(char *s);
void	sort_env(t_shell *sh, int in);
void	print_env(t_shell *sh, int in, char **elem);
void	the_sorter(t_shell *sh, char *tempura, char *a, char *b);
void	dup_array_to_env(t_shell *sh, char **array);

//cd.c - Claire
int		b_cd(t_shell *sh, int in);
int		where_in_env(t_shell *sh, char *key, int len);
void	update_env(t_shell *sh, char *dir);
int		print_cd(char *s, int n);
int		no_place_like_home(t_shell *sh);

//b_export.c - Claire
int		b_export(t_shell *sh, int in);
void	add_key(t_shell *sh, char *key, char *val);
char	*define_val(char *key, char *val);
void	update_arr(t_shell *sh, char **new_array, int add_key, char *new_val);
void	update_key(t_shell *sh, char *key, char *val, char **new_array);

//b_unset.c - Claire
int		b_unset(t_shell *sh, int in);
void	remove_key(t_shell *sh, char *key);

//b_echo.c - Claire
int		b_echo(t_shell *sh, int in);
void	print_echo_n(t_input *in, int i);

//b_init.c - Claire
void	b_init(t_shell *sh, char *envp[]);
void	malloc_checker(char *s);
void	freearray(char **m, int n);

//var.c - Verena - OK
void	conv_var(t_shell *sh, int in, int i);
char	*find_dollar(t_input *in, int j, char *tmp, int i);

//quotes_utils.c - Clairec
int		trimquotes(t_shell *sh, char *s, int in, int i);

//redir_utils.c - Nous
int		count_redir(t_shell *sh, int in);
void	init_redir(t_shell *sh, int in);
int		pop_redir(t_shell *sh, int in, int i);
int		checker_redir(t_shell *sh, int in, int i);

//redir.c - Nous
void	exec_redir(t_shell *sh);
void	redir_output(t_shell *sh, int i, int j);
void	redir_input(t_shell *sh, int i, int j);
void	append_in(t_shell *sh, int i, int j);
void	heredoc(t_shell *sh, int i, int j);

//redir_again.c - Nous
void	mgmnt_fd(t_shell *sh);
void	open_fd(t_shell *sh, int i, int j);
void	init_fd(t_shell *sh);
void	reset_fd(t_fd *fdk);

//execve.c - Verena 
void	exec_boarders(t_shell *sh, int in);
int		exec_middle(t_shell *sh, int in, int ok, int i);
int		on_my_way(t_shell *sh, int ok, char *cmd_path, int in);
void	execution(t_shell *sh, int in, int i, int ok);
int		len_array(char **array);

//signals.c - Nous
void	sig_int(int c);
void	sig_double(int c);
char	*ft_set_signal(void);

//error.c - Verena - OK
int		ft_exit_word(char *msg, int status, int print)
int		msg_cmd_404(t_shell *sh, int i);

//free.c - Claire
void	free_sh(t_shell *sh);
void	free_redir(t_shell *sh, int i);

//ft_split_exception_utils.c
int		check_qts_split(char *s, int i, char c);

#endif
