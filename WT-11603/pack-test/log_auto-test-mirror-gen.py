#!/usr/bin/env python3

# Generate tests based on meta data in log.py and log_data.py
# MUST BE RUN BY log_auto-test-gen.sh ONLY!

import os
from log import *

S = '\\'
NN = '\\n'
TT = '\\t'
N = '\n'
T = '\t'

def optype_format_args(optype):
    return {
        'name' : optype.name,
        'macro' : optype.macro_name,
        'comma' : ',' if optype.fields else '',
        'local_decls_direct': (('\n'.join(
            '    const char *'+f.fieldname+'_direct;'
            if f.typename == 'string' else
            '    '+f.ctype+' '+f.fieldname+'_direct;'
            for f in optype.fields))
            if optype.fields else ''),
        'local_init_direct': (('\n'.join(
            '    WT_CLEAR('+f.fieldname+'_direct); WT_ASSERT(session, __wt_buf_init(session, &'+f.fieldname+'_direct, 0) == 0);'
            if f.typename == 'WT_ITEM' else
            ''
            for f in optype.fields))
            if optype.fields else ''),
        'local_cleanup_direct': (('\n'.join(
            '    __wt_buf_free(session, &'+f.fieldname+'_direct);'
            if f.typename == 'WT_ITEM' else
            ''
            for f in optype.fields))
            if optype.fields else ''),
        'arg_decls_in': ', '.join('' + f.cindecl for f in optype.fields),
        'arg_decls_in_or_void' : ', '.join(
            f.cindecl
            for f in optype.fields)
            if optype.fields else 'void',
        'arg_decls_out' : ', '.join(f.coutdecl for f in optype.fields),
        'pack_args': ', '.join('' + ('&' if f.byptr else '') + f.fieldname for f in optype.fields),
        'pack_fwd_args': ', '.join(f.fieldname for f in optype.fields),
        'pack_args_direct': ', '.join('' + ('&' if f.byptr else '') + f.fieldname + '_direct' for f in optype.fields),
        'unpack_args': ', '.join('&' + f.fieldname for f in optype.fields),
        'unpack_fwd_args': ', '.join(f.fieldname+'p' for f in optype.fields),
        'unpack_args_direct': ', '.join('&' + f.fieldname+'_direct' for f in optype.fields),
        'check_fields': ''.join(
            '    assert_eq_size_t('+f.fieldname+'p->size, '+f.fieldname+'_direct.size);\n    WT_ASSERT(session, memcmp('+f.fieldname+'p->data, '+f.fieldname+'_direct.data, '+f.fieldname+'p->size) == 0);\n'
            if f.typename == 'WT_ITEM' else
            '    WT_ASSERT(session, '+f.fieldname+'p->l.file == '+f.fieldname+'_direct.l.file);\n    WT_ASSERT(session, '+f.fieldname+'p->l.offset == '+f.fieldname+'_direct.l.offset);\n'
            if f.typename == 'WT_LSN' else
            '    WT_ASSERT(session, !strcmp(*'+f.fieldname+'p, '+f.fieldname+'_direct));\n'
            if f.typename == 'string' else
            '    assert_eq_'+f.ctype+'(*'+f.fieldname+'p, '+f.fieldname+'_direct);\n'
            for f in optype.fields),
    }

print(f'''/* DO NOT EDIT: automatically built by {os.environ['MYNAME']} */

#pragma once



#include "../utility/test_util.h"
#include "log_auto_fmt.h"
#include "log_auto_direct.h"

#define testutil_die_mirror(e, fmt, ...) \
do {{ \
    (void)fflush(stdout); \
    (void)fflush(stderr); \
    fprintf(stderr, "FAILED: "); \
    fprintf(stderr, fmt, __VA_ARGS__); \
    if ((e) != 0) \
        fprintf(stderr, ": %s", wiredtiger_strerror(e)); \
    fprintf(stderr, "{S}n"); \
    (void)fflush(stderr); \
    fprintf(stderr, "process aborting{S}n"); \
    __wt_abort(NULL); \
}} while(0)

#define testutil_assertfmt__(a, fmt, ...)                                               {S}
    do {{                                                                                {S}
        if (!(a))                                                                       {S}
            testutil_die_mirror(0, "{NN}%s:%d:{NN}  %s:{NN}    " fmt, __FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__); {S}
    }} while (0)

#define assert_eq(a, b) testutil_assertfmt__((a) == (b), "%s != %s", #a, #b)
#define assert_eq_int_t(FMT, a, b) testutil_assertfmt__((a) == (b), "%s != %s : (%" FMT ") != (%" FMT ")", #a, #b, (a), (b))
#define assert_eq_int(a, b) assert_eq_int_t("d", a, b)
#define assert_eq_uint16_t(a, b) assert_eq_int_t(PRIu16, a, b)
#define assert_eq_uint32_t(a, b) assert_eq_int_t(PRIu32, a, b)
#define assert_eq_uint64_t(a, b) assert_eq_int_t(PRIu64, a, b)
#define assert_eq_size_t(a, b) assert_eq_int_t("zu", a, b)

''')

for optype in log_data.optypes:
    print('''
WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_%(name)s_pack__mirror(
    WT_SESSION_IMPL *session, WT_ITEM *logrec%(comma)s
    %(arg_decls_in)s)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_%(name)s_pack__fmt(session, logrec%(comma)s%(pack_fwd_args)s), 0);
    assert_eq_int(__wt_logop_%(name)s_pack__direct(session, &logrec_direct%(comma)s%(pack_fwd_args)s), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t*)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_%(name)s_unpack__mirror(
    WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end%(comma)s
    %(arg_decls_out)s)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
%(local_decls_direct)s

    pp_direct = *pp;
%(local_init_direct)s

    ret_fmt = __wt_logop_%(name)s_unpack__fmt(session, pp, end%(comma)s%(unpack_fwd_args)s);
    ret_direct = __wt_logop_%(name)s_unpack__direct(session, &pp_direct, end%(comma)s%(unpack_args_direct)s);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
%(check_fields)s
    }

%(local_cleanup_direct)s

    return (ret_fmt);
}

'''  %  {
            **optype_format_args(optype),
            **locals()
        }
    )

