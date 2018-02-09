/**
 * SECTION:rygel-media-player
 * @short_description: Interface for mapping AVTransport:2 methods to the specific implementation.
 * 
 * <para>This class is useful only when implementing Rygel plugins.</para>
 */
/**
 * rygel_media_player_seek:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance
 */
/**
 * rygel_media_player_get_protocols:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance
 * 
 * Returns: (array length=result_length1): 
 */
/**
 * rygel_media_player_get_mime_types:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance
 * 
 * Returns: (array length=result_length1): 
 */
/**
 * RygelMediaPlayer:playback-state:
 */
/**
 * rygel_media_player_get_playback_state:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--playback-state"><type>"playback-state"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--playback-state"><type>"playback-state"</type></link> property
 */
/**
 * rygel_media_player_set_playback_state:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaPlayer--playback-state"><type>"playback-state"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaPlayer--playback-state"><type>"playback-state"</type></link> property to @value.
 */
/**
 * RygelMediaPlayer:uri:
 */
/**
 * rygel_media_player_get_uri:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--uri"><type>"uri"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--uri"><type>"uri"</type></link> property
 */
/**
 * rygel_media_player_set_uri:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaPlayer--uri"><type>"uri"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaPlayer--uri"><type>"uri"</type></link> property to @value.
 */
/**
 * RygelMediaPlayer:volume:
 */
/**
 * rygel_media_player_get_volume:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--volume"><type>"volume"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--volume"><type>"volume"</type></link> property
 */
/**
 * rygel_media_player_set_volume:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaPlayer--volume"><type>"volume"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaPlayer--volume"><type>"volume"</type></link> property to @value.
 */
/**
 * RygelMediaPlayer:duration:
 */
/**
 * rygel_media_player_get_duration:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--duration"><type>"duration"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--duration"><type>"duration"</type></link> property
 */
/**
 * RygelMediaPlayer:metadata:
 */
/**
 * rygel_media_player_get_metadata:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--metadata"><type>"metadata"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--metadata"><type>"metadata"</type></link> property
 */
/**
 * rygel_media_player_set_metadata:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaPlayer--metadata"><type>"metadata"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaPlayer--metadata"><type>"metadata"</type></link> property to @value.
 */
/**
 * RygelMediaPlayer:mime-type:
 */
/**
 * rygel_media_player_get_mime_type:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--mime-type"><type>"mime-type"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--mime-type"><type>"mime-type"</type></link> property
 */
/**
 * rygel_media_player_set_mime_type:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaPlayer--mime-type"><type>"mime-type"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaPlayer--mime-type"><type>"mime-type"</type></link> property to @value.
 */
/**
 * RygelMediaPlayer:content-features:
 */
/**
 * rygel_media_player_get_content_features:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--content-features"><type>"content-features"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--content-features"><type>"content-features"</type></link> property
 */
/**
 * rygel_media_player_set_content_features:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaPlayer--content-features"><type>"content-features"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaPlayer--content-features"><type>"content-features"</type></link> property to @value.
 */
/**
 * RygelMediaPlayer:duration-as-str:
 */
/**
 * rygel_media_player_get_duration_as_str:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--duration-as-str"><type>"duration-as-str"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--duration-as-str"><type>"duration-as-str"</type></link> property
 */
/**
 * RygelMediaPlayer:position:
 */
/**
 * rygel_media_player_get_position:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--position"><type>"position"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--position"><type>"position"</type></link> property
 */
/**
 * RygelMediaPlayer:position-as-str:
 */
/**
 * rygel_media_player_get_position_as_str:
 * @self: the <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaPlayer--position-as-str"><type>"position-as-str"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaPlayer--position-as-str"><type>"position-as-str"</type></link> property
 */
/**
 * RygelMediaPlayer:
 * 
 * Interface for mapping AVTransport:2 methods to the specific implementation.
 * 
 * <para>This class is useful only when implementing Rygel plugins.</para>
 */
/**
 * RygelMediaPlayerIface:
 * @seek: virtual method called by <link linkend="rygel-media-player-seek"><function>rygel_media_player_seek()</function></link>
 * @get_protocols: virtual method called by <link linkend="rygel-media-player-get-protocols"><function>rygel_media_player_get_protocols()</function></link>
 * @get_mime_types: virtual method called by <link linkend="rygel-media-player-get-mime-types"><function>rygel_media_player_get_mime_types()</function></link>
 * @get_playback_state: getter method for the abstract property <link linkend="RygelMediaPlayer--playback-state"><type>"playback-state"</type></link>
 * @set_playback_state: setter method for the abstract property <link linkend="RygelMediaPlayer--playback-state"><type>"playback-state"</type></link>
 * @get_uri: getter method for the abstract property <link linkend="RygelMediaPlayer--uri"><type>"uri"</type></link>
 * @set_uri: setter method for the abstract property <link linkend="RygelMediaPlayer--uri"><type>"uri"</type></link>
 * @get_volume: getter method for the abstract property <link linkend="RygelMediaPlayer--volume"><type>"volume"</type></link>
 * @set_volume: setter method for the abstract property <link linkend="RygelMediaPlayer--volume"><type>"volume"</type></link>
 * @get_duration: getter method for the abstract property <link linkend="RygelMediaPlayer--duration"><type>"duration"</type></link>
 * @get_metadata: getter method for the abstract property <link linkend="RygelMediaPlayer--metadata"><type>"metadata"</type></link>
 * @set_metadata: setter method for the abstract property <link linkend="RygelMediaPlayer--metadata"><type>"metadata"</type></link>
 * @get_mime_type: getter method for the abstract property <link linkend="RygelMediaPlayer--mime-type"><type>"mime-type"</type></link>
 * @set_mime_type: setter method for the abstract property <link linkend="RygelMediaPlayer--mime-type"><type>"mime-type"</type></link>
 * @get_content_features: getter method for the abstract property <link linkend="RygelMediaPlayer--content-features"><type>"content-features"</type></link>
 * @set_content_features: setter method for the abstract property <link linkend="RygelMediaPlayer--content-features"><type>"content-features"</type></link>
 * @get_position: getter method for the abstract property <link linkend="RygelMediaPlayer--position"><type>"position"</type></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="RygelMediaPlayer"><type>RygelMediaPlayer</type></link> implementations.
 */
