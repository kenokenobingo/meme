/*
 *   add.c
 *
 *   _ __ ___   ___ _ __ ___   ___
 *  | '_ ` _ \ / _ \ '_ ` _ \ / _ \
 *  | | | | | |  __/ | | | | |  __/
 *  |_| |_| |_|\___|_| |_| |_|\___|
 *
 *
 *  Adding a new meme to the repository.
 *
 *  Created by K E N O  on 17.06.18.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <fnmatch.h>
#include <emoji.h>
/* meme */
#include "meme.h"
#include "util.h"
#include "package.h"
#include "conf.h"
#include "emoji.h"
#include "add.h"

/* Initialize curl library */
static int init_add_meme () {
    CURL *curl = curl_easy_init();
}

static int meme_add(const char *pathname, const char *filename, const char *rootmeme, const char *repo)
{
 // File
 // Name
    if(curl) {
        printf(_("%s adding meme ...\n"), cycle);
        /* upload to this place */
        curl_easy_setopt(curl, CURLOPT_URL,
                         "https://mememgmt.tk/meme/upload");

        /* tell it to "upload" to the URL */
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        /* set where to read from */
        curl_easy_setopt(curl, CURLOPT_READDATA, fd);

        /* and give the size of the upload (optional) */
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                         (curl_off_t)file_info.st_size);

        /* enable verbose for easier tracing */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }
        else {
            /* now extract transfer info */
            curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &total_time);

            fprintf(stderr, "Speed: %" CURL_FORMAT_CURL_OFF_T " bytes/sec during %"
            CURL_FORMAT_CURL_OFF_T ".%06ld seconds\n",
                    speed_upload,
                    (total_time / 1000000), (long)(total_time % 1000000));
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    return 0;
}

static int add_error()
{
    if(file_is_remote == NULL) {
        mm_printf(ALPM_LOG_ERROR, _("%s memory exhausted\n"), exhausted);
        return 1;
    }

    // Global Handling?

    return 0;
}

static int add_success()
{
    // Yay
    return 0;
}
