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
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "https://mememgmt.tk/meme/upload");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    printf(_("%s adding meme ...\n"), cycle);
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
