#!/usr/bin/perl

# 1. Collect all function and fn-like macro names.
# 2. Append a suffix to them specified in the SUFFIX environment variable.
# 3. Generate a set of #define's for them

@a=<>;                                   # read all lines
for (@a) { /^(?:#define\s+)?(__\w++)(?=\()/ and $fn{$1}=1; }  # collect locally defined functions and fn-like macros
$FNRE = join "|", map {"\\b$_\\b"} keys %fn;              # make a regex out of them
print << "_END";
/* DO NOT EDIT: automatically built by $ENV{MYNAME} */

#pragma once

/* Remove optype checking for garbage testing purpose */
#define WT_CHECK_OPTYPE(session, opvar, op)

#include "../../src/include/intpack_inline.h"


#ifndef WT_ATTRIBUTE_UNUSED
#if defined(DOXYGEN) || defined(SWIG) || !defined(__GNUC__)
#define WT_ATTRIBUTE_UNUSED
#else
#define WT_ATTRIBUTE_UNUSED __attribute__((__unused__))
#endif
#endif

#if defined(NO_OPTYPE_CHECKING)
#define WT_ASSERT_OPTYPE(session, exp)
#else
#define WT_ASSERT_OPTYPE(session, exp) WT_ASSERT(session, exp)
#endif

#ifdef WT_STRUCT_PACKING_@{[uc $ENV{SUFFIX}]}
@{[join "\n", map {"#define ${_} ${_}__$ENV{SUFFIX}"} sort keys %fn]}
#endif
_END
for (@a) {
    s{\Q#include "wt_internal.h"}{#include "../../src/include/wt_internal.h"} ||
    s{WT_ASSERT(\Q(session, optype == \E.*)}{WT_ASSERT_OPTYPE$1} ||    # Remove optype checking for garbage testing purpose
    s{\Q__wt_json_unpack_str((*escapedp)->mem, (*escapedp)->memsize, item->data, item->size));}{__wt_json_unpack_str((u_char*)(*escapedp)->mem, (*escapedp)->memsize, (const u_char *)item->data, item->size));} ||    # ? fix bug?
    s{\Q__wt_fill_hex(item->data, item->size, (*escapedp)->mem, (*escapedp)->memsize, NULL);}{__wt_fill_hex((const uint8_t *)item->data, item->size, (uint8_t *)(*escapedp)->mem, (*escapedp)->memsize, NULL);} ||    # ? fix bug?
    s/^(int|void)/WT_ATTRIBUTE_UNUSED\nstatic $1/ ||          # add "static" to all function defs
    s/($FNRE)/${1}__$ENV{SUFFIX}/g;      # append suffix to all locally defined funcs
    print;
}
