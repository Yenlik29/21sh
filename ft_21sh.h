/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:12:06 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:12:07 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>
# define IS_QUOTE(x) (x == '"' || x == '\'')

typedef struct 		s_history
{
	char 	*record;
	struct s_history *next;
	struct s_history *prev;
}					t_history;

typedef struct 		s_shell
{
	t_history		*history;
}					t_shell;

void		loop(char **env);
int			terminal_init();
int			terminal_define(void);
int			re_putchar(int ch);

int			ft_find(char **envp, char *word);
char		*ft_join_f(char *s1, char *s2);
char		*ft_join_f2(char *s1, char *s2);
int			len_env(char **envp);
size_t		word_count(char const *s, char c);

void		ft_env(char **w_splited, char **envp);
void		ft_putnstr(char *str, int n);
void		echo(char **str, int pos);
void		ft_echo(char **w_splited);
char		**ft_exec_buil_in(char **w_splited, char **envp);

int			ft_parsed_cd(char *w_splited);
char		**ft_chdir(char **envp, char *w_splited, char *pwd);
char		**ft_cd_one(char *w_splited, char **envp);
char		**ft_only_cd(char **envp);
char		**ft_cd(char **w_splited, char **envp);

char		*ft_pwd0(char **envp, char *pwd);
char		*ft_look(char **envp, char *pwd, char *find);
char		**ft_envp(char **envp, char *home_path, char *pwd);
char		**ft_change_envp1(char **envp, char *home, char *cur, char *old);

int			ft_splited_parse(char **w_splited);
void		ft_free_not_cwd(char *w_splited);
int			ft_parsed_cd2(char **w_splited);
char		**ft_cd_two(char **w_splited, char **envp);

int			ft_count_before(char *str, char c);
int			ft_check_build_in(char **w_splited);
void		ft_available_command(char **command, char **envp);
char		**ft_commands(char **w_splited, char **envp);
char		**ft_core(char **w_splited, char **env);

char		*ft_change(char *str, char *join, char *home_path);
void		ft_default2(int *var1, int *var2);
void		ft_default(int *i, int *flag1, int *flag2);
int			ft_quote_len(char **w_splited);
void		display_prompt(void);

char		**ft_pwd(char **envp, char *word, char *pwd);
void		ft_print_without_env(char *w_splited, char **envp);
void		ft_parse_env(char **w_splited, char **envp);
int			ft_env_check(char *w_splited);
char		**envp_create(char **env, char **envp);

char		**str_split1(char **w, char *s, char c, size_t i);
char		**ft_new_envp(char **envp, char *new);

void		ft_illegal_env_opt(char c);
void		ft_opt_require_arg(char c);
void		ft_parse_error(void);
void		ft_wrong_quantity_env(void);
void		ft_command_not_found(char *command);

void		ft_no_such_file_env_1(char *w_splited);
void		ft_permission_env(char *w_splited);
void		ft_no_such_file(char *w_splited);
void		ft_not_directory(char *w_splited);
void		ft_permission_denied(char *w_splited);

void		ft_not_set(char *word);
void		ft_not_in_cwd(char *w_splited);
void		ft_setenv_parse_error(char *w_splited);
void		ft_setenv_arg_error(void);
void		ft_setenv_overload(void);

void		ft_quote_error(int q);

char		*ft_read_dir(char *path, char **command, char **envp, char *c_p);
void		ft_exec_sys(char **path, char **command, char **envp);

void		free_3var(char *var1, char *var2, char *var3);
void		free_2var(char *home_path, char *cur_pwd);
void		free_2darray(char ***str);

char		**ft_word(char **word, char **env);
char		**parsed_word(char **word, char **env);
char		**str_split(char *s, char c);
char		**split_word(char *word);
char		**read_line(char **env, char **w_splited);

char		**ft_path(char **env);
int			ft_if_path(char **command);

char		**ft_edit_envp(char *new, char *w_splited, char **envp);
char		**ft_setenv_work(char *w_splited, char **envp);
int			ft_parse_name(char *name, char **envp);
int			ft_parse_setenv(char *w_splited);
char		**ft_setenv(char **w_splited, char **envp);

char		*ft_home(char **env, char *home_path);
char		*ft_check(char *sentence, char *word, char c);
char		*ft_environments(char *word, char **new, char **env);
char		*ft_dollar(char **env, char *word);
char		*ft_tilda(char **env, char *word);

void		ft_error_tcgetattr(void);
void		ft_error_termdef(char *termtype);
void		ft_error_term_access(void);
void		ft_error_noterm(void);
void		ft_error_isatty(void);

void		ft_error_tcsetattr(void);

char		**ft_new_envp1(char **new_envp, char **envp, char *w_splited);
char		**ft_unsetenv_work(char *w_splited, char **envp);
int			ft_parse_unset(char *w_splited);
char		**ft_unsetenv(char **w_splited, char **envp);

void		sighandler(int signum);

#endif
