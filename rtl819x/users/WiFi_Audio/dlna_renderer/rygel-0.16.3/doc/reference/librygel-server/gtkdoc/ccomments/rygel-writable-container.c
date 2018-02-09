/**
 * SECTION:rygel-writable-container
 * @short_description: This interface should be implemented by &apos;writable&apos; containers - ones that allow adding, removal and editing of items directly under them. Currently, only addition and removal is supported.
 * 
 * <para>In addition to implementing this interface, a writable container must also:</para><orderedlist><listitem><para>Provide one URI that points to a writable folder on a GIO-supported filesystem.</para></listitem><listitem><para>Monitor not only its own URI but also that of its child items, though the latter is implied in the former if you use GIO for monitoring.</para></listitem></orderedlist>
 */
/**
 * rygel_writable_container_can_create:
 * @self: the <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> instance
 * @upnp_class: (in): The upnp class of an item to check 
 * 
 * Check if this container can contain an item with the given upnp class, meaning that rygel_writable_container_add_item() should succeed.
 * 
 * Returns: true if it can, false, if not. 
 */
/**
 * rygel_writable_container_add_item:
 * @self: the <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> instance
 * @item: (in): The item to add to this container 
 * @cancellable: (in) (allow-none): optional cancellable for this operation 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Add a new item directly under this container.
 * 
 * <para>The caller should not first create the file(s) pointed to by the item&apos;s URI(s). That is handled by the container class.</para><para>This method corresponds to the UPnP ContentDirectory&apos;s CreateObject action. Currently there is no way to add child containers.</para>
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-writable-container-add-item-finish"><function>rygel_writable_container_add_item_finish()</function></link>
 */
/**
 * rygel_writable_container_add_item_finish:
 * @self: the <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Add a new item directly under this container.
 * 
 * <para>The caller should not first create the file(s) pointed to by the item&apos;s URI(s). That is handled by the container class.</para><para>This method corresponds to the UPnP ContentDirectory&apos;s CreateObject action. Currently there is no way to add child containers.</para>
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-writable-container-add-item"><function>rygel_writable_container_add_item()</function></link>
 * 
 * Returns: nothing. 
 */
/**
 * rygel_writable_container_remove_item:
 * @self: the <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> instance
 * @id: (in): The ID of the item to remove from this container 
 * @cancellable: (in) (allow-none): optional cancellable for this operation 
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * Remove an item directly under this container that has the ID @id.
 * 
 * <para>The caller should not first remove the file(s) pointed to by the item&apos;s URI(s). That is handled by the container class.</para><para>This method corresponds to the UPnP ContentDirectory&apos;s DestroyObject action.</para>
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-writable-container-remove-item-finish"><function>rygel_writable_container_remove_item_finish()</function></link>
 */
/**
 * rygel_writable_container_remove_item_finish:
 * @self: the <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Remove an item directly under this container that has the ID @id.
 * 
 * <para>The caller should not first remove the file(s) pointed to by the item&apos;s URI(s). That is handled by the container class.</para><para>This method corresponds to the UPnP ContentDirectory&apos;s DestroyObject action.</para>
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-writable-container-remove-item"><function>rygel_writable_container_remove_item()</function></link>
 * 
 * Returns: nothing. 
 */
/**
 * RygelWritableContainer:create-classes:
 * 
 * The list of upnp classes that can be added to this container.
 * 
 * <para>See rygel_writable_container_add_item().</para><para>This corresponds to the UPnP ContentDirectory&apos;s createClass properties.</para>
 */
/**
 * rygel_writable_container_get_create_classes:
 * @self: the <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelWritableContainer--create-classes"><type>"create-classes"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelWritableContainer--create-classes"><type>"create-classes"</type></link> property
 */
/**
 * rygel_writable_container_set_create_classes:
 * @self: the <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelWritableContainer--create-classes"><type>"create-classes"</type></link> property
 * 
 * Set the value of the <link linkend="RygelWritableContainer--create-classes"><type>"create-classes"</type></link> property to @value.
 */
/**
 * RygelWritableContainer:
 * 
 * This interface should be implemented by &apos;writable&apos; containers - ones that allow adding, removal and editing of items directly under them. Currently, only addition and removal is supported.
 * 
 * <para>In addition to implementing this interface, a writable container must also:</para><orderedlist><listitem><para>Provide one URI that points to a writable folder on a GIO-supported filesystem.</para></listitem><listitem><para>Monitor not only its own URI but also that of its child items, though the latter is implied in the former if you use GIO for monitoring.</para></listitem></orderedlist>
 */
/**
 * RygelWritableContainerIface:
 * @add_item: virtual method called by <link linkend="rygel-writable-container-add-item"><function>rygel_writable_container_add_item()</function></link>
 * @add_item_finish: asynchronous finish function for <structfield>add_item</structfield>, called by <link linkend="rygel-writable-container-add-item"><function>rygel_writable_container_add_item()</function></link>
 * @remove_item: virtual method called by <link linkend="rygel-writable-container-remove-item"><function>rygel_writable_container_remove_item()</function></link>
 * @remove_item_finish: asynchronous finish function for <structfield>remove_item</structfield>, called by <link linkend="rygel-writable-container-remove-item"><function>rygel_writable_container_remove_item()</function></link>
 * @get_create_classes: getter method for the abstract property <link linkend="RygelWritableContainer--create-classes"><type>"create-classes"</type></link>
 * @set_create_classes: setter method for the abstract property <link linkend="RygelWritableContainer--create-classes"><type>"create-classes"</type></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="RygelWritableContainer"><type>RygelWritableContainer</type></link> implementations.
 */
