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

static int add_error(CURLcode error)
{
    return 0;
}

static int add_success()
{
    // Yay, success!
    printf("Yay, success!");
    return 0;
}

int meme_add(const char *file, const char *name, const char *base)
{
    CURL *curl;
    CURLcode res;

    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist=NULL;
    static const char buf[] = "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);

    /* Add meme_title to form-data */
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "meme_title",
                 CURLFORM_COPYCONTENTS, name,
                 CURLFORM_END);

    /* Add meme_base to form-data */
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "meme_base",
                 CURLFORM_COPYCONTENTS, base,
                 CURLFORM_END);

    /* Add meme_file to form-data */
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "meme_file",
                 CURLFORM_FILE, file,
                 CURLFORM_END);

    curl = curl_easy_init();
    headerlist = curl_slist_append(headerlist, buf);
    if(curl) {
        /* what URL that receives this POST */
        curl_easy_setopt(curl, CURLOPT_URL, "https://mememgmt.tk/meme/upload/");
        /* if ((argc == 2) && (!strcmp(argv[1], "noexpectheader"))) */
            /* only disable 100-continue header if explicitly requested */
            /* curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist); */
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        res = curl_easy_perform(curl);

        /* always cleanup */
        curl_easy_cleanup(curl);

        /* then cleanup the formpost chain */
        curl_formfree(formpost);
        /* free slist */
        curl_slist_free_all(headerlist);
    }
}
