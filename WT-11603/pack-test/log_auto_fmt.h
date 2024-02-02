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

#ifdef WT_STRUCT_PACKING_FMT
#define __logrec_make_hex_str __logrec_make_hex_str__fmt
#define __logrec_make_json_str __logrec_make_json_str__fmt
#define __wt_logop_backup_id_pack __wt_logop_backup_id_pack__fmt
#define __wt_logop_backup_id_print __wt_logop_backup_id_print__fmt
#define __wt_logop_backup_id_unpack __wt_logop_backup_id_unpack__fmt
#define __wt_logop_checkpoint_start_pack __wt_logop_checkpoint_start_pack__fmt
#define __wt_logop_checkpoint_start_print __wt_logop_checkpoint_start_print__fmt
#define __wt_logop_checkpoint_start_unpack __wt_logop_checkpoint_start_unpack__fmt
#define __wt_logop_col_modify_pack __wt_logop_col_modify_pack__fmt
#define __wt_logop_col_modify_print __wt_logop_col_modify_print__fmt
#define __wt_logop_col_modify_unpack __wt_logop_col_modify_unpack__fmt
#define __wt_logop_col_put_pack __wt_logop_col_put_pack__fmt
#define __wt_logop_col_put_print __wt_logop_col_put_print__fmt
#define __wt_logop_col_put_unpack __wt_logop_col_put_unpack__fmt
#define __wt_logop_col_remove_pack __wt_logop_col_remove_pack__fmt
#define __wt_logop_col_remove_print __wt_logop_col_remove_print__fmt
#define __wt_logop_col_remove_unpack __wt_logop_col_remove_unpack__fmt
#define __wt_logop_col_truncate_pack __wt_logop_col_truncate_pack__fmt
#define __wt_logop_col_truncate_print __wt_logop_col_truncate_print__fmt
#define __wt_logop_col_truncate_unpack __wt_logop_col_truncate_unpack__fmt
#define __wt_logop_prev_lsn_pack __wt_logop_prev_lsn_pack__fmt
#define __wt_logop_prev_lsn_print __wt_logop_prev_lsn_print__fmt
#define __wt_logop_prev_lsn_unpack __wt_logop_prev_lsn_unpack__fmt
#define __wt_logop_read __wt_logop_read__fmt
#define __wt_logop_row_modify_pack __wt_logop_row_modify_pack__fmt
#define __wt_logop_row_modify_print __wt_logop_row_modify_print__fmt
#define __wt_logop_row_modify_unpack __wt_logop_row_modify_unpack__fmt
#define __wt_logop_row_put_pack __wt_logop_row_put_pack__fmt
#define __wt_logop_row_put_print __wt_logop_row_put_print__fmt
#define __wt_logop_row_put_unpack __wt_logop_row_put_unpack__fmt
#define __wt_logop_row_remove_pack __wt_logop_row_remove_pack__fmt
#define __wt_logop_row_remove_print __wt_logop_row_remove_print__fmt
#define __wt_logop_row_remove_unpack __wt_logop_row_remove_unpack__fmt
#define __wt_logop_row_truncate_pack __wt_logop_row_truncate_pack__fmt
#define __wt_logop_row_truncate_print __wt_logop_row_truncate_print__fmt
#define __wt_logop_row_truncate_unpack __wt_logop_row_truncate_unpack__fmt
#define __wt_logop_txn_timestamp_pack __wt_logop_txn_timestamp_pack__fmt
#define __wt_logop_txn_timestamp_print __wt_logop_txn_timestamp_print__fmt
#define __wt_logop_txn_timestamp_unpack __wt_logop_txn_timestamp_unpack__fmt
#define __wt_logrec_alloc __wt_logrec_alloc__fmt
#define __wt_logrec_free __wt_logrec_free__fmt
#define __wt_logrec_read __wt_logrec_read__fmt
#define __wt_txn_op_printlog __wt_txn_op_printlog__fmt
#endif
/* DO NOT EDIT: automatically built by dist/log.py. */

#include "../../src/include/wt_internal.h"

/*
 * __wt_logrec_alloc__fmt --
 *     Allocate a new WT_ITEM structure.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logrec_alloc__fmt(WT_SESSION_IMPL *session, size_t size, WT_ITEM **logrecp)
{
    WT_ITEM *logrec;
    WT_LOG *log;

    log = S2C(session)->log;
    WT_RET(__wt_scr_alloc(session, WT_ALIGN(size + 1, log->allocsize), &logrec));
    WT_CLEAR(*(WT_LOG_RECORD *)logrec->data);
    logrec->size = offsetof(WT_LOG_RECORD, record);

    *logrecp = logrec;
    return (0);
}

/*
 * __wt_logrec_free__fmt --
 *     Free the given WT_ITEM structure.
 */
WT_ATTRIBUTE_UNUSED
static void
__wt_logrec_free__fmt(WT_SESSION_IMPL *session, WT_ITEM **logrecp)
{
    __wt_scr_free(session, logrecp);
}

/*
 * __wt_logrec_read__fmt --
 *     Read the record type.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logrec_read__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, uint32_t *rectypep)
{
    uint64_t rectype;

    WT_UNUSED(session);
    WT_RET(__wt_vunpack_uint(pp, WT_PTRDIFF(end, *pp), &rectype));
    *rectypep = (uint32_t)rectype;
    return (0);
}

/*
 * __wt_logop_read__fmt --
 *     Read the operation type.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_read__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *optypep, uint32_t *opsizep)
{
    return (__wt_struct_unpack(session, *pp, WT_PTRDIFF(end, *pp), "II", optypep, opsizep));
}

/*
 * __logrec_make_json_str__fmt --
 *     Unpack a string into JSON escaped format.
 */
static int
__logrec_make_json_str__fmt(WT_SESSION_IMPL *session, WT_ITEM **escapedp, WT_ITEM *item)
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
 * __logrec_make_hex_str__fmt --
 *     Convert data to a hexadecimal representation.
 */
static int
__logrec_make_hex_str__fmt(WT_SESSION_IMPL *session, WT_ITEM **escapedp, WT_ITEM *item)
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
 * __wt_logop_col_modify_pack__fmt --
 *     Pack the log operation col_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_modify_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIru);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_COL_MODIFY;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, recno, value));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, fileid, recno, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_modify_unpack__fmt --
 *     Unpack the log operation col_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_modify_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIru);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(
           session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp, recnop, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_col_modify: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_COL_MODIFY);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_col_modify_print__fmt --
 *     Print the log operation col_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_modify_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_col_modify_unpack__fmt(session, pp, end, &fileid, &recno, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"col_modify\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"recno\": %" PRIu64 ",\n", recno));
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_logop_col_put_pack__fmt --
 *     Pack the log operation col_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_put_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIru);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_COL_PUT;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, recno, value));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, fileid, recno, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_put_unpack__fmt --
 *     Unpack the log operation col_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_put_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, uint64_t *recnop, WT_ITEM *valuep)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIru);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(
           session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp, recnop, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_col_put: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_COL_PUT);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_col_put_print__fmt --
 *     Print the log operation col_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_put_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_col_put_unpack__fmt(session, pp, end, &fileid, &recno, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"col_put\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"recno\": %" PRIu64 ",\n", recno));
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_logop_col_remove_pack__fmt --
 *     Pack the log operation col_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_remove_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t recno)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIr);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_COL_REMOVE;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, recno));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(
      session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype, recsize, fileid, recno));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_remove_unpack__fmt --
 *     Unpack the log operation col_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_remove_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, uint64_t *recnop)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIr);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(
           session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp, recnop)) != 0)
        WT_RET_MSG(session, ret, "logop_col_remove: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_COL_REMOVE);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_col_remove_print__fmt --
 *     Print the log operation col_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_remove_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t fileid;
    uint64_t recno;

    WT_RET(__wt_logop_col_remove_unpack__fmt(session, pp, end, &fileid, &recno));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"col_remove\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_RET(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_RET(__wt_fprintf(session, args->fs, "        \"recno\": %" PRIu64 "", recno));
    return (0);
}

/*
 * __wt_logop_col_truncate_pack__fmt --
 *     Pack the log operation col_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_truncate_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, uint64_t start, uint64_t stop)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIrr);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_COL_TRUNCATE;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, start, stop));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, fileid, start, stop));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_col_truncate_unpack__fmt --
 *     Unpack the log operation col_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_truncate_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, uint64_t *startp, uint64_t *stopp)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIrr);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(
           session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp, startp, stopp)) != 0)
        WT_RET_MSG(session, ret, "logop_col_truncate: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_COL_TRUNCATE);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_col_truncate_print__fmt --
 *     Print the log operation col_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_col_truncate_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t fileid;
    uint64_t start;
    uint64_t stop;

    WT_RET(__wt_logop_col_truncate_unpack__fmt(session, pp, end, &fileid, &start, &stop));

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
 * __wt_logop_row_modify_pack__fmt --
 *     Pack the log operation row_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_modify_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIuu);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_ROW_MODIFY;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, key, value));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, fileid, key, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_modify_unpack__fmt --
 *     Unpack the log operation row_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_modify_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIuu);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(
           session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp, keyp, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_row_modify: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_ROW_MODIFY);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_row_modify_print__fmt --
 *     Print the log operation row_modify.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_modify_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_modify_unpack__fmt(session, pp, end, &fileid, &key, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_modify\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &key));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"key\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &key));
        WT_ERR(
          __wt_fprintf(session, args->fs, "        \"key-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_logop_row_put_pack__fmt --
 *     Pack the log operation row_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_put_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIuu);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_ROW_PUT;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, key, value));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, fileid, key, value));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_put_unpack__fmt --
 *     Unpack the log operation row_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_put_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, WT_ITEM *keyp, WT_ITEM *valuep)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIuu);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(
           session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp, keyp, valuep)) != 0)
        WT_RET_MSG(session, ret, "logop_row_put: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_ROW_PUT);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_row_put_print__fmt --
 *     Print the log operation row_put.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_put_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_put_unpack__fmt(session, pp, end, &fileid, &key, &value));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_put\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &key));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"key\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &key));
        WT_ERR(
          __wt_fprintf(session, args->fs, "        \"key-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &value));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"value\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &value));
        WT_ERR(__wt_fprintf(
          session, args->fs, ",\n        \"value-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_logop_row_remove_pack__fmt --
 *     Pack the log operation row_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_remove_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid, WT_ITEM *key)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIu);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_ROW_REMOVE;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, key));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(
      session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype, recsize, fileid, key));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_remove_unpack__fmt --
 *     Unpack the log operation row_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_remove_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *fileidp, WT_ITEM *keyp)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIu);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(
           session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp, keyp)) != 0)
        WT_RET_MSG(session, ret, "logop_row_remove: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_ROW_REMOVE);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_row_remove_print__fmt --
 *     Print the log operation row_remove.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_remove_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM key;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_remove_unpack__fmt(session, pp, end, &fileid, &key));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_remove\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &key));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"key\": \"%s\"", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &key));
        WT_ERR(
          __wt_fprintf(session, args->fs, ",\n        \"key-hex\": \"%s\"", (char *)escaped->mem));
    }

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_logop_row_truncate_pack__fmt --
 *     Pack the log operation row_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_truncate_pack__fmt(WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t fileid,
  WT_ITEM *start, WT_ITEM *stop, uint32_t mode)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIuuI);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_ROW_TRUNCATE;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, fileid, start, stop, mode));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, fileid, start, stop, mode));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_row_truncate_unpack__fmt --
 *     Unpack the log operation row_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_truncate_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint32_t *fileidp, WT_ITEM *startp, WT_ITEM *stopp, uint32_t *modep)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIuuI);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, fileidp,
           startp, stopp, modep)) != 0)
        WT_RET_MSG(session, ret, "logop_row_truncate: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_ROW_TRUNCATE);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_row_truncate_print__fmt --
 *     Print the log operation row_truncate.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_row_truncate_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_DECL_RET;
    uint32_t fileid;
    WT_ITEM start;
    WT_ITEM stop;
    uint32_t mode;
    WT_DECL_ITEM(escaped);

    WT_RET(__wt_logop_row_truncate_unpack__fmt(session, pp, end, &fileid, &start, &stop, &mode));

    if (!FLD_ISSET(args->flags, WT_TXN_PRINTLOG_UNREDACT) && fileid != WT_METAFILE_ID)
        return (__wt_fprintf(session, args->fs, " REDACTED"));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"row_truncate\",\n"));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid\": %" PRIu32 ",\n", fileid));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"fileid-hex\": \"0x%" PRIx32 "\",\n", fileid));
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &start));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"start\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &start));
        WT_ERR(__wt_fprintf(
          session, args->fs, "        \"start-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__logrec_make_json_str__fmt(session, &escaped, &stop));
    WT_ERR(__wt_fprintf(session, args->fs, "        \"stop\": \"%s\",\n", (char *)escaped->mem));
    if (FLD_ISSET(args->flags, WT_TXN_PRINTLOG_HEX)) {
        WT_ERR(__logrec_make_hex_str__fmt(session, &escaped, &stop));
        WT_ERR(
          __wt_fprintf(session, args->fs, "        \"stop-hex\": \"%s\",\n", (char *)escaped->mem));
    }
    WT_ERR(__wt_fprintf(session, args->fs, "        \"mode\": %" PRIu32 "", mode));

err:
    __wt_scr_free(session, &escaped);
    return (ret);
}

/*
 * __wt_logop_checkpoint_start_pack__fmt --
 *     Pack the log operation checkpoint_start.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_checkpoint_start_pack__fmt(WT_SESSION_IMPL *session, WT_ITEM *logrec)
{
    const char *fmt = WT_UNCHECKED_STRING(II);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_CHECKPOINT_START;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(
      session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype, recsize));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_checkpoint_start_unpack__fmt --
 *     Unpack the log operation checkpoint_start.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_checkpoint_start_unpack__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(II);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size)) != 0)
        WT_RET_MSG(session, ret, "logop_checkpoint_start: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_CHECKPOINT_START);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_checkpoint_start_print__fmt --
 *     Print the log operation checkpoint_start.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_checkpoint_start_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{

    WT_RET(__wt_logop_checkpoint_start_unpack__fmt(session, pp, end));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"checkpoint_start\"\n"));

    return (0);
}

/*
 * __wt_logop_prev_lsn_pack__fmt --
 *     Pack the log operation prev_lsn.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_prev_lsn_pack__fmt(WT_SESSION_IMPL *session, WT_ITEM *logrec, WT_LSN *prev_lsn)
{
    const char *fmt = WT_UNCHECKED_STRING(IIII);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_PREV_LSN;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, prev_lsn->l.file, prev_lsn->l.offset));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, prev_lsn->l.file, prev_lsn->l.offset));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_prev_lsn_unpack__fmt --
 *     Unpack the log operation prev_lsn.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_prev_lsn_unpack__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_LSN *prev_lsnp)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIII);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size,
           &prev_lsnp->l.file, &prev_lsnp->l.offset)) != 0)
        WT_RET_MSG(session, ret, "logop_prev_lsn: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_PREV_LSN);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_prev_lsn_print__fmt --
 *     Print the log operation prev_lsn.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_prev_lsn_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    WT_LSN prev_lsn;

    WT_RET(__wt_logop_prev_lsn_unpack__fmt(session, pp, end, &prev_lsn));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"prev_lsn\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"prev_lsn\": [%" PRIu32 ", %" PRIu32 "]",
      prev_lsn.l.file, prev_lsn.l.offset));
    return (0);
}

/*
 * __wt_logop_backup_id_pack__fmt --
 *     Pack the log operation backup_id.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_backup_id_pack__fmt(
  WT_SESSION_IMPL *session, WT_ITEM *logrec, uint32_t index, uint64_t granularity, const char *id)
{
    const char *fmt = WT_UNCHECKED_STRING(IIIQS);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_BACKUP_ID;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, index, granularity, id));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, index, granularity, id));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_backup_id_unpack__fmt --
 *     Unpack the log operation backup_id.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_backup_id_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end,
  uint32_t *indexp, uint64_t *granularityp, const char **idp)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIIQS);
    uint32_t optype, size;

    if ((ret = __wt_struct_unpack(session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, indexp,
           granularityp, idp)) != 0)
        WT_RET_MSG(session, ret, "logop_backup_id: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_BACKUP_ID);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_backup_id_print__fmt --
 *     Print the log operation backup_id.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_backup_id_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t index;
    uint64_t granularity;
    const char *id;

    WT_RET(__wt_logop_backup_id_unpack__fmt(session, pp, end, &index, &granularity, &id));

    WT_RET(__wt_fprintf(session, args->fs, " \"optype\": \"backup_id\",\n"));
    WT_RET(__wt_fprintf(session, args->fs, "        \"index\": %" PRIu32 ",\n", index));
    WT_RET(__wt_fprintf(session, args->fs, "        \"granularity\": %" PRIu64 ",\n", granularity));
    WT_RET(__wt_fprintf(session, args->fs, "        \"id\": \"%s\"", id));
    return (0);
}

/*
 * __wt_logop_txn_timestamp_pack__fmt --
 *     Pack the log operation txn_timestamp.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_txn_timestamp_pack__fmt(WT_SESSION_IMPL *session, WT_ITEM *logrec, uint64_t time_sec,
  uint64_t time_nsec, uint64_t commit_ts, uint64_t durable_ts, uint64_t first_commit_ts,
  uint64_t prepare_ts, uint64_t read_ts)
{
    const char *fmt = WT_UNCHECKED_STRING(IIQQQQQQQ);
    size_t size;
    uint32_t optype, recsize;

    optype = WT_LOGOP_TXN_TIMESTAMP;
    WT_RET(__wt_struct_size(session, &size, fmt, optype, 0, time_sec, time_nsec, commit_ts,
      durable_ts, first_commit_ts, prepare_ts, read_ts));

    __wt_struct_size_adjust(session, &size);
    WT_RET(__wt_buf_extend(session, logrec, logrec->size + size));
    recsize = (uint32_t)size;
    WT_RET(__wt_struct_pack(session, (uint8_t *)logrec->data + logrec->size, size, fmt, optype,
      recsize, time_sec, time_nsec, commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts));

    logrec->size += (uint32_t)size;
    return (0);
}

/*
 * __wt_logop_txn_timestamp_unpack__fmt --
 *     Unpack the log operation txn_timestamp.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_txn_timestamp_unpack__fmt(WT_SESSION_IMPL *session, const uint8_t **pp,
  const uint8_t *end, uint64_t *time_secp, uint64_t *time_nsecp, uint64_t *commit_tsp,
  uint64_t *durable_tsp, uint64_t *first_commit_tsp, uint64_t *prepare_tsp, uint64_t *read_tsp)
{
    WT_DECL_RET;
    const char *fmt = WT_UNCHECKED_STRING(IIQQQQQQQ);
    uint32_t optype, size;

    if ((ret =
            __wt_struct_unpack(session, *pp, WT_PTRDIFF(end, *pp), fmt, &optype, &size, time_secp,
              time_nsecp, commit_tsp, durable_tsp, first_commit_tsp, prepare_tsp, read_tsp)) != 0)
        WT_RET_MSG(session, ret, "logop_txn_timestamp: unpack failure");
    WT_ASSERT_OPTYPE(session, optype == WT_LOGOP_TXN_TIMESTAMP);

    *pp += size;
    return (0);
}

/*
 * __wt_logop_txn_timestamp_print__fmt --
 *     Print the log operation txn_timestamp.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_logop_txn_timestamp_print__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint64_t time_sec;
    uint64_t time_nsec;
    uint64_t commit_ts;
    uint64_t durable_ts;
    uint64_t first_commit_ts;
    uint64_t prepare_ts;
    uint64_t read_ts;

    WT_RET(__wt_logop_txn_timestamp_unpack__fmt(session, pp, end, &time_sec, &time_nsec, &commit_ts,
      &durable_ts, &first_commit_ts, &prepare_ts, &read_ts));

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
 * __wt_txn_op_printlog__fmt --
 *     Print operation from a log cookie.
 */
WT_ATTRIBUTE_UNUSED
static int
__wt_txn_op_printlog__fmt(
  WT_SESSION_IMPL *session, const uint8_t **pp, const uint8_t *end, WT_TXN_PRINTLOG_ARGS *args)
{
    uint32_t optype, opsize;

    /* Peek at the size and the type. */
    WT_RET(__wt_logop_read__fmt(session, pp, end, &optype, &opsize));
    end = *pp + opsize;

    switch (optype) {
    case WT_LOGOP_COL_MODIFY:
        WT_RET(__wt_logop_col_modify_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_COL_PUT:
        WT_RET(__wt_logop_col_put_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_COL_REMOVE:
        WT_RET(__wt_logop_col_remove_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_COL_TRUNCATE:
        WT_RET(__wt_logop_col_truncate_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_MODIFY:
        WT_RET(__wt_logop_row_modify_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_PUT:
        WT_RET(__wt_logop_row_put_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_REMOVE:
        WT_RET(__wt_logop_row_remove_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_ROW_TRUNCATE:
        WT_RET(__wt_logop_row_truncate_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_CHECKPOINT_START:
        WT_RET(__wt_logop_checkpoint_start_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_PREV_LSN:
        WT_RET(__wt_logop_prev_lsn_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_BACKUP_ID:
        WT_RET(__wt_logop_backup_id_print__fmt(session, pp, end, args));
        break;

    case WT_LOGOP_TXN_TIMESTAMP:
        WT_RET(__wt_logop_txn_timestamp_print__fmt(session, pp, end, args));
        break;

    default:
        return (__wt_illegal_value(session, optype));
    }

    return (0);
}
