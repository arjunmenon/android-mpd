/*
 * Copyright (C) 2013 Thomas Guillem
 * http://www.musicpd.org
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
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPD_ANDROID_OUTPUT_PLUGIN_H
#define MPD_ANDROID_OUTPUT_PLUGIN_H

#include <glib.h>

struct audiotrack_output;
struct audiotrack_mixer;
extern const struct audio_output_plugin audiotrack_output_plugin;

int audiotrack_set_volume(struct audiotrack_output *ao, unsigned volume);
int audiotrack_get_volume(struct audiotrack_output *ao);
int audiotrack_set_mixer(struct audiotrack_output *ao, struct audiotrack_mixer *am);

#endif
