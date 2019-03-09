//*/---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
//*/---------------------------------------------------------------------------
const char *scan_file_name        = "memory_scan.txt";
const char *scan_file_memory_name = "memory_log.txt";
const int   step                  = 1000;
const int   max_line_length       = 40;
//*/---------------------------------------------------------------------------
void memory_scan ()
{
  FILE *in  = fopen (scan_file_memory_name, "r");
  FILE *out = fopen (scan_file_name,   "w");

  char *s = (char *)malloc (max_line_length);
  char pointers[step]{0};

  int  pos = 0;
  int  num = 0;
  char c   = 0;
  int line = 1;
  fseek (in, 0, SEEK_SET);

  while (fgets (s, max_line_length, in) != NULL)
  {
    sscanf (s, "%d %c", &num, &c);
    pos = num%step;
    if (c == 'a') pointers[pos] += 1;
    if (c == 'f') pointers[pos] -= 1;

    if (pointers[pos] > 1) fprintf (out, "extra alloc %d\n", line);
    if (pointers[pos] < 0) fprintf (out, "extra free  %d\n", line);

    line++;
  }

  for (int i = 0; i < step; i++)
  {
    if (pointers[i] < 0) fprintf (out, "lack of alloc %d\n", i);
    if (pointers[i] > 0) fprintf (out, "lack of free  %d\n", i);
  }

  fclose (in);
  fclose (out);
  free (s);
}

int main ()
{
  printf (" # START scanning...\n");
  memory_scan();
  printf (" # ENDED scanning.\n");
}
//*/---------------------------------------------------------------------------
