/**
 * SECTION:rygel-plugin
 * @short_description: Represents a Rygel plugin. Plugins are supposed to provide an object of this class or a subclass.
 */
/**
 * RYGEL_TYPE_PLUGIN:
 * 
 * The type for <link linkend="RygelPlugin"><type>RygelPlugin</type></link>.
 */
/**
 * rygel_plugin_add_resource:
 * @self: the <link linkend="RygelPlugin"><type>RygelPlugin</type></link> instance
 */
/**
 * rygel_plugin_add_icon:
 * @self: the <link linkend="RygelPlugin"><type>RygelPlugin</type></link> instance
 */
/**
 * rygel_plugin_apply_hacks:
 * @self: the <link linkend="RygelPlugin"><type>RygelPlugin</type></link> instance
 * @error: location to store the error occuring, or %NULL to ignore
 */
/**
 * rygel_plugin_new:
 */
/**
 * RygelPlugin:active:
 */
/**
 * rygel_plugin_get_active:
 * @self: the <link linkend="RygelPlugin"><type>RygelPlugin</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelPlugin--active"><type>"active"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelPlugin--active"><type>"active"</type></link> property
 */
/**
 * rygel_plugin_set_active:
 * @self: the <link linkend="RygelPlugin"><type>RygelPlugin</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelPlugin--active"><type>"active"</type></link> property
 * 
 * Set the value of the <link linkend="RygelPlugin--active"><type>"active"</type></link> property to @value.
 */
/**
 * RygelPlugin:
 * 
 * Represents a Rygel plugin. Plugins are supposed to provide an object of this class or a subclass.
 */
/**
 * RygelPluginClass:
 * @apply_hacks: virtual method called by <link linkend="rygel-plugin-apply-hacks"><function>rygel_plugin_apply_hacks()</function></link>
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-PLUGIN:CAPS"><literal>RYGEL_TYPE_PLUGIN</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
