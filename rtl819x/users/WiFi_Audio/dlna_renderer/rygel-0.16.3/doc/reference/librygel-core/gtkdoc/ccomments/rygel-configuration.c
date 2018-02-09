/**
 * SECTION:rygel-configuration
 * @short_description: Interface for dealing with Rygel configuration.
 */
/**
 * RygelConfigurationError:
 */
/**
 * rygel_configuration_get_upnp_enabled:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_interface:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_port:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_transcoding:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_mp3_transcoder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_mp2ts_transcoder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_lpcm_transcoder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_wmv_transcoder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_aac_transcoder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_avc_transcoder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_allow_upload:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_allow_deletion:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_log_levels:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_plugin_path:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_video_upload_folder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_music_upload_folder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_picture_upload_folder:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_enabled:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_title:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_string:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_string_list:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_int:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_int_list:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_configuration_get_bool:
 * @self: the <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * RygelConfiguration:
 * 
 * Interface for dealing with Rygel configuration.
 */
/**
 * RygelConfigurationIface:
 * @get_upnp_enabled: virtual method called by <link linkend="rygel-configuration-get-upnp-enabled"><function>rygel_configuration_get_upnp_enabled()</function></link>
 * @get_interface: virtual method called by <link linkend="rygel-configuration-get-interface"><function>rygel_configuration_get_interface()</function></link>
 * @get_port: virtual method called by <link linkend="rygel-configuration-get-port"><function>rygel_configuration_get_port()</function></link>
 * @get_transcoding: virtual method called by <link linkend="rygel-configuration-get-transcoding"><function>rygel_configuration_get_transcoding()</function></link>
 * @get_mp3_transcoder: virtual method called by <link linkend="rygel-configuration-get-mp3-transcoder"><function>rygel_configuration_get_mp3_transcoder()</function></link>
 * @get_mp2ts_transcoder: virtual method called by <link linkend="rygel-configuration-get-mp2ts-transcoder"><function>rygel_configuration_get_mp2ts_transcoder()</function></link>
 * @get_lpcm_transcoder: virtual method called by <link linkend="rygel-configuration-get-lpcm-transcoder"><function>rygel_configuration_get_lpcm_transcoder()</function></link>
 * @get_wmv_transcoder: virtual method called by <link linkend="rygel-configuration-get-wmv-transcoder"><function>rygel_configuration_get_wmv_transcoder()</function></link>
 * @get_aac_transcoder: virtual method called by <link linkend="rygel-configuration-get-aac-transcoder"><function>rygel_configuration_get_aac_transcoder()</function></link>
 * @get_avc_transcoder: virtual method called by <link linkend="rygel-configuration-get-avc-transcoder"><function>rygel_configuration_get_avc_transcoder()</function></link>
 * @get_allow_upload: virtual method called by <link linkend="rygel-configuration-get-allow-upload"><function>rygel_configuration_get_allow_upload()</function></link>
 * @get_allow_deletion: virtual method called by <link linkend="rygel-configuration-get-allow-deletion"><function>rygel_configuration_get_allow_deletion()</function></link>
 * @get_log_levels: virtual method called by <link linkend="rygel-configuration-get-log-levels"><function>rygel_configuration_get_log_levels()</function></link>
 * @get_plugin_path: virtual method called by <link linkend="rygel-configuration-get-plugin-path"><function>rygel_configuration_get_plugin_path()</function></link>
 * @get_video_upload_folder: virtual method called by <link linkend="rygel-configuration-get-video-upload-folder"><function>rygel_configuration_get_video_upload_folder()</function></link>
 * @get_music_upload_folder: virtual method called by <link linkend="rygel-configuration-get-music-upload-folder"><function>rygel_configuration_get_music_upload_folder()</function></link>
 * @get_picture_upload_folder: virtual method called by <link linkend="rygel-configuration-get-picture-upload-folder"><function>rygel_configuration_get_picture_upload_folder()</function></link>
 * @get_enabled: virtual method called by <link linkend="rygel-configuration-get-enabled"><function>rygel_configuration_get_enabled()</function></link>
 * @get_title: virtual method called by <link linkend="rygel-configuration-get-title"><function>rygel_configuration_get_title()</function></link>
 * @get_string: virtual method called by <link linkend="rygel-configuration-get-string"><function>rygel_configuration_get_string()</function></link>
 * @get_string_list: virtual method called by <link linkend="rygel-configuration-get-string-list"><function>rygel_configuration_get_string_list()</function></link>
 * @get_int: virtual method called by <link linkend="rygel-configuration-get-int"><function>rygel_configuration_get_int()</function></link>
 * @get_int_list: virtual method called by <link linkend="rygel-configuration-get-int-list"><function>rygel_configuration_get_int_list()</function></link>
 * @get_bool: virtual method called by <link linkend="rygel-configuration-get-bool"><function>rygel_configuration_get_bool()</function></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="RygelConfiguration"><type>RygelConfiguration</type></link> implementations.
 */
