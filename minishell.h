#ifndef MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <assert.h>
# include <sys/param.h>
# define MINISHELL_H
# ifndef EXEC
#  define EXEC "\
\
#!/bin/bash\n \
process_command(){\n \
regex='(\\|*[^|]*cd_script.sh[^|]*)||([^|]*cd_script.sh[^|]*\\|*)||\
(\\|*[^|]*export_script.sh[^|]*)||([^|]*export_script.sh[^|]*\\|*)||\
(\\|*[^|]*unset_script.sh[^|]*)||([^|]*unset_script.sh[^|]*\\|*)'\n\
reg_pipes='([^|]+\\|)||(\\|[^|]+)||([^|]+\\|[^|]+)' \n \
num=$(echo \"${1}\" | grep -Eo $reg_pipes | wc -l) \n \
matches=$(echo \"${1}\" | grep -Eo $regex) \n \
final_word=$1 \n \
if [[ $num -gt 0 ]] \n \
then \n \
    while IFS= read -r match; do \n \
        final_word=${final_word//\"$match\"/} \n \
    done <<< \"$matches\" \n \
fi \n \
  command=\"$final_word\"\n \
  eval \"$command\"\n \
  exit $?\n \
}\n \
get_here_doc(){\n \
NL=$'\\n'\n \
while read -p \">\" var; do\n \
    if [ \"$var\" == \"$2\" ];then\n \
        break;\n \
    fi\n \
    str=\"${str}${var}\"$NL\n \
done\n \
echo \"$str\" | sed '$ d' > $1;\n \
}\n \
end_of_file_regex(){\n \
  echo \"${1}\" | grep -Eo '<+ *[A-Za-z]+' | grep -Eo '[A-Za-z]+' | tail -1\n \
}\n \
get_last_redirection(){\n \
  echo \"${1}\" | grep -Eo '<+ *[A-Za-z]+' | tail -1\n \
}\n \
command_regex_double_redirect(){\n \
  final_word=\"${1}\"\n \
  matches=$(echo \"${1}\" | grep -Eo '<+ *[A-Za-z]+')\n \
  while IFS= read -r match; do\n \
      final_word=${final_word//\"$match\"/}\n \
  done <<< \"$matches\"\n \
  echo \"$final_word\"\n \
}\n \
parse_and_execute() {\n \
  local input=\"$1\"\n \
  final_command=\"\"\n \
  NL=$'\\n'\n \
  IFS='|' read -ra commands <<< \"$input\"\n \
  for ((i=0; i<${#commands[@]}; i++)); do\n \
    command=\"${commands[i]}\"\n \
    command=$(echo \"$command\")\n \
    if [[ $i -eq 0 ]]; then\n \
      if [[ \"$command\" == *\"<\"* ]]; then\n \
        redirect_type=$(get_last_redirection \"$command\")\n \
        if [[ \"$redirect_type\" == *\"<<\"* ]]; then\n \
          doc_file=\"$(mktemp)\"\n \
          doc_file_buffer=\"$doc_file\"'|'\n \
          here_doc_val=\"$(get_here_doc \"$doc_file\" \
\"$(end_of_file_regex \"$command\")\")\"\n \
          final_command=\"\"$(command_regex_double_redirect \
\"$command\")\" < $doc_file\"\n \
        else\n \
          final_command=\"$command\"\n \
        fi\n \
      else\n \
        final_command=\"$command\"\n \
      fi\n \
    else\n \
      if [[ \"$command\" == *\"<\"* ]]; then\n \
        redirect_type=$(get_last_redirection \"$command\")\n \
        if [[ \"$redirect_type\" == *\"<<\"* ]]; then\n \
          doc_file=\"$(mktemp)\"\n \
          doc_file_buffer=\"${doc_file_buffer}${doc_file}\"'|'\n \
          here_doc_val=\"$(get_here_doc \"$doc_file\" \
\"$(end_of_file_regex \"$command\")\")\"\n \
          com=\"$(command_regex_double_redirect \"$command\")\"\n \
          final_command=\"${final_command} | $com < $doc_file\"\n \
        else\n \
          final_command=\"$final_command | $command\"\n \
        fi\n \
      else\n \
        final_command=\"$final_command | $command\"\n \
      fi\n \
    fi\n \
  done\n \
  process_command \"$final_command\"\n \
  IFS='|' read -ra docs <<< \"$doc_file_buffer\"\n \
  for ((i=0; i<${#docs[@]}; i++)); do\n \
    doc=\"${docs[i]}\"\n \
    rm -rf $doc\n \
  done\n \
}\n \
comm=\"${1/;/\"';'\"}\"\n \
parse_and_execute \"$comm\""
# endif

# ifndef TIMESTAMP
#  define TIMESTAMP "date +%s%N | tr -d \'\n\'"
# endif

//void	cargar_envs(int signals);
//char	**our_envs(char *file, char **init_envs);

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void	only_exec_permissions(char **env, char *filename);
void	create_export_script(char **env);
void	create_unset_script(char **env);
void	create_systax_file(char **env);
void	create_final_file(char **env, char *filename, char *file_content);
void	execute(char **env, char *full_command_line);
void	create_unique_name(char **env);
char	*unique_file_name(void);
char	*export_script(void);
char	*unset_script(void);
char	*cd_script(void);
char	*pwd_script(void);
char	**our_envs(char *file, char **init_envs);
void	cargar_envs(int signal);
void	delete_file(char **env, char *filename);
char	*ft_strjoin(char const *s1, char const *s2);
char	*builtin_replace(char *comm1);
void	get_cd_or_pwd(int signal);
void	create_cd_script(char **env);
void	create_pwd_script(char **env);
void	handle_cd(int *count_status);
int		*status_exit(int new_status);
char	*ft_itoa(int n);
char	*parse_line(char *line);
int		check_exit(char *line);
int		check_single_quote(char *line);
char	*check_dollar(char *line);
char	*replace2(char *comm, int pos, char *word, char *path);
char	*check_command(char *comm, char *word, int pos);
void	default_sig(int sig);
void	ctrl_c_handler(int sig);
void	free_array(char **input, int i);
char	**create_array(char *str);
char	**list_commands(void);
char	*command_path(int num);
void	ft_putstrfd(int fd, char *s);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
#endif
