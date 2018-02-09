/**
 * SECTION:rygel-playbin-renderer
 * @short_description: A UPnP renderer that uses a GStreamer Playbin2 element.
 * 
 * <para>Using GstPlayBin2 as a model, it reflects any changes done externally, such as changing the currently played URI, volume, pause/play etc., to UPnP.</para><para>Likewise, the playbin can be modified externally using UPnP.</para><para>You can retrieve the GstPlayBin2 by calling rygel_playbin_player_get_playbin() on the default player - see rygel_playbin_player_get_default(). You should then set the &quot;video-sink&quot; and &quot;audio-sink&quot; properties of the playbin.</para><para>Call rygel_media_device_add_interface() on the Renderer to allow it to be controlled by a control point and to retrieve data streams via that network interface.</para><para>See the standalone-renderer.c example.</para>
 */
/**
 * RYGEL_PLAYBIN_TYPE_RENDERER:
 * 
 * The type for <link linkend="RygelPlaybinRenderer"><type>RygelPlaybinRenderer</type></link>.
 */
/**
 * rygel_playbin_renderer_new:
 * @title: (in): Friendly name of the new UPnP renderer on the network. 
 * 
 * Create a new instance of Renderer.
 * 
 * <para>Renderer will instantiate its own instance of GstPlayBin2. The GstPlayBin2 can be accessed by using rygel_playbin_player_get_playbin().</para>
 */
/**
 * rygel_playbin_renderer_new_wrap:
 * @pipeline: (in): Instance of GstPlayBin2 to wrap. 
 * @title: (in): Friendly name of the new UPnP renderer on the network. 
 * 
 * Create a new instance of Renderer, wrapping an existing GstPlayBin2 instance.
 */
/**
 * RygelPlaybinRenderer:
 * 
 * A UPnP renderer that uses a GStreamer Playbin2 element.
 * 
 * <para>Using GstPlayBin2 as a model, it reflects any changes done externally, such as changing the currently played URI, volume, pause/play etc., to UPnP.</para><para>Likewise, the playbin can be modified externally using UPnP.</para><para>You can retrieve the GstPlayBin2 by calling rygel_playbin_player_get_playbin() on the default player - see rygel_playbin_player_get_default(). You should then set the &quot;video-sink&quot; and &quot;audio-sink&quot; properties of the playbin.</para><para>Call rygel_media_device_add_interface() on the Renderer to allow it to be controlled by a control point and to retrieve data streams via that network interface.</para><para>See the standalone-renderer.c example.</para>
 */
/**
 * RygelPlaybinRendererClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-PLAYBIN-TYPE-RENDERER:CAPS"><literal>RYGEL_PLAYBIN_TYPE_RENDERER</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
