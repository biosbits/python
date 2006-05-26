/* stringlib: find/index implementation */

#ifndef STRINGLIB_FIND_H
#define STRINGLIB_FIND_H

#ifndef STRINGLIB_FASTSEARCH_H
#error must include "stringlib/fastsearch.h" before including this module
#endif

Py_LOCAL(Py_ssize_t)
stringlib_find(const STRINGLIB_CHAR* str, Py_ssize_t str_len,
               const STRINGLIB_CHAR* sub, Py_ssize_t sub_len,
               Py_ssize_t offset)
{
    Py_ssize_t pos;

    if (sub_len == 0)
        return offset;

    pos = fastsearch(str, str_len, sub, sub_len, FAST_SEARCH);

    if (pos >= 0)
        pos += offset;

    return pos;
}

Py_LOCAL(Py_ssize_t)
stringlib_rfind(const STRINGLIB_CHAR* str, Py_ssize_t str_len,
                const STRINGLIB_CHAR* sub, Py_ssize_t sub_len,
                Py_ssize_t offset)
{
    Py_ssize_t pos;

    /* XXX - create reversefastsearch helper! */
    if (sub_len == 0)
	pos = str_len + offset;
    else {
	Py_ssize_t j;
        pos = -1;
	for (j = str_len - sub_len; j >= 0; --j)
            if (STRINGLIB_CMP(str+j, sub, sub_len) == 0) {
                pos = j + offset;
                break;
            }
    }

    return pos;
}

#endif

/*
Local variables:
c-basic-offset: 4
indent-tabs-mode: nil
End:
*/