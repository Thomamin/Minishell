/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:24:30 by hyeonjo           #+#    #+#             */
/*   Updated: 2023/05/03 13:35:12 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <term.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/_types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# define READ 0
# define WRITE 1

# define READLINE 0
# define DEFAULT 1
# define IGNORE 2

int	g_exit_signal_code;

typedef struct s_cmd_info
{
	char				**cmd_and_av;
	int					ac;
	bool				pipe_flag;
	bool				dollar_flag;
	int					fd[2];
	int					in_fd;
	int					out_fd;
	char				*in_file_name;
	char				*command_path;
	struct s_cmd_info	*prev;
	struct s_cmd_info	*next;
}						t_cmd_info;

typedef struct s_env_info
{
	char				*env_key;
	char				*env_val;
	struct s_env_info	*next;
	struct s_env_info	*prev;
}						t_env_info;

typedef struct s_chs
{
	int	quote;
	int	pipe;
}		t_chs;

void		print_checker(t_cmd_info *cmd, t_env_info *env);

void		*ft_free(void *ptr);
t_cmd_info	*initialize_cmd(void);
void		free_list(t_cmd_info *cmd);
t_env_info	*compare_env_key(t_env_info *info_env, char *key);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t destsize);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *s, int fd);
int			ft_isspace(char c);

char		*ft_strchr(const char *s, int c);

int			ft_open(char *fname, int oflag, int mode);
int			ft_close(int fd);
void		ft_dup2(int fd1, int fd2);
void		ft_pipe(int *fds);
pid_t		ft_fork(void);
void		*ft_malloc(size_t size, size_t n);
int			ft_write(int fd, const void *buf, size_t byte);
void		ft_execve(const char *file, char *const *argv, char *const *envp);
char		*ft_getcwd(char *buf, size_t size);

char		**get_envp(t_env_info *head);

int			is_exist_file(char *tmp_file_name);

void		print_quote_err3(char *cmd, char *str1, char *str2);
void		print_err1(char *str);
void		print_err2(char *str1, char *str2);
void		print_err3(char *cmd, char *str1, char *str2);
void		print_err_with_errno(char *str1, char *str2, int exit_code);

void		exit_errno(char *str1, char *str2, int exit_code);

void		set_signal(int sig_int, int sig_quit);

int			ft_str_isspace(char *str);
void		check_argument(t_cmd_info **cmd);

char		**ft_split_arg(char const *s, char c, int *argc);

char		*ft_join_ascii(char *s1, char s2);

void		parse(char *input, t_cmd_info *cmd);

int			set_quotes(char str, int ch_quotes, t_cmd_info *cmd);
char		*ft_strjoin_free(char *s1, char *s2);
void		ft_del_argv(t_cmd_info *cmd, int *i);
void		ft_change_argv(t_cmd_info *cmd, char *new, int i);

void		tokenize(t_cmd_info *cmd, t_env_info *head);

int			initialize_env(t_env_info *cur, char **envp);
t_env_info	*new_env(char *key_value);
t_env_info	*compare_env_key(t_env_info *info_env, char *key);
char		*get_env_value(char *key_value);
char		*get_env_key(char *key_value);

char		*ft_getenv(t_env_info *info_env, char *key);

void		execute(t_cmd_info *cmd, t_env_info *info_env);
void		redirect(t_cmd_info *cmd);
int			heredoc(t_cmd_info *cmd, t_env_info *env);

int			check_heredoc(t_cmd_info *cmd);
void		input_heredoc(t_cmd_info *cmd, int index_lim, t_env_info *env);
int			wait_heredoc(pid_t pid);
int			do_fork_heredoc(t_cmd_info *cmd, int index_lim, t_env_info *env);

char		*parse_dollar_sign(char *src, t_env_info *env);

void		close_unused_fd(t_cmd_info *cmd, pid_t pid);
int			check_valid_syntax(t_cmd_info *cmd);
void		wait_child(void);
int			is_need_fork(t_cmd_info *cmd);
void		restore_redirection_char(t_cmd_info *cmd);

char		*get_cmd_path(t_cmd_info *cmd, t_env_info *info_env);

int			io_file_open(t_cmd_info *cmd, t_env_info *info_env);
void		trim_cmd_argv(t_cmd_info *cmd, const char *set, int direction);

char		*get_tmp_file_name(void);
void		delete_tmp_file(char *file_name);
int			initialize_heredoc(t_cmd_info *cmd, t_env_info *env);
void		clear_cmd(t_cmd_info *cmd);

int			ft_open(char *fname, int oflag, int mode);
int			ft_close(int fd);
void		ft_dup2(int fd1, int fd2);
void		ft_pipe(int *fds);
pid_t		ft_fork(void);

void		set_env(t_env_info *env, char *key_value);
int			mini_exit(t_cmd_info *cmd, t_env_info *env);
int			ft_is_valid_identifier(char *identifier);
int			printstderr(char *str);
int			cmd_and_av_cnt(char **cmd_and_av);
int			mini_cd(t_cmd_info *cmd, t_env_info *env);
int			mini_echo(t_cmd_info *cmd, t_env_info *env);
int			mini_env(t_cmd_info *cmd, t_env_info *env);
int			mini_export(t_cmd_info *cmd, t_env_info *env);
int			mini_pwd(t_cmd_info *cmd, t_env_info *env);
int			mini_unset(t_cmd_info *cmd, t_env_info *env);

int			mini_print_sorted_ev(t_env_info *env);

#endif
