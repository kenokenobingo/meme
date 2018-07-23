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
#include <fnmatch.h>
#include <fcntl.h>

#include <alpm.h>
#include <alpm_list.h>

/* libcurl */
#ifdef HAVE_LIBCURL
#include <curl/curl.h>
#endif

/* meme */
#include "meme.h"
#include "util.h"
#include "package.h"
#include "conf.h"
#include "emoji.h"
#include "add.h"

/* Initialize curl library */

static int add_error(const char *error)
{
    return 0;
}

static int add_success()
{
    // Yay, success!
    printf("Yay, success!");
    return 0;
}

static int meme_upload_api(const char *pathname, const char *filename, const char *rootmeme, const char *repo)
{
    CURL *curl = curl_easy_init();
    CURLcode res;
    struct stat file_info;
    curl_off_t speed_upload, total_time;
    FILE *fd;

    init_add_meme();
    fd = fopen("debugit", "rb"); /* open file to upload */
    if(!fd)
        return 1; /* can't continue */

    /* to get the file size */
    if(fstat(fileno(fd), &file_info) != 0)
        return 1; /* can't continue */
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
                         (curl_off_t) file_info.st_size);

        /* enable verbose for easier tracing */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            add_error(res);
        } else {
            /* now extract transfer info */
            curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &total_time);

            fprintf(stderr, "Speed: %"
            CURL_FORMAT_CURL_OFF_T
            " bytes/sec during %"
            CURL_FORMAT_CURL_OFF_T
            ".%06ld seconds\n",
                    speed_upload,
                    (total_time / 1000000), (long) (total_time % 1000000));
            add_success();
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    fclose(fd);
    return 0;
}
