#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char str[500];
    int i = 0;

    printf("Enter a C statement:\n");
    fgets(str, sizeof(str), stdin);

    while (str[i] != '\0')
    {
        // Ignore spaces, tabs and newlines
        if (isspace((unsigned char)str[i]))
        {
            i++;
        }

        // Ignore single-line comments
        else if (str[i] == '/' && str[i + 1] == '/')
        {
            break;
        }

        // Ignore multi-line comments (within the input line)
        else if (str[i] == '/' && str[i + 1] == '*')
        {
            i += 2;
            while (str[i] != '\0' &&
                   !(str[i] == '*' && str[i + 1] == '/'))
            {
                i++;
            }

            if (str[i] != '\0')
                i += 2;
        }

        // Identify identifiers
        else if (isalpha((unsigned char)str[i]) || str[i] == '_')
        {
            char token[100];
            int j = 0;

            while (isalnum((unsigned char)str[i]) ||
                   str[i] == '_')
            {
                if (j < 99)
                    token[j++] = str[i];

                i++;
            }

            token[j] = '\0';
            printf("%s - Identifier\n", token);
        }

        // Identify numeric constants
        else if (isdigit((unsigned char)str[i]))
        {
            char token[100];
            int j = 0;

            while (isdigit((unsigned char)str[i]) ||
                   str[i] == '.')
            {
                if (j < 99)
                    token[j++] = str[i];

                i++;
            }

            token[j] = '\0';
            printf("%s - Constant\n", token);
        }

        // Identify operators
        else if (strchr("+-*/%=<>!&|^", str[i]) != NULL)
        {
            if ((str[i] == '+' && str[i + 1] == '+') ||
                (str[i] == '-' && str[i + 1] == '-') ||
                (str[i] == '=' && str[i + 1] == '=') ||
                (str[i] == '!' && str[i + 1] == '=') ||
                (str[i] == '<' && str[i + 1] == '=') ||
                (str[i] == '>' && str[i + 1] == '=') ||
                (str[i] == '+' && str[i + 1] == '=') ||
                (str[i] == '-' && str[i + 1] == '=') ||
                (str[i] == '*' && str[i + 1] == '=') ||
                (str[i] == '/' && str[i + 1] == '=') ||
                (str[i] == '&' && str[i + 1] == '&') ||
                (str[i] == '|' && str[i + 1] == '|'))
            {
                printf("%c%c - Operator\n", str[i], str[i + 1]);
                i += 2;
            }
            else
            {
                printf("%c - Operator\n", str[i]);
                i++;
            }
        }

        // Ignore other symbols
        else
        {
            i++;
        }
    }

    return 0;
}
