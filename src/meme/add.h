//
//  add.h
//  meme
//
//  Created by K E N O  on 17.06.18.
//

#ifndef MM_CHECK_H
#define MM_CHECK_H

#include <stdio.h>

#ifdef HAVE_LIBCURL
CURLcode curlerr;       /* last error produced by curl */
#endif

static int meme_add(const char *pathname, const char *filename, const char *repo);

#endif /* add_h */
