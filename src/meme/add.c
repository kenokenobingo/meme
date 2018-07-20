/*
 *  add.c
 *
 *  _ __ ___   ___ _ __ ___   ___
 * | '_ ` _ \ / _ \ '_ ` _ \ / _ \
 * | | | | | |  __/ | | | | |  __/
 * |_| |_| |_|\___|_| |_| |_|\___|
 *
 *
 * Adding a new meme to the repository.
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

    // Global Handling?
    return 0;
}

static int add_success()
{
    // Yay
    return 0;
}




int meme_upgrade(alpm_list_t *targets)
{
    int retval = 0, *file_is_remote;
    alpm_list_t *i;
    unsigned int n, num_targets;

    if(targets == NULL) {
        mm_printf(ALPM_LOG_ERROR, _("%s no targets specified (use -h for help)\n"), error);
        return 1;
    }

    num_targets = alpm_list_count(targets);

    /* Check for URL targets and process them */
    file_is_remote = malloc(num_targets * sizeof(int));
    if(file_is_remote == NULL) {
        mm_printf(ALPM_LOG_ERROR, _("%s memory exhausted\n"), exhausted);
        return 1;
    }

    for(i = targets, n = 0; i; i = alpm_list_next(i), n++) {
        if(strstr(i->data, "://")) {
            char *str = alpm_fetch_pkgurl(config->handle, i->data);
            if(str == NULL) {
                mm_printf(ALPM_LOG_ERROR, "'%s': %s\n",
                          (char *)i->data, alpm_strerror(alpm_errno(config->handle)));
                retval = 1;
            } else {
                free(i->data);
                i->data = str;
                file_is_remote[n] = 1;
            }
        } else {
            file_is_remote[n] = 0;
        }
    }

    if(retval) {
        goto fail_free;
    }

    /* Step 1: create a new transaction */
    if(trans_init(config->flags, 1) == -1) {
        retval = 1;
        goto fail_free;
    }

    printf(_("%s loading memes ...\n"), cycle);
    /* add targets to the created transaction */
    for(i = targets, n = 0; i; i = alpm_list_next(i), n++) {
        const char *targ = i->data;
        alpm_pkg_t *pkg;
        int siglevel;

        if(file_is_remote[n]) {
            siglevel = alpm_option_get_remote_file_siglevel(config->handle);
        } else {
            siglevel = alpm_option_get_local_file_siglevel(config->handle);
        }

        if(alpm_pkg_load(config->handle, targ, 1, siglevel, &pkg) != 0) {
            mm_printf(ALPM_LOG_ERROR, "'%s': %s\n",
                      targ, alpm_strerror(alpm_errno(config->handle)));
            retval = 1;
            continue;
        }
        if(alpm_add_pkg(config->handle, pkg) == -1) {
            mm_printf(ALPM_LOG_ERROR, "'%s': %s\n",
                      targ, alpm_strerror(alpm_errno(config->handle)));
            alpm_pkg_free(pkg);
            retval = 1;
            continue;
        }
        config->explicit_adds = alpm_list_add(config->explicit_adds, pkg);
    }

    if(retval) {
        goto fail_release;
    }

    free(file_is_remote);

    /* now that targets are resolved, we can hand it all off to the sync code */
    return sync_prepare_execute();

    fail_release:
    trans_release();
    fail_free:
    free(file_is_remote);

    return retval;
}