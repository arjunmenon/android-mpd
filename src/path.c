/* the Music Player Daemon (MPD)
 * Copyright (C) 2003-2007 by Warren Dukes (warren.dukes@gmail.com)
 * This project's homepage is: http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "path.h"
#include "log.h"
#include "conf.h"
#include "utf8.h"
#include "utils.h"
#include "playlist.h"
#include "os_compat.h"

#ifdef HAVE_LOCALE
#ifdef HAVE_LANGINFO_CODESET
#include <locale.h>
#include <langinfo.h>
#endif
#endif

#include <glib.h>

static const char *playlistDir;
static size_t playlist_dir_len;
static char *fsCharset;

char *fs_charset_to_utf8(char *dst, const char *str)
{
	gchar *p;
	GError *error = NULL;

	p = g_convert(str, -1,
		      fsCharset, "utf-8",
		      NULL, NULL, &error);
	if (p == NULL)
		/* no fallback */
		return NULL;

	g_strlcpy(dst, p, MPD_PATH_MAX);
	g_free(p);
	return dst;
}

char *utf8_to_fs_charset(char *dst, const char *str)
{
	gchar *p;
	GError *error = NULL;

	p = g_convert(str, -1,
		      "utf-8", fsCharset,
		      NULL, NULL, &error);
	if (p == NULL) {
		/* fall back to UTF-8 */
		g_error_free(error);
		return strcpy(dst, str);
	}

	g_strlcpy(dst, p, MPD_PATH_MAX);
	g_free(p);
	return dst;
}

void setFsCharset(const char *charset)
{
	int error = 0;

	if (fsCharset)
		free(fsCharset);

	fsCharset = xstrdup(charset);

	DEBUG("setFsCharset: fs charset is: %s\n", fsCharset);

	if (error) {
		free(fsCharset);
		WARNING("setting fs charset to ISO-8859-1!\n");
		fsCharset = xstrdup("ISO-8859-1");
	}
}

const char *getFsCharset(void)
{
	return fsCharset;
}

void initPaths(void)
{
	ConfigParam *playlistParam = parseConfigFilePath(CONF_PLAYLIST_DIR, 1);
	ConfigParam *fsCharsetParam = getConfigParam(CONF_FS_CHARSET);

	char *charset = NULL;
	char *originalLocale;
	DIR *dir;

	playlistDir = xstrdup(playlistParam->value);
	playlist_dir_len = strlen(playlistDir);

	if ((dir = opendir(playlistDir)) == NULL) {
		ERROR("cannot open %s \"%s\" (config line %i): %s\n",
		      CONF_PLAYLIST_DIR, playlistParam->value,
		      playlistParam->line, strerror(errno));
	} else
		closedir(dir);

	if (fsCharsetParam) {
		charset = xstrdup(fsCharsetParam->value);
	}
#ifdef HAVE_LOCALE
#ifdef HAVE_LANGINFO_CODESET
	else if ((originalLocale = setlocale(LC_CTYPE, NULL))) {
		char *temp;
		char *currentLocale;
		originalLocale = xstrdup(originalLocale);

		if (!(currentLocale = setlocale(LC_CTYPE, ""))) {
			WARNING("problems setting current locale with "
				"setlocale()\n");
		} else {
			if (strcmp(currentLocale, "C") == 0 ||
			    strcmp(currentLocale, "POSIX") == 0) {
				WARNING("current locale is \"%s\"\n",
					currentLocale);
			} else if ((temp = nl_langinfo(CODESET))) {
				charset = xstrdup(temp);
			} else
				WARNING
				    ("problems getting charset for locale\n");
			if (!setlocale(LC_CTYPE, originalLocale)) {
				WARNING
				    ("problems resetting locale with setlocale()\n");
			}
		}

		free(originalLocale);
	} else
		WARNING("problems getting locale with setlocale()\n");
#endif
#endif

	if (charset) {
		setFsCharset(charset);
		free(charset);
	} else {
		WARNING("setting filesystem charset to ISO-8859-1\n");
		setFsCharset("ISO-8859-1");
	}
}

void finishPaths(void)
{
	free(fsCharset);
	fsCharset = NULL;
}

char *pfx_dir(char *dst,
              const char *path, const size_t path_len,
              const char *pfx, const size_t pfx_len)
{
	if (mpd_unlikely((pfx_len + path_len + 1) >= MPD_PATH_MAX))
		FATAL("Cannot prefix '%s' to '%s', PATH_MAX: %d\n",
		      pfx, path, MPD_PATH_MAX);

	/* memmove allows dst == path */
	memmove(dst + pfx_len + 1, path, path_len + 1);
	memcpy(dst, pfx, pfx_len);
	dst[pfx_len] = '/';

	/* this is weird, but directory.c can use it more safely/efficiently */
	return (dst + pfx_len + 1);
}

char *rpp2app_r(char *dst, const char *rel_path)
{
	pfx_dir(dst, rel_path, strlen(rel_path),
	        (const char *)playlistDir, playlist_dir_len);
	return dst;
}

char *sanitizePathDup(const char *path)
{
	int len = strlen(path) + 1;
	char *ret = xmalloc(len);
	char *cp = ret;

	memset(ret, 0, len);

	len = 0;

	/* eliminate more than one '/' in a row, like "///" */
	while (*path) {
		while (*path == '/')
			path++;
		if (*path == '.') {
			/* we don't want to have hidden directories, or '.' or
			   ".." in our path */
			free(ret);
			return NULL;
		}
		while (*path && *path != '/') {
			*(cp++) = *(path++);
			len++;
		}
		if (*path == '/') {
			*(cp++) = *(path++);
			len++;
		}
	}

	if (len && ret[len - 1] == '/') {
		len--;
		ret[len] = '\0';
	}

	DEBUG("sanitized: %s\n", ret);

	return xrealloc(ret, len + 1);
}

void utf8_to_fs_playlist_path(char *path_max_tmp, const char *utf8path)
{
	utf8_to_fs_charset(path_max_tmp, utf8path);
	rpp2app_r(path_max_tmp, path_max_tmp);
	strncat(path_max_tmp, "." PLAYLIST_FILE_SUFFIX, MPD_PATH_MAX - 1);
}
