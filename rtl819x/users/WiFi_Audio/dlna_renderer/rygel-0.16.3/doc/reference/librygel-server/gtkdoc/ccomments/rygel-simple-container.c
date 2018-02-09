/**
 * SECTION:rygel-simple-container
 * @short_description: A simple implementation of RygelMediaContainer that keeps all RygelMediaObjects in memory. You should add children via rygel_simple_container_add_child_item().
 */
/**
 * RYGEL_TYPE_SIMPLE_CONTAINER:
 * 
 * The type for <link linkend="RygelSimpleContainer"><type>RygelSimpleContainer</type></link>.
 */
/**
 * rygel_simple_container_add_child_item:
 * @self: the <link linkend="RygelSimpleContainer"><type>RygelSimpleContainer</type></link> instance
 * @child: (in): The child item to add to the container. 
 * 
 * Adds an item to the container.
 */
/**
 * rygel_simple_container_get_all_children:
 * @self: the <link linkend="RygelSimpleContainer"><type>RygelSimpleContainer</type></link> instance
 * 
 * Get all children, including the empty children.
 * 
 * <para>This is useful when all children are empty, so get_children() would return no objects, but when you need to add items to the empty items.</para><para>This is useful only when implementing derived classes.</para>
 */
/**
 * rygel_simple_container_add_child_container:
 * @self: the <link linkend="RygelSimpleContainer"><type>RygelSimpleContainer</type></link> instance
 * 
 * Adds a child container to this container.
 * 
 * <para>The child container will only be added to the hierarchy if, or when, it contains some children.</para>
 */
/**
 * rygel_simple_container_remove_child:
 * @self: the <link linkend="RygelSimpleContainer"><type>RygelSimpleContainer</type></link> instance
 * 
 * Removes the item from the container.
 */
/**
 * rygel_simple_container_clear:
 * @self: the <link linkend="RygelSimpleContainer"><type>RygelSimpleContainer</type></link> instance
 * 
 * Removes all child items and child containers from the container.
 */
/**
 * rygel_simple_container_is_child_id_unique:
 * @self: the <link linkend="RygelSimpleContainer"><type>RygelSimpleContainer</type></link> instance
 * @child_id: (in): The ID to check for uniqueness. 
 * 
 * Check that the ID is unique within this container.
 * 
 * <para>This is useful only when implementing derived classes.</para>
 * 
 * Returns: true if the child ID is unique within this container. 
 */
/**
 * rygel_simple_container_new:
 * @id: (in): The ID of the item. This should be unique in the server. 
 * @parent: (in) (allow-none): The parent of the container. 
 * @title: (in): The title of the container. 
 * 
 * Creates a child RygelSimpleContainer.
 */
/**
 * rygel_simple_container_new_root:
 * @title: (in): The title of the container. 
 * 
 * Creates a RygelSimpleContainer as a root container.
 */
/**
 * RygelSimpleContainer:
 * 
 * A simple implementation of RygelMediaContainer that keeps all RygelMediaObjects in memory. You should add children via rygel_simple_container_add_child_item().
 */
/**
 * RygelSimpleContainerClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-SIMPLE-CONTAINER:CAPS"><literal>RYGEL_TYPE_SIMPLE_CONTAINER</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
