/* DO NOT EDIT: automatically built by log_auto-test-gen.sh */

#pragma once


#include "log_auto_mirror.h"

/*
 * Functions to compare packing and unpacking for pre-defined inputs
 */

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_col_modify(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    uint64_t recno_fmt, recno_direct;
    WT_ITEM value_fmt, value_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    recno_fmt = recno;
    recno_direct = recno;
    value_fmt.data = value->data;
    value_direct.data = value->data;
    value_fmt.size = value->size;
    value_direct.size = value->size;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(
      __wt_logop_col_modify_pack__fmt(session, logrec_fmt, fileid_fmt, recno_fmt, &value_fmt) == 0);
    assert(__wt_logop_col_modify_pack__direct(
             session, logrec_direct, fileid_direct, recno_direct, &value_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_col_modify_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &fileid_fmt, &recno_fmt, &value_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_col_modify_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &recno_direct, &value_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_uint64_t(recno_fmt, recno_direct);
    assert_eq_size_t(value_fmt.size, value_direct.size);
    assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);

    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_col_put(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, uint64_t recno, WT_ITEM *value)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    uint64_t recno_fmt, recno_direct;
    WT_ITEM value_fmt, value_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    recno_fmt = recno;
    recno_direct = recno;
    value_fmt.data = value->data;
    value_direct.data = value->data;
    value_fmt.size = value->size;
    value_direct.size = value->size;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(
      __wt_logop_col_put_pack__fmt(session, logrec_fmt, fileid_fmt, recno_fmt, &value_fmt) == 0);
    assert(__wt_logop_col_put_pack__direct(
             session, logrec_direct, fileid_direct, recno_direct, &value_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_col_put_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &fileid_fmt, &recno_fmt, &value_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_col_put_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &recno_direct, &value_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_uint64_t(recno_fmt, recno_direct);
    assert_eq_size_t(value_fmt.size, value_direct.size);
    assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);

    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_col_remove(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, uint64_t recno)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    uint64_t recno_fmt, recno_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    recno_fmt = recno;
    recno_direct = recno;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(__wt_logop_col_remove_pack__fmt(session, logrec_fmt, fileid_fmt, recno_fmt) == 0);
    assert(
      __wt_logop_col_remove_pack__direct(session, logrec_direct, fileid_direct, recno_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_col_remove_unpack__fmt(
             session, &data_fmt, data_fmt + logrec_fmt->size, &fileid_fmt, &recno_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_col_remove_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &recno_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_uint64_t(recno_fmt, recno_direct);
    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_col_truncate(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, uint64_t start, uint64_t stop)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    uint64_t start_fmt, start_direct;
    uint64_t stop_fmt, stop_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    start_fmt = start;
    start_direct = start;
    stop_fmt = stop;
    stop_direct = stop;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(
      __wt_logop_col_truncate_pack__fmt(session, logrec_fmt, fileid_fmt, start_fmt, stop_fmt) == 0);
    assert(__wt_logop_col_truncate_pack__direct(
             session, logrec_direct, fileid_direct, start_direct, stop_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_col_truncate_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &fileid_fmt, &start_fmt, &stop_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_col_truncate_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &start_direct, &stop_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_uint64_t(start_fmt, start_direct);
    assert_eq_uint64_t(stop_fmt, stop_direct);
    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_row_modify(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM key_fmt, key_direct;
    WT_ITEM value_fmt, value_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    key_fmt.data = key->data;
    key_direct.data = key->data;
    key_fmt.size = key->size;
    key_direct.size = key->size;
    value_fmt.data = value->data;
    value_direct.data = value->data;
    value_fmt.size = value->size;
    value_direct.size = value->size;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(
      __wt_logop_row_modify_pack__fmt(session, logrec_fmt, fileid_fmt, &key_fmt, &value_fmt) == 0);
    assert(__wt_logop_row_modify_pack__direct(
             session, logrec_direct, fileid_direct, &key_direct, &value_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_row_modify_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &fileid_fmt, &key_fmt, &value_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_row_modify_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &key_direct, &value_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_size_t(key_fmt.size, key_direct.size);
    assert(memcmp(key_fmt.data, key_direct.data, key_fmt.size) == 0);

    assert_eq_size_t(value_fmt.size, value_direct.size);
    assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);

    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_row_put(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, WT_ITEM *key, WT_ITEM *value)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM key_fmt, key_direct;
    WT_ITEM value_fmt, value_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    key_fmt.data = key->data;
    key_direct.data = key->data;
    key_fmt.size = key->size;
    key_direct.size = key->size;
    value_fmt.data = value->data;
    value_direct.data = value->data;
    value_fmt.size = value->size;
    value_direct.size = value->size;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(
      __wt_logop_row_put_pack__fmt(session, logrec_fmt, fileid_fmt, &key_fmt, &value_fmt) == 0);
    assert(__wt_logop_row_put_pack__direct(
             session, logrec_direct, fileid_direct, &key_direct, &value_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_row_put_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &fileid_fmt, &key_fmt, &value_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_row_put_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &key_direct, &value_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_size_t(key_fmt.size, key_direct.size);
    assert(memcmp(key_fmt.data, key_direct.data, key_fmt.size) == 0);

    assert_eq_size_t(value_fmt.size, value_direct.size);
    assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);

    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_row_remove(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, WT_ITEM *key)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM key_fmt, key_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    key_fmt.data = key->data;
    key_direct.data = key->data;
    key_fmt.size = key->size;
    key_direct.size = key->size;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(__wt_logop_row_remove_pack__fmt(session, logrec_fmt, fileid_fmt, &key_fmt) == 0);
    assert(
      __wt_logop_row_remove_pack__direct(session, logrec_direct, fileid_direct, &key_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_row_remove_unpack__fmt(
             session, &data_fmt, data_fmt + logrec_fmt->size, &fileid_fmt, &key_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_row_remove_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &key_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_size_t(key_fmt.size, key_direct.size);
    assert(memcmp(key_fmt.data, key_direct.data, key_fmt.size) == 0);

    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_row_truncate(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t fileid, WT_ITEM *start, WT_ITEM *stop, uint32_t mode)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM start_fmt, start_direct;
    WT_ITEM stop_fmt, stop_direct;
    uint32_t mode_fmt, mode_direct;

    fileid_fmt = fileid;
    fileid_direct = fileid;
    start_fmt.data = start->data;
    start_direct.data = start->data;
    start_fmt.size = start->size;
    start_direct.size = start->size;
    stop_fmt.data = stop->data;
    stop_direct.data = stop->data;
    stop_fmt.size = stop->size;
    stop_direct.size = stop->size;
    mode_fmt = mode;
    mode_direct = mode;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(__wt_logop_row_truncate_pack__fmt(
             session, logrec_fmt, fileid_fmt, &start_fmt, &stop_fmt, mode_fmt) == 0);
    assert(__wt_logop_row_truncate_pack__direct(
             session, logrec_direct, fileid_direct, &start_direct, &stop_direct, mode_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_row_truncate_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &fileid_fmt, &start_fmt, &stop_fmt, &mode_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_row_truncate_unpack__direct(session, &data_direct,
             data_direct + logrec_direct->size, &fileid_direct, &start_direct, &stop_direct,
             &mode_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(fileid_fmt, fileid_direct);
    assert_eq_size_t(start_fmt.size, start_direct.size);
    assert(memcmp(start_fmt.data, start_direct.data, start_fmt.size) == 0);

    assert_eq_size_t(stop_fmt.size, stop_direct.size);
    assert(memcmp(stop_fmt.data, stop_direct.data, stop_fmt.size) == 0);

    assert_eq_uint32_t(mode_fmt, mode_direct);
    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_checkpoint_start(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/

    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(__wt_logop_checkpoint_start_pack__fmt(session, logrec_fmt) == 0);
    assert(__wt_logop_checkpoint_start_pack__direct(session, logrec_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_checkpoint_start_unpack__fmt(
             session, &data_fmt, data_fmt + logrec_fmt->size) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_checkpoint_start_unpack__direct(
             session, &data_direct, data_direct + logrec_direct->size) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_prev_lsn(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct, WT_LSN *prev_lsn)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    WT_LSN prev_lsn_fmt, prev_lsn_direct;

    prev_lsn_fmt.l.file = prev_lsn->l.file;
    prev_lsn_direct.l.file = prev_lsn->l.file;
    prev_lsn_fmt.l.offset = prev_lsn->l.offset;
    prev_lsn_direct.l.offset = prev_lsn->l.offset;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(__wt_logop_prev_lsn_pack__fmt(session, logrec_fmt, &prev_lsn_fmt) == 0);
    assert(__wt_logop_prev_lsn_pack__direct(session, logrec_direct, &prev_lsn_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_prev_lsn_unpack__fmt(
             session, &data_fmt, data_fmt + logrec_fmt->size, &prev_lsn_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(__wt_logop_prev_lsn_unpack__direct(
             session, &data_direct, data_direct + logrec_direct->size, &prev_lsn_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert(prev_lsn_fmt.l.file == prev_lsn_direct.l.file);
    assert(prev_lsn_fmt.l.offset == prev_lsn_direct.l.offset);

    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_backup_id(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint32_t index, uint64_t granularity, const char *id)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint32_t index_fmt, index_direct;
    uint64_t granularity_fmt, granularity_direct;
    const char *id_fmt, *id_direct;

    index_fmt = index;
    index_direct = index;
    granularity_fmt = granularity;
    granularity_direct = granularity;
    id_fmt = id;
    id_direct = id;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(
      __wt_logop_backup_id_pack__fmt(session, logrec_fmt, index_fmt, granularity_fmt, id_fmt) == 0);
    assert(__wt_logop_backup_id_pack__direct(
             session, logrec_direct, index_direct, granularity_direct, id_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_backup_id_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &index_fmt, &granularity_fmt, &id_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(
      __wt_logop_backup_id_unpack__direct(session, &data_direct, data_direct + logrec_direct->size,
        &index_direct, &granularity_direct, &id_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint32_t(index_fmt, index_direct);
    assert_eq_uint64_t(granularity_fmt, granularity_direct);
    assert(!strcmp(id_fmt, id_direct));
    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_one__wt_logop_txn_timestamp(WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt,
  WT_ITEM *logrec_direct, uint64_t time_sec, uint64_t time_nsec, uint64_t commit_ts,
  uint64_t durable_ts, uint64_t first_commit_ts, uint64_t prepare_ts, uint64_t read_ts)
{
    const uint8_t *data_fmt, *data_direct;
    /*size_t sz_fmt, sz_direct;*/
    uint64_t time_sec_fmt, time_sec_direct;
    uint64_t time_nsec_fmt, time_nsec_direct;
    uint64_t commit_ts_fmt, commit_ts_direct;
    uint64_t durable_ts_fmt, durable_ts_direct;
    uint64_t first_commit_ts_fmt, first_commit_ts_direct;
    uint64_t prepare_ts_fmt, prepare_ts_direct;
    uint64_t read_ts_fmt, read_ts_direct;

    time_sec_fmt = time_sec;
    time_sec_direct = time_sec;
    time_nsec_fmt = time_nsec;
    time_nsec_direct = time_nsec;
    commit_ts_fmt = commit_ts;
    commit_ts_direct = commit_ts;
    durable_ts_fmt = durable_ts;
    durable_ts_direct = durable_ts;
    first_commit_ts_fmt = first_commit_ts;
    first_commit_ts_direct = first_commit_ts;
    prepare_ts_fmt = prepare_ts;
    prepare_ts_direct = prepare_ts;
    read_ts_fmt = read_ts;
    read_ts_direct = read_ts;
    logrec_fmt->size = logrec_direct->size = 0;
    /*sz_fmt = logrec_fmt->size;*/
    /*sz_direct = logrec_direct->size;*/

    /* test packing */
    assert(__wt_logop_txn_timestamp_pack__fmt(session, logrec_fmt, time_sec_fmt, time_nsec_fmt,
             commit_ts_fmt, durable_ts_fmt, first_commit_ts_fmt, prepare_ts_fmt, read_ts_fmt) == 0);
    assert(__wt_logop_txn_timestamp_pack__direct(session, logrec_direct, time_sec_direct,
             time_nsec_direct, commit_ts_direct, durable_ts_direct, first_commit_ts_direct,
             prepare_ts_direct, read_ts_direct) == 0);

    assert_eq_size_t(logrec_fmt->size, logrec_direct->size);
    assert(memcmp(logrec_fmt->data, logrec_direct->data, logrec_fmt->size) == 0);

    /* test unpacking */
    data_fmt = logrec_fmt->data;
    data_direct = logrec_direct->data;
    assert(__wt_logop_txn_timestamp_unpack__fmt(session, &data_fmt, data_fmt + logrec_fmt->size,
             &time_sec_fmt, &time_nsec_fmt, &commit_ts_fmt, &durable_ts_fmt, &first_commit_ts_fmt,
             &prepare_ts_fmt, &read_ts_fmt) == 0);
    assert_eq_size_t(logrec_fmt->size, WT_PTRDIFF(data_fmt, logrec_fmt->data));
    assert(
      __wt_logop_txn_timestamp_unpack__direct(session, &data_direct,
        data_direct + logrec_direct->size, &time_sec_direct, &time_nsec_direct, &commit_ts_direct,
        &durable_ts_direct, &first_commit_ts_direct, &prepare_ts_direct, &read_ts_direct) == 0);
    assert_eq_size_t(logrec_direct->size, WT_PTRDIFF(data_direct, logrec_direct->data));

    assert_eq_uint64_t(time_sec_fmt, time_sec_direct);
    assert_eq_uint64_t(time_nsec_fmt, time_nsec_direct);
    assert_eq_uint64_t(commit_ts_fmt, commit_ts_direct);
    assert_eq_uint64_t(durable_ts_fmt, durable_ts_direct);
    assert_eq_uint64_t(first_commit_ts_fmt, first_commit_ts_direct);
    assert_eq_uint64_t(prepare_ts_fmt, prepare_ts_direct);
    assert_eq_uint64_t(read_ts_fmt, read_ts_direct);
    /*logrec_fmt->size = sz_fmt;*/
    /*logrec_direct->size = sz_direct;*/
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_col_modify(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    fileid = (uint32_t)(0);
    recno = (uint64_t)(0);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(1);
    recno = (uint64_t)(1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    recno = (uint64_t)(POS_1BYTE_MAX - 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    recno = (uint64_t)(POS_1BYTE_MAX);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    recno = (uint64_t)(POS_1BYTE_MAX + 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    recno = (uint64_t)(POS_2BYTE_MAX - 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    recno = (uint64_t)(POS_2BYTE_MAX);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    recno = (uint64_t)(POS_2BYTE_MAX + 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(rand());
    recno = (uint64_t)(rand());
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(rand());
    recno = (uint64_t)(rand());
    value.data = "data";
    value.size = 4;
    test_cmp_one__wt_logop_col_modify(session, logrec_fmt, logrec_direct, fileid, recno, &value);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_col_put(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    fileid = (uint32_t)(0);
    recno = (uint64_t)(0);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(1);
    recno = (uint64_t)(1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    recno = (uint64_t)(POS_1BYTE_MAX - 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    recno = (uint64_t)(POS_1BYTE_MAX);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    recno = (uint64_t)(POS_1BYTE_MAX + 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    recno = (uint64_t)(POS_2BYTE_MAX - 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    recno = (uint64_t)(POS_2BYTE_MAX);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    recno = (uint64_t)(POS_2BYTE_MAX + 1);
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(rand());
    recno = (uint64_t)(rand());
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);

    fileid = (uint32_t)(rand());
    recno = (uint64_t)(rand());
    value.data = "data";
    value.size = 4;
    test_cmp_one__wt_logop_col_put(session, logrec_fmt, logrec_direct, fileid, recno, &value);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_col_remove(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    uint64_t recno;

    fileid = (uint32_t)(0);
    recno = (uint64_t)(0);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(1);
    recno = (uint64_t)(1);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    recno = (uint64_t)(POS_1BYTE_MAX - 1);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    recno = (uint64_t)(POS_1BYTE_MAX);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    recno = (uint64_t)(POS_1BYTE_MAX + 1);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    recno = (uint64_t)(POS_2BYTE_MAX - 1);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    recno = (uint64_t)(POS_2BYTE_MAX);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    recno = (uint64_t)(POS_2BYTE_MAX + 1);
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(rand());
    recno = (uint64_t)(rand());
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);

    fileid = (uint32_t)(rand());
    recno = (uint64_t)(rand());
    test_cmp_one__wt_logop_col_remove(session, logrec_fmt, logrec_direct, fileid, recno);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_col_truncate(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    uint64_t start;
    uint64_t stop;

    fileid = (uint32_t)(0);
    start = (uint64_t)(0);
    stop = (uint64_t)(0);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(1);
    start = (uint64_t)(1);
    stop = (uint64_t)(1);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    start = (uint64_t)(POS_1BYTE_MAX - 1);
    stop = (uint64_t)(POS_1BYTE_MAX - 1);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    start = (uint64_t)(POS_1BYTE_MAX);
    stop = (uint64_t)(POS_1BYTE_MAX);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    start = (uint64_t)(POS_1BYTE_MAX + 1);
    stop = (uint64_t)(POS_1BYTE_MAX + 1);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    start = (uint64_t)(POS_2BYTE_MAX - 1);
    stop = (uint64_t)(POS_2BYTE_MAX - 1);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    start = (uint64_t)(POS_2BYTE_MAX);
    stop = (uint64_t)(POS_2BYTE_MAX);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    start = (uint64_t)(POS_2BYTE_MAX + 1);
    stop = (uint64_t)(POS_2BYTE_MAX + 1);
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(rand());
    start = (uint64_t)(rand());
    stop = (uint64_t)(rand());
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);

    fileid = (uint32_t)(rand());
    start = (uint64_t)(rand());
    stop = (uint64_t)(rand());
    test_cmp_one__wt_logop_col_truncate(session, logrec_fmt, logrec_direct, fileid, start, stop);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_row_modify(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    fileid = (uint32_t)(0);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(rand());
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(rand());
    key.data = "data";
    key.size = 4;
    value.data = "data";
    value.size = 4;
    test_cmp_one__wt_logop_row_modify(session, logrec_fmt, logrec_direct, fileid, &key, &value);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_row_put(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    fileid = (uint32_t)(0);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(rand());
    key.data = NULL;
    key.size = 0;
    value.data = NULL;
    value.size = 0;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);

    fileid = (uint32_t)(rand());
    key.data = "data";
    key.size = 4;
    value.data = "data";
    value.size = 4;
    test_cmp_one__wt_logop_row_put(session, logrec_fmt, logrec_direct, fileid, &key, &value);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_row_remove(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    WT_ITEM key;

    fileid = (uint32_t)(0);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(1);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(rand());
    key.data = NULL;
    key.size = 0;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);

    fileid = (uint32_t)(rand());
    key.data = "data";
    key.size = 4;
    test_cmp_one__wt_logop_row_remove(session, logrec_fmt, logrec_direct, fileid, &key);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_row_truncate(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t fileid;
    WT_ITEM start;
    WT_ITEM stop;
    uint32_t mode;

    fileid = (uint32_t)(0);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(0);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(1);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(1);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(POS_1BYTE_MAX - 1);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(POS_1BYTE_MAX - 1);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(POS_1BYTE_MAX);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(POS_1BYTE_MAX);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(POS_1BYTE_MAX + 1);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(POS_1BYTE_MAX + 1);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(POS_2BYTE_MAX - 1);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(POS_2BYTE_MAX - 1);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(POS_2BYTE_MAX);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(POS_2BYTE_MAX);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(POS_2BYTE_MAX + 1);
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(POS_2BYTE_MAX + 1);
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(rand());
    start.data = NULL;
    start.size = 0;
    stop.data = NULL;
    stop.size = 0;
    mode = (uint32_t)(rand());
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);

    fileid = (uint32_t)(rand());
    start.data = "data";
    start.size = 4;
    stop.data = "data";
    stop.size = 4;
    mode = (uint32_t)(rand());
    test_cmp_one__wt_logop_row_truncate(
      session, logrec_fmt, logrec_direct, fileid, &start, &stop, mode);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_checkpoint_start(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);

    test_cmp_one__wt_logop_checkpoint_start(session, logrec_fmt, logrec_direct);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_prev_lsn(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    WT_LSN prev_lsn;

    prev_lsn.l.file = (uint32_t)(0);
    prev_lsn.l.offset = (uint32_t)(0);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(1);
    prev_lsn.l.offset = (uint32_t)(1);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(POS_1BYTE_MAX - 1);
    prev_lsn.l.offset = (uint32_t)(POS_1BYTE_MAX - 1);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(POS_1BYTE_MAX);
    prev_lsn.l.offset = (uint32_t)(POS_1BYTE_MAX);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(POS_1BYTE_MAX + 1);
    prev_lsn.l.offset = (uint32_t)(POS_1BYTE_MAX + 1);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(POS_2BYTE_MAX - 1);
    prev_lsn.l.offset = (uint32_t)(POS_2BYTE_MAX - 1);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(POS_2BYTE_MAX);
    prev_lsn.l.offset = (uint32_t)(POS_2BYTE_MAX);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(POS_2BYTE_MAX + 1);
    prev_lsn.l.offset = (uint32_t)(POS_2BYTE_MAX + 1);
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(rand());
    prev_lsn.l.offset = (uint32_t)(rand());
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);

    prev_lsn.l.file = (uint32_t)(rand());
    prev_lsn.l.offset = (uint32_t)(rand());
    test_cmp_one__wt_logop_prev_lsn(session, logrec_fmt, logrec_direct, &prev_lsn);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_backup_id(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint32_t index;
    uint64_t granularity;
    const char *id;

    index = (uint32_t)(0);
    granularity = (uint64_t)(0);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(1);
    granularity = (uint64_t)(1);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(POS_1BYTE_MAX - 1);
    granularity = (uint64_t)(POS_1BYTE_MAX - 1);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(POS_1BYTE_MAX);
    granularity = (uint64_t)(POS_1BYTE_MAX);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(POS_1BYTE_MAX + 1);
    granularity = (uint64_t)(POS_1BYTE_MAX + 1);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(POS_2BYTE_MAX - 1);
    granularity = (uint64_t)(POS_2BYTE_MAX - 1);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(POS_2BYTE_MAX);
    granularity = (uint64_t)(POS_2BYTE_MAX);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(POS_2BYTE_MAX + 1);
    granularity = (uint64_t)(POS_2BYTE_MAX + 1);
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(rand());
    granularity = (uint64_t)(rand());
    id = "";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);

    index = (uint32_t)(rand());
    granularity = (uint64_t)(rand());
    id = "string";
    test_cmp_one__wt_logop_backup_id(session, logrec_fmt, logrec_direct, index, granularity, id);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all__wt_logop_txn_timestamp(
  WT_SESSION_IMPL *session, WT_ITEM *logrec_fmt, WT_ITEM *logrec_direct)
{
    uint64_t time_sec;
    uint64_t time_nsec;
    uint64_t commit_ts;
    uint64_t durable_ts;
    uint64_t first_commit_ts;
    uint64_t prepare_ts;
    uint64_t read_ts;

    time_sec = (uint64_t)(0);
    time_nsec = (uint64_t)(0);
    commit_ts = (uint64_t)(0);
    durable_ts = (uint64_t)(0);
    first_commit_ts = (uint64_t)(0);
    prepare_ts = (uint64_t)(0);
    read_ts = (uint64_t)(0);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(1);
    time_nsec = (uint64_t)(1);
    commit_ts = (uint64_t)(1);
    durable_ts = (uint64_t)(1);
    first_commit_ts = (uint64_t)(1);
    prepare_ts = (uint64_t)(1);
    read_ts = (uint64_t)(1);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(POS_1BYTE_MAX - 1);
    time_nsec = (uint64_t)(POS_1BYTE_MAX - 1);
    commit_ts = (uint64_t)(POS_1BYTE_MAX - 1);
    durable_ts = (uint64_t)(POS_1BYTE_MAX - 1);
    first_commit_ts = (uint64_t)(POS_1BYTE_MAX - 1);
    prepare_ts = (uint64_t)(POS_1BYTE_MAX - 1);
    read_ts = (uint64_t)(POS_1BYTE_MAX - 1);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(POS_1BYTE_MAX);
    time_nsec = (uint64_t)(POS_1BYTE_MAX);
    commit_ts = (uint64_t)(POS_1BYTE_MAX);
    durable_ts = (uint64_t)(POS_1BYTE_MAX);
    first_commit_ts = (uint64_t)(POS_1BYTE_MAX);
    prepare_ts = (uint64_t)(POS_1BYTE_MAX);
    read_ts = (uint64_t)(POS_1BYTE_MAX);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(POS_1BYTE_MAX + 1);
    time_nsec = (uint64_t)(POS_1BYTE_MAX + 1);
    commit_ts = (uint64_t)(POS_1BYTE_MAX + 1);
    durable_ts = (uint64_t)(POS_1BYTE_MAX + 1);
    first_commit_ts = (uint64_t)(POS_1BYTE_MAX + 1);
    prepare_ts = (uint64_t)(POS_1BYTE_MAX + 1);
    read_ts = (uint64_t)(POS_1BYTE_MAX + 1);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(POS_2BYTE_MAX - 1);
    time_nsec = (uint64_t)(POS_2BYTE_MAX - 1);
    commit_ts = (uint64_t)(POS_2BYTE_MAX - 1);
    durable_ts = (uint64_t)(POS_2BYTE_MAX - 1);
    first_commit_ts = (uint64_t)(POS_2BYTE_MAX - 1);
    prepare_ts = (uint64_t)(POS_2BYTE_MAX - 1);
    read_ts = (uint64_t)(POS_2BYTE_MAX - 1);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(POS_2BYTE_MAX);
    time_nsec = (uint64_t)(POS_2BYTE_MAX);
    commit_ts = (uint64_t)(POS_2BYTE_MAX);
    durable_ts = (uint64_t)(POS_2BYTE_MAX);
    first_commit_ts = (uint64_t)(POS_2BYTE_MAX);
    prepare_ts = (uint64_t)(POS_2BYTE_MAX);
    read_ts = (uint64_t)(POS_2BYTE_MAX);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(POS_2BYTE_MAX + 1);
    time_nsec = (uint64_t)(POS_2BYTE_MAX + 1);
    commit_ts = (uint64_t)(POS_2BYTE_MAX + 1);
    durable_ts = (uint64_t)(POS_2BYTE_MAX + 1);
    first_commit_ts = (uint64_t)(POS_2BYTE_MAX + 1);
    prepare_ts = (uint64_t)(POS_2BYTE_MAX + 1);
    read_ts = (uint64_t)(POS_2BYTE_MAX + 1);
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(rand());
    time_nsec = (uint64_t)(rand());
    commit_ts = (uint64_t)(rand());
    durable_ts = (uint64_t)(rand());
    first_commit_ts = (uint64_t)(rand());
    prepare_ts = (uint64_t)(rand());
    read_ts = (uint64_t)(rand());
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);

    time_sec = (uint64_t)(rand());
    time_nsec = (uint64_t)(rand());
    commit_ts = (uint64_t)(rand());
    durable_ts = (uint64_t)(rand());
    first_commit_ts = (uint64_t)(rand());
    prepare_ts = (uint64_t)(rand());
    read_ts = (uint64_t)(rand());
    test_cmp_one__wt_logop_txn_timestamp(session, logrec_fmt, logrec_direct, time_sec, time_nsec,
      commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);
}

WT_ATTRIBUTE_UNUSED
static void
test_cmp_all(WT_SESSION_IMPL *session)
{
    WT_ITEM logrec_fmt, logrec_direct;

    WT_CLEAR(logrec_fmt);
    assert(__wt_buf_init(session, &logrec_fmt, 0) == 0);
    WT_CLEAR(logrec_direct);
    assert(__wt_buf_init(session, &logrec_direct, 0) == 0);

    test_cmp_all__wt_logop_col_modify(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_col_put(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_col_remove(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_col_truncate(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_row_modify(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_row_put(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_row_remove(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_row_truncate(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_checkpoint_start(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_prev_lsn(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_backup_id(session, &logrec_fmt, &logrec_direct);
    test_cmp_all__wt_logop_txn_timestamp(session, &logrec_fmt, &logrec_direct);

    __wt_buf_free(session, &logrec_fmt);
    __wt_buf_free(session, &logrec_direct);
}

/*
 * Functions to compare packing and unpacking of garbage inputs.
 */

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_col_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    uint64_t recno_fmt, recno_direct;
    WT_ITEM value_fmt, value_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_col_modify_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &recno_fmt, &value_fmt);
    unpack_res_direct = __wt_logop_col_modify_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &fileid_direct, &recno_direct, &value_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_uint64_t(recno_fmt, recno_direct);
        assert_eq_size_t(value_fmt.size, value_direct.size);
        assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_col_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    data = garbage;
    unpack_res = __wt_logop_col_modify_unpack__fmt(
      session, &data, data + garbage_size, &fileid, &recno, &value);
    fprintf(stderr, "  %s returned: %d", "col_modify", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "  value[%zu]\n",
          fileid, recno, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_col_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    data = garbage;
    unpack_res = __wt_logop_col_modify_unpack__direct(
      session, &data, data + garbage_size, &fileid, &recno, &value);
    fprintf(stderr, "  %s returned: %d", "col_modify", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "  value[%zu]\n",
          fileid, recno, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_col_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    data = garbage;
    unpack_res = __wt_logop_col_modify_unpack__mirror(
      session, &data, data + garbage_size, &fileid, &recno, &value);
    fprintf(stderr, "  %s returned: %d", "col_modify", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "  value[%zu]\n",
          fileid, recno, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_col_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    uint64_t recno_fmt, recno_direct;
    WT_ITEM value_fmt, value_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_col_put_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &recno_fmt, &value_fmt);
    unpack_res_direct = __wt_logop_col_put_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &fileid_direct, &recno_direct, &value_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_uint64_t(recno_fmt, recno_direct);
        assert_eq_size_t(value_fmt.size, value_direct.size);
        assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_col_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    data = garbage;
    unpack_res =
      __wt_logop_col_put_unpack__fmt(session, &data, data + garbage_size, &fileid, &recno, &value);
    fprintf(stderr, "  %s returned: %d", "col_put", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "  value[%zu]\n",
          fileid, recno, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_col_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    data = garbage;
    unpack_res = __wt_logop_col_put_unpack__direct(
      session, &data, data + garbage_size, &fileid, &recno, &value);
    fprintf(stderr, "  %s returned: %d", "col_put", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "  value[%zu]\n",
          fileid, recno, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_col_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;
    WT_ITEM value;

    data = garbage;
    unpack_res = __wt_logop_col_put_unpack__mirror(
      session, &data, data + garbage_size, &fileid, &recno, &value);
    fprintf(stderr, "  %s returned: %d", "col_put", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "  value[%zu]\n",
          fileid, recno, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_col_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    uint64_t recno_fmt, recno_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_col_remove_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &recno_fmt);
    unpack_res_direct = __wt_logop_col_remove_unpack__direct(
      session, &data_direct, data_direct + garbage_size, &fileid_direct, &recno_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_uint64_t(recno_fmt, recno_direct);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_col_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;

    data = garbage;
    unpack_res =
      __wt_logop_col_remove_unpack__fmt(session, &data, data + garbage_size, &fileid, &recno);
    fprintf(stderr, "  %s returned: %d", "col_remove", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(
          stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "\n", fileid, recno);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_col_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;

    data = garbage;
    unpack_res =
      __wt_logop_col_remove_unpack__direct(session, &data, data + garbage_size, &fileid, &recno);
    fprintf(stderr, "  %s returned: %d", "col_remove", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(
          stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "\n", fileid, recno);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_col_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t recno;

    data = garbage;
    unpack_res =
      __wt_logop_col_remove_unpack__mirror(session, &data, data + garbage_size, &fileid, &recno);
    fprintf(stderr, "  %s returned: %d", "col_remove", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(
          stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  recno=%" PRIu64 "\n", fileid, recno);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_col_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    uint64_t start_fmt, start_direct;
    uint64_t stop_fmt, stop_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_col_truncate_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &start_fmt, &stop_fmt);
    unpack_res_direct = __wt_logop_col_truncate_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &fileid_direct, &start_direct, &stop_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_uint64_t(start_fmt, start_direct);
        assert_eq_uint64_t(stop_fmt, stop_direct);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_col_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t start;
    uint64_t stop;

    data = garbage;
    unpack_res = __wt_logop_col_truncate_unpack__fmt(
      session, &data, data + garbage_size, &fileid, &start, &stop);
    fprintf(stderr, "  %s returned: %d", "col_truncate", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  fileid=\"0x%" PRIx32 "\"  start=%" PRIu64 "  stop=%" PRIu64 "\n", fileid,
          start, stop);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_col_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t start;
    uint64_t stop;

    data = garbage;
    unpack_res = __wt_logop_col_truncate_unpack__direct(
      session, &data, data + garbage_size, &fileid, &start, &stop);
    fprintf(stderr, "  %s returned: %d", "col_truncate", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  fileid=\"0x%" PRIx32 "\"  start=%" PRIu64 "  stop=%" PRIu64 "\n", fileid,
          start, stop);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_col_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    uint64_t start;
    uint64_t stop;

    data = garbage;
    unpack_res = __wt_logop_col_truncate_unpack__mirror(
      session, &data, data + garbage_size, &fileid, &start, &stop);
    fprintf(stderr, "  %s returned: %d", "col_truncate", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  fileid=\"0x%" PRIx32 "\"  start=%" PRIu64 "  stop=%" PRIu64 "\n", fileid,
          start, stop);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_row_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM key_fmt, key_direct;
    WT_ITEM value_fmt, value_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_row_modify_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &key_fmt, &value_fmt);
    unpack_res_direct = __wt_logop_row_modify_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &fileid_direct, &key_direct, &value_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_size_t(key_fmt.size, key_direct.size);
        assert(memcmp(key_fmt.data, key_direct.data, key_fmt.size) == 0);

        assert_eq_size_t(value_fmt.size, value_direct.size);
        assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_row_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    data = garbage;
    unpack_res =
      __wt_logop_row_modify_unpack__fmt(session, &data, data + garbage_size, &fileid, &key, &value);
    fprintf(stderr, "  %s returned: %d", "row_modify", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]  value[%zu]\n", fileid,
          key.size, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_row_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    data = garbage;
    unpack_res = __wt_logop_row_modify_unpack__direct(
      session, &data, data + garbage_size, &fileid, &key, &value);
    fprintf(stderr, "  %s returned: %d", "row_modify", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]  value[%zu]\n", fileid,
          key.size, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_row_modify(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    data = garbage;
    unpack_res = __wt_logop_row_modify_unpack__mirror(
      session, &data, data + garbage_size, &fileid, &key, &value);
    fprintf(stderr, "  %s returned: %d", "row_modify", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]  value[%zu]\n", fileid,
          key.size, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_row_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM key_fmt, key_direct;
    WT_ITEM value_fmt, value_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_row_put_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &key_fmt, &value_fmt);
    unpack_res_direct = __wt_logop_row_put_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &fileid_direct, &key_direct, &value_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_size_t(key_fmt.size, key_direct.size);
        assert(memcmp(key_fmt.data, key_direct.data, key_fmt.size) == 0);

        assert_eq_size_t(value_fmt.size, value_direct.size);
        assert(memcmp(value_fmt.data, value_direct.data, value_fmt.size) == 0);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_row_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    data = garbage;
    unpack_res =
      __wt_logop_row_put_unpack__fmt(session, &data, data + garbage_size, &fileid, &key, &value);
    fprintf(stderr, "  %s returned: %d", "row_put", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]  value[%zu]\n", fileid,
          key.size, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_row_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    data = garbage;
    unpack_res =
      __wt_logop_row_put_unpack__direct(session, &data, data + garbage_size, &fileid, &key, &value);
    fprintf(stderr, "  %s returned: %d", "row_put", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]  value[%zu]\n", fileid,
          key.size, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_row_put(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;
    WT_ITEM value;

    data = garbage;
    unpack_res =
      __wt_logop_row_put_unpack__mirror(session, &data, data + garbage_size, &fileid, &key, &value);
    fprintf(stderr, "  %s returned: %d", "row_put", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]  value[%zu]\n", fileid,
          key.size, value.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_row_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM key_fmt, key_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_row_remove_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &key_fmt);
    unpack_res_direct = __wt_logop_row_remove_unpack__direct(
      session, &data_direct, data_direct + garbage_size, &fileid_direct, &key_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_size_t(key_fmt.size, key_direct.size);
        assert(memcmp(key_fmt.data, key_direct.data, key_fmt.size) == 0);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_row_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;

    data = garbage;
    unpack_res =
      __wt_logop_row_remove_unpack__fmt(session, &data, data + garbage_size, &fileid, &key);
    fprintf(stderr, "  %s returned: %d", "row_remove", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]\n", fileid, key.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_row_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;

    data = garbage;
    unpack_res =
      __wt_logop_row_remove_unpack__direct(session, &data, data + garbage_size, &fileid, &key);
    fprintf(stderr, "  %s returned: %d", "row_remove", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]\n", fileid, key.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_row_remove(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM key;

    data = garbage;
    unpack_res =
      __wt_logop_row_remove_unpack__mirror(session, &data, data + garbage_size, &fileid, &key);
    fprintf(stderr, "  %s returned: %d", "row_remove", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  fileid=\"0x%" PRIx32 "\"  key[%zu]\n", fileid, key.size);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_row_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t fileid_fmt, fileid_direct;
    WT_ITEM start_fmt, start_direct;
    WT_ITEM stop_fmt, stop_direct;
    uint32_t mode_fmt, mode_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_row_truncate_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &fileid_fmt, &start_fmt, &stop_fmt, &mode_fmt);
    unpack_res_direct = __wt_logop_row_truncate_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &fileid_direct, &start_direct, &stop_direct, &mode_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(fileid_fmt, fileid_direct);
        assert_eq_size_t(start_fmt.size, start_direct.size);
        assert(memcmp(start_fmt.data, start_direct.data, start_fmt.size) == 0);

        assert_eq_size_t(stop_fmt.size, stop_direct.size);
        assert(memcmp(stop_fmt.data, stop_direct.data, stop_fmt.size) == 0);

        assert_eq_uint32_t(mode_fmt, mode_direct);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_row_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM start;
    WT_ITEM stop;
    uint32_t mode;

    data = garbage;
    unpack_res = __wt_logop_row_truncate_unpack__fmt(
      session, &data, data + garbage_size, &fileid, &start, &stop, &mode);
    fprintf(stderr, "  %s returned: %d", "row_truncate", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  fileid=\"0x%" PRIx32 "\"  start[%zu]  stop[%zu]  mode=%" PRIu32 "\n",
          fileid, start.size, stop.size, mode);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_row_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM start;
    WT_ITEM stop;
    uint32_t mode;

    data = garbage;
    unpack_res = __wt_logop_row_truncate_unpack__direct(
      session, &data, data + garbage_size, &fileid, &start, &stop, &mode);
    fprintf(stderr, "  %s returned: %d", "row_truncate", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  fileid=\"0x%" PRIx32 "\"  start[%zu]  stop[%zu]  mode=%" PRIu32 "\n",
          fileid, start.size, stop.size, mode);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_row_truncate(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t fileid;
    WT_ITEM start;
    WT_ITEM stop;
    uint32_t mode;

    data = garbage;
    unpack_res = __wt_logop_row_truncate_unpack__mirror(
      session, &data, data + garbage_size, &fileid, &start, &stop, &mode);
    fprintf(stderr, "  %s returned: %d", "row_truncate", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  fileid=\"0x%" PRIx32 "\"  start[%zu]  stop[%zu]  mode=%" PRIu32 "\n",
          fileid, start.size, stop.size, mode);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_checkpoint_start(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt =
      __wt_logop_checkpoint_start_unpack__fmt(session, &data_fmt, data_fmt + garbage_size);
    unpack_res_direct =
      __wt_logop_checkpoint_start_unpack__direct(session, &data_direct, data_direct + garbage_size);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_checkpoint_start(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;

    data = garbage;
    unpack_res = __wt_logop_checkpoint_start_unpack__fmt(session, &data, data + garbage_size);
    fprintf(stderr, "  %s returned: %d", "checkpoint_start", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:\n");
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_checkpoint_start(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;

    data = garbage;
    unpack_res = __wt_logop_checkpoint_start_unpack__direct(session, &data, data + garbage_size);
    fprintf(stderr, "  %s returned: %d", "checkpoint_start", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:\n");
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_checkpoint_start(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;

    data = garbage;
    unpack_res = __wt_logop_checkpoint_start_unpack__mirror(session, &data, data + garbage_size);
    fprintf(stderr, "  %s returned: %d", "checkpoint_start", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:\n");
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_prev_lsn(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    WT_LSN prev_lsn_fmt, prev_lsn_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt =
      __wt_logop_prev_lsn_unpack__fmt(session, &data_fmt, data_fmt + garbage_size, &prev_lsn_fmt);
    unpack_res_direct = __wt_logop_prev_lsn_unpack__direct(
      session, &data_direct, data_direct + garbage_size, &prev_lsn_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert(prev_lsn_fmt.l.file == prev_lsn_direct.l.file);
        assert(prev_lsn_fmt.l.offset == prev_lsn_direct.l.offset);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_prev_lsn(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    WT_LSN prev_lsn;

    data = garbage;
    unpack_res = __wt_logop_prev_lsn_unpack__fmt(session, &data, data + garbage_size, &prev_lsn);
    fprintf(stderr, "  %s returned: %d", "prev_lsn", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  prev_lsn=%u:%u\n", prev_lsn.l.file, prev_lsn.l.offset);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_prev_lsn(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    WT_LSN prev_lsn;

    data = garbage;
    unpack_res = __wt_logop_prev_lsn_unpack__direct(session, &data, data + garbage_size, &prev_lsn);
    fprintf(stderr, "  %s returned: %d", "prev_lsn", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  prev_lsn=%u:%u\n", prev_lsn.l.file, prev_lsn.l.offset);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_prev_lsn(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    WT_LSN prev_lsn;

    data = garbage;
    unpack_res = __wt_logop_prev_lsn_unpack__mirror(session, &data, data + garbage_size, &prev_lsn);
    fprintf(stderr, "  %s returned: %d", "prev_lsn", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  prev_lsn=%u:%u\n", prev_lsn.l.file, prev_lsn.l.offset);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_backup_id(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint32_t index_fmt, index_direct;
    uint64_t granularity_fmt, granularity_direct;
    const char *id_fmt, *id_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_backup_id_unpack__fmt(
      session, &data_fmt, data_fmt + garbage_size, &index_fmt, &granularity_fmt, &id_fmt);
    unpack_res_direct = __wt_logop_backup_id_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &index_direct, &granularity_direct, &id_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint32_t(index_fmt, index_direct);
        assert_eq_uint64_t(granularity_fmt, granularity_direct);
        assert(!strcmp(id_fmt, id_direct));
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_backup_id(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t index;
    uint64_t granularity;
    const char *id;

    data = garbage;
    unpack_res = __wt_logop_backup_id_unpack__fmt(
      session, &data, data + garbage_size, &index, &granularity, &id);
    fprintf(stderr, "  %s returned: %d", "backup_id", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  index=%" PRIu32 "  granularity=%" PRIu64 "  id=string[%lu]\n",
          index, granularity, strlen(id));
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_backup_id(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t index;
    uint64_t granularity;
    const char *id;

    data = garbage;
    unpack_res = __wt_logop_backup_id_unpack__direct(
      session, &data, data + garbage_size, &index, &granularity, &id);
    fprintf(stderr, "  %s returned: %d", "backup_id", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  index=%" PRIu32 "  granularity=%" PRIu64 "  id=string[%lu]\n",
          index, granularity, strlen(id));
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_backup_id(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint32_t index;
    uint64_t granularity;
    const char *id;

    data = garbage;
    unpack_res = __wt_logop_backup_id_unpack__mirror(
      session, &data, data + garbage_size, &index, &granularity, &id);
    fprintf(stderr, "  %s returned: %d", "backup_id", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr, "    Fields:  index=%" PRIu32 "  granularity=%" PRIu64 "  id=string[%lu]\n",
          index, granularity, strlen(id));
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_both_one__wt_logop_txn_timestamp(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data_fmt, *data_direct;
    int unpack_res_fmt, unpack_res_direct;
    uint64_t time_sec_fmt, time_sec_direct;
    uint64_t time_nsec_fmt, time_nsec_direct;
    uint64_t commit_ts_fmt, commit_ts_direct;
    uint64_t durable_ts_fmt, durable_ts_direct;
    uint64_t first_commit_ts_fmt, first_commit_ts_direct;
    uint64_t prepare_ts_fmt, prepare_ts_direct;
    uint64_t read_ts_fmt, read_ts_direct;

    data_fmt = data_direct = garbage;
    unpack_res_fmt = __wt_logop_txn_timestamp_unpack__fmt(session, &data_fmt,
      data_fmt + garbage_size, &time_sec_fmt, &time_nsec_fmt, &commit_ts_fmt, &durable_ts_fmt,
      &first_commit_ts_fmt, &prepare_ts_fmt, &read_ts_fmt);
    unpack_res_direct = __wt_logop_txn_timestamp_unpack__direct(session, &data_direct,
      data_direct + garbage_size, &time_sec_direct, &time_nsec_direct, &commit_ts_direct,
      &durable_ts_direct, &first_commit_ts_direct, &prepare_ts_direct, &read_ts_direct);
    assert_eq_int(unpack_res_fmt, unpack_res_direct);
    if (unpack_res_fmt == 0) {
        assert_eq_size_t(WT_PTRDIFF(data_fmt, garbage), WT_PTRDIFF(data_direct, garbage));

        assert_eq_uint64_t(time_sec_fmt, time_sec_direct);
        assert_eq_uint64_t(time_nsec_fmt, time_nsec_direct);
        assert_eq_uint64_t(commit_ts_fmt, commit_ts_direct);
        assert_eq_uint64_t(durable_ts_fmt, durable_ts_direct);
        assert_eq_uint64_t(first_commit_ts_fmt, first_commit_ts_direct);
        assert_eq_uint64_t(prepare_ts_fmt, prepare_ts_direct);
        assert_eq_uint64_t(read_ts_fmt, read_ts_direct);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_fmt_one__wt_logop_txn_timestamp(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint64_t time_sec;
    uint64_t time_nsec;
    uint64_t commit_ts;
    uint64_t durable_ts;
    uint64_t first_commit_ts;
    uint64_t prepare_ts;
    uint64_t read_ts;

    data = garbage;
    unpack_res = __wt_logop_txn_timestamp_unpack__fmt(session, &data, data + garbage_size,
      &time_sec, &time_nsec, &commit_ts, &durable_ts, &first_commit_ts, &prepare_ts, &read_ts);
    fprintf(stderr, "  %s returned: %d", "txn_timestamp", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  time_sec=%" PRIu64 "  time_nsec=%" PRIu64 "  commit_ts=%" PRIu64
          "  durable_ts=%" PRIu64 "  first_commit_ts=%" PRIu64 "  prepare_ts=%" PRIu64
          "  read_ts=%" PRIu64 "\n",
          time_sec, time_nsec, commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_direct_one__wt_logop_txn_timestamp(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint64_t time_sec;
    uint64_t time_nsec;
    uint64_t commit_ts;
    uint64_t durable_ts;
    uint64_t first_commit_ts;
    uint64_t prepare_ts;
    uint64_t read_ts;

    data = garbage;
    unpack_res = __wt_logop_txn_timestamp_unpack__direct(session, &data, data + garbage_size,
      &time_sec, &time_nsec, &commit_ts, &durable_ts, &first_commit_ts, &prepare_ts, &read_ts);
    fprintf(stderr, "  %s returned: %d", "txn_timestamp", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  time_sec=%" PRIu64 "  time_nsec=%" PRIu64 "  commit_ts=%" PRIu64
          "  durable_ts=%" PRIu64 "  first_commit_ts=%" PRIu64 "  prepare_ts=%" PRIu64
          "  read_ts=%" PRIu64 "\n",
          time_sec, time_nsec, commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);
    } else {
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_mirror_one__wt_logop_txn_timestamp(
  WT_SESSION_IMPL *session, const uint8_t *garbage, size_t garbage_size)
{
    const uint8_t *data;
    int unpack_res;
    uint64_t time_sec;
    uint64_t time_nsec;
    uint64_t commit_ts;
    uint64_t durable_ts;
    uint64_t first_commit_ts;
    uint64_t prepare_ts;
    uint64_t read_ts;

    data = garbage;
    unpack_res = __wt_logop_txn_timestamp_unpack__mirror(session, &data, data + garbage_size,
      &time_sec, &time_nsec, &commit_ts, &durable_ts, &first_commit_ts, &prepare_ts, &read_ts);
    fprintf(stderr, "  %s returned: %d", "txn_timestamp", unpack_res);
    if (unpack_res == 0) {
        fprintf(stderr, " used buffer: %zu of %zu\n", WT_PTRDIFF(data, garbage), garbage_size);
        fprintf(stderr,
          "    Fields:  time_sec=%" PRIu64 "  time_nsec=%" PRIu64 "  commit_ts=%" PRIu64
          "  durable_ts=%" PRIu64 "  first_commit_ts=%" PRIu64 "  prepare_ts=%" PRIu64
          "  read_ts=%" PRIu64 "\n",
          time_sec, time_nsec, commit_ts, durable_ts, first_commit_ts, prepare_ts, read_ts);
    } else {
        fprintf(stderr, "\n");
    }
}

#define MAX_GARBAGE_SIZE 1024
#define N_GARBAGE_TESTS 1000
#define GARBAGE_RAND_SEED 1

static void
dump(const uint8_t *data, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
        fprintf(stderr, " %02x", data[i]);
}

static void
init_garbage(size_t seed, uint8_t (*garbage)[MAX_GARBAGE_SIZE], size_t *garbage_size, int verbose)
{
    size_t j;
    WT_RAND_STATE rnd;

    __wt_random_init_custom_seed(&rnd, GARBAGE_RAND_SEED + seed);
    *garbage_size = __wt_random(&rnd) % MAX_GARBAGE_SIZE;
    for (j = 0; j < MAX_GARBAGE_SIZE / sizeof(uint32_t); j++) {
        ((uint32_t *)garbage)[j] = __wt_random(&rnd);
    }
    if (verbose) {
        fprintf(stderr, ">>> %zu: [%zu]", seed, *garbage_size);
        dump(*garbage, *garbage_size);
        fprintf(stderr, "\n");
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_all(WT_SESSION_IMPL *session)
{
    size_t i;
    uint8_t garbage[MAX_GARBAGE_SIZE];
    size_t garbage_size;

    for (i = 0; i < N_GARBAGE_TESTS; i++) {
        init_garbage(i, &garbage, &garbage_size, 1);
        test_garbage_both_one__wt_logop_col_modify(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_col_put(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_col_remove(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_col_truncate(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_row_modify(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_row_put(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_row_remove(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_row_truncate(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_checkpoint_start(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_prev_lsn(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_backup_id(session, garbage, garbage_size);
        test_garbage_both_one__wt_logop_txn_timestamp(session, garbage, garbage_size);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_all_fmt(WT_SESSION_IMPL *session)
{
    size_t i;
    uint8_t garbage[MAX_GARBAGE_SIZE];
    size_t garbage_size;

    for (i = 0; i < N_GARBAGE_TESTS; i++) {
        init_garbage(i, &garbage, &garbage_size, 1);
        test_garbage_fmt_one__wt_logop_col_modify(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_col_put(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_col_remove(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_col_truncate(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_row_modify(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_row_put(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_row_remove(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_row_truncate(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_checkpoint_start(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_prev_lsn(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_backup_id(session, garbage, garbage_size);
        test_garbage_fmt_one__wt_logop_txn_timestamp(session, garbage, garbage_size);
    }
}

WT_ATTRIBUTE_UNUSED
static void
test_garbage_all_direct(WT_SESSION_IMPL *session)
{
    size_t i;
    uint8_t garbage[MAX_GARBAGE_SIZE];
    size_t garbage_size;

    for (i = 0; i < N_GARBAGE_TESTS; i++) {
        init_garbage(i, &garbage, &garbage_size, 1);
        test_garbage_direct_one__wt_logop_col_modify(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_col_put(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_col_remove(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_col_truncate(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_row_modify(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_row_put(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_row_remove(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_row_truncate(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_checkpoint_start(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_prev_lsn(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_backup_id(session, garbage, garbage_size);
        test_garbage_direct_one__wt_logop_txn_timestamp(session, garbage, garbage_size);
    }
}

WT_ATTRIBUTE_UNUSED
static inline const char *
test_list_ops(void)
{
    return "  col_modify\n"
           "  col_put\n"
           "  col_remove\n"
           "  col_truncate\n"
           "  row_modify\n"
           "  row_put\n"
           "  row_remove\n"
           "  row_truncate\n"
           "  checkpoint_start\n"
           "  prev_lsn\n"
           "  backup_id\n"
           "  txn_timestamp\n";
}

WT_ATTRIBUTE_UNUSED
static void
test_unpack_run(
  WT_SESSION_IMPL *session, char *mode, char *optype, const uint8_t *data, size_t size)
{
    if (0) {
    } else if (!strcmp(optype, "col_modify")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_col_modify(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_col_modify(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_col_modify(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "col_put")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_col_put(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_col_put(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_col_put(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "col_remove")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_col_remove(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_col_remove(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_col_remove(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "col_truncate")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_col_truncate(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_col_truncate(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_col_truncate(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "row_modify")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_row_modify(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_row_modify(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_row_modify(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "row_put")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_row_put(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_row_put(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_row_put(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "row_remove")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_row_remove(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_row_remove(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_row_remove(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "row_truncate")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_row_truncate(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_row_truncate(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_row_truncate(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "checkpoint_start")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_checkpoint_start(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_checkpoint_start(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_checkpoint_start(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "prev_lsn")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_prev_lsn(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_prev_lsn(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_prev_lsn(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "backup_id")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_backup_id(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_backup_id(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_backup_id(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else if (!strcmp(optype, "txn_timestamp")) {
        if (!strcmp(mode, "fmt")) {
            test_garbage_fmt_one__wt_logop_txn_timestamp(session, data, size);
        } else if (!strcmp(mode, "direct")) {
            test_garbage_direct_one__wt_logop_txn_timestamp(session, data, size);
        } else if (!strcmp(mode, "mirror")) {
            test_garbage_mirror_one__wt_logop_txn_timestamp(session, data, size);
        } else {
            fprintf(stderr, "Unknown mode: '%s'. Must be 'fmt' / 'direct' / 'mirror'.\n", mode);
            exit(1);
        }
    } else {
        fprintf(stderr, "Invalid optype '%s'. List of available operations:\n%s", optype,
          test_list_ops());
    }
}
