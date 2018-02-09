/**
 * RYGEL_TYPE_MEDIA_DEVICE:
 * 
 * The type for <link linkend="RygelMediaDevice"><type>RygelMediaDevice</type></link>.
 */
/**
 * rygel_media_device_add_interface:
 * @self: the <link linkend="RygelMediaDevice"><type>RygelMediaDevice</type></link> instance
 * @iface: (in): Name of the network interface, e.g. eth0 
 * 
 * Add a network interface the device should listen on.
 * 
 * <para>If the network interface is not already up, it will be used as soon as it&apos;s ready, otherwise it&apos;s used right away.</para>
 */
/**
 * rygel_media_device_remove_interface:
 * @self: the <link linkend="RygelMediaDevice"><type>RygelMediaDevice</type></link> instance
 * @iface: (in): Name of the network interface, e.g. eth0 
 * 
 * Remove a previously added network interface from the device.
 */
/**
 * rygel_media_device_get_interfaces:
 * @self: the <link linkend="RygelMediaDevice"><type>RygelMediaDevice</type></link> instance
 * 
 * Get a list of the network interfaces the device is currently allowed to use.
 * 
 * Returns: list of interface names. 
 */
/**
 * RygelMediaDevice:plugin:
 */
/**
 * rygel_media_device_get_plugin:
 * @self: the <link linkend="RygelMediaDevice"><type>RygelMediaDevice</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelMediaDevice--plugin"><type>"plugin"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelMediaDevice--plugin"><type>"plugin"</type></link> property
 */
/**
 * rygel_media_device_set_plugin:
 * @self: the <link linkend="RygelMediaDevice"><type>RygelMediaDevice</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelMediaDevice--plugin"><type>"plugin"</type></link> property
 * 
 * Set the value of the <link linkend="RygelMediaDevice--plugin"><type>"plugin"</type></link> property to @value.
 */
/**
 * RygelMediaDevice:
 */
/**
 * RygelMediaDeviceClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-MEDIA-DEVICE:CAPS"><literal>RYGEL_TYPE_MEDIA_DEVICE</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
