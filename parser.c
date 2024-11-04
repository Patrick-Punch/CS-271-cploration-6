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
		char label[MAX_LABEL_LENGTH] = {0};
		while (fgets(line, sizeof(line), file))
		{
			strip(line);
			if (!*line){
				continue;
			}
			if (is_label(line))
			{
				inst_type = 'L';
				extract_label(line, label);
				strcpy(line, label);
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
	/* Function: is_Atype
	 * -------------
	 * Determine if the line is an A type assembly command
	 *
	 * line: pointer to the line to check
	 *
	 * returns: True if A type, false otherwise
	 */
	{
		if (line != NULL && line[0] == '@')
		{
			return true;
		}
		return false;
	}

	bool is_label(const char *line)
	/* Function: is_label
	 * -------------
	 * Determine if the line is an assembly label declaration
	 *
	 * line: pointer to the line to check
	 *
	 * returns: True if it is a label, false otherwise
	 */
	{
		size_t len = strlen(line);
		return (line[0] == '(' && line[len - 1] == ')');
	}

	bool is_Ctype(const char *line)
	/* Function: is_Ctype
	 * -------------
	 * Determine if the line is a C type assembly command
	 *
	 * line: pointer to the line to check
	 *
	 * returns: True if C type, false otherwise
	 */
	{
		if (!is_label(line) && !is_Atype(line))
		{
			return true;
		} else 
		{
			return false;
		}
	}

	char *extract_label(const char *line, char *label)
	/* Function: extract_label
	 * -------------
	 * Remove parenthesis from a label, to extract only the label that was declared
	 *
	 * line: pointer to the line to check
	 * 
	 * label: the label to be stripped
	 *
	 * returns: the label without the parenthesis
	 */
	{
		size_t len = strlen(line);
		strncpy(label, line + 1, len - 2);
		label[len - 2] = '\0';
		return label;
	}