#define QUIET	(opt_quiet || opt_realquiet)

#ifdef HAVE_LIBUSB
#define USB_CONFIG 1
#define USB_TIMEOUT 0
#endif

#include <blkmaker.h>
#include <blktemplate.h>

/* Maximum number of minutes after which we consider a long dead share
 * request to have timed out and drop the entry to stop accumulating old
 * entries */
#define STALE_SHARE_TIMEOUT 120

#define JSON_INCLUDE_CONF "include"
#define JSON_LOAD_ERROR "JSON decode of file '%s' failed\n %s"
#define JSON_LOAD_ERROR_LEN strlen(JSON_LOAD_ERROR)
#define JSON_MAX_DEPTH 10
#define JSON_MAX_DEPTH_ERR "Too many levels of JSON includes (limit 10) or a loop"

/* Global variable definitions - these were declared as extern but never defined */
char *current_fullhash = NULL;
struct timeval block_timeval = {0, 0};
pthread_mutex_t ch_lock = PTHREAD_MUTEX_INITIALIZER;

static bool time_before(struct tm *tm1, struct tm *tm2)
