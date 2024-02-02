/* DO NOT EDIT: automatically built by log_auto-test-gen.sh */

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

#ifdef WT_STRUCT_PACKING_DIRECT
#define __logrec_make_hex_str __logrec_make_hex_str__direct
#define __logrec_make_json_str __logrec_make_json_str__direct
#define __pack_decode__WT_ITEM __pack_decode__WT_ITEM__direct
#define __pack_decode__WT_ITEM_last __pack_decode__WT_ITEM_last__direct
#define __pack_decode__string __pack_decode__string__direct
#define __pack_decode__uintAny __pack_decode__uintAny__direct
#define __pack_encode__WT_ITEM __pack_encode__WT_ITEM__direct
#define __pack_encode__WT_ITEM_last __pack_encode__WT_ITEM_last__direct
#define __pack_encode__string __pack_encode__string__direct
#define __pack_encode__uintAny __pack_encode__uintAny__direct
#define __wt_logop_backup_id_pack __wt_logop_backup_id_pack__direct
#define __wt_logop_backup_id_print __wt_logop_backup_id_print__direct
#define __wt_logop_backup_id_unpack __wt_logop_backup_id_unpack__direct
#define __wt_logop_checkpoint_start_pack __wt_logop_checkpoint_start_pack__direct
#define __wt_logop_checkpoint_start_print __wt_logop_checkpoint_start_print__direct
#define __wt_logop_checkpoint_start_unpack __wt_logop_checkpoint_start_unpack__direct
#define __wt_logop_col_modify_pack __wt_logop_col_modify_pack__direct
#define __wt_logop_col_modify_print __wt_logop_col_modify_print__direct
#define __wt_logop_col_modify_unpack __wt_logop_col_modify_unpack__direct
#define __wt_logop_col_put_pack __wt_logop_col_put_pack__direct
#define __wt_logop_col_put_print __wt_logop_col_put_print__direct
#define __wt_logop_col_put_unpack __wt_logop_col_put_unpack__direct
#define __wt_logop_col_remove_pack __wt_logop_col_remove_pack__direct
#define __wt_logop_col_remove_print __wt_logop_col_remove_print__direct
#define __wt_logop_col_remove_unpack __wt_logop_col_remove_unpack__direct
#define __wt_logop_col_truncate_pack __wt_logop_col_truncate_pack__direct
#define __wt_logop_col_truncate_print __wt_logop_col_truncate_print__direct
#define __wt_logop_col_truncate_unpack __wt_logop_col_truncate_unpack__direct
#define __wt_logop_prev_lsn_pack __wt_logop_prev_lsn_pack__direct
#define __wt_logop_prev_lsn_print __wt_logop_prev_lsn_print__direct
#define __wt_logop_prev_lsn_unpack __wt_logop_prev_lsn_unpack__direct
#define __wt_logop_read __wt_logop_read__direct
#define __wt_logop_row_modify_pack __wt_logop_row_modify_pack__direct
#define __wt_logop_row_modify_print __wt_logop_row_modify_print__direct
#define __wt_logop_row_modify_unpack __wt_logop_row_modify_unpack__direct
#define __wt_logop_row_put_pack __wt_logop_row_put_pack__direct
#define __wt_logop_row_put_print __wt_logop_row_put_print__direct
#define __wt_logop_row_put_unpack __wt_logop_row_put_unpack__direct
#define __wt_logop_row_remove_pack __wt_logop_row_remove_pack__direct
#define __wt_logop_row_remove_print __wt_logop_row_remove_print__direct
#define __wt_logop_row_remove_unpack __wt_logop_row_remove_unpack__direct
#define __wt_logop_row_truncate_pack __wt_logop_row_truncate_pack__direct
#define __wt_logop_row_truncate_print __wt_logop_row_truncate_print__direct
#define __wt_logop_row_truncate_unpack __wt_logop_row_truncate_unpack__direct
#define __wt_logop_txn_timestamp_pack __wt_logop_txn_timestamp_pack__direct
#define __wt_logop_txn_timestamp_print __wt_logop_txn_timestamp_print__direct
#define __wt_logop_txn_timestamp_unpack __wt_logop_txn_timestamp_unpack__direct
#define __wt_logop_unpack __wt_logop_unpack__direct
#define __wt_logop_write __wt_logop_write__direct
#define __wt_logrec_alloc __wt_logrec_alloc__direct
#define __wt_logrec_free __wt_logrec_free__direct
#define __wt_logrec_read __wt_logrec_read__direct
#define __wt_struct_pack_backup_id __wt_struct_pack_backup_id__direct
#define __wt_struct_pack_checkpoint_start __wt_struct_pack_checkpoint_start__direct
#define __wt_struct_pack_col_modify __wt_struct_pack_col_modify__direct
#define __wt_struct_pack_col_put __wt_struct_pack_col_put__direct
#define __wt_struct_pack_col_remove __wt_struct_pack_col_remove__direct
#define __wt_struct_pack_col_truncate __wt_struct_pack_col_truncate__direct
#define __wt_struct_pack_prev_lsn __wt_struct_pack_prev_lsn__direct
#define __wt_struct_pack_row_modify __wt_struct_pack_row_modify__direct
#define __wt_struct_pack_row_put __wt_struct_pack_row_put__direct
#define __wt_struct_pack_row_remove __wt_struct_pack_row_remove__direct
#define __wt_struct_pack_row_truncate __wt_struct_pack_row_truncate__direct
#define __wt_struct_pack_txn_timestamp __wt_struct_pack_txn_timestamp__direct
#define __wt_struct_size_backup_id __wt_struct_size_backup_id__direct
#define __wt_struct_size_checkpoint_start __wt_struct_size_checkpoint_start__direct
#define __wt_struct_size_col_modify __wt_struct_size_col_modify__direct
#define __wt_struct_size_col_put __wt_struct_size_col_put__direct
#define __wt_struct_size_col_remove __wt_struct_size_col_remove__direct
#define __wt_struct_size_col_truncate __wt_struct_size_col_truncate__direct
#define __wt_struct_size_prev_lsn __wt_struct_size_prev_lsn__direct
#define __wt_struct_size_row_modify __wt_struct_size_row_modify__direct
#define __wt_struct_size_row_put __wt_struct_size_row_put__direct
#define __wt_struct_size_row_remove __wt_struct_size_row_remove__direct
#define __wt_struct_size_row_truncate __wt_struct_size_row_truncate__direct
#define __wt_struct_size_txn_timestamp __wt_struct_size_txn_timestamp__direct
#define __wt_struct_unpack_backup_id __wt_struct_unpack_backup_id__direct
#define __wt_struct_unpack_checkpoint_start __wt_struct_unpack_checkpoint_start__direct
#define __wt_struct_unpack_col_modify __wt_struct_unpack_col_modify__direct
#define __wt_struct_unpack_col_put __wt_struct_unpack_col_put__direct
#define __wt_struct_unpack_col_remove __wt_struct_unpack_col_remove__direct
#define __wt_struct_unpack_col_truncate __wt_struct_unpack_col_truncate__direct
#define __wt_struct_unpack_prev_lsn __wt_struct_unpack_prev_lsn__direct
#define __wt_struct_unpack_row_modify __wt_struct_unpack_row_modify__direct
#define __wt_struct_unpack_row_put __wt_struct_unpack_row_put__direct
#define __wt_struct_unpack_row_remove __wt_struct_unpack_row_remove__direct
#define __wt_struct_unpack_row_truncate __wt_struct_unpack_row_truncate__direct
#define __wt_struct_unpack_txn_timestamp __wt_struct_unpack_txn_timestamp__direct
#define __wt_txn_op_printlog __wt_txn_op_printlog__direct
#endif
/* DO NOT EDIT: automatically built by dist/log.py. */

#include "../../src/include/wt_internal.h"

#define WT_SIZE_CHECK_PACK_PTR(p, end) WT_RET_TEST(!(p) || !(end) || (p) >= (end), ENOMEM)
#define WT_SIZE_CHECK_UNPACK_PTR(p, end) WT_RET_TEST(!(p) || !(end) || (p) >= (end), EINVAL)
#define WT_SIZE_CHECK_UNPACK_PTR0(p, end) WT_RET_TEST(!(p) || !(end) || (p) > (end), EINVAL)

#ifndef WT_CHECK_OPTYPE
#define WT_CHECK_OPTYPE(session, opvar, op) \
    if (opvar != op)                        \
        WT_RET_MSG(session, EINVAL, "unpacking " #op ": optype mismatch");
#endif

/*
 * __pack_encode__uintAny__direct --
 *     Pack an unsigned integer.
 */
static inline int
__pack_encode__uintAny__direct(uint8_t **pp, uint8_t *end, uint64_t item)
{
    /* Check that there is at least one byte available:
     * the low-level routines treat zero length as unchecked. */
    WT_SIZE_CHECK_PACK_PTR(*pp, end);
    return (__wt_vpack_uint(pp, WT_PTRDIFF(end, *pp), item));
}

/*
 * __pack_encode__WT_ITEM__direct --
 *     Pack a WT_ITEM structure - size and WT_ITEM.
 */
static inline int
__pack_encode__WT_ITEM__direct(uint8_t **pp, uint8_t *end, WT_ITEM *item)
{
    WT_RET(__wt_vpack_uint(pp, WT_PTRDIFF(end, *pp), item->size));
    WT_SIZE_CHECK_PACK(item->size, WT_PTRDIFF(end, *pp));
    memcpy(*pp, item->data, item->size);
    *pp += item->size;
    return (0);
}

/*
 * __pack_encode__WT_ITEM_last__direct --
 *     Pack a WT_ITEM structure without its size.
 */
static inline int
__pack_encode__WT_ITEM_last__direct(uint8_t **pp, uint8_t *end, WT_ITEM *item)
{
    WT_SIZE_CHECK_PACK(item->size, WT_PTRDIFF(end, *pp));
    memcpy(*pp, item->data, item->size);
    *pp += item->size;
    return (0);
}

/*
 * __pack_encode__string__direct --
 *     Pack a string.
 */
static inline int
__pack_encode__string__direct(uint8_t **pp, uint8_t *end, const char *item)
{
    size_t s, sz;

    sz = WT_PTRDIFF(end, *pp);
    s = __wt_strnlen(item, sz - 1);
    WT_SIZE_CHECK_PACK(s + 1, sz);
    memcpy(*pp, item, s);
    *pp += s;
    **pp = '\0';
    *pp += 1;
    return (0);
}

#define __pack_decode__uintAny__direct(TYPE, pval)                                             \
    do {                                                                                       \
        uint64_t v; /* Check that there is at least one byte available: the low-level routines \
                       treat zero length as unchecked. */                                      \
        WT_SIZE_CHECK_UNPACK_PTR(*pp, end);                                                    \
        WT_RET(__wt_vunpack_uint(pp, WT_PTRDIFF(end, *pp), &v));                               \
        *(pval) = (TYPE)v;                                                                     \
    } while (0)

#define __pack_decode__WT_ITEM__direct(val)                    \
    do {                                                       \
        __pack_decode__uintAny__direct(size_t, &val->size);    \
        WT_SIZE_CHECK_UNPACK(val->size, WT_PTRDIFF(end, *pp)); \
        val->data = *pp;                                       \
        *pp += val->size;                                      \
    } while (0)

#define __pack_decode__WT_ITEM_last__direct(val) \
    do {                                         \
        WT_SIZE_CHECK_UNPACK_PTR0(*pp, end);     \
        val->size = WT_PTRDIFF(end, *pp);        \
        val->data = *pp;                         \
        *pp += val->size;                        \
    } while (0)

#define __pack_decode__string__direct(val)             \
    do {                                               \
        size_t s;                                      \
        *val = (const char *)*pp;                      \
        s = strlen((const char *)*pp) + 1;             \
        WT_SIZE_CHECK_UNPACK(s, WT_PTRDIFF(end, *pp)); \
        *pp += s;                                      \
    } while (0)

/*
 * __wt_logrec_alloc__direct --
 *     Allocate a new WT_ITEM structure.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logrec_alloc__direct(WT_SESSION_IMPL *session, size_t size, WT_ITEM **logrecp)
{
    WT_ITEM *logrec;
    WT_LOG *log;
    size_t allocsize;

    log = S2C(session)->log;
    allocsize = log == NULL ? WT_LOG_ALIGN : log->allocsize;
    WT_RET(__wt_scr_alloc(session, WT_ALIGN(size + 1, allocsize), &logrec));
    WT_CLEAR(*(WT_LOG_RECORD *)logrec->data);
    logrec->size = offsetof(WT_LOG_RECORD, record);

    *logrecp = logrec;
    return (0);
}

/*
 * __wt_logrec_free__direct --
 *     Free the given WT_ITEM structure.
 */
WT_ATTRIBUTE_UNUSED
static void
__wt_logrec_free__direct(WT_SESSION_IMPL *session, WT_ITEM **logrecp)
{
    __wt_scr_free(session, logrecp);
}

/*
 * __wt_logrec_read__direct --
 *     Read the record type.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logrec_read__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, uint32_t *rectypep)
{
    WT_UNUSED(session);
    __pack_decode__uintAny__direct(uint32_t, rectypep);
    return (0);
}

/*
 * __wt_logop_read__direct --
 *     Peek at the operation type.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_read__direct(WT_SESSION_IMPL *session, const uint8_t **pp2, const uint8_t *end,
  uint32_t *optypep, uint32_t *opsizep)
{
    const uint8_t *p, **pp;
    WT_UNUSED(session);

    p = *pp2;
    pp = &p;
    __pack_decode__uintAny__direct(uint32_t, optypep);
    __pack_decode__uintAny__direct(uint32_t, opsizep);
    return (0);
}

/*
 * __wt_logop_unpack__direct --
 *     Read the operation type.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *optypep, uint32_t *opsizep)
{
    WT_UNUSED(session);
    __pack_decode__uintAny__direct(uint32_t, optypep);
    __pack_decode__uintAny__direct(uint32_t, opsizep);
    return (0);
}

/*
 * __wt_logop_write__direct --
 *     Write the operation type.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_write__direct(
  WT_SESSION_IMPL *session, uint8_t **pp, uint8_t *end, uint32_t optype, uint32_t opsize)
{
    WT_UNUSED(session);
    WT_RET(__pack_encode__uintAny__direct(pp, end, optype));
    WT_RET(__pack_encode__uintAny__direct(pp, end, opsize));
    return (0);
}

/*
 * __logrec_make_json_str__direct --
 *     Unpack a string into JSON escaped format.
 */
static int
__logrec_make_json_str__direct(WT_SESSION_IMPL *session, WT_ITEM **escapedp, WT_ITEM *item)
{
    size_t needed;

    needed = (item->size * WT_MAX_JSON_ENCODE) + 1;

    if (*escapedp == NULL)
        WT_RET(__wt_scr_alloc(session, needed, escapedp));
    else
        WT_RET(__wt_buf_grow(session, *escapedp, needed));
    WT_IGNORE_RET(__wt_json_unpack_str(
      (u_char *)(*escapedp)->mem, (*escapedp)->memsize, (const u_char *)item->data, item->size));
    return (0);
}

/*
 * __logrec_make_hex_str__direct --
 *     Convert data to a hexadecimal representation.
 */
static int
__logrec_make_hex_str__direct(WT_SESSION_IMPL *session, WT_ITEM **escapedp, WT_ITEM *item)
{
    size_t needed;

    needed = (item->size * 2) + 1;

    if (*escapedp == NULL)
        WT_RET(__wt_scr_alloc(session, needed, escapedp));
    else
        WT_RET(__wt_buf_grow(session, *escapedp, needed));
    __wt_fill_hex((const uint8_t *)item->data, item->size, (uint8_t *)(*escapedp)->mem,
      (*escapedp)->memsize, NULL);
    return (0);
}

/*
 * __wt_struct_size_col_modify__direct --
 *     Calculate size of col_modify struct.
 */
static inline size_t
__wt_struct_size_col_modify__direct(uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    return (__wt_vsize_uint(fileid) + __wt_vsize_uint(recno) + value->size);
}

/*
 * __wt_struct_pack_col_modify__direct --
 *     Pack the col_modify struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_col_modify__direct(
  uint8_t **pp, uint8_t *end, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__uintAny__direct(pp, end, recno));
    WT_RET(__pack_encode__WT_ITEM_last__direct(pp, end, value));

    return (0);
}

/*
 * __wt_struct_unpack_col_modify__direct --
 *     Unpack the col_modify struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_col_modify__direct(
  const uint8_t **pp, const uint8_t *end, uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__uintAny__direct(uint64_t, recnop);
    __pack_decode__WT_ITEM_last__direct(valuep);

    return (0);
}

/*
 * __wt_logop_col_modify_pack__direct --
 *     Pack the log operation col_modify.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_modify_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_col_modify__direct(fileid, recno, value);
    size += __wt_vsize_uint(WT_LOGOP_COL_MODIFY) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_COL_MODIFY, (uint32_t)size));
    WT_RET(__wt_struct_pack_col_modify__direct(&buf, end, fileid, recno, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_modify_unpack__direct --
 *     Unpack the log operation col_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_modify_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_col_modify__direct(pp, end, fileidp, recnop, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_col_modify: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_COL_MODIFY);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_col_modify: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_col_modify_print__direct --
 *     Print the log operation col_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_modify_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_col_modify_unpack__direct(session, pp, end, &fileid, &recno, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"col_modify\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"recno\": %" PRIu64 ",\n", recno));
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_struct_size_col_put__direct --
 *     Calculate size of col_put struct.
 */
static inline size_t
__wt_struct_size_col_put__direct(uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    return (__wt_vsize_uint(fileid) + __wt_vsize_uint(recno) + value->size);
}

/*
 * __wt_struct_pack_col_put__direct --
 *     Pack the col_put struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_col_put__direct(
  uint8_t **pp, uint8_t *end, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__uintAny__direct(pp, end, recno));
    WT_RET(__pack_encode__WT_ITEM_last__direct(pp, end, value));

    return (0);
}

/*
 * __wt_struct_unpack_col_put__direct --
 *     Unpack the col_put struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_col_put__direct(
  const uint8_t **pp, const uint8_t *end, uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__uintAny__direct(uint64_t, recnop);
    __pack_decode__WT_ITEM_last__direct(valuep);

    return (0);
}

/*
 * __wt_logop_col_put_pack__direct --
 *     Pack the log operation col_put.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_put_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_col_put__direct(fileid, recno, value);
    size += __wt_vsize_uint(WT_LOGOP_COL_PUT) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_COL_PUT, (uint32_t)size));
    WT_RET(__wt_struct_pack_col_put__direct(&buf, end, fileid, recno, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_put_unpack__direct --
 *     Unpack the log operation col_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_put_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_col_put__direct(pp, end, fileidp, recnop, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_col_put: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_COL_PUT);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_col_put: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_col_put_print__direct --
 *     Print the log operation col_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_put_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_col_put_unpack__direct(session, pp, end, &fileid, &recno, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"col_put\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"recno\": %" PRIu64 ",\n", recno));
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_struct_size_col_remove__direct --
 *     Calculate size of col_remove struct.
 */
static inline size_t
__wt_struct_size_col_remove__direct(uint32_t fileid, uint64_t recno)
{
    return (__wt_vsize_uint(fileid) + __wt_vsize_uint(recno));
}

/*
 * __wt_struct_pack_col_remove__direct --
 *     Pack the col_remove struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_col_remove__direct(uint8_t **pp, uint8_t *end, uint32_t fileid, uint64_t recno)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__uintAny__direct(pp, end, recno));

    return (0);
}

/*
 * __wt_struct_unpack_col_remove__direct --
 *     Unpack the col_remove struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_col_remove__direct(
  const uint8_t **pp, const uint8_t *end, uint32_t *fileidp, uint64_t *recnop)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__uintAny__direct(uint64_t, recnop);

    return (0);
}

/*
 * __wt_logop_col_remove_pack__direct --
 *     Pack the log operation col_remove.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_remove_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_col_remove__direct(fileid, recno);
    size += __wt_vsize_uint(WT_LOGOP_COL_REMOVE) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_COL_REMOVE, (uint32_t)size));
    WT_RET(__wt_struct_pack_col_remove__direct(&buf, end, fileid, recno));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_remove_unpack__direct --
 *     Unpack the log operation col_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_remove_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, uint64_t *recnop)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_col_remove__direct(pp, end, fileidp, recnop)) != 0)
        WT_RET_MSG(session, ret, "logop_col_remove: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_COL_REMOVE);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_col_remove: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_col_remove_print__direct --
 *     Print the log operation col_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_remove_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t fileid;
    uint64_t recno;

    WT_RET(__wt_logop_col_remove_unpack__direct(session, pp, end, &fileid, &recno));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"col_remove\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_RET(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_RET(__wt_fprintf(session, args->fs, "        \"recno\": %" PRIu64 "", recno));
    return (0);
}

/*
 * __wt_struct_size_col_truncate__direct --
 *     Calculate size of col_truncate struct.
 */
static inline size_t
__wt_struct_size_col_truncate__direct(uint32_t fileid, uint64_t start, uint64_t stop)
{
    return (__wt_vsize_uint(fileid) + __wt_vsize_uint(start) + __wt_vsize_uint(stop));
}

/*
 * __wt_struct_pack_col_truncate__direct --
 *     Pack the col_truncate struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_col_truncate__direct(
  uint8_t **pp, uint8_t *end, uint32_t fileid, uint64_t start, uint64_t stop)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__uintAny__direct(pp, end, start));
    WT_RET(__pack_encode__uintAny__direct(pp, end, stop));

    return (0);
}

/*
 * __wt_struct_unpack_col_truncate__direct --
 *     Unpack the col_truncate struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_col_truncate__direct(
  const uint8_t **pp, const uint8_t *end, uint32_t *fileidp, uint64_t *startp, uint64_t *stopp)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__uintAny__direct(uint64_t, startp);
    __pack_decode__uintAny__direct(uint64_t, stopp);

    return (0);
}

/*
 * __wt_logop_col_truncate_pack__direct --
 *     Pack the log operation col_truncate.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_truncate_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t start, uint64_t stop)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_col_truncate__direct(fileid, start, stop);
    size += __wt_vsize_uint(WT_LOGOP_COL_TRUNCATE) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_COL_TRUNCATE, (uint32_t)size));
    WT_RET(__wt_struct_pack_col_truncate__direct(&buf, end, fileid, start, stop));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_truncate_unpack__direct --
 *     Unpack the log operation col_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_truncate_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, uint64_t *startp, uint64_t *stopp)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_col_truncate__direct(pp, end, fileidp, startp, stopp)) != 0)
        WT_RET_MSG(session, ret, "logop_col_truncate: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_COL_TRUNCATE);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_col_truncate: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_col_truncate_print__direct --
 *     Print the log operation col_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_truncate_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t fileid;
    uint64_t start;
    uint64_t stop;

    WT_RET(__wt_logop_col_truncate_unpack__direct(session, pp, end, &fileid, &start, &stop));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"col_truncate\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_RET(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_RET(__wt_fprintf(session, args->fs, "        \"start\": %" PRIu64 ",\n", start));
    WT_RET(__wt_fprintf(session, args->fs, "        \"stop\": %" PRIu64 "", stop));
    return (0);
}

/*
 * __wt_struct_size_row_modify__direct --
 *     Calculate size of row_modify struct.
 */
static inline size_t
__wt_struct_size_row_modify__direct(uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    return (__wt_vsize_uint(fileid) + __wt_vsize_uint(key->size) + key->size + value->size);
}

/*
 * __wt_struct_pack_row_modify__direct --
 *     Pack the row_modify struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_row_modify__direct(
  uint8_t **pp, uint8_t *end, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__WT_ITEM__direct(pp, end, key));
    WT_RET(__pack_encode__WT_ITEM_last__direct(pp, end, value));

    return (0);
}

/*
 * __wt_struct_unpack_row_modify__direct --
 *     Unpack the row_modify struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_row_modify__direct(
  const uint8_t **pp, const uint8_t *end, uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__WT_ITEM__direct(keyp);
    __pack_decode__WT_ITEM_last__direct(valuep);

    return (0);
}

/*
 * __wt_logop_row_modify_pack__direct --
 *     Pack the log operation row_modify.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_modify_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_row_modify__direct(fileid, key, value);
    size += __wt_vsize_uint(WT_LOGOP_ROW_MODIFY) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_ROW_MODIFY, (uint32_t)size));
    WT_RET(__wt_struct_pack_row_modify__direct(&buf, end, fileid, key, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_modify_unpack__direct --
 *     Unpack the log operation row_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_modify_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_row_modify__direct(pp, end, fileidp, keyp, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_row_modify: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_ROW_MODIFY);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_row_modify: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_row_modify_print__direct --
 *     Print the log operation row_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_modify_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_modify_unpack__direct(session, pp, end, &fileid, &key, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_modify\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &key));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"key\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &key));
        WT_ERR(
          __wt_fprintf(session, args->fs, "        \"key-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_struct_size_row_put__direct --
 *     Calculate size of row_put struct.
 */
static inline size_t
__wt_struct_size_row_put__direct(uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    return (__wt_vsize_uint(fileid) + __wt_vsize_uint(key->size) + key->size + value->size);
}

/*
 * __wt_struct_pack_row_put__direct --
 *     Pack the row_put struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_row_put__direct(
  uint8_t **pp, uint8_t *end, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__WT_ITEM__direct(pp, end, key));
    WT_RET(__pack_encode__WT_ITEM_last__direct(pp, end, value));

    return (0);
}

/*
 * __wt_struct_unpack_row_put__direct --
 *     Unpack the row_put struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_row_put__direct(
  const uint8_t **pp, const uint8_t *end, uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__WT_ITEM__direct(keyp);
    __pack_decode__WT_ITEM_last__direct(valuep);

    return (0);
}

/*
 * __wt_logop_row_put_pack__direct --
 *     Pack the log operation row_put.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_put_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_row_put__direct(fileid, key, value);
    size += __wt_vsize_uint(WT_LOGOP_ROW_PUT) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_ROW_PUT, (uint32_t)size));
    WT_RET(__wt_struct_pack_row_put__direct(&buf, end, fileid, key, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_put_unpack__direct --
 *     Unpack the log operation row_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_put_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_row_put__direct(pp, end, fileidp, keyp, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_row_put: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_ROW_PUT);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_row_put: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_row_put_print__direct --
 *     Print the log operation row_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_put_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_put_unpack__direct(session, pp, end, &fileid, &key, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_put\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &key));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"key\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &key));
        WT_ERR(
          __wt_fprintf(session, args->fs, "        \"key-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_struct_size_row_remove__direct --
 *     Calculate size of row_remove struct.
 */
static inline size_t
__wt_struct_size_row_remove__direct(uint32_t fileid, WT_ITEM *key)
{
    return (__wt_vsize_uint(fileid) + key->size);
}

/*
 * __wt_struct_pack_row_remove__direct --
 *     Pack the row_remove struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_row_remove__direct(uint8_t **pp, uint8_t *end, uint32_t fileid, WT_ITEM *key)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__WT_ITEM_last__direct(pp, end, key));

    return (0);
}

/*
 * __wt_struct_unpack_row_remove__direct --
 *     Unpack the row_remove struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_row_remove__direct(
  const uint8_t **pp, const uint8_t *end, uint32_t *fileidp, WT_ITEM *keyp)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__WT_ITEM_last__direct(keyp);

    return (0);
}

/*
 * __wt_logop_row_remove_pack__direct --
 *     Pack the log operation row_remove.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_remove_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_row_remove__direct(fileid, key);
    size += __wt_vsize_uint(WT_LOGOP_ROW_REMOVE) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_ROW_REMOVE, (uint32_t)size));
    WT_RET(__wt_struct_pack_row_remove__direct(&buf, end, fileid, key));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_remove_unpack__direct --
 *     Unpack the log operation row_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_remove_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, WT_ITEM *keyp)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_row_remove__direct(pp, end, fileidp, keyp)) != 0)
        WT_RET_MSG(session, ret, "logop_row_remove: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_ROW_REMOVE);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_row_remove: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_row_remove_print__direct --
 *     Print the log operation row_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_remove_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM key;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_remove_unpack__direct(session, pp, end, &fileid, &key));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_remove\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &key));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"key\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &key));
        WT_ERR(
          __wt_fprintf(session, args->fs, ",\n        \"key-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_struct_size_row_truncate__direct --
 *     Calculate size of row_truncate struct.
 */
static inline size_t
__wt_struct_size_row_truncate__direct(uint32_t fileid, WT_ITEM *start, WT_ITEM *stop, uint32_t mode)
{
    return (__wt_vsize_uint(fileid) + __wt_vsize_uint(start->size) + start->size +
      __wt_vsize_uint(stop->size) + stop->size + __wt_vsize_uint(mode));
}

/*
 * __wt_struct_pack_row_truncate__direct --
 *     Pack the row_truncate struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_row_truncate__direct(
  uint8_t **pp, uint8_t *end, uint32_t fileid, WT_ITEM *start, WT_ITEM *stop, uint32_t mode)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, fileid));
    WT_RET(__pack_encode__WT_ITEM__direct(pp, end, start));
    WT_RET(__pack_encode__WT_ITEM__direct(pp, end, stop));
    WT_RET(__pack_encode__uintAny__direct(pp, end, mode));

    return (0);
}

/*
 * __wt_struct_unpack_row_truncate__direct --
 *     Unpack the row_truncate struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_row_truncate__direct(const uint8_t **pp, const uint8_t *end, uint32_t *fileidp,
  WT_ITEM *startp, WT_ITEM *stopp, uint32_t *modep)
{
    __pack_decode__uintAny__direct(uint32_t, fileidp);
    __pack_decode__WT_ITEM__direct(startp);
    __pack_decode__WT_ITEM__direct(stopp);
    __pack_decode__uintAny__direct(uint32_t, modep);

    return (0);
}

/*
 * __wt_logop_row_truncate_pack__direct --
 *     Pack the log operation row_truncate.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_truncate_pack__direct(WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid,
  WT_ITEM *start, WT_ITEM *stop, uint32_t mode)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_row_truncate__direct(fileid, start, stop, mode);
    size += __wt_vsize_uint(WT_LOGOP_ROW_TRUNCATE) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_ROW_TRUNCATE, (uint32_t)size));
    WT_RET(__wt_struct_pack_row_truncate__direct(&buf, end, fileid, start, stop, mode));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_truncate_unpack__direct --
 *     Unpack the log operation row_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_truncate_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, WT_ITEM *startp, WT_ITEM *stopp, uint32_t *modep)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_row_truncate__direct(pp, end, fileidp, startp, stopp, modep)) != 0)
        WT_RET_MSG(session, ret, "logop_row_truncate: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_ROW_TRUNCATE);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_row_truncate: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_row_truncate_print__direct --
 *     Print the log operation row_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_truncate_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM start;
    WT_ITEM stop;
    uint32_t mode;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_truncate_unpack__direct(session, pp, end, &fileid, &start, &stop, &mode));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_truncate\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &start));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"start\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &start));
        WT_ERR(__wt_fprintf(
          session, args->fs, "        \"start-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__logrec_make_json_str__direct(session, &escaped, &stop));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"stop\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__direct(session, &escaped, &stop));
        WT_ERR(
          __wt_fprintf(session, args->fs, "        \"stop-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__wt_fprintf(session, args->fs, "        \"mode\": %" PRIu32 "", mode));

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_struct_size_checkpoint_start__direct --
 *     Calculate size of checkpoint_start struct.
 */
static inline size_t
__wt_struct_size_checkpoint_start__direct(void)
{
    return (0);
}

/*
 * __wt_struct_pack_checkpoint_start__direct --
 *     Pack the checkpoint_start struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_checkpoint_start__direct(uint8_t **pp, uint8_t *end)
{
    WT_UNUSED(pp);
    WT_UNUSED(end);
    return (0);
}

/*
 * __wt_struct_unpack_checkpoint_start__direct --
 *     Unpack the checkpoint_start struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_checkpoint_start__direct(const uint8_t **pp, const uint8_t *end)
{
    WT_UNUSED(pp);
    WT_UNUSED(end);
    return (0);
}

/*
 * __wt_logop_checkpoint_start_pack__direct --
 *     Pack the log operation checkpoint_start.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_checkpoint_start_pack__direct(WT_SESSION_IMPL *session, WT_ITEM *logrec)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_checkpoint_start__direct();
    size += __wt_vsize_uint(WT_LOGOP_CHECKPOINT_START) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_CHECKPOINT_START, (uint32_t)size));
    WT_RET(__wt_struct_pack_checkpoint_start__direct(&buf, end));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_checkpoint_start_unpack__direct --
 *     Unpack the log operation checkpoint_start.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_checkpoint_start_unpack__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_checkpoint_start__direct(pp, end)) != 0)
        WT_RET_MSG(session, ret, "logop_checkpoint_start: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_CHECKPOINT_START);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL,
          "logop_checkpoint_start: size mismatch: expected %u, got %" PRIuPTR, size,
          WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_checkpoint_start_print__direct --
 *     Print the log operation checkpoint_start.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_checkpoint_start_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{

    WT_RET(__wt_logop_checkpoint_start_unpack__direct(session, pp, end));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"checkpoint_start\"\n"));

    return (0);
}

/*
 * __wt_struct_size_prev_lsn__direct --
 *     Calculate size of prev_lsn struct.
 */
static inline size_t
__wt_struct_size_prev_lsn__direct(WT_LSN *prev_lsn)
{
    return (__wt_vsize_uint(prev_lsn->l.file) + __wt_vsize_uint(prev_lsn->l.offset));
}

/*
 * __wt_struct_pack_prev_lsn__direct --
 *     Pack the prev_lsn struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_prev_lsn__direct(uint8_t **pp, uint8_t *end, WT_LSN *prev_lsn)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, prev_lsn->l.file));
    WT_RET(__pack_encode__uintAny__direct(pp, end, prev_lsn->l.offset));

    return (0);
}

/*
 * __wt_struct_unpack_prev_lsn__direct --
 *     Unpack the prev_lsn struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_prev_lsn__direct(const uint8_t **pp, const uint8_t *end, WT_LSN *prev_lsnp)
{
    __pack_decode__uintAny__direct(uint32_t, &prev_lsnp->l.file);
    __pack_decode__uintAny__direct(uint32_t, &prev_lsnp->l.offset);

    return (0);
}

/*
 * __wt_logop_prev_lsn_pack__direct --
 *     Pack the log operation prev_lsn.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_prev_lsn_pack__direct(WT_SESSION_IMPL *session, WT_ITEM *logrec, WT_LSN *prev_lsn)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_prev_lsn__direct(prev_lsn);
    size += __wt_vsize_uint(WT_LOGOP_PREV_LSN) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_PREV_LSN, (uint32_t)size));
    WT_RET(__wt_struct_pack_prev_lsn__direct(&buf, end, prev_lsn));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_prev_lsn_unpack__direct --
 *     Unpack the log operation prev_lsn.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_prev_lsn_unpack__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_LSN *prev_lsnp)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_prev_lsn__direct(pp, end, prev_lsnp)) != 0)
        WT_RET_MSG(session, ret, "logop_prev_lsn: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_PREV_LSN);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_prev_lsn: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_prev_lsn_print__direct --
 *     Print the log operation prev_lsn.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_prev_lsn_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_LSN prev_lsn;

    WT_RET(__wt_logop_prev_lsn_unpack__direct(session, pp, end, &prev_lsn));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"prev_lsn\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"prev_lsn\": [%" PRIu32 ", %" PRIu32 "]",
      prev_lsn.l.file, prev_lsn.l.offset));
    return (0);
}

/*
 * __wt_struct_size_backup_id__direct --
 *     Calculate size of backup_id struct.
 */
static inline size_t
__wt_struct_size_backup_id__direct(uint32_t index, uint64_t granularity, const char *id)
{
    return (__wt_vsize_uint(index) + __wt_vsize_uint(granularity) + strlen(id) + 1);
}

/*
 * __wt_struct_pack_backup_id__direct --
 *     Pack the backup_id struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_backup_id__direct(
  uint8_t **pp, uint8_t *end, uint32_t index, uint64_t granularity, const char *id)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, index));
    WT_RET(__pack_encode__uintAny__direct(pp, end, granularity));
    WT_RET(__pack_encode__string__direct(pp, end, id));

    return (0);
}

/*
 * __wt_struct_unpack_backup_id__direct --
 *     Unpack the backup_id struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_backup_id__direct(const uint8_t **pp, const uint8_t *end, uint32_t *indexp,
  uint64_t *granularityp, const char **idp)
{
    __pack_decode__uintAny__direct(uint32_t, indexp);
    __pack_decode__uintAny__direct(uint64_t, granularityp);
    __pack_decode__string__direct(idp);

    return (0);
}

/*
 * __wt_logop_backup_id_pack__direct --
 *     Pack the log operation backup_id.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_backup_id_pack__direct(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t index, uint64_t granularity, const char *id)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_backup_id__direct(index, granularity, id);
    size += __wt_vsize_uint(WT_LOGOP_BACKUP_ID) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_BACKUP_ID, (uint32_t)size));
    WT_RET(__wt_struct_pack_backup_id__direct(&buf, end, index, granularity, id));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_backup_id_unpack__direct --
 *     Unpack the log operation backup_id.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_backup_id_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *indexp, uint64_t *granularityp, const char **idp)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_backup_id__direct(pp, end, indexp, granularityp, idp)) != 0)
        WT_RET_MSG(session, ret, "logop_backup_id: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_BACKUP_ID);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL, "logop_backup_id: size mismatch: expected %u, got %" PRIuPTR,
          size, WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_backup_id_print__direct --
 *     Print the log operation backup_id.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_backup_id_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t index;
    uint64_t granularity;
    const char *id;

    WT_RET(__wt_logop_backup_id_unpack__direct(session, pp, end, &index, &granularity, &id));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"backup_id\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"index\": %" PRIu32 ",\n", index));
    WT_RET(__wt_fprintf(session, args->fs, "        \"granularity\": %" PRIu64 ",\n", granularity));
    WT_RET(__wt_fprintf(session, args->fs, "        \"id\": \"%s\"", id));
    return (0);
}

/*
 * __wt_struct_size_txn_timestamp__direct --
 *     Calculate size of txn_timestamp struct.
 */
static inline size_t
__wt_struct_size_txn_timestamp__direct(uint64_t time_sec, uint64_t time_nsec, uint64_t commit_ts,
  uint64_t durable_ts, uint64_t first_commit_ts, uint64_t prepare_ts, uint64_t read_ts)
{
    return (__wt_vsize_uint(time_sec) + __wt_vsize_uint(time_nsec) + __wt_vsize_uint(commit_ts) +
      __wt_vsize_uint(durable_ts) + __wt_vsize_uint(first_commit_ts) + __wt_vsize_uint(prepare_ts) +
      __wt_vsize_uint(read_ts));
}

/*
 * __wt_struct_pack_txn_timestamp__direct --
 *     Pack the txn_timestamp struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_pack_txn_timestamp__direct(uint8_t **pp, uint8_t *end, uint64_t time_sec,
  uint64_t time_nsec, uint64_t commit_ts, uint64_t durable_ts, uint64_t first_commit_ts,
  uint64_t prepare_ts, uint64_t read_ts)
{
    WT_RET(__pack_encode__uintAny__direct(pp, end, time_sec));
    WT_RET(__pack_encode__uintAny__direct(pp, end, time_nsec));
    WT_RET(__pack_encode__uintAny__direct(pp, end, commit_ts));
    WT_RET(__pack_encode__uintAny__direct(pp, end, durable_ts));
    WT_RET(__pack_encode__uintAny__direct(pp, end, first_commit_ts));
    WT_RET(__pack_encode__uintAny__direct(pp, end, prepare_ts));
    WT_RET(__pack_encode__uintAny__direct(pp, end, read_ts));

    return (0);
}

/*
 * __wt_struct_unpack_txn_timestamp__direct --
 *     Unpack the txn_timestamp struct.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
static inline int
__wt_struct_unpack_txn_timestamp__direct(const uint8_t **pp, const uint8_t *end,
  uint64_t *time_secp, uint64_t *time_nsecp, uint64_t *commit_tsp, uint64_t *durable_tsp,
  uint64_t *first_commit_tsp, uint64_t *prepare_tsp, uint64_t *read_tsp)
{
    __pack_decode__uintAny__direct(uint64_t, time_secp);
    __pack_decode__uintAny__direct(uint64_t, time_nsecp);
    __pack_decode__uintAny__direct(uint64_t, commit_tsp);
    __pack_decode__uintAny__direct(uint64_t, durable_tsp);
    __pack_decode__uintAny__direct(uint64_t, first_commit_tsp);
    __pack_decode__uintAny__direct(uint64_t, prepare_tsp);
    __pack_decode__uintAny__direct(uint64_t, read_tsp);

    return (0);
}

/*
 * __wt_logop_txn_timestamp_pack__direct --
 *     Pack the log operation txn_timestamp.
 */
WT_GCC_FUNC_DECL_ATTRIBUTE((warn_unused_result))
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_txn_timestamp_pack__direct(WT_SESSION_IMPL *session, WT_ITEM *logrec, uint64_t time_sec,
  uint64_t time_nsec, uint64_t commit_ts, uint64_t durable_ts, uint64_t first_commit_ts,
  uint64_t prepare_ts, uint64_t read_ts)
{
    size_t size;
    uint8_t *buf, *end;

    size = __wt_struct_size_txn_timestamp__direct(
      time_sec, time_nsec, commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);
    size += __wt_vsize_uint(WT_LOGOP_TXN_TIMESTAMP) + __wt_vsize_uint(0);
    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));

    buf = (uint8_t *)logrec->data + logrec->size;
    end = buf + size;
    WT_RET(__wt_logop_write__direct(session, &buf, end, WT_LOGOP_TXN_TIMESTAMP, (uint32_t)size));
    WT_RET(__wt_struct_pack_txn_timestamp__direct(
      &buf, end, time_sec, time_nsec, commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_txn_timestamp_unpack__direct --
 *     Unpack the log operation txn_timestamp.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_txn_timestamp_unpack__direct(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint64_t *time_secp, uint64_t *time_nsecp, uint64_t *commit_tsp,
  uint64_t *durable_tsp, uint64_t *first_commit_tsp, uint64_t *prepare_tsp, uint64_t *read_tsp)
{
    WT_DECL_RET;
    uint32_t optype, size;

#if !defined(NO_STRICT_PACKING_CHECK) || defined(PACKING_COMPATIBILITY_MODE)
    const uint8_t *pp_orig;
    pp_orig = *pp;
#endif

    if ((ret = __wt_logop_unpack__direct(session, pp, end, &optype, &size)) != 0 ||
      (ret = __wt_struct_unpack_txn_timestamp__direct(pp, end, time_secp, time_nsecp, commit_tsp,
         durable_tsp, first_commit_tsp, prepare_tsp, read_tsp)) != 0)
        WT_RET_MSG(session, ret, "logop_txn_timestamp: unpack failure");

    WT_CHECK_OPTYPE(session, optype, WT_LOGOP_TXN_TIMESTAMP);

#if !defined(NO_STRICT_PACKING_CHECK)
    if (WT_PTRDIFF(*pp, pp_orig) != size) {
        WT_RET_MSG(session, EINVAL,
          "logop_txn_timestamp: size mismatch: expected %u, got %" PRIuPTR, size,
          WT_PTRDIFF(*pp, pp_orig));
    }
#endif
#if defined(PACKING_COMPATIBILITY_MODE)
    *pp = pp_orig + size;
#endif

    return (0);
}

/*
 * __wt_logop_txn_timestamp_print__direct --
 *     Print the log operation txn_timestamp.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_txn_timestamp_print__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint64_t time_sec;
    uint64_t time_nsec;
    uint64_t commit_ts;
    uint64_t durable_ts;
    uint64_t first_commit_ts;
    uint64_t prepare_ts;
    uint64_t read_ts;

    WT_RET(__wt_logop_txn_timestamp_unpack__direct(session, pp, end, &time_sec, &time_nsec,
      &commit_ts, &durable_ts, &first_commit_ts, &prepare_ts, &read_ts));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"txn_timestamp\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"time_sec\": %" PRIu64 ",\n", time_sec));
    WT_RET(__wt_fprintf(session, args->fs, "        \"time_nsec\": %" PRIu64 ",\n", time_nsec));
    WT_RET(__wt_fprintf(session, args->fs, "        \"commit_ts\": %" PRIu64 ",\n", commit_ts));
    WT_RET(__wt_fprintf(session, args->fs, "        \"durable_ts\": %" PRIu64 ",\n", durable_ts));
    WT_RET(__wt_fprintf(
      session, args->fs, "        \"first_commit_ts\": %" PRIu64 ",\n", first_commit_ts));
    WT_RET(__wt_fprintf(session, args->fs, "        \"prepare_ts\": %" PRIu64 ",\n", prepare_ts));
    WT_RET(__wt_fprintf(session, args->fs, "        \"read_ts\": %" PRIu64 "", read_ts));
    return (0);
}

/*
 * __wt_txn_op_printlog__direct --
 *     Print operation from a log cookie.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_txn_op_printlog__direct(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t optype, opsize;

    /* Peek at the size and the type. */
    WT_RET(__wt_logop_read__direct(session, pp, end, &optype, &opsize));
    end = *pp + opsize;

    switch (optype) {
    case WT_LOGOP_COL_MODIFY:
        WT_RET(__wt_logop_col_modify_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_COL_PUT:
        WT_RET(__wt_logop_col_put_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_COL_REMOVE:
        WT_RET(__wt_logop_col_remove_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_COL_TRUNCATE:
        WT_RET(__wt_logop_col_truncate_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_MODIFY:
        WT_RET(__wt_logop_row_modify_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_PUT:
        WT_RET(__wt_logop_row_put_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_REMOVE:
        WT_RET(__wt_logop_row_remove_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_TRUNCATE:
        WT_RET(__wt_logop_row_truncate_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_CHECKPOINT_START:
        WT_RET(__wt_logop_checkpoint_start_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_PREV_LSN:
        WT_RET(__wt_logop_prev_lsn_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_BACKUP_ID:
        WT_RET(__wt_logop_backup_id_print__direct(session, pp, end, args));
        break;

    case WT_LOGOP_TXN_TIMESTAMP:
        WT_RET(__wt_logop_txn_timestamp_print__direct(session, pp, end, args));
        break;

    default:
        return (__wt_illegal_value(session, optype));
    }

    return (0);
}
