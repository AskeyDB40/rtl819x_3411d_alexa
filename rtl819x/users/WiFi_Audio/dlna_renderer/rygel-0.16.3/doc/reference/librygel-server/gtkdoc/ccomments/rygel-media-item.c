/**
 * SECTION:rygel-media-item
 * @short_description: Represents a media item (Music, Video or Image).
 * 
 * <para>These objects correspond to items in the UPnP ContentDirectory&apos;s DIDL-Lite XML.</para>
 */
/**
 * RYGEL_TYPE_MEDIA_ITEM:
 * 
 * The type for <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link>.
 */
/**
 * rygel_media_item_create_stream_source:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance
 */
/**
 * rygel_media_item_is_live_stream:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance
 */
/**
 * rygel_media_item_streamable:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance
 */
/**
 * rygel_media_item_add_uri:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance
 */
/**
 * rygel_media_item_get_protocol_info:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance
 */
/**
 * rygel_media_item_add_resources:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * RygelMediaItem:size:
 */
/**
 * rygel_media_item_get_size:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaItem--size"><type>"size"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaItem--size"><type>"size"</type></link> property
 */
/**
 * rygel_media_item_set_size:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaItem--size"><type>"size"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaItem--size"><type>"size"</type></link> property to @value.
 */
/**
 * RygelMediaItem:place-holder:
 */
/**
 * rygel_media_item_get_place_holder:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaItem--place-holder"><type>"place-holder"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaItem--place-holder"><type>"place-holder"</type></link> property
 */
/**
 * rygel_media_item_set_place_holder:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaItem--place-holder"><type>"place-holder"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaItem--place-holder"><type>"place-holder"</type></link> property to @value.
 */
/**
 * RygelMediaItem:description:
 */
/**
 * rygel_media_item_get_description:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaItem--description"><type>"description"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaItem--description"><type>"description"</type></link> property
 */
/**
 * rygel_media_item_set_description:
 * @self: the <link linkend="RygelMediaItem"><type>RygelMediaItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaItem--description"><type>"description"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaItem--description"><type>"description"</type></link> property to @value.
 */
/**
 * RygelMediaItem:
 * 
 * Represents a media item (Music, Video or Image).
 * 
 * <para>These objects correspond to items in the UPnP ContentDirectory&apos;s DIDL-Lite XML.</para>
 */
/**
 * RygelMediaItemClass:
 * @create_stream_source: virtual method called by <link linkend="rygel-media-item-create-stream-source"><function>rygel_media_item_create_stream_source()</function></link>
 * @streamable: virtual method called by <link linkend="rygel-media-item-streamable"><function>rygel_media_item_streamable()</function></link>
 * @add_uri: virtual method called by <link linkend="rygel-media-item-add-uri"><function>rygel_media_item_add_uri()</function></link>
 * @get_protocol_info: virtual method used internally
 * @add_resources: virtual method used internally
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-MEDIA-ITEM:CAPS"><literal>RYGEL_TYPE_MEDIA_ITEM</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
