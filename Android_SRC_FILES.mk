LOCAL_SRC_FILES := src/archive_api.c \
	src/archive_list.c \
	src/archive_plugin.c \
	src/filter/null_filter_plugin.c \
	src/filter/chain_filter_plugin.c \
	src/filter/autoconvert_filter_plugin.c \
	src/filter/convert_filter_plugin.c \
	src/filter/route_filter_plugin.c \
	src/filter/normalize_filter_plugin.c \
	src/filter/replay_gain_filter_plugin.c \
	src/filter/volume_filter_plugin.c \
	src/input/archive_input_plugin.c \
	src/decoder/pcm_decoder_plugin.c \
	src/decoder/dsdiff_decoder_plugin.c \
	src/decoder/dsf_decoder_plugin.c \
	src/decoder/dsdlib.c \
	src/decoder_buffer.c \
	src/decoder_plugin.c \
	src/decoder_list.c \
	src/decoder/_ogg_common.c \
	src/decoder/ffmpeg_metadata.c \
	src/decoder/ffmpeg_decoder_plugin.c \
	src/encoder_list.c \
	src/encoder/null_encoder.c \
	src/input_init.c \
	src/input_registry.c \
	src/input_stream.c \
	src/input_internal.c \
	src/input/rewind_input_plugin.c \
	src/input/file_input_plugin.c \
	src/input/curl_input_plugin.c \
	src/icy_metadata.c \
	src/input/ffmpeg_input_plugin.c \
	src/mixer/software_mixer_plugin.c \
	src/mixer/opensles_android_mixer_plugin.c \
	src/mixer/audiotrack_mixer_plugin.c \
	src/output/opensles_android_output_plugin.c \
	src/output/audiotrack_output_plugin.c \
	src/output/null_output_plugin.c \
	src/icy_server.c \
	src/pcm_buffer.c \
	src/pcm_export.c \
	src/pcm_convert.c \
	src/dsd2pcm/dsd2pcm.c \
	src/pcm_dsd.c \
	src/pcm_dsd_usb.c \
	src/pcm_volume.c \
	src/pcm_mix.c \
	src/pcm_channels.c \
	src/pcm_pack.c \
	src/pcm_format.c \
	src/pcm_resample.c \
	src/pcm_resample_fallback.c \
	src/pcm_dither.c \
	src/playlist/extm3u_playlist_plugin.c \
	src/playlist/m3u_playlist_plugin.c \
	src/playlist/pls_playlist_plugin.c \
	src/playlist/xspf_playlist_plugin.c \
	src/playlist/asx_playlist_plugin.c \
	src/playlist/rss_playlist_plugin.c \
	src/playlist/cue_playlist_plugin.c \
	src/playlist/embcue_playlist_plugin.c \
	src/playlist/soundcloud_playlist_plugin.c \
	src/playlist_list.c \
	src/ape.c \
	src/replay_gain_ape.c \
	src/tag_ape.c \
	src/riff.c \
	src/aiff.c \
        src/util/list_sort.c \
        src/util/byte_reverse.c \
        src/util/bit_reverse.c \
	src/song_sort.c \
	src/output_list.c \
	src/output_all.c \
	src/output_thread.c \
	src/output_control.c \
	src/output_state.c \
	src/output_print.c \
	src/output_command.c \
	src/output_plugin.c \
	src/output_finish.c \
	src/output_init.c \
	src/mixer_control.c \
	src/mixer_type.c \
	src/mixer_all.c \
	src/mixer_api.c \
	src/clock.c \
	src/notify.c \
	src/audio_config.c \
	src/audio_check.c \
	src/audio_format.c \
	src/audio_parser.c \
	src/protocol/argparser.c \
	src/protocol/result.c \
	src/command.c \
	src/idle.c \
	src/cmdline.c \
	src/conf.c \
	src/crossfade.c \
	src/cue/cue_parser.c \
	src/dbUtils.c \
	src/decoder_thread.c \
	src/decoder_control.c \
	src/decoder_api.c \
	src/decoder_internal.c \
	src/decoder_print.c \
	src/directory.c \
	src/directory_save.c \
	src/database.c \
	src/db_lock.c \
	src/db_save.c \
	src/db_print.c \
	src/db/simple_db_plugin.c \
	src/exclude.c \
	src/fd_util.c \
	src/fifo_buffer.c \
	src/growing_fifo.c \
	src/filter_config.c \
	src/filter_plugin.c \
	src/filter_registry.c \
	src/update.c \
	src/update_queue.c \
	src/update_io.c \
	src/update_db.c \
	src/update_walk.c \
	src/update_song.c \
	src/update_container.c \
	src/update_remove.c \
	src/client.c \
	src/client_event.c \
	src/client_expire.c \
	src/client_global.c \
	src/client_idle.c \
	src/client_list.c \
	src/client_new.c \
	src/client_process.c \
	src/client_read.c \
	src/client_write.c \
	src/client_message.c \
	src/client_subscribe.c \
	src/client_file.c \
	src/server_socket.c \
	src/listen.c \
	src/log.c \
	src/ls.c \
	src/io_thread.c \
	src/event_pipe.c \
	src/daemon.c \
	src/AudioCompress/compress.c \
	src/buffer.c \
	src/pipe.c \
	src/chunk.c \
	src/path.c \
	src/mapper.c \
	src/page.c \
	src/permission.c \
	src/player_thread.c \
	src/player_control.c \
	src/playlist.c \
	src/playlist_global.c \
	src/playlist_control.c \
	src/playlist_edit.c \
	src/playlist_print.c \
	src/playlist_save.c \
	src/playlist_mapper.c \
	src/playlist_any.c \
	src/playlist_song.c \
	src/playlist_state.c \
	src/playlist_queue.c \
	src/playlist_vector.c \
	src/playlist_database.c \
	src/queue.c \
	src/queue_print.c \
	src/queue_save.c \
	src/replay_gain_config.c \
	src/replay_gain_info.c \
	src/sig_handlers.c \
	src/song.c \
	src/song_update.c \
	src/song_print.c \
	src/song_save.c \
	src/resolver.c \
	src/socket_util.c \
	src/state_file.c \
	src/stats.c \
	src/tag.c \
	src/tag_pool.c \
	src/tag_print.c \
	src/tag_save.c \
	src/tag_handler.c \
	src/tag_file.c \
	src/tokenizer.c \
	src/text_file.c \
	src/text_input_stream.c \
	src/strset.c \
	src/uri.c \
	src/utils.c \
	src/string_util.c \
	src/volume.c \
	src/locate.c \
	src/stored_playlist.c \
	src/timer.c \
	src/inotify_source.c \
	src/inotify_queue.c \
	src/inotify_update.c \
	src/sticker.c \
	src/sticker_print.c \
	src/song_sticker.c \
	src/libmpd.c
