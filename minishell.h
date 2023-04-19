
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	4096
# endif

# define READ 0
# define WRITE 1

# define SHE 0
# define DFL 1
# define IGN 2

int	g_exit_signal_code;

typedef struct s_cmd_info
{
	char				**cmd_and_av;
	int					ac;
	bool				ft_pipe_flag;
	bool				ft_dollar_flag;
	int					fd[2];
	int					ft_in_files;
	int					ft_out_files;
	char				*ft_command_path;
	struct s_cmd_info	*prev;
	struct s_cmd_info	*next;
}			t_cmd_info;

typedef struct s_env_info
{
	char				*env_key;
	char				*env_val;
	struct s_env_info	*next;
	struct s_env_info	*prev;
}			t_env_info;

void		print_checker(t_cmd_info *cmd, t_env_info *env);

void		*ft_free(void *ptr);
t_cmd_info	*ft_cmd_init(void);
void		ft_free_list(t_cmd_info *cmd);
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

int			is_exist_file(char *tmp_file_name);
void		exit_errno(char *str1, char *str2, int exit_code);
void		print_quote_err3(char *cmd, char *str1, char *str2);
void		print_err1(char *str);
void		print_err2(char *str1, char *str2);
void		print_err3(char *cmd, char *str1, char *str2);

void		set_signal(int sig_int, int sig_quit);

int			ft_str_isspace(char *str);
void		ft_main_init(int argc, char **argv);
void		ft_arg_check(t_cmd_info **cmd);

char		**ft_split_arg(char const *s, char c, int *argc);

char		*ft_join_ascii(char *s1, char s2);

void		ft_parse(char *input, t_cmd_info *cmd);

int			set_quotes(char str, int ch_quotes, t_cmd_info *cmd);
char		*ft_strjoin_free(char *s1, char *s2);
void		ft_del_argv(t_cmd_info *cmd, int *i);
void		ft_change_argv(t_cmd_info *cmd, char *new, int i);

void		ft_tokenize(t_cmd_info *cmd, t_env_info *head);

int			ft_env_init(t_env_info *cur, char **envp);
t_env_info	*new_env(char *key_value);
t_env_info	*compare_env_key(t_env_info *info_env, char *key);
char		*get_env_value(char *key_value);
char		*get_env_key(char *key_value);

char		*ft_getenv(t_env_info *info_env, char *key);
void		ft_setenv(t_env_info *env_head, char *key_value);

void		execute(t_cmd_info *cmd, t_env_info *info_env);
void		redirect(t_cmd_info *cmd);
int			heredoc(t_cmd_info *cmd);
void		close_unused_fd(t_cmd_info *cmd, pid_t pid);
int			check_valid_syntax(t_cmd_info *cmd);
void		wait_child(void);
int			is_need_fork(t_cmd_info *cmd);
void		restore_redirection_char(t_cmd_info *cmd);

char		*get_cmd_path(t_cmd_info *cmd, t_env_info *info_env);

int			io_file_open(t_cmd_info *cmd, t_env_info *info_env);
void		trim_cmd_argv(t_cmd_info *cmd, const char *set, int direction);

char		*get_tmp_file_name(void);
void		delete_tmp_file(void);
int			init_heredoc(t_cmd_info *cmd);
void		clear_cmd(t_cmd_info *cmd);

int			ft_open(char *fname, int oflag, int mode);
int			ft_close(int fd);
void		ft_dup2(int fd1, int fd2);
void		ft_pipe(int *fds);
pid_t		ft_fork(void);

int			mini_exit(t_cmd_info *cmd, t_env_info *env);
int			ft_is_valid_identifier(char *identifier);
int			printstderr(char *str);
int			cmd_and_av_cnt(char **cmd_and_av);
int			change_dir(char *path, t_env_info *env);
int			mini_cd(t_cmd_info *cmd, t_env_info *env);
int			mini_echo(t_cmd_info *cmd, t_env_info *env);
int			mini_env(t_cmd_info *cmd, t_env_info *env);
int			mini_export(t_cmd_info *cmd, t_env_info *env);
int			mini_pwd(t_cmd_info *cmd, t_env_info *env);
int			mini_unset(t_cmd_info *cmd, t_env_info *env);

#endif