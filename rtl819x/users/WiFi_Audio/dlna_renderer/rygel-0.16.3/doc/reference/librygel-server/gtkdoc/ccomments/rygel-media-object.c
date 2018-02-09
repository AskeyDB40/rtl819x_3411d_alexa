/**
 * SECTION:rygel-media-object
 * @short_description: Represents a media object (container or item).
 * 
 * <para>The derived RygelMediaContainer class represents a container, and the derived RygelMediaItem classes (RygelAudioItem, RygelImageItem and RygelVideoItem) represent media items.</para><para>These objects correspond to items and containers in the UPnP ContentDirectory&apos;s DIDL-Lite XML.</para>
 */
/**
 * RYGEL_TYPE_MEDIA_OBJECT:
 * 
 * The type for <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link>.
 */
/**
 * rygel_media_object_get_writable:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance
 * @cancellable: (in) (allow-none): A GLib.Cancellable 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Fetches a File object for any writable URI available for this object.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-object-get-writable-finish"><function>rygel_media_object_get_writable_finish()</function></link>
 */
/**
 * rygel_media_object_get_writable_finish:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Fetches a File object for any writable URI available for this object.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-object-get-writable"><function>rygel_media_object_get_writable()</function></link>
 */
/**
 * rygel_media_object_get_writables:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance
 * @cancellable: (in) (allow-none): A GLib.Cancellable 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Fetches File objects for all writable URIs available for this object.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-object-get-writables-finish"><function>rygel_media_object_get_writables_finish()</function></link>
 */
/**
 * rygel_media_object_get_writables_finish:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Fetches File objects for all writable URIs available for this object.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-object-get-writables"><function>rygel_media_object_get_writables()</function></link>
 */
/**
 * rygel_media_object_compare_string_props:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance
 */
/**
 * rygel_media_object_compare_int_props:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance
 */
/**
 * RygelMediaObject:parent-ref:
 */
/**
 * rygel_media_object_get_parent_ref:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaObject--parent-ref"><type>"parent-ref"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaObject--parent-ref"><type>"parent-ref"</type></link> property
 */
/**
 * rygel_media_object_set_parent_ref:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaObject--parent-ref"><type>"parent-ref"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaObject--parent-ref"><type>"parent-ref"</type></link> property to @value.
 */
/**
 * RygelMediaObject:title:
 */
/**
 * rygel_media_object_get_title:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaObject--title"><type>"title"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaObject--title"><type>"title"</type></link> property
 */
/**
 * rygel_media_object_set_title:
 * @self: the <link linkend="RygelMediaObject"><type>RygelMediaObject</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaObject--title"><type>"title"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaObject--title"><type>"title"</type></link> property to @value.
 */
/**
 * RygelMediaObject:
 * 
 * Represents a media object (container or item).
 * 
 * <para>The derived RygelMediaContainer class represents a container, and the derived RygelMediaItem classes (RygelAudioItem, RygelImageItem and RygelVideoItem) represent media items.</para><para>These objects correspond to items and containers in the UPnP ContentDirectory&apos;s DIDL-Lite XML.</para>
 */
/**
 * RygelMediaObjectClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-MEDIA-OBJECT:CAPS"><literal>RYGEL_TYPE_MEDIA_OBJECT</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
