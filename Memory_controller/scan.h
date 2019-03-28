//---------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
//---------------------------------------------------------------------------*/
const char *scan_file_name        = "memory_scan.txt";
const char *scan_file_memory_name = "memory_log.txt";
const int   MAX_LINE_LENGTH       = 150;
//---------------------------------------------------------------------------*/
void memory_scan (const size_t step)
{
  printf (" # START scanning...\n");

  FILE *out = fopen (scan_file_name,        "w");
  FILE *in  = fopen (scan_file_memory_name, "r");

  if (out == NULL)  fprintf (out, " ! ERROR Log file was not found\n");
  else              fprintf (out, " ! Started using %d\n", step);

  char    s[MAX_LINE_LENGTH] = {0};
  char skip[MAX_LINE_LENGTH] = {0};
  char pointers[step]{0};

  int  pos = 0;
  int  num = 0;
  char c   = 0;
  int line = 1;
  fseek (in, 0, SEEK_SET);

  while (fgets (s, MAX_LINE_LENGTH, in) != NULL)
  {
    sscanf (s, "%s %d %c", &skip, &num, &c);
    pos = num%step;

    if (c == 'a') pointers[pos] += 1;
    if (c == 'f') pointers[pos] -= 1;

    if (pointers[pos] > 1) fprintf (out, " ! extra alloc %d\n", line);
    if (pointers[pos] < 0) fprintf (out, " ! extra free  %d\n", line);

    ++line;
  }

  for (int i = 0; i < step; i++)
  {
    if (pointers[i] < 0) fprintf (out, " ! lack of alloc %d\n", i);
    if (pointers[i] > 0) fprintf (out, " ! lack of free  %d\n", i);
  }
  fprintf (out, " ! Ended\n");

  fclose (in);
  fclose (out);

  printf (" # ENDED scanning.\n");
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
