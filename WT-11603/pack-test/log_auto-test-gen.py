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

print(f'''/* DO NOT EDIT: automatically built by {os.environ['MYNAME']} */

#pragma once


#include "log_auto_mirror.h"

''')

def optype_format_args(optype):
    return {
        'local_decls': (('\n'.join(
            '    '+f.ctype+' '+f.fieldname+';'
            for f in optype.fields))
            if optype.fields else ''),
        'local_decls2': (('\n'.join(
            '    const char *'+f.fieldname+'_fmt, *'+f.fieldname+'_direct;'
            if f.typename == 'string' else
            '    '+f.ctype+' '+f.fieldname+'_fmt, '+f.fieldname+'_direct;'
            for f in optype.fields))
            if optype.fields else ''),
        'local_init2': (('\n'.join(
            '    '+f.fieldname+'_fmt.data='+f.fieldname+'->data; '+f.fieldname+'_direct.data='+f.fieldname+'->data;'+
            '    '+f.fieldname+'_fmt.size='+f.fieldname+'->size; '+f.fieldname+'_direct.size='+f.fieldname+'->size;'
            if f.typename == 'WT_ITEM' else
            '    '+f.fieldname+'_fmt.l.file='+f.fieldname+'->l.file; '+f.fieldname+'_direct.l.file='+f.fieldname+'->l.file;'+
            '    '+f.fieldname+'_fmt.l.offset='+f.fieldname+'->l.offset; '+f.fieldname+'_direct.l.offset='+f.fieldname+'->l.offset;'
            if f.typename == 'WT_LSN' else
            '    '+f.fieldname+'_fmt='+f.fieldname+'; '+f.fieldname+'_direct='+f.fieldname+';'
            for f in optype.fields))
            if optype.fields else ''),
        'arg_decls_in': ''.join(', ' + f.cindecl for f in optype.fields),
        'pack_args': ''.join(', ' + ('&' if f.byptr else '') + f.fieldname for f in optype.fields),
        'pack_args_fmt': ''.join(', ' + ('&' if f.byptr else '') + f.fieldname + '_fmt' for f in optype.fields),
        'pack_args_direct': ''.join(', ' + ('&' if f.byptr else '') + f.fieldname + '_direct' for f in optype.fields),
        'unpack_args': ''.join(', &' + f.fieldname for f in optype.fields),
        'unpack_args_fmt': ''.join(', &' + f.fieldname + '_fmt' for f in optype.fields),
        'unpack_args_direct': ''.join(', &' + f.fieldname + '_direct' for f in optype.fields),
        'check_fields': '\n'.join(
            '    assert_eq_size_t('+f.fieldname+'_fmt.size, '+f.fieldname+'_direct.size);\n    assert(memcmp('+f.fieldname+'_fmt.data, '+f.fieldname+'_direct.data, '+f.fieldname+'_fmt.size) == 0);\n'
            if f.typename == 'WT_ITEM' else
            '    assert('+f.fieldname+'_fmt.l.file == '+f.fieldname+'_direct.l.file);\n    assert('+f.fieldname+'_fmt.l.offset == '+f.fieldname+'_direct.l.offset);\n'
            if f.typename == 'WT_LSN' else
            '    assert(!strcmp('+f.fieldname+'_fmt, '+f.fieldname+'_direct));'
            if f.typename == 'string' else
            '    assert_eq_'+f.ctype+'('+f.fieldname+'_fmt, '+f.fieldname+'_direct);'
            for f in optype.fields),
        'print_fields': 'fprintf(stderr, "    Fields:{ffmt}\\n"{fields});'.format(
            ffmt = ''.join('  ' + (
                    f.fieldname + "[%zu]"
                    if f.typename == 'WT_ITEM' else
                    f.fieldname + "=%u:%u"
                    if f.typename == 'WT_LSN' else
                    f.fieldname + "=string[%lu]"
                    if f.typename == 'string' else
                    f.fieldname + "=" + f.printf_fmt(f.always_hex)
                )
                for f in optype.fields),
            fields = ''.join(
                ', ' + f.fieldname + '.size'
                if f.typename == 'WT_ITEM' else
                ', ' + f.fieldname + '.l.file' + ', ' + f.fieldname + '.l.offset'
                if f.typename == 'WT_LSN' else
                ', strlen(' + f.fieldname + ')'
                if f.typename == 'string' else
                ', ' + f.printf_arg
                for f in optype.fields)
        )
    }

def optype_format_local_init(optype, name, init):
    return {
        name: (('\n'.join(
            '    '+f.fieldname+'.data='+init['WT_ITEM']['data']+';'
            '    '+f.fieldname+'.size='+init['WT_ITEM']['size']+';'
            if f.typename == 'WT_ITEM' else
            '    '+f.fieldname+'.l.file=(uint32_t)('+init['WT_LSN']['file']+');'
            '    '+f.fieldname+'.l.offset=(uint32_t)('+init['WT_LSN']['offset']+');'
            if f.typename == 'WT_LSN' else
            '    '+f.fieldname+'='+init['string']+';'
            if f.typename == 'string' else
            '    '+f.fieldname+'=('+f.ctype+')('+init['int']+');'
            for f in optype.fields))
            if optype.fields else ''),
    }

def optype_format_local_init_int(optype, name, num):
    return optype_format_local_init(optype, name, {
        'WT_ITEM': {'data': 'NULL', 'size': '0'},
        'WT_LSN': {'file': num, 'offset': num},
        'string': '""',
        'int': num,
    });

print(f'''/*
 * Functions to compare packing and unpacking for pre-defined inputs
 */
''')

for optype in log_data.optypes:
    print('''
WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_{optype.name}(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct{arg_decls_in}) {{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
{local_decls2}

{local_init2}
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(__wt_logop_{optype.name}_pack__fmt(session, logrec_fmt{pack_args_fmt}) == 0);
    assert(__wt_logop_{optype.name}_pack__direct(session, logrec_direct{pack_args_direct}) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_{optype.name}_unpack__fmt(session, &data_fmt, data_fmt+logrec_fmt->size{unpack_args_fmt}) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_{optype.name}_unpack__direct(session, &data_direct, data_direct+logrec_direct->size{unpack_args_direct}) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

{check_fields}
    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}}
'''.format(
    **optype_format_args(optype),
    **locals()))

for optype in log_data.optypes:
    print('''
WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_{optype.name}(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct) {{
{local_decls}

{local_init_test_int1}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int2}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int3}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int4}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int5}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int6}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int7}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int8}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_int9}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});

{local_init_test_data1}
    test_cmp_one__wt_logop_{optype.name}(session, logrec_fmt, logrec_direct{pack_args});
}}
'''.format(
            **optype_format_args(optype),
            **optype_format_local_init_int(optype, 'local_init_test_int1', '0'),
            **optype_format_local_init_int(optype, 'local_init_test_int2', '1'),
            **optype_format_local_init_int(optype, 'local_init_test_int3', 'POS_1BYTE_MAX-1'),
            **optype_format_local_init_int(optype, 'local_init_test_int4', 'POS_1BYTE_MAX'),
            **optype_format_local_init_int(optype, 'local_init_test_int5', 'POS_1BYTE_MAX+1'),
            **optype_format_local_init_int(optype, 'local_init_test_int6', 'POS_2BYTE_MAX-1'),
            **optype_format_local_init_int(optype, 'local_init_test_int7', 'POS_2BYTE_MAX'),
            **optype_format_local_init_int(optype, 'local_init_test_int8', 'POS_2BYTE_MAX+1'),
            **optype_format_local_init_int(optype, 'local_init_test_int9', 'rand()'),
            **optype_format_local_init(optype, 'local_init_test_data1', {
                'WT_ITEM': {'data': '"data"', 'size': '4'},
                'WT_LSN': {'file': 'rand()', 'offset': 'rand()'},
                'string': '"string"',
                'int': 'rand()',
            }),
            **locals()
        )
    )

print(f'''

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all(WT_SESSION_IMPL *session) {{
    WT_ITEM logrec_fmt, logrec_direct;

    WT_CLEAR(logrec_fmt);
    assert(__wt_buf_init(session, &logrec_fmt, 0) == 0);
    WT_CLEAR(logrec_direct);
    assert(__wt_buf_init(session, &logrec_direct, 0) == 0);

''')

for optype in log_data.optypes:
    print('    test_cmp_all__wt_logop_{optype.name}(session, &logrec_fmt, &logrec_direct);'.format(
        **optype_format_args(optype),
        **locals()))

print(f'''

    __wt_buf_free(session, &logrec_fmt);
    __wt_buf_free(session, &logrec_direct);
}}

''')

print(f'''/*
 * Functions to compare packing and unpacking of garbage inputs.
 */

''')

for optype in log_data.optypes:
    print('''
WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_{optype.name}(WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size) {{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
{local_decls2}

    data_fmt = data_direct = garbage;
    unpack_res_fmt    = __wt_logop_{optype.name}_unpack__fmt(session, &data_fmt, data_fmt+garbage_size{unpack_args_fmt});
    unpack_res_direct = __wt_logop_{optype.name}_unpack__direct(session, &data_direct, data_direct+garbage_size{unpack_args_direct});
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {{
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

{check_fields}
    }}
}}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_{optype.name}(WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size) {{
    const uint8_t *data;
    int unpack_res;
{local_decls}

    data = garbage;
    unpack_res = __wt_logop_{optype.name}_unpack__fmt(session, &data, data + garbage_size{unpack_args});
    fprintf(stderr, "  %s returned: %d", "{optype.name}", unpack_res);
    if (unpack_res == 0) {{
        fprintf(stderr, " used buffer: %zu of %zu{S}n", WT_PTRDIFF(data, garbage), garbage_size);
{print_fields}
    }} else {{
        fprintf(stderr, "{S}n");
    }}
}}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_{optype.name}(WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size) {{
    const uint8_t *data;
    int unpack_res;
{local_decls}

    data = garbage;
    unpack_res = __wt_logop_{optype.name}_unpack__direct(session, &data, data + garbage_size{unpack_args});
    fprintf(stderr, "  %s returned: %d", "{optype.name}", unpack_res);
    if (unpack_res == 0) {{
        fprintf(stderr, " used buffer: %zu of %zu{S}n", WT_PTRDIFF(data, garbage), garbage_size);
{print_fields}
    }} else {{
        fprintf(stderr, "{S}n");
    }}
}}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_{optype.name}(WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size) {{
    const uint8_t *data;
    int unpack_res;
{local_decls}

    data = garbage;
    unpack_res = __wt_logop_{optype.name}_unpack__mirror(session, &data, data + garbage_size{unpack_args});
    fprintf(stderr, "  %s returned: %d", "{optype.name}", unpack_res);
    if (unpack_res == 0) {{
        fprintf(stderr, " used buffer: %zu of %zu{S}n", WT_PTRDIFF(data, garbage), garbage_size);
{print_fields}
    }} else {{
        fprintf(stderr, "{S}n");
    }}
}}

'''.format(
    **optype_format_args(optype),
    **locals()))

print(f'''
#define MAX_GARBAGE_SIZE 1024
#define N_GARBAGE_TESTS 1000
#define GARBAGE_RAND_SEED 1

static void
dump(const uint8_t *data, size_t size) {{
    size_t i;
    for (i = 0; i < size; i++) fprintf(stderr, " %02x", data[i]);
}}

static void
init_garbage(size_t seed, uint8_t (*garbage)[MAX_GARBAGE_SIZE], size_t *garbage_size, int verbose) {{
    size_t j;
    WT_RAND_STATE rnd;

    __wt_random_init_custom_seed(&rnd, GARBAGE_RAND_SEED + seed);
    *garbage_size = __wt_random(&rnd) % MAX_GARBAGE_SIZE;
    for (j = 0; j < MAX_GARBAGE_SIZE / sizeof(uint32_t); j++) {{
        ((uint32_t*)garbage)[j] = __wt_random(&rnd);
    }}
    if (verbose) {{
        fprintf(stderr, ">>> %zu: [%zu]", seed, *garbage_size);
        dump(*garbage, *garbage_size);
        fprintf(stderr, "{S}n");
    }}
}}
''')

print(f'''
WT_ATTRIBUTE_UNUSED
static void
test_garbage_all(WT_SESSION_IMPL *session) {{
    size_t i;
    uint8_t garbage[MAX_GARBAGE_SIZE];
    size_t garbage_size;

    for (i = 0; i < N_GARBAGE_TESTS; i++) {{
        init_garbage(i, &garbage, &garbage_size, 1);''')
for optype in log_data.optypes:
    print('    test_garbage_both_one__wt_logop_{optype.name}(session, garbage, garbage_size);'.format(
        **optype_format_args(optype),
        **locals()))
print(f'''
    }}
}}

''')

print(f'''
WT_ATTRIBUTE_UNUSED
static void
test_garbage_all_fmt(WT_SESSION_IMPL *session) {{
    size_t i;
    uint8_t garbage[MAX_GARBAGE_SIZE];
    size_t garbage_size;

    for (i = 0; i < N_GARBAGE_TESTS; i++) {{
        init_garbage(i, &garbage, &garbage_size, 1);''')
for optype in log_data.optypes:
    print('    test_garbage_fmt_one__wt_logop_{optype.name}(session, garbage, garbage_size);'.format(
        **optype_format_args(optype),
        **locals()))
print(f'''
    }}
}}

''')

print(f'''
WT_ATTRIBUTE_UNUSED
static void
test_garbage_all_direct(WT_SESSION_IMPL *session) {{
    size_t i;
    uint8_t garbage[MAX_GARBAGE_SIZE];
    size_t garbage_size;

    for (i = 0; i < N_GARBAGE_TESTS; i++) {{
        init_garbage(i, &garbage, &garbage_size, 1);''')
for optype in log_data.optypes:
    print('    test_garbage_direct_one__wt_logop_{optype.name}(session, garbage, garbage_size);'.format(
        **optype_format_args(optype),
        **locals()))
print(f'''
    }}
}}
''')

print(f'''
WT_ATTRIBUTE_UNUSED
static inline const char *
test_list_ops(void) {{
    return''')
for optype in log_data.optypes: print('        "  '+optype.name+'\\n"')
print(f''';
}}
''')

print(f'''
WT_ATTRIBUTE_UNUSED
static void
test_unpack_run(WT_SESSION_IMPL *session, char *mode, char *optype, const uint8_t *data, size_t size) {{
    if (0) {{
    }}''', end='')
for optype in log_data.optypes:
    print(''' else if (!strcmp(optype, "{optype.name}")) {{
        if (!strcmp(mode, "fmt")) {{
            test_garbage_fmt_one__wt_logop_{optype.name}(session, data, size);
        }} else if (!strcmp(mode, "direct")) {{
            test_garbage_direct_one__wt_logop_{optype.name}(session, data, size);
        }} else if (!strcmp(mode, "mirror")) {{
            test_garbage_mirror_one__wt_logop_{optype.name}(session, data, size);
        }} else {{
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.{S}n", mode);
            exit(1);
        }}
    }}'''.format(
        **optype_format_args(optype),
        **locals()), end='')
print(f''' else {{
        fprintf(stderr, "Invalid optype '%s'. List of available operations:{S}n%s", optype, test_list_ops());
    }}
}}
''')

