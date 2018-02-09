/**
 * FREE_DESKTOP_DBUS_SERVICE:
 */
/**
 * FREE_DESKTOP_DBUS_OBJECT_PATH:
 */
/**
 * FreeDesktopDBusRequestNameReply:
 */
/**
 * free_desktop_dbus_object_request_name:
 * @self: the <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> instance
 * @error: (error-domains GDBusError): location to store the error occuring, or %NULL to ignore
 */
/**
 * free_desktop_dbus_object_start_service_by_name:
 * @self: the <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> instance
 * @error: (error-domains GDBusError): location to store the error occuring, or %NULL to ignore
 */
/**
 * free_desktop_dbus_object_list_names:
 * @self: the <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> instance
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * <emphasis>See also</emphasis>: <link linkend="free-desktop-dbus-object-list-names-finish"><function>free_desktop_dbus_object_list_names_finish()</function></link>
 */
/**
 * free_desktop_dbus_object_list_names_finish:
 * @self: the <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: (error-domains GDBusError): location to store the error occuring, or %NULL to ignore
 * 
 * <emphasis>See also</emphasis>: <link linkend="free-desktop-dbus-object-list-names"><function>free_desktop_dbus_object_list_names()</function></link>
 */
/**
 * free_desktop_dbus_object_list_activatable_names:
 * @self: the <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> instance
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * <emphasis>See also</emphasis>: <link linkend="free-desktop-dbus-object-list-activatable-names-finish"><function>free_desktop_dbus_object_list_activatable_names_finish()</function></link>
 */
/**
 * free_desktop_dbus_object_list_activatable_names_finish:
 * @self: the <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: (error-domains GDBusError): location to store the error occuring, or %NULL to ignore
 * 
 * <emphasis>See also</emphasis>: <link linkend="free-desktop-dbus-object-list-activatable-names"><function>free_desktop_dbus_object_list_activatable_names()</function></link>
 */
/**
 * FreeDesktopDBusObject::name-owner-changed:
 * @dbus_object: the <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> instance that received the signal
 * @name: 
 * @old_owner: 
 * @new_owner: 
 */
/**
 * FreeDesktopDBusObject:
 */
/**
 * FreeDesktopDBusObjectIface:
 * @request_name: virtual method called by <link linkend="free-desktop-dbus-object-request-name"><function>free_desktop_dbus_object_request_name()</function></link>
 * @start_service_by_name: virtual method called by <link linkend="free-desktop-dbus-object-start-service-by-name"><function>free_desktop_dbus_object_start_service_by_name()</function></link>
 * @list_names: virtual method called by <link linkend="free-desktop-dbus-object-list-names"><function>free_desktop_dbus_object_list_names()</function></link>
 * @list_names_finish: asynchronous finish function for <structfield>list_names</structfield>, called by <link linkend="free-desktop-dbus-object-list-names"><function>free_desktop_dbus_object_list_names()</function></link>
 * @list_activatable_names: virtual method called by <link linkend="free-desktop-dbus-object-list-activatable-names"><function>free_desktop_dbus_object_list_activatable_names()</function></link>
 * @list_activatable_names_finish: asynchronous finish function for <structfield>list_activatable_names</structfield>, called by <link linkend="free-desktop-dbus-object-list-activatable-names"><function>free_desktop_dbus_object_list_activatable_names()</function></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="FreeDesktopDBusObject"><type>FreeDesktopDBusObject</type></link> implementations.
 */
/**
 * free_desktop_properties_get_all:
 * @self: the <link linkend="FreeDesktopProperties"><type>FreeDesktopProperties</type></link> instance
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * <emphasis>See also</emphasis>: <link linkend="free-desktop-properties-get-all-finish"><function>free_desktop_properties_get_all_finish()</function></link>
 */
/**
 * free_desktop_properties_get_all_finish:
 * @self: the <link linkend="FreeDesktopProperties"><type>FreeDesktopProperties</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * @error: (error-domains GDBusError): location to store the error occuring, or %NULL to ignore
 * 
 * <emphasis>See also</emphasis>: <link linkend="free-desktop-properties-get-all"><function>free_desktop_properties_get_all()</function></link>
 */
/**
 * FreeDesktopProperties:
 */
/**
 * FreeDesktopPropertiesIface:
 * @get_all: virtual method called by <link linkend="free-desktop-properties-get-all"><function>free_desktop_properties_get_all()</function></link>
 * @get_all_finish: asynchronous finish function for <structfield>get_all</structfield>, called by <link linkend="free-desktop-properties-get-all"><function>free_desktop_properties_get_all()</function></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="FreeDesktopProperties"><type>FreeDesktopProperties</type></link> implementations.
 */
