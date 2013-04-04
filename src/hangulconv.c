/**
 * File: hangulconv.c
 * Author: Daniel Rasband <danrasband@gmail.com>
 * Description: This is the command-line tool part of the libhtr
 *   package. It allows you to use the command line to convert hangul and
 *   romaja.
 */

#include "hangulconv.h"
#include "common.h"
#include <errno.h>

#define STR_REALLOC_FACTOR 1.5

void get_input_string();
void hangulconv();
bool set_t13n_system(char* system);

void version();
void usage(int status);

static char* program_name;

static int hangulize_flag = 0;
static struct option const long_options[] = {
    {"transliteration-system", required_argument, NULL, 't'},
    {"hangulize", no_argument, &hangulize_flag, 1},
    {"output", required_argument, NULL, 'o'},
    {"input", required_argument, NULL, 'i'},
    {"version", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, 'h'}
};
static char *optstring = "t:o:i:zhv";

// Set default romanization system. Default to Yale.
static T13N_SYSTEM t13n_system = YALE;

static FILE *input;
static FILE *output;
static char *input_string;

int
main (int argc, char * argv[])
{
    // Must use int because char has different implementations on
    // different systems and EOF may not trigger properly.
    int c;
    int oi = -1;
    char *output_filename = NULL;
    char *input_filename = NULL;

    // Localization setup.
    setlocale (LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);

    // Set the program name.
    program_name = argv[0];

    // Go through options.
    while ((c = getopt_long(argc, argv, optstring, long_options, &oi)) != EOF) {
        switch (c) {
        case 't':
            if (!set_t13n_system (optarg))
                usage(HANGULCONV_FAILURE);
            break;
        case 'o':
            output_filename = optarg;
            if (!(output = fopen(output_filename, "w"))) {
                perror(output_filename);
                exit(1);
            }
            break;
        case 'i':
            input_filename = optarg;
            if (!(input = fopen(input_filename, "r"))) {
                perror(input_filename);
                exit(1);
            }
            break;
        case 'z':
            hangulize_flag = 1;
            break;
        case 'v':
            version();
        case 'h':
            usage(EXIT_SUCCESS);
        default:
            usage(HANGULCONV_FAILURE);
        }
    }

    /* Make sure there is an input and output. */
    if (!output)
        output = stdout;
    if (!input)
        input = stdin;

    get_input_string ();
    hangulconv ();

    free (input_string);
    fclose (output);
    fclose (input);
    return 0;
}

void
get_input_string() {
    int c, i = 0;
    unsigned int min_buffer_size = 128;
    unsigned int current_buffer_size = min_buffer_size;

    input_string = xmalloc(min_buffer_size);
    memset (input_string, 0, min_buffer_size);

    while ((c = getchar()) != EOF) {
        input_string[i++] = (char)c;
        if (i == current_buffer_size) {
            current_buffer_size = current_buffer_size * STR_REALLOC_FACTOR;
            input_string = xrealloc (input_string, current_buffer_size);
        }
    }

    input_string[i] = '\0';
}

void
hangulconv() {
    int initial_buffer = strlen (input_string) * 2;
    int needed_buffer = 0;
    char *output_string = xmalloc (initial_buffer);
    needed_buffer = transliterate_hangul (output_string, initial_buffer, input_string, t13n_system);

    if (needed_buffer >= initial_buffer) {
        output_string = xrealloc(output_string, needed_buffer);
    }

    fputs(output_string, output);
}

bool
set_t13n_system(char* system)
{
    int i;
    bool system_set_success = false;

    struct t13n_system_data {
        char* name;
        T13N_SYSTEM system;
    };

    struct t13n_system_data t13n_systems[] = {
        {"yale", YALE},
        {"y", YALE},
        {"revised-romanization", REVISED_ROMANIZATION},
        {"revised", REVISED_ROMANIZATION},
        {"r", REVISED_ROMANIZATION},
        {"mccune-reischauer", MCCUNE_REISCHAUER},
        {"mccune", MCCUNE_REISCHAUER},
        {"m", MCCUNE_REISCHAUER},
        {"kontsevich", KONTSEVICH},
        {"k", KONTSEVICH},
        {"skats", SKATS},
        {"s", SKATS}
    };

    for (i = 0; i < NARRAY(t13n_systems); i++) {
        if (0 == strncmp(t13n_systems[i].name, system, strlen(t13n_systems[i].name))) {
            t13n_system = t13n_systems[i].system;
            system_set_success = true;
            break;
        }
    }

    return system_set_success;
}

void
version ()
{
    printf("Version: %s\n", PACKAGE_VERSION);
    exit(0);
}

void
usage (int status)
{
    if (status != EXIT_SUCCESS) {
        fprintf (stderr, _("Try `%s --help`' for more information.\n"), program_name);
    } else {
        printf (_("Usage: %s [OPTION]... [INPUT]...\n"), program_name);
        fputs (_("Transliterate Hangul text.\n\n"), stdout);
        fputs (_("Mandatory arguments to long options are mandatory for short options, too.\n"), stdout);
        fputs (_("\
Convert hangul to romaja characters or romaja to hangul.\n"), stdout);
        fputs (_("\
  -t, --transliteration-system=SYSTEM   use transliteration system SYSTEM:\n\
                                          yale (y), revised-romanization (revised, r),\n\
                                          mccune-reischauer (mccune, m), kontsevich\n\
                                          (k), skats (s)\n\
"), stdout);
        fputs (_("\
  -z, --hangulize                       hangulize previously transliterated\n\
                                          text\n\
"), stdout);
        fputs (_("\
  -o, --output=FILE                     print output to FILE\n\
"), stdout);
        fputs (_("\
  -i, --input=FILE                      get input from FILE\n\
"), stdout);
        fputs (_("\
  -v, --version                         print version information and quit\n\
"), stdout);
        fputs (_("\
  -h, --help                            print this help message and quit\n\
"), stdout);
    }
    exit (status);
}
