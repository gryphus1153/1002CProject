/*
 * ICT1002 Assignment 2, 2018-19 Trimester 1.
 *
 * This file implements all of the functions required for drawing a worksheet
 * in the screen.
 *
 * The viewport_display() function is invoked by the main loop when it wants
 * to display the worksheet on the screen. The other functions are invoked by
 * commands such as CURSOR, PREC, etc, that modify the way in which the
 * worksheet is displayed. The display does NOT need to be updated immediately
 * after these functions have been invoked; the new settings will come into
 * effect the next time viewport_display() is invoked.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sheet1002.h"

static WORKSHEET *worksheet = NULL;

/*
 * Print the current viewing window to the screen.
 *
 * Input:
 *   term_cols - the width of the space in which to display the window, in characters
 *   term_rows - the height of the space in which to display the window, in characters
 */
void viewport_display(int term_cols, int term_rows)
{
	if (worksheet == NULL)
	{
		return;
	}
	else
	{
		int cursorCols = worksheet->currentCursor.column;
		int cursorRows = worksheet->currentCursor.row;
		int width = worksheet->cell_width;
		int cols, rows, i, j;

		int num_cols_in_vp = term_cols / width;
		char placeHolder[MAX_WORD] = "################################";
		char cellDisplay[MAX_WORD]; //This is created to store formatted strings
		bool cellWidth_overflow = false;

		//Setting the number of columns that are going to be in the viewport
		if (worksheet->cols - cursorCols > num_cols_in_vp)
		{
			cols = cursorCols + num_cols_in_vp;
		}
		else
		{
			cols = worksheet->cols;
		}

		//Setting the number of rows that are going to be in the viewport
		if (worksheet->rows - cursorRows > term_rows)
		{
			rows = cursorRows + term_rows;
		}
		else
		{
			rows = worksheet->rows;
		}

		//this whole chunk is printing
		printf("    ");
		for (int col = cursorCols; col < cols; col++)
		{
			printf("%-*c", width, col + 'A');
		}
		printf("\n");
		for (i = cursorRows; i < rows; i++)
		{
			printf("%-4d", i + 1); // row number
			for (j = cursorCols; j < cols; j++)
			{
				//convert ascii to float
				if (atof(worksheet->sheet[j][i]) != 0)
				{
					//format string to calculate length
					snprintf(cellDisplay, MAX_WORD, "%*.*f", width, worksheet->cell_prec, atof(worksheet->sheet[j][i]));
					if (strlen(cellDisplay) > width)
					{
						(j == cols) ? (printf("%.*s\n", width, placeHolder)) : (printf("%.*s", width, placeHolder));
					}
					else
					{
						(j == cols) ? (printf("%s\n", cellDisplay)) : (printf("%s", cellDisplay));
					}
				}
				else
				{ //else just print it out
					(strlen(worksheet->sheet[j][i]) > width) ? (cellWidth_overflow = true) : (cellWidth_overflow = false);
					if (cellWidth_overflow)
					{
						(j == cols) ? (printf("%.*s\n", width, placeHolder)) : (printf("%.*s", width, placeHolder));
					}
					else
					{
						(j == cols) ? (printf("%*s\n", width, worksheet->sheet[j][i])) : (printf("%*s", width, worksheet->sheet[j][i]));
					}
				}
			}
			printf("\n");
		}
	}
}

/*
 * Get the precisiion with which floating-point numbers will be displayed.
 *
 * Returns:
 *   the number of decimal places that will be shown
 */
int viewport_get_cellprec(void)
{
	return worksheet->cell_prec;
}

/*
 * Set the precision with which floating-point numbers will be displayed.
 *
 * Input:
 *   prec - the number of decimal places to show
 */
void viewport_set_cellprec(int prec)
{
	worksheet->cell_prec = prec;
}

/*
 * Set the width in which the cells will be displayed.
 *
 * Input:
 *   width - the number of characters in each cell to be displayed
 */
void viewport_set_cellwidth(int width)
{
	worksheet->cell_width = width;
}

/*
 * Set the position of the cursor.
 *
 * Input:
 *   col - the column number
 *   row - the row number
 */
void viewport_set_cursor(int col, int row)
{
	worksheet->currentCursor.column = col;
	worksheet->currentCursor.row = row;
}
/*
 * Get a pointer to the worksheet currently being displayed.
 *
 * Returns:
 *   a pointer to the WORKSHEET structure currently displayed
 *   NULL, if there is no worksheet displayed
 */
WORKSHEET *viewport_get_worksheet(void)
{
	if (worksheet)
	{
		return worksheet;
	}
	else
	{
		return NULL;
	}
}

/*
 * Set the worksheet to be displayed.
 *
 * Input:
 *   ws - a pointer to the worksheet to be displayed
 */
void viewport_set_worksheet(WORKSHEET *ws)
{
	worksheet = ws;
}