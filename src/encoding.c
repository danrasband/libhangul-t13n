
#include "encoding.h"

#define UTF8 "UTF8"

iconv_t initialize_conv (const char *to_code, const char *from_code);
void finalize_conv (iconv_t cd);

char *
encode (char *orig, char *to_code, char *from_code) {
    size_t iconv_value;
    char *output = NULL;
    char *output_helper = NULL;
    size_t len;
    size_t output_len;
    iconv_t cd = initialize_conv (to_code, from_code);

    len = strlen (orig);
    if (!len) {
        fprintf (stderr, _("Input string is empty.\n"));
        return false;
    }

    /* Assign enough space to put the new string. */
    output_len = 3 * len;
    output = xmalloc (output_len);
    output_helper = output;

    iconv_value = iconv (cd, &orig, &len, &output_helper, &output_len);

    /* Handle failures. */
    if ((size_t)-1 == iconv_value) {
        switch (errno) {
        case EILSEQ:
            fputs (_("Invalid multibyte sequence.\n"), stderr);
            break;
        case EINVAL:
            fputs (_("Incomplete multibyte sequence.\n"), stderr);
            break;
        case E2BIG:
            fputs (_("No more room.\n"), stderr);
            break;
        default:
            fprintf (stderr, "Error: %s.\n", strerror (errno));
        }
        exit (1);
    }

    finalize_conv (cd);
    return output;
}

iconv_t
initialize_conv(const char *to_code, const char *from_code) {
    iconv_t cd;
    cd = iconv_open (to_code, from_code);
    if ((iconv_t)-1 == cd) {
        /* Initialization failure. */
        if (errno == EINVAL) {
            fprintf (stderr,
                 _("Conversion from '%s' to '%s' is not supported.\n"),
                 from_code, to_code);
        } else {
            fprintf (stderr, _("Encoding initialization failure: %s\n"),
                 strerror (errno));
        }
        exit (1);
    }
    return cd;
}

void
finalize_conv(iconv_t cd) {
    int v;
    v = iconv_close (cd);
    if (v != 0) {
        fprintf (stderr, _("iconv_close failed: %s\n"), strerror (errno));
        exit (1);
    }
}
