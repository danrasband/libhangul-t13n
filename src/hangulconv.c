/**
 * File: hangulconv.c
 * Author: Daniel Rasband <danrasband@gmail.com>
 * Description: This is the command-line tool part of the libhtr
 *   package. It allows you to use the command line to convert hangul and
 *   romaja.
 */

#include "hangulconv.h"
#include "common.h"

bool set_t13n_system(char* system);

void version();
void usage(int status);

static char* program_name;

static bool hangulize_flag = 0;

static struct option const long_options[] = {
    {"transliteration-system", required_argument, NULL, 't'},
    {"hangulize", no_argument, &hangulize_flag, 1},
    {"output", required_argument, NULL, 'o'},
    {"input", required_argument, NULL, 'i'},
    {"version", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, 'h'}
};
static char *optstring = "t:o:i:zhv";

// Set default romanization system.
static T13N_SYSTEM t13n_system;

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
            break;
        case 'i':
            input_filename = optarg;
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

    return 0;
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
