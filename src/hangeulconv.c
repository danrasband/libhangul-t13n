/**
 * File: hangeulconv.c
 * Author: Daniel Rasband <danrasband@gmail.com>
 * Description: This is the command-line tool part of the libhangeul-romaja
 *   package. It allows you to use the command line to convert hangeul and
 *   romaja.
 */

#include "hangeulconv.h"

void version();
void usage(int status);

typedef enum {
  YALE,
  REVISED_ROMANIZATION,
  MCCUNE_REISCHAUER
} ROMANIZATION;


static struct option const long_options[] =
{
  {"yale", no_argument, NULL, 'y'},
  {"revised", no_argument, NULL, 'r'},
  {"mccune-reischauer", no_argument, NULL, 'm'},
  {"output", required_argument, NULL, 'o'},
  {"input", required_argument, NULL, 'i'},
  {"version", no_argument, NULL, 'v'},
  {"help", no_argument, NULL, 'h'}
};
static char *optstring = "yrmo:i:hv";

int
main (int argc, char * argv[])
{
  // Must use int because char has different implementations on
  // different systems and EOF may not trigger properly.
  int c; 
  int oi = -1;
  char *output_filename = NULL;
  char *input_filename = NULL;

  // Set default romanization system.
  ROMANIZATION t = YALE;

  // Set the program name.
  set_program_name(argv[0]);

  // Go through options.
  while ((c = getopt_long(argc, argv, optstring, long_options, &oi)) != EOF) {

    switch (c) {
      case 'y':
        t = YALE;
        break;
      case 'r':
        t = REVISED_ROMANIZATION;
        break;
      case 'm':
        t = MCCUNE_REISCHAUER;
        break;
      case 'o':
        output_filename = optarg;
        break;
      case 'i':
        input_filename = optarg;
        break;
      case 'v':
        version();
      case 'h':
        usage(EXIT_SUCCESS);
      default:
        usage(HANGEULCONV_FAILURE);
    }
  }

  return 0;
}

void
version () {
  printf("Version\n");
  exit(0);
}

void
usage (int status) {
  if (status != EXIT_SUCCESS) {
    fprintf(stderr, _("Try `%s --help`' for more information.\n"), program_name);
  }
  else {
    printf(_("Usage: %s [OPTION]... [FILE]...\n"), program_name);
    fputs(_("\
      Convert hangeul to romaja characters or romaja to hangeul.\n"), stdout);
  }
}

