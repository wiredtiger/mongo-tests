/* DO NOT EDIT: automatically built by log_auto-test-gen.sh */

#pragma once



#include "../utility/test_util.h"
#include "log_auto_fmt.h"
#include "log_auto_direct.h"

#define testutil_die_mirror(e, fmt, ...)                     \
    do {                                                     \
        (void)fflush(stdout);                                \
        (void)fflush(stderr);                                \
        fprintf(stderr, "FAILED: ");                         \
        fprintf(stderr, fmt, __VA_ARGS__);                   \
        if ((e) != 0)                                        \
            fprintf(stderr, ": %s", wiredtiger_strerror(e)); \
        fprintf(stderr, "\n");                               \
        (void)fflush(stderr);                                \
        fprintf(stderr, "process aborting\n");               \
        __wt_abort(NULL);                                    \
    } while (0)

#define testutil_assertfmt__(a, fmt, ...)                                           \
    do {                                                                            \
        if (!(a))                                                                   \
            testutil_die_mirror(0, "\n%s:%d:\n  %s:\n    " fmt, __FILE__, __LINE__, \
              __PRETTY_FUNCTION__, __VA_ARGS__);                                    \
    } while (0)

#define assert_eq(a, b) testutil_assertfmt__((a) == (b), "%s != %s", #a, #b)
#define assert_eq_int_t(FMT, a, b) \
    testutil_assertfmt__((a) == (b), "%s != %s : (%" FMT ") != (%" FMT ")", #a, #b, (a), (b))
#define assert_eq_int(a, b) assert_eq_int_t("d", a, b)
#define assert_eq_uint16_t(a, b) assert_eq_int_t(PRIu16, a, b)
#define assert_eq_uint32_t(a, b) assert_eq_int_t(PRIu32, a, b)
#define assert_eq_uint64_t(a, b) assert_eq_int_t(PRIu64, a, b)
#define assert_eq_size_t(a, b) assert_eq_int_t("zu", a, b)

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_modify_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_col_modify_pack__fmt(session, logrec, fileid, recno, value), 0);
    assert_eq_int(
      __wt_logop_col_modify_pack__direct(session, &logrec_direct, fileid, recno, value), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_modify_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    uint64_t recno_direct;
    WT_ITEM value_direct;

    pp_direct = *pp;

    WT_CLEAR(value_direct);
    WT_ASSERT(session, __wt_buf_init(session, &value_direct, 0) == 0);

    ret_fmt = __wt_logop_col_modify_unpack__fmt(session, pp, end, fileidp, recnop, valuep);
    ret_direct = __wt_logop_col_modify_unpack__direct(
      session, &pp_direct, end, &fileid_direct, &recno_direct, &value_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_uint64_t(*recnop, recno_direct);
        assert_eq_size_t(valuep->size, value_direct.size);
        WT_ASSERT(session, memcmp(valuep->data, value_direct.data, valuep->size) == 0);
    }

    __wt_buf_free(session, &value_direct);

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_put_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_col_put_pack__fmt(session, logrec, fileid, recno, value), 0);
    assert_eq_int(
      __wt_logop_col_put_pack__direct(session, &logrec_direct, fileid, recno, value), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_put_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    uint64_t recno_direct;
    WT_ITEM value_direct;

    pp_direct = *pp;

    WT_CLEAR(value_direct);
    WT_ASSERT(session, __wt_buf_init(session, &value_direct, 0) == 0);

    ret_fmt = __wt_logop_col_put_unpack__fmt(session, pp, end, fileidp, recnop, valuep);
    ret_direct = __wt_logop_col_put_unpack__direct(
      session, &pp_direct, end, &fileid_direct, &recno_direct, &value_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_uint64_t(*recnop, recno_direct);
        assert_eq_size_t(valuep->size, value_direct.size);
        WT_ASSERT(session, memcmp(valuep->data, value_direct.data, valuep->size) == 0);
    }

    __wt_buf_free(session, &value_direct);

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_remove_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_col_remove_pack__fmt(session, logrec, fileid, recno), 0);
    assert_eq_int(__wt_logop_col_remove_pack__direct(session, &logrec_direct, fileid, recno), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_remove_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, uint64_t *recnop)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    uint64_t recno_direct;

    pp_direct = *pp;

    ret_fmt = __wt_logop_col_remove_unpack__fmt(session, pp, end, fileidp, recnop);
    ret_direct =
      __wt_logop_col_remove_unpack__direct(session, &pp_direct, end, &fileid_direct, &recno_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_uint64_t(*recnop, recno_direct);
    }

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_truncate_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t start, uint64_t stop)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_col_truncate_pack__fmt(session, logrec, fileid, start, stop), 0);
    assert_eq_int(
      __wt_logop_col_truncate_pack__direct(session, &logrec_direct, fileid, start, stop), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_col_truncate_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, uint64_t *startp, uint64_t *stopp)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    uint64_t start_direct;
    uint64_t stop_direct;

    pp_direct = *pp;

    ret_fmt = __wt_logop_col_truncate_unpack__fmt(session, pp, end, fileidp, startp, stopp);
    ret_direct = __wt_logop_col_truncate_unpack__direct(
      session, &pp_direct, end, &fileid_direct, &start_direct, &stop_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_uint64_t(*startp, start_direct);
        assert_eq_uint64_t(*stopp, stop_direct);
    }

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_modify_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_row_modify_pack__fmt(session, logrec, fileid, key, value), 0);
    assert_eq_int(
      __wt_logop_row_modify_pack__direct(session, &logrec_direct, fileid, key, value), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_modify_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    WT_ITEM key_direct;
    WT_ITEM value_direct;

    pp_direct = *pp;

    WT_CLEAR(key_direct);
    WT_ASSERT(session, __wt_buf_init(session, &key_direct, 0) == 0);
    WT_CLEAR(value_direct);
    WT_ASSERT(session, __wt_buf_init(session, &value_direct, 0) == 0);

    ret_fmt = __wt_logop_row_modify_unpack__fmt(session, pp, end, fileidp, keyp, valuep);
    ret_direct = __wt_logop_row_modify_unpack__direct(
      session, &pp_direct, end, &fileid_direct, &key_direct, &value_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_size_t(keyp->size, key_direct.size);
        WT_ASSERT(session, memcmp(keyp->data, key_direct.data, keyp->size) == 0);
        assert_eq_size_t(valuep->size, value_direct.size);
        WT_ASSERT(session, memcmp(valuep->data, value_direct.data, valuep->size) == 0);
    }

    __wt_buf_free(session, &key_direct);
    __wt_buf_free(session, &value_direct);

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_put_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_row_put_pack__fmt(session, logrec, fileid, key, value), 0);
    assert_eq_int(__wt_logop_row_put_pack__direct(session, &logrec_direct, fileid, key, value), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_put_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    WT_ITEM key_direct;
    WT_ITEM value_direct;

    pp_direct = *pp;

    WT_CLEAR(key_direct);
    WT_ASSERT(session, __wt_buf_init(session, &key_direct, 0) == 0);
    WT_CLEAR(value_direct);
    WT_ASSERT(session, __wt_buf_init(session, &value_direct, 0) == 0);

    ret_fmt = __wt_logop_row_put_unpack__fmt(session, pp, end, fileidp, keyp, valuep);
    ret_direct = __wt_logop_row_put_unpack__direct(
      session, &pp_direct, end, &fileid_direct, &key_direct, &value_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_size_t(keyp->size, key_direct.size);
        WT_ASSERT(session, memcmp(keyp->data, key_direct.data, keyp->size) == 0);
        assert_eq_size_t(valuep->size, value_direct.size);
        WT_ASSERT(session, memcmp(valuep->data, value_direct.data, valuep->size) == 0);
    }

    __wt_buf_free(session, &key_direct);
    __wt_buf_free(session, &value_direct);

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_remove_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_row_remove_pack__fmt(session, logrec, fileid, key), 0);
    assert_eq_int(__wt_logop_row_remove_pack__direct(session, &logrec_direct, fileid, key), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_remove_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, WT_ITEM *keyp)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    WT_ITEM key_direct;

    pp_direct = *pp;

    WT_CLEAR(key_direct);
    WT_ASSERT(session, __wt_buf_init(session, &key_direct, 0) == 0);

    ret_fmt = __wt_logop_row_remove_unpack__fmt(session, pp, end, fileidp, keyp);
    ret_direct =
      __wt_logop_row_remove_unpack__direct(session, &pp_direct, end, &fileid_direct, &key_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_size_t(keyp->size, key_direct.size);
        WT_ASSERT(session, memcmp(keyp->data, key_direct.data, keyp->size) == 0);
    }

    __wt_buf_free(session, &key_direct);

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_truncate_pack__mirror(WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid,
  WT_ITEM *start, WT_ITEM *stop, uint32_t mode)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_row_truncate_pack__fmt(session, logrec, fileid, start, stop, mode), 0);
    assert_eq_int(
      __wt_logop_row_truncate_pack__direct(session, &logrec_direct, fileid, start, stop, mode), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_row_truncate_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, WT_ITEM *startp, WT_ITEM *stopp, uint32_t *modep)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t fileid_direct;
    WT_ITEM start_direct;
    WT_ITEM stop_direct;
    uint32_t mode_direct;

    pp_direct = *pp;

    WT_CLEAR(start_direct);
    WT_ASSERT(session, __wt_buf_init(session, &start_direct, 0) == 0);
    WT_CLEAR(stop_direct);
    WT_ASSERT(session, __wt_buf_init(session, &stop_direct, 0) == 0);

    ret_fmt = __wt_logop_row_truncate_unpack__fmt(session, pp, end, fileidp, startp, stopp, modep);
    ret_direct = __wt_logop_row_truncate_unpack__direct(
      session, &pp_direct, end, &fileid_direct, &start_direct, &stop_direct, &mode_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*fileidp, fileid_direct);
        assert_eq_size_t(startp->size, start_direct.size);
        WT_ASSERT(session, memcmp(startp->data, start_direct.data, startp->size) == 0);
        assert_eq_size_t(stopp->size, stop_direct.size);
        WT_ASSERT(session, memcmp(stopp->data, stop_direct.data, stopp->size) == 0);
        assert_eq_uint32_t(*modep, mode_direct);
    }

    __wt_buf_free(session, &start_direct);
    __wt_buf_free(session, &stop_direct);

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_checkpoint_start_pack__mirror(WT_SESSION_IMPL *session, WT_ITEM *logrec)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_checkpoint_start_pack__fmt(session, logrec), 0);
    assert_eq_int(__wt_logop_checkpoint_start_pack__direct(session, &logrec_direct), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_checkpoint_start_unpack__mirror(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;

    pp_direct = *pp;

    ret_fmt = __wt_logop_checkpoint_start_unpack__fmt(session, pp, end);
    ret_direct = __wt_logop_checkpoint_start_unpack__direct(session, &pp_direct, end);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
    }

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_prev_lsn_pack__mirror(WT_SESSION_IMPL *session, WT_ITEM *logrec, WT_LSN *prev_lsn)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_prev_lsn_pack__fmt(session, logrec, prev_lsn), 0);
    assert_eq_int(__wt_logop_prev_lsn_pack__direct(session, &logrec_direct, prev_lsn), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_prev_lsn_unpack__mirror(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_LSN *prev_lsnp)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    WT_LSN prev_lsn_direct;

    pp_direct = *pp;

    ret_fmt = __wt_logop_prev_lsn_unpack__fmt(session, pp, end, prev_lsnp);
    ret_direct = __wt_logop_prev_lsn_unpack__direct(session, &pp_direct, end, &prev_lsn_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        WT_ASSERT(session, prev_lsnp->l.file == prev_lsn_direct.l.file);
        WT_ASSERT(session, prev_lsnp->l.offset == prev_lsn_direct.l.offset);
    }

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_backup_id_pack__mirror(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t index, uint64_t granularity, const char *id)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_backup_id_pack__fmt(session, logrec, index, granularity, id), 0);
    assert_eq_int(
      __wt_logop_backup_id_pack__direct(session, &logrec_direct, index, granularity, id), 0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_backup_id_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *indexp, uint64_t *granularityp, const char **idp)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint32_t index_direct;
    uint64_t granularity_direct;
    const char *id_direct;

    pp_direct = *pp;

    ret_fmt = __wt_logop_backup_id_unpack__fmt(session, pp, end, indexp, granularityp, idp);
    ret_direct = __wt_logop_backup_id_unpack__direct(
      session, &pp_direct, end, &index_direct, &granularity_direct, &id_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint32_t(*indexp, index_direct);
        assert_eq_uint64_t(*granularityp, granularity_direct);
        WT_ASSERT(session, !strcmp(*idp, id_direct));
    }

    return (ret_fmt);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_txn_timestamp_pack__mirror(WT_SESSION_IMPL *session, WT_ITEM *logrec, uint64_t time_sec,
  uint64_t time_nsec, uint64_t commit_ts, uint64_t durable_ts, uint64_t first_commit_ts,
  uint64_t prepare_ts, uint64_t read_ts)
{
    size_t size_fmt_orig, size_fmt, size_direct;
    WT_ITEM logrec_direct;

    size_fmt_orig = logrec->size;
    WT_CLEAR(logrec_direct);
    WT_ASSERT(session, __wt_buf_init(session, &logrec_direct, 0) == 0);

    assert_eq_int(__wt_logop_txn_timestamp_pack__fmt(session, logrec, time_sec, time_nsec,
                    commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts),
      0);
    assert_eq_int(__wt_logop_txn_timestamp_pack__direct(session, &logrec_direct, time_sec,
                    time_nsec, commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts),
      0);

    size_fmt = logrec->size - size_fmt_orig;
    size_direct = logrec_direct.size;
    assert_eq_size_t(size_fmt, size_direct);
    assert_eq_int(memcmp((uint8_t *)logrec->data + size_fmt_orig, logrec_direct.data, size_fmt), 0);

    __wt_buf_free(session, &logrec_direct);
    return (0);
}

WT_ATTRIBUTE_UNUSED
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static int
__wt_logop_txn_timestamp_unpack__mirror(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint64_t *time_secp, uint64_t *time_nsecp, uint64_t *commit_tsp,
  uint64_t *durable_tsp, uint64_t *first_commit_tsp, uint64_t *prepare_tsp, uint64_t *read_tsp)
{
    int ret_fmt, ret_direct;
    const uint8_t *pp_direct;
    uint64_t time_sec_direct;
    uint64_t time_nsec_direct;
    uint64_t commit_ts_direct;
    uint64_t durable_ts_direct;
    uint64_t first_commit_ts_direct;
    uint64_t prepare_ts_direct;
    uint64_t read_ts_direct;

    pp_direct = *pp;

    ret_fmt = __wt_logop_txn_timestamp_unpack__fmt(session, pp, end, time_secp, time_nsecp,
      commit_tsp, durable_tsp, first_commit_tsp, prepare_tsp, read_tsp);
    ret_direct = __wt_logop_txn_timestamp_unpack__direct(session, &pp_direct, end, &time_sec_direct,
      &time_nsec_direct, &commit_ts_direct, &durable_ts_direct, &first_commit_ts_direct,
      &prepare_ts_direct, &read_ts_direct);

    assert_eq_int(ret_fmt, ret_direct);

    if (ret_fmt == 0 && ret_direct == 0) {
        assert_eq_size_t(WT_PTRDIFF(*pp, pp_direct), WT_PTRDIFF(pp_direct, *pp));
        assert_eq_uint64_t(*time_secp, time_sec_direct);
        assert_eq_uint64_t(*time_nsecp, time_nsec_direct);
        assert_eq_uint64_t(*commit_tsp, commit_ts_direct);
        assert_eq_uint64_t(*durable_tsp, durable_ts_direct);
        assert_eq_uint64_t(*first_commit_tsp, first_commit_ts_direct);
        assert_eq_uint64_t(*prepare_tsp, prepare_ts_direct);
        assert_eq_uint64_t(*read_tsp, read_ts_direct);
    }

    return (ret_fmt);
}
