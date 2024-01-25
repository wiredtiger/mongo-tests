#define NO_STRICT_PACKING_CHECK
#define PACKING_COMPATIBILITY_MODE

/* DO NOT EDIT: automatically built by log_auto-test-gen.sh */

#define NO_OPTYPE_CHECKING
#include "test_util.h"
#include "log_auto_test.h"

/* boilerplate from test_bloom.c */

#define HOME_SIZE 512

static struct {
    WT_CONNECTION *wt_conn; /* WT_CONNECTION handle */
    WT_SESSION *wt_session; /* WT_SESSION handle */

    char *config_open; /* Command-line configuration */

    uint32_t c_cache; /* Config values */
    uint32_t c_key_max;
    uint32_t c_ops;
    uint32_t c_k;      /* Number of hash iterations */
    uint32_t c_factor; /* Number of bits per item */

    WT_RAND_STATE rand;
} g;

/*
 * setup --
 *     Set up the test.
 */
static void
setup(void)
{
    WT_CONNECTION *conn;
    WT_SESSION *session;
    char config[512];
    static char home[HOME_SIZE]; /* Base home directory */

    g.c_cache = 10;
    g.c_ops = 100 * WT_THOUSAND;
    g.c_key_max = 100;
    g.c_k = 8;
    g.c_factor = 16;

    testutil_work_dir_from_path(home, HOME_SIZE, "WT_TEST");

    /* Create the home test directory for the test (delete the previous directory if it exists). */
    testutil_recreate_dir(home);

    /*
     * This test doesn't test public Wired Tiger functionality, it still needs connection and
     * session handles.
     */

    /*
     * Open configuration -- put command line configuration options at the end so they can override
     * "standard" configuration.
     */
    testutil_snprintf(config, sizeof(config),
      "create,statistics=(all),error_prefix=\"%s\",cache_size=%" PRIu32 "MB,%s", progname,
      g.c_cache, g.config_open == NULL ? "" : g.config_open);

    testutil_check(wiredtiger_open(home, NULL, config, &conn));

    testutil_check(conn->open_session(conn, NULL, NULL, &session));

    g.wt_conn = conn;
    g.wt_session = session;
}

/*
 * cleanup --
 *     Clean up the test.
 */
static void
cleanup(void)
{
    testutil_check(g.wt_session->close(g.wt_session, NULL));
    testutil_check(g.wt_conn->close(g.wt_conn, NULL));
}

/*
 * main --
 *     Test valid and invalid format strings to pack data.
 */
int
main(int argc, char **argv)
{
    (void)argc;
    (void)testutil_set_progname(argv);
    /*
     * Required on some systems to pull in parts of the library for which we have data references.
     */
    testutil_check(__wt_library_init());

    setup();

    test_garbage_all_direct((WT_SESSION_IMPL *)g.wt_session);

    cleanup();

    return (0);
}
