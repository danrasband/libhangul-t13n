/**
 * File: hangulconv.c
 * Author: Daniel Rasband <danrasband@gmail.com>
 * Description: This is the command-line tool part of the libhtr
 *   package. It allows you to use the command line to convert hangul and
 *   romaja.
 */

#include "hangulconv.h"

#define STR_REALLOC_FACTOR 1.5

void get_input_string();
void hangulconv();

bool set_t13n_system(char *system);

void version();
void usage(int status);

static char* program_name;

static int hangulize_flag = 0;
static struct option const long_options[] = {
    {"transliteration-system", required_argument, NULL, 't'},
    {"hangulize", no_argument, &hangulize_flag, 1},
    {"output", required_argument, NULL, 'o'},
    {"output-encoding", required_argument, NULL, 'o' + 'e'}, // 0xd4
    {"input", required_argument, NULL, 'i'},
    {"input-encoding", required_argument, NULL, 'i' + 'e'}, // 0xce
    {"version", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, 'h'}
};
static char *optstring = "t:o:i:zhv";

// Set default romanization system. Default to Yale.
static T13N_SYSTEM t13n_system = YALE;

// I/O Files
static FILE *input_file;
static FILE *output_file;

// Encodings
static char* input_encoding = "UTF8";
static char* output_encoding = "UTF8";

// Input string.
static char *input_string = NULL;

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
            if (!(output_file = fopen(output_filename, "w"))) {
                perror(output_filename);
                exit(1);
            }
            break;
        case 0xd4:
            output_encoding = optarg;
            break;
        case 'i':
            input_filename = optarg;
            if (!(input_file = fopen(input_filename, "r"))) {
                perror(input_filename);
                exit(1);
            }
            break;
        case 0xce:
            input_encoding = optarg;
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
    if (!output_file)
        output_file = stdout;
    if (!input_file)
        input_file = stdin;

    get_input_string ();
    hangulconv ();

    free (input_string);
    fclose (output_file);
    fclose (input_file);
    return 0;
}

void
get_input_string() {
    int c, i = 0;
    unsigned int min_buffer_size = 128;
    unsigned int current_buffer_size = min_buffer_size;
    char *utf8_input_string = NULL;

    input_string = xmalloc(min_buffer_size);
    memset (input_string, 0, min_buffer_size);

    while ((c = fgetc(input_file)) != EOF) {
        input_string[i++] = (char)c;
        if (i == current_buffer_size) {
            current_buffer_size = current_buffer_size * STR_REALLOC_FACTOR;
            input_string = xrealloc (input_string, current_buffer_size);
        }
    }

    input_string[i] = '\0';
    if (i < current_buffer_size)
        input_string = xrealloc (input_string, i + 1);

    if (strncmp (input_encoding, "UTF8", 4) != 0 &&
        strncmp (input_encoding, "UTF-8", 5) != 0) {
        utf8_input_string = encode (input_string, "UTF8", input_encoding);
        free (input_string);
        input_string = utf8_input_string;
    }
}

void
hangulconv() {
    int initial_buffer = strlen (input_string) * 2;
    int needed_buffer = 0;
    char *output_string = xmalloc (initial_buffer);
    char *encoded_output_string = NULL;

    int (*t13n_fn) (char*, size_t, char*, T13N_SYSTEM);

    if (hangulize_flag)
        t13n_fn = hangul_t13n_hangulize;
    else
        t13n_fn = hangul_t13n_transliterate;

    needed_buffer = t13n_fn (output_string, initial_buffer, input_string, t13n_system);

    if (needed_buffer >= initial_buffer) {
        output_string = xrealloc(output_string, needed_buffer);
        t13n_fn (output_string, initial_buffer, input_string, t13n_system);
    }

    // Re-encode.
    if (strncmp (output_encoding, "UTF8", 4) != 0 &&
        strncmp (output_encoding, "UTF-8", 5) != 0) {
        encoded_output_string = encode (output_string, output_encoding, "UTF8");
        free (output_string);
        output_string = encoded_output_string;
    }

    // Write output to output FILE. This is the end of our responsibility.
    fputs (output_string, output_file);
    free (output_string);
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
      --output-encoding=ENCODING        character encoding of the output:\n\
                                          e.g. UTF8, EUC-KR (as supported by\n\
                                          iconv)\n\
"), stdout);
        fputs (_("\
  -i, --input=FILE                      get input from FILE\n\
"), stdout);
        fputs (_("\
      --input-encoding=ENCODING         character encoding of the input:\n\
                                          e.g. UTF8, EUC-KR (as supported by\n\
                                          iconv)\n\
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
