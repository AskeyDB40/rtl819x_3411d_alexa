/**
 * SECTION:rygel-searchable-container
 * @short_description: The base class for searchable containers.
 * 
 * <para>Classes that implement this interface can, for instance:</para><orderedlist><listitem><para>Allow backends to implement a UPnP Search call using native searching (such as SQL or SPARQL queries).</para></listitem><listitem><para>Provide the naïve default implementation of search, from this base class, which does a recursive tree walk.</para></listitem></orderedlist><para>The search_classes property lists what information this container may be searched for. It is mapped to upnp:searchClass (with includeDerived assumed to be false),</para>
 */
/**
 * rygel_searchable_container_search:
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance
 * @expression: (in) (allow-none): the search expression or null for wildcard 
 * @offset: (in): zero-based index of the first object to return 
 * @max_count: (in): maximum number of objects to return 
 * @total_matches: (out): sets it to the actual number of objects that satisfy 
 * @cancellable: (in) (allow-none): optional cancellable for this operation. 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Recursively searches for all media objects that satisfy the given search expression in this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-searchable-container-search-finish"><function>rygel_searchable_container_search_finish()</function></link>
 */
/**
 * rygel_searchable_container_search_finish:
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Recursively searches for all media objects that satisfy the given search expression in this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-searchable-container-search"><function>rygel_searchable_container_search()</function></link>
 * 
 * Returns: A list of matching media objects or null if no object matched. 
 */
/**
 * rygel_searchable_container_simple_search:
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance
 * @expression: (in) (allow-none): the search expression or `null` for wildcard 
 * @offset: (in): zero-based index of the first object to return 
 * @max_count: (in): maximum number of objects to return 
 * @total_matches: (out): sets it to the actual number of objects that satisfy the given search expression. If it is not possible to compute this value (in a timely mannger), it is set to &apos;0&apos;. 
 * @cancellable: (in) (allow-none): optional cancellable for this operation 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Utility method that retrieves all children and recursively searches for all media objects that satisfy the given search expression in this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-searchable-container-simple-search-finish"><function>rygel_searchable_container_simple_search_finish()</function></link>
 */
/**
 * rygel_searchable_container_simple_search_finish:
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Utility method that retrieves all children and recursively searches for all media objects that satisfy the given search expression in this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-searchable-container-simple-search"><function>rygel_searchable_container_simple_search()</function></link>
 * 
 * Returns: A list of media objects. 
 */
/**
 * rygel_searchable_container_find_object:
 * @callback: function to call when result is ready 
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance
 * @id: (in): ID of the media object to search for 
 * @cancellable: (in) (allow-none): optional cancellable for this operation 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Recursively searches for media object with the given id in this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-searchable-container-find-object-finish"><function>rygel_searchable_container_find_object_finish()</function></link>
 */
/**
 * rygel_searchable_container_find_object_finish:
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Recursively searches for media object with the given id in this container.
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-searchable-container-find-object"><function>rygel_searchable_container_find_object()</function></link>
 * 
 * Returns: the found media object. 
 */
/**
 * RygelSearchableContainer:search-classes:
 */
/**
 * rygel_searchable_container_get_search_classes:
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelSearchableContainer--search-classes"><type>"search-classes"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelSearchableContainer--search-classes"><type>"search-classes"</type></link> property
 */
/**
 * rygel_searchable_container_set_search_classes:
 * @self: the <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelSearchableContainer--search-classes"><type>"search-classes"</type></link> property
 * 
 * Set the value of the <link linkend="RygelSearchableContainer--search-classes"><type>"search-classes"</type></link> property to @value.
 */
/**
 * RygelSearchableContainer:
 * 
 * The base class for searchable containers.
 * 
 * <para>Classes that implement this interface can, for instance:</para><orderedlist><listitem><para>Allow backends to implement a UPnP Search call using native searching (such as SQL or SPARQL queries).</para></listitem><listitem><para>Provide the naïve default implementation of search, from this base class, which does a recursive tree walk.</para></listitem></orderedlist><para>The search_classes property lists what information this container may be searched for. It is mapped to upnp:searchClass (with includeDerived assumed to be false),</para>
 */
/**
 * RygelSearchableContainerIface:
 * @search: virtual method called by <link linkend="rygel-searchable-container-search"><function>rygel_searchable_container_search()</function></link>
 * @search_finish: asynchronous finish function for <structfield>search</structfield>, called by <link linkend="rygel-searchable-container-search"><function>rygel_searchable_container_search()</function></link>
 * @get_search_classes: getter method for the abstract property <link linkend="RygelSearchableContainer--search-classes"><type>"search-classes"</type></link>
 * @set_search_classes: setter method for the abstract property <link linkend="RygelSearchableContainer--search-classes"><type>"search-classes"</type></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="RygelSearchableContainer"><type>RygelSearchableContainer</type></link> implementations.
 */
