/**
 * SECTION:rygel-media-container
 * @short_description: This is a container (folder) for media items and child containers.
 * 
 * <para>It provides a basic serialization implementation (to DIDLLiteWriter).</para><para>A derived class should provide a working implementation of get_children and should emit the container_updated signal.</para>
 */
/**
 * RYGEL_TYPE_MEDIA_CONTAINER:
 * 
 * The type for <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link>.
 */
/**
 * rygel_media_container_get_children:
 * @self: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance
 * @offset: (in): zero-based index of the first item to return 
 * @max_count: (in): maximum number of objects to return 
 * @sort_criteria: (in): sorting order of objects to return 
 * @cancellable: (in) (allow-none): optional cancellable for this operation 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Fetches the list of media objects directly under this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-container-get-children-finish"><function>rygel_media_container_get_children_finish()</function></link>
 */
/**
 * rygel_media_container_get_children_finish:
 * @self: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Fetches the list of media objects directly under this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-container-get-children"><function>rygel_media_container_get_children()</function></link>
 * 
 * Returns: A list of media objects. 
 */
/**
 * rygel_media_container_find_object:
 * @self: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance
 * @id: (in): ID of the media object to search for 
 * @cancellable: (in) (allow-none): optional cancellable for this operation 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Recursively searches this container for a media object with the given ID.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-container-find-object-finish"><function>rygel_media_container_find_object_finish()</function></link>
 */
/**
 * rygel_media_container_find_object_finish:
 * @self: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Recursively searches this container for a media object with the given ID.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-media-container-find-object"><function>rygel_media_container_find_object()</function></link>
 * 
 * Returns: the found media object. 
 */
/**
 * rygel_media_container_updated:
 * @self: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance
 * 
 * This method should be called each time this container is updated.
 * 
 * <para>For instance, this should be called if there are metadata changes for this container, if items under it are removed or added, if there are metadata changes to items under it, etc.</para>
 */
/**
 * RYGEL_MEDIA_CONTAINER_UPNP_CLASS:
 */
/**
 * RYGEL_MEDIA_CONTAINER_STORAGE_FOLDER:
 */
/**
 * RYGEL_MEDIA_CONTAINER_MUSIC_ALBUM:
 */
/**
 * RYGEL_MEDIA_CONTAINER_MUSIC_ARTIST:
 */
/**
 * RYGEL_MEDIA_CONTAINER_MUSIC_GENRE:
 */
/**
 * RYGEL_MEDIA_CONTAINER_ALBUM_SORT_CRITERIA:
 */
/**
 * RygelMediaContainer:sort-criteria:
 */
/**
 * rygel_media_container_get_sort_criteria:
 * @self: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaContainer--sort-criteria"><type>"sort-criteria"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaContainer--sort-criteria"><type>"sort-criteria"</type></link> property
 */
/**
 * rygel_media_container_set_sort_criteria:
 * @self: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaContainer--sort-criteria"><type>"sort-criteria"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaContainer--sort-criteria"><type>"sort-criteria"</type></link> property to @value.
 */
/**
 * RygelMediaContainer::container-updated:
 * @media_container: the <link linkend="RygelMediaContainer"><type>RygelMediaContainer</type></link> instance that received the signal
 * @container: The child container that has been updated. <para></para>
 * 
 * The container_updated signal is emitted if a child container under the tree of this container has been updated.
 */
/**
 * RygelMediaContainer:
 * 
 * This is a container (folder) for media items and child containers.
 * 
 * <para>It provides a basic serialization implementation (to DIDLLiteWriter).</para><para>A derived class should provide a working implementation of get_children and should emit the container_updated signal.</para>
 */
/**
 * RygelMediaContainerClass:
 * @get_children: virtual method called by <link linkend="rygel-media-container-get-children"><function>rygel_media_container_get_children()</function></link>
 * @get_children_finish: asynchronous finish function for <structfield>get_children</structfield>, called by <link linkend="rygel-media-container-get-children"><function>rygel_media_container_get_children()</function></link>
 * @find_object: virtual method called by <link linkend="rygel-media-container-find-object"><function>rygel_media_container_find_object()</function></link>
 * @find_object_finish: asynchronous finish function for <structfield>find_object</structfield>, called by <link linkend="rygel-media-container-find-object"><function>rygel_media_container_find_object()</function></link>
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-MEDIA-CONTAINER:CAPS"><literal>RYGEL_TYPE_MEDIA_CONTAINER</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
