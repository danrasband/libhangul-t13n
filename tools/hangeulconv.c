#include <stdio.h>
#include <string.h>
#include <hangeul-romaja.h>
#include <getopt.h>

void help_message();
void add_to_string(char **destRef, const char *src);

static int verbose_flag;
static int hangeulize_flag;
static char* input_string = NULL;

int
main(int argc, char *argv[])
{
  int c;
  char romanization_type = 'y';
  char *input_filename = NULL;
  char *output_filename = NULL;
  char *input_string = NULL;

  while (1) {
    static struct option long_options[] = {
      /* Help */
      { "help", no_argument, 0, 'h'},
      /* Set a flag for verbosity. */
      { "verbose", no_argument, &verbose_flag, 1},
      /* Display version */
      { "version", no_argument, 0, 'v'},
      /* Romanization Types */
      { "yale", no_argument, 0, 'y'},
      { "yale-original", no_argument, 0, 'l'},
      { "mccune-reischaeur", no_argument, 0, 'm'},
      { "revised", no_argument, 0, 'r'},
      /* For input/output files */
      { "input", required_argument, 0, 'i'},
      { "output", required_argument, 0, 'o'},
      /* Hangeulize romaja. */
      { "hangeulize", no_argument, &hangeulize_flag, 1},
      { 0, 0, 0, 0}
    };

    int option_index = 0;

    c = getopt_long(argc, argv, "vylmri:o:h", long_options, &option_index);

    /* Detect the end of the options */
    if (c == -1) {
      break;
    }
    switch (c) {
      /* If this option set a flag, do nothing else now. */
      case 0:
        if (long_options[option_index].flag != 0) {
          break;
        }
        printf ("option %s", long_options[option_index].name);
        if (optarg) {
          printf(" with arg %s", optarg);
        }
        printf("\n");
        break;

      /* Print version and exit. */
      case 'v':
        printf("Version 0.0.1");
        exit(0);

      /* Help message */
      case 'h':
        help_message();
        exit(0);

      /* Get romanization type. Last flag takes precedence. */
      case 'y':
      case 'l':
      case 'm':
      case 'r':
        romanization_type = c;
        break;

      /* Input filename */
      case 'i':
        input_filename = malloc(strlen(optarg) * sizeof(char));
        strcpy(input_filename, optarg);
        break;

      /* Output filename. */
      case 'o':
        output_filename = malloc(strlen(optarg) * sizeof(char));
        strcpy(output_filename, optarg);
        break;

      default:
        help_message();
        exit(0);
    }
  }

  if (optind < argc) {
    while (optind < argc) {
      add_to_string(&input_string, argv[optind++]);
    }
  }
  else if (input_filename == NULL || !strlen(input_filename)) {
    help_message();
    exit(0);
  }

  return 0;
}

void
help_message()
{
  puts("Help message");
}

void
add_to_string(char **destRef, const char *src)
{
  if (*destRef == NULL) {
    *destRef = realloc(NULL, strlen(src) + 1);
    strcpy(*destRef, src);
  }
  else {
    *destRef = realloc(*destRef, (strlen(*destRef) + strlen(src) + 2));
    strcat(*destRef, " ");
    strcat(*destRef, src);
  }
}
