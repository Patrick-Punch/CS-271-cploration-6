/****************************************
 * C-ploration 6 for CS 271
 * 
 * Patrick Punch
 * Fall 2024
 * 
 ****************************************/
#include "parser.h"

	/* Function: strip
	 * -------------
	 * remove whitespace and comments from a line
	 *
	 * s: the char* string to strip
	 *
	 * returns: the stripped char* string
	 */
	char *strip(char *s)
	{
		int i = 0;
		char s_new[strlen(s) + 1];
		for (char *s2 = s; *s2; s2++){
			if (*s2 == '/' && *(s2 + 1) == '/'){
				break;
			}
			else if (!isspace(*s2)){
				s_new[i++] = *s2;
			}
		}
		s_new[i] = '\0';
		strcpy(s, s_new); 
		return s;
	}

	/* Function: parse
	 * -------------
	 * iterate each line in the file and strip whitespace and comments.
	 *
	 * file: pointer to FILE to parse
	 *
	 * returns: nothing
	 */
	void parse(FILE * file)
	{
		char inst_type;
		char line[MAX_LINE_LENGTH] = {0};
		while (fgets(line, sizeof(line), file))
		{
			strip(line);
			if (!*line){
				continue;
			}
			if (is_label(line))
			{
				inst_type = 'L';
			}
			else if (is_Atype(line))
			{
				inst_type = 'A';
			}
			else if (is_Ctype(line))
			{
				inst_type = 'C';
			}
			else
			{
				inst_type = ' ';
			}
			printf("%c  %s\n", inst_type, line);
		}
	}

	bool is_Atype(const char *line)
	{
		if (line != NULL && line[0] == '@')
		{
			return true;
		}
		return false;
	}

	bool is_label(const char *line)
	{
		size_t len = strlen(line);
		return (line[0] == '(' && line[len - 1] == ')');
	}

	bool is_Ctype(const char *line)
	{
		if (!is_label(line) && !is_Atype(line))
		{
			return true;
		} else 
		{
			return false;
		}
	}