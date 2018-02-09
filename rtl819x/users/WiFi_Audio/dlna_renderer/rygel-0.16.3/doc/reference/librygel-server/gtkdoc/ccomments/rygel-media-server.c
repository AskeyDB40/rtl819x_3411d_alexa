/**
 * SECTION:rygel-media-server
 * @short_description: This class may be used to implement in-process UPnP-AV media servers.
 * 
 * <para>Call rygel_media_device_add_interface() on the RygelMediaServer to allow it to serve media via that network interface.</para><para>See the standalone-server.c example.</para>
 */
/**
 * RYGEL_TYPE_MEDIA_SERVER:
 * 
 * The type for <link linkend="RygelMediaServer"><type>RygelMediaServer</type></link>.
 */
/**
 * rygel_media_server_new:
 * 
 * Create a MediaServer to serve the media in the RygelMediaContainer. For instance, you might use a RygelSimpleContainer. Alternatively, you might use your own RygelMediaContainer implementation.
 * 
 * <para>Assuming that the RygelMediaContainer is correctly implemented, the RygelMediaServer will respond appropriately to changes in the RygelMediaContainer.</para>
 */
/**
 * RygelMediaServer:
 * 
 * This class may be used to implement in-process UPnP-AV media servers.
 * 
 * <para>Call rygel_media_device_add_interface() on the RygelMediaServer to allow it to serve media via that network interface.</para><para>See the standalone-server.c example.</para>
 */
/**
 * RygelMediaServerClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-MEDIA-SERVER:CAPS"><literal>RYGEL_TYPE_MEDIA_SERVER</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
