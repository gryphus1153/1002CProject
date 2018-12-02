/*
 * ICT1002 Assignment 2, 2018-19 Trimester 1.
 *
 * This file contains one function corresponding to each command understood
 * by the spreadsheet. Each function accepts zero, one or two input arguments
 * (arg1 and/or arg2) as documented in the assignment specification, and a
 * pointer to buffer (output) into which the results of the command should be
 * placed. The contents of the output buffer will be displayed on the screen
 * at the end of the command loop (make it empty if you don't want to print
 * anything).
 *
 * The contents of arg1 and arg2 are guaranteed to be no more than MAX_INPUT
 * characters in length. The contents of the output buffer should not exceed
 * MAX_OUTPUT characters (including the terminating null).
 */

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sheet1002.h"

/* student's global variables */
int AVERAGE = 0;

/*
 * Execute a command.
 *
 * Input:
 *   command - the name of the command
 *   arg1 - the first argument (may be NULL)
 *   arg2 - the second argument (may be NULL)
 *   output - a buffer into which the output of the command is to be placed (must be at least MAX_OUTPUT characters long)
 *
 * Returns:
 *   0, if the program should continue
 *   1, if the command indicates that the interpreter should exit
 */
int do_command(const char *command, const char *arg1, const char *arg2, char *output)
{

	int done = 0; /* return value */

	if (command == NULL || strlen(command) == 0)
	{
		/* blank line; do nothing and return */
		return 0;
	}
	//if (arg1 == NULL) { /* validation for first parameter */
	//	snprintf(output, MAX_OUTPUT, "First parameter cannot be empty.");
	//	return 0;
	//}

	/* determine which command was given and execute the appropriate function */
	if (compare_token(command, "avg") == 0)
		do_avg(arg1, arg2, output);
	else if (compare_token(command, "cursor") == 0)
		do_cursor(arg1, output);
	else if (compare_token(command, "load") == 0)
		do_load(arg1, output);
	else if (compare_token(command, "new") == 0)
		do_new(arg1, arg2, output);
	else if (compare_token(command, "prec") == 0)
		do_prec(arg1, output);
	else if (compare_token(command, "save") == 0)
		do_save(arg1, output);
	else if (compare_token(command, "set") == 0)
		do_set(arg1, arg2, output);
	else if (compare_token(command, "sum") == 0)
		do_sum(arg1, arg2, output);
	else if (compare_token(command, "width") == 0)
		do_width(arg1, output);
	else if (compare_token(command, "exit") == 0)
		done = 1;
	else
		snprintf(output, MAX_OUTPUT, "Unrecognised command: %s.", command);

	return done;
}

/*
 * AVG command.
 *
 * Input:
 *   arg1 - one corner of the rectangle to be averaged
 *   arg2 - the opposite corner of the rectangle to be averaged
 */
void do_avg(const char *arg1, const char *arg2, char *output)
{
	/* wrong input validation */
	if (arg1 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "First parameter cannot be empty.");
		return;
	}
	if (arg2 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "Second parameter cannot be empty.");
		return;
	}
	int *arr1 = getGrid(arg1);
	if (arr1 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "First Argument was Invalid.");
		return;
	}
	int botCol = arr1[0];
	int topCol = arr1[0];
	int botRow = arr1[1];
	int topRow = arr1[1];
	int *arr2 = getGrid(arg2);
	if (arr2 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "Second Argument was Invalid.");
		return;
	}
	if (arr2[0] < botCol)
	{
		botCol = arr2[0];
	}
	if (arr2[0] > topCol)
	{
		topCol = arr2[0];
	}
	if (arr2[1] < botRow)
	{
		botRow = arr2[1];
	}
	if (arr2[1] > topRow)
	{
		topRow = arr2[1];
	}
	float sum = 0;
	int num = 0;
	for (int r = botRow; r <= topRow; r++)
	{
		for (int c = botCol; c <= topCol; c++)
		{
			if (checkInt(ws_curr.sheet[c][r]))
			{ /* check if char array contain all int */
				//printf("|ENTER [%d][%d] = '%s'|\n", col, row, ws_curr.sheet[col][row]);
				sum += atof(ws_curr.sheet[c][r]); /* convert char array to int and add to sum */
				num++;
			}
		}
	}
	snprintf(output, MAX_OUTPUT, "Average of %s to %s is %f.", arg1, arg2, sum / num);

	//if (strlen(arg1) == 1 || strlen(arg2) == 1 ||
	//	!isalpha(arg1[0]) || !isalpha(arg2[0]) || /* check for alphabet */
	//	!checkInt(arg1 + 1) || !checkInt(arg2 + 1))
	//{ /* check for int */
	//	snprintf(output, MAX_OUTPUT, "Invalid cell value.");
	//	return;
	//}
	//
	///* seperate cell value into alphabet and num */
	//int alpha1 = toupper(arg1[0]) - NUM_ALPHA_DIFF, alpha2 = toupper(arg2[0]) - NUM_ALPHA_DIFF, /* change alphabet to int */
	//	num1 = atoi(&arg1[1]), num2 = atoi(&arg2[1]);

	/* out of range validation */
	//if (alpha1 > ws_curr.cols - 1 || alpha2 > ws_curr.cols - 1 ||
	//num1 > ws_curr.rows || num2 > ws_curr.rows ||
	//num1 == 0 || num2 == 0)
	//{ /* check for 0th row (eg. A0) */
	//	snprintf(output, MAX_OUTPUT, "cell value out of range.");
	//	return;
	//}
}

/*
 * CURSOR command.
 *
 * Input:
 *   arg1 - the identifier of the cell to which to move the cursor
 */
void do_cursor(const char *arg1, char *output)
{
	if (arg1 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "First parameter cannot be empty");
		return;
	}
	int *arr1;
	arr1 = getGrid(arg1);
	if (arr1 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "Invalid Cursor Position.");
	}
	else
	{
		currentCursor.column = arr1[0];
		currentCursor.row = arr1[1];
		snprintf(output, MAX_OUTPUT, "Cursor Set.");
	}
}

/*
 * LOAD command.
 *
 * Input:
 *   arg1 - the filename
 */
void do_load(const char *arg1, char *output)
{
	//check if there is no filename
	if (arg1 == 0x0)
	{
		snprintf(output, MAX_OUTPUT, "No filename entered.");
		return;
	}

	//open csv file
	FILE *f = fopen(arg1, "rb");

	//return if the program could not open the csv file
	if (f == NULL)
	{
		snprintf(output, MAX_OUTPUT, "Unable to load file. Ensure file exists and name does not contain spaces.");
		return;
	}

	//Check the maximum number of rows and columns
	int rows = 0, cols = 0;
	char ch[MAX_WORD * MAX_COLS + 1];
	//fgets(f, MAX_WORD*MAX_COLS + 1, f);
	//fscanf(f, "%s", ch);
	while (fgets(ch, MAX_WORD * MAX_COLS + 1, f) != NULL)
	{
		rows++;
		char *pch;
		int col = 0;

		//Check all rows for maximum number of columns, delimited by comma
		pch = strchr(ch, ',');
		while (pch != NULL)
		{
			col++;
			pch = strchr(pch + 1, ',');
		}
		col++;
		if (cols < col)
			cols = col;
		//fscanf(f, "%s", ch);
	}
	if (cols > MAX_COLS)
	{
		snprintf(output, MAX_OUTPUT, "File has too many columns");
		return;
	}
	//create a new worksheet
	ws_new(cols, rows);

	//to load data and write into sheet
	rewind(f); //re-initialize the file pointer
	for (int r = 0; r < rows; r++)
	{
		fgets(ch, MAX_WORD * MAX_COLS + 1, f);
		char *pos;
		if ((pos=strchr(ch, '\n')) != NULL)
    	*pos = '\0';
		if ((pos=strchr(ch, '\r')) != NULL)
    	*pos = '\0';
		const char tok[] = ",";
		char *tmp = (char *)ch;
		char *teee = (char *)tmp;
		size_t count;
		for (count = 0; tmp[count]; tmp[count] == tok[0] ? count++ : *tmp++)
		{
			//Empty loop body.
		}
		tmp = (char *)ch;
		//copy each word into cell, delimited by comma
		for (size_t i = 0, l = 0; i < count + 1; i++)
		{
			l = strcspn(tmp, tok);
			teee = (char *)tmp;
			teee[l] = '\0';
			if (strchr(teee, ' '))
			{
				strcpy(teee, "\0");
			}
			strcpy(ws_curr.sheet[i][r], teee);

			tmp += sizeof(char) * (l + 1);
		}
	}
	//close csv file
	fclose(f);

	//Output: Sheet Loaded
	snprintf(output, MAX_OUTPUT, "Sheet Loaded.");

	return;
}

/*
 * NEW command.
 *
 * Input:
 *   arg1 - the number of columns
 *   arg2 - the number of rows
 */
void do_new(const char *arg1, const char *arg2, char *output)
{
	if (arg1 == 0x0 || arg2 == 0x0)
	{
		snprintf(output, MAX_OUTPUT, "A parameter was empty");
		return;
	}

	char *chk;
	int cols = strtol(arg1, &chk, 10);
	if (strcmp(chk, "") != 0)
	{
		snprintf(output, MAX_OUTPUT, "First parameter is invalid");
		return;
	}

	int rows = strtol(arg2, &chk, 10);
	if (strcmp(chk, "") != 0)
	{
		snprintf(output, MAX_OUTPUT, "Second parameter is invalid");
		return;
	}
	if (ws_new(cols, rows) == NULL)
		snprintf(output, MAX_OUTPUT, "Could not allocate memory to sheet");
	else
		snprintf(output, MAX_OUTPUT, "New worksheet created with %s columns and %s rows.", arg1, arg2); /* output message */
}

/*
 * PREC command.
 *
 * Input:
 *   arg1 - the number of decimal places to show
 */
void do_prec(const char *arg1, char *output)
{
	if (arg1 != NULL && checkInt(arg1) == 1)
	{
		char *chk;
		int prec = strtol(arg1, &chk, 10);
		if (prec >= 0)
		{
			viewport_set_cellprec(prec);
			snprintf(output, MAX_OUTPUT, "Cell Precision was set to %s", arg1);
		}
		else
		{
			snprintf(output, MAX_OUTPUT, "Precision cannot be be less than 0");
		}
	}
	else
	{
		snprintf(output, MAX_OUTPUT, "Input was Invalid");
	}
}

/*
 * SAVE command.
 *
 * Input:
 *  arg1 - the filename
 */
void do_save(const char *arg1, char *output)
{
	//check if there is no filename
	if (arg1 == 0x0)
	{
		snprintf(output, MAX_OUTPUT, "No filename entered.");
		return;
	}

	//create a csv file
	FILE *f = fopen(arg1, "wb+");
	//return if the program could not create the csv file
	if (f == NULL)
	{
		snprintf(output, MAX_OUTPUT, "Unable to save file. Ensure file is not opened in another program.");
		return;
	}

	//check the current number of rows and columns
	int rows = ws_curr.rows;
	int cols = ws_curr.cols;

	//write data into the csv file
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			fprintf(f, ws_curr.sheet[c][r]);
			//insert comma as long as it is not the last column
			if (c != cols - 1)
				fprintf(f, ",");
		}
		//insert a newline as long as it is not the last row
		if (r != rows - 1)
			fprintf(f, "\n");
	}

	//close csv file
	fclose(f);

	//output: File Saved.
	snprintf(output, MAX_OUTPUT, "File Saved.");

	return;
}

/*
 * SET command.
 *
 * Input:
 *   arg1 - the cell identifier
 *   arg2 - the value for the cell (NULL to make the cell blank)
 */
void do_set(const char *arg1, const char *arg2, char *output)
{
	/* wrong input validation */
	if (arg1 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "First parameter cannot be empty.");
		return;
	}
	//if (arg2 == NULL)
	//{
	//	snprintf(output, MAX_OUTPUT, "Second parameter cannot be empty.");
	//	return;
	//}
	if (strlen(arg1) == 1 || !isalpha(arg1[0]) || !checkInt(arg1 + 1))
	{ /* check for cell length, alphabet and integer */
		snprintf(output, MAX_OUTPUT, "Invalid cell value.");
		return;
	}

	/* out of range validation */
	int alpha1 = toupper(arg1[0]) - NUM_ALPHA_DIFF, num1 = atoi(&arg1[1]); /* seperate cell value into alphabet and num */
	if (alpha1 > ws_curr.cols - 1 || num1 > ws_curr.rows || num1 == 0)
	{
		snprintf(output, MAX_OUTPUT, "Cell value out of range.");
		return;
	}

	int *arr1;
	arr1 = getGrid(arg1);
	if (arg2 == NULL)
	{
		strcpy(ws_curr.sheet[arr1[0]][arr1[1]], ""); /* erase */
		snprintf(output, MAX_OUTPUT, "%s cell is erased.", arg1);
		return;
	}
	if (arr1 == NULL || arg2 == 0x0)
	{
		snprintf(output, MAX_OUTPUT, "Input was invalid");
		return;
	}
	else
	{
		strcpy(ws_curr.sheet[arr1[0]][arr1[1]], arg2);
	}

	snprintf(output, MAX_OUTPUT, "Cell %s set to %s.", arg1, arg2); /* output message */
}

/*
 * SUM command.
 *
 * Input:
 *   arg1 - one corner of the rectangle to be summed
 *   arg2 - the opposite corner of the rectangle to be summed
 */
void do_sum(const char *arg1, const char *arg2, char *output)
{
	/* wrong input validation */
	if (arg2 == NULL)
	{
		snprintf(output, MAX_OUTPUT, "Second parameter cannot be empty.");
		return;
	}
	if (strlen(arg1) == 1 || strlen(arg2) == 1 ||
		!isalpha(arg1[0]) || !isalpha(arg2[0]) || /* check for alphabet */
		!checkInt(arg1 + 1) || !checkInt(arg2 + 1))
	{ /* check for int */
		snprintf(output, MAX_OUTPUT, "Invalid cell value.");
		return;
	}

	/* seperate cell value into alphabet and num */
	int alpha1 = toupper(arg1[0]) - NUM_ALPHA_DIFF, alpha2 = toupper(arg2[0]) - NUM_ALPHA_DIFF, /* change alphabet to int */
		num1 = atoi(&arg1[1]), num2 = atoi(&arg2[1]);

	/* out of range validation */
	if (alpha1 > ws_curr.cols - 1 || alpha2 > ws_curr.cols - 1 ||
		num1 > ws_curr.rows || num2 > ws_curr.rows ||
		num1 <= 0 || num2 <= 0)
	{ /* check for 0th row (eg. A0) */
		snprintf(output, MAX_OUTPUT, "Cell value out of range.");
		return;
	}

	/* sort alphabet & num from smallest to biggest */
	int colStart = alpha1, colEnd = alpha2, rowStart = num1, rowEnd = num2;
	if (alpha2 < alpha1)
	{
		colStart = alpha2;
		colEnd = alpha1;
	}
	if (num2 < num1)
	{
		rowStart = num2;
		rowEnd = num1;
	}

	/* sum all int cells up */
	float sum = 0;
	int num = 0;
	for (int col = colStart; col < colEnd + 1; col++)
	{
		for (int row = rowStart - 1; row < (rowEnd - 1) + 1; row++)
		{ /* num-1 because array start from 0 */
			if (checkInt(ws_curr.sheet[col][row]))
			{ /* check if char array contain all int */
				//printf("|ENTER [%d][%d] = '%s'|\n", col, row, ws_curr.sheet[col][row]);
				sum += atof(ws_curr.sheet[col][row]); /* convert char array to int and add to sum */
				num++;
			}
		}
	}

	/* calculation for AVG command */
	if (num == 0) /* anything divide by 0 will give you error */
		num = 1;
	AVERAGE = sum / num; /* calculation for AVG command */

	snprintf(output, MAX_OUTPUT, "Sum of %s to %s is %f.", arg1, arg2, sum); /* output message */
}

/*
 * WIDTH command.
 *
 * Input:
 *   arg1 - the number of characters for each column
 */
void do_width(const char *arg1, char *output)
{
	if (arg1 != NULL && checkInt(arg1) == 1)
	{
		char *chk;
		int width = strtol(arg1, &chk, 10);

		if (width > 0)
		{
			viewport_set_cellwidth(width);
			snprintf(output, MAX_OUTPUT, "Column width set to %s", arg1);
		}
		else
		{
			snprintf(output, MAX_OUTPUT, "Width cannot be be less than 1");
		}
	}
	else
	{
		snprintf(output, MAX_OUTPUT, "Invalid Width");
	}
}

/*
 * GET GRID
 * Input:
 * 	arg - the grid in format (Letter)(Number) e.g. A5, Z15
 * Output:
 *  arr - an array of {column, row} OR NULL if error
 */
int *getGrid(const char *arg)
{
	//check if its not in the (letter)(number format)
	if (!(strlen(arg) >= 2 && isalpha(arg[0])))
	{
		return NULL;
	}

	int col = (int)toupper(arg[0]) - 65;//get the column as int
	arg++;
	char *chk;
	int row = strtol(arg, &chk, 10);//convert the number to row

	if (row == 0x0 || *chk != 0x0 || col > ws_curr.cols || row > ws_curr.rows || col < 0 || row < 0)//check if out of range or invalid
		return NULL;
	else
	{
		static int arr[2];
		arr[0] = col;
		arr[1] = row - 1;
		return arr;
	}
}

/*
 * Check if char array contain all int.
 * Input:
 *   arg - cell char array.
 *
 * Returns:
 *   int - if char array not all int return 0, else return 1.
*/
int checkInt(const char *arg)
{
	//int len = strlen(arg);
	//if (len == 0) /* if nothing inside cell, return 0 */
	//	return 0;
	//
	//int checkDot = 0; /* false */
	//for (int i = 0; i < len; i++)
	//{
	//	if (i > 0 && arg[i] == '.' && checkDot == 0) /* at least a digit before '.' */
	//		checkDot = 1;							 /* true */
	//	else if (!isdigit(arg[i]))					 /* if cell consist of a alphabet, return 0*/
	//		return 0;
	//}
	//return 1; /* char array contain all int, return 1 */
	char *chk;
	float num = strtof(arg, &chk);
	if (strcmp(chk, "") != 0 || (num == 0.0 && strlen(arg) == 0))//Check for any leftover after strtof, (prevent 0 from being counted as invalid)
	{
		return 0;
	}
	else
		return 1;
}
