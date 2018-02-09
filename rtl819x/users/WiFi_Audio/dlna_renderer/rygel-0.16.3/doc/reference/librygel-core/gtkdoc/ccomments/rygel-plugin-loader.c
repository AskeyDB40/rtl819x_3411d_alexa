/**
 * SECTION:rygel-plugin-loader
 * @short_description: Responsible for plugin loading. Probes for shared library files in a specific directry and tries to grab a function with a specific name and signature, calls it. The loaded module can then add plugins to Rygel by calling the add_plugin method. NOTE: The module SHOULD make sure that plugin is not disabled by user using plugin_disabled method before creating the plugin instance and resources related to that instance.
 */
/**
 * RYGEL_TYPE_PLUGIN_LOADER:
 * 
 * The type for <link linkend="RygelPluginLoader"><type>RygelPluginLoader</type></link>.
 */
/**
 * rygel_plugin_loader_load_plugins:
 * @self: the <link linkend="RygelPluginLoader"><type>RygelPluginLoader</type></link> instance
 */
/**
 * rygel_plugin_loader_plugin_disabled:
 * @self: the <link linkend="RygelPluginLoader"><type>RygelPluginLoader</type></link> instance
 * @name: (in): the name of plugin to check for. 
 * 
 * Checks if a plugin is disabled by user
 * 
 * Returns: true if plugin is disabled, false if not. 
 */
/**
 * rygel_plugin_loader_add_plugin:
 * @self: the <link linkend="RygelPluginLoader"><type>RygelPluginLoader</type></link> instance
 */
/**
 * rygel_plugin_loader_get_plugin_by_name:
 * @self: the <link linkend="RygelPluginLoader"><type>RygelPluginLoader</type></link> instance
 */
/**
 * rygel_plugin_loader_list_plugins:
 * @self: the <link linkend="RygelPluginLoader"><type>RygelPluginLoader</type></link> instance
 */
/**
 * rygel_plugin_loader_new:
 */
/**
 * RygelPluginLoader::plugin-available:
 * @plugin_loader: the <link linkend="RygelPluginLoader"><type>RygelPluginLoader</type></link> instance that received the signal
 * @plugin: 
 */
/**
 * RygelPluginLoader:
 * 
 * Responsible for plugin loading. Probes for shared library files in a specific directry and tries to grab a function with a specific name and signature, calls it. The loaded module can then add plugins to Rygel by calling the add_plugin method. NOTE: The module SHOULD make sure that plugin is not disabled by user using plugin_disabled method before creating the plugin instance and resources related to that instance.
 */
/**
 * RygelPluginLoaderClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-PLUGIN-LOADER:CAPS"><literal>RYGEL_TYPE_PLUGIN_LOADER</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
