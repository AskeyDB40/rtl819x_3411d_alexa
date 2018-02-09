/**
 * SECTION:rygel-visual-item
 * @short_description: An interface that visual (video and image) items must implement.
 */
/**
 * RygelVisualItem:width:
 * 
 * The width of the item in pixels. A value of -1 means that the width is unknown and will not, or did not, appear in DIDL-Lite XML.
 */
/**
 * rygel_visual_item_get_width:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelVisualItem--width"><type>"width"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelVisualItem--width"><type>"width"</type></link> property
 */
/**
 * rygel_visual_item_set_width:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelVisualItem--width"><type>"width"</type></link> property
 * 
 * Set the value of the <link linkend="RygelVisualItem--width"><type>"width"</type></link> property to @value.
 */
/**
 * RygelVisualItem:height:
 * 
 * The height of the item in pixels. A value of -1 means that the height is unknown and will not, or did not, appear in DIDL-Lite XML.
 */
/**
 * rygel_visual_item_get_height:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelVisualItem--height"><type>"height"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelVisualItem--height"><type>"height"</type></link> property
 */
/**
 * rygel_visual_item_set_height:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelVisualItem--height"><type>"height"</type></link> property
 * 
 * Set the value of the <link linkend="RygelVisualItem--height"><type>"height"</type></link> property to @value.
 */
/**
 * RygelVisualItem:pixel-width:
 */
/**
 * rygel_visual_item_get_pixel_width:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelVisualItem--pixel-width"><type>"pixel-width"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelVisualItem--pixel-width"><type>"pixel-width"</type></link> property
 */
/**
 * rygel_visual_item_set_pixel_width:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelVisualItem--pixel-width"><type>"pixel-width"</type></link> property
 * 
 * Set the value of the <link linkend="RygelVisualItem--pixel-width"><type>"pixel-width"</type></link> property to @value.
 */
/**
 * RygelVisualItem:pixel-height:
 */
/**
 * rygel_visual_item_get_pixel_height:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelVisualItem--pixel-height"><type>"pixel-height"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelVisualItem--pixel-height"><type>"pixel-height"</type></link> property
 */
/**
 * rygel_visual_item_set_pixel_height:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelVisualItem--pixel-height"><type>"pixel-height"</type></link> property
 * 
 * Set the value of the <link linkend="RygelVisualItem--pixel-height"><type>"pixel-height"</type></link> property to @value.
 */
/**
 * RygelVisualItem:color-depth:
 * 
 * The number of bits per pixel used to represent the video or image resource. A value of -1 means that the color depth is unknown and will not, or did not, appear in DIDL-Lite XML.
 */
/**
 * rygel_visual_item_get_color_depth:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelVisualItem--color-depth"><type>"color-depth"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelVisualItem--color-depth"><type>"color-depth"</type></link> property
 */
/**
 * rygel_visual_item_set_color_depth:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelVisualItem--color-depth"><type>"color-depth"</type></link> property
 * 
 * Set the value of the <link linkend="RygelVisualItem--color-depth"><type>"color-depth"</type></link> property to @value.
 */
/**
 * RygelVisualItem:thumbnails:
 */
/**
 * rygel_visual_item_get_thumbnails:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelVisualItem--thumbnails"><type>"thumbnails"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelVisualItem--thumbnails"><type>"thumbnails"</type></link> property
 */
/**
 * rygel_visual_item_set_thumbnails:
 * @self: the <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelVisualItem--thumbnails"><type>"thumbnails"</type></link> property
 * 
 * Set the value of the <link linkend="RygelVisualItem--thumbnails"><type>"thumbnails"</type></link> property to @value.
 */
/**
 * RygelVisualItem:
 * 
 * An interface that visual (video and image) items must implement.
 */
/**
 * RygelVisualItemIface:
 * @get_width: getter method for the abstract property <link linkend="RygelVisualItem--width"><type>"width"</type></link>
 * @set_width: setter method for the abstract property <link linkend="RygelVisualItem--width"><type>"width"</type></link>
 * @get_height: getter method for the abstract property <link linkend="RygelVisualItem--height"><type>"height"</type></link>
 * @set_height: setter method for the abstract property <link linkend="RygelVisualItem--height"><type>"height"</type></link>
 * @get_pixel_width: getter method for the abstract property <link linkend="RygelVisualItem--pixel-width"><type>"pixel-width"</type></link>
 * @set_pixel_width: setter method for the abstract property <link linkend="RygelVisualItem--pixel-width"><type>"pixel-width"</type></link>
 * @get_pixel_height: getter method for the abstract property <link linkend="RygelVisualItem--pixel-height"><type>"pixel-height"</type></link>
 * @set_pixel_height: setter method for the abstract property <link linkend="RygelVisualItem--pixel-height"><type>"pixel-height"</type></link>
 * @get_color_depth: getter method for the abstract property <link linkend="RygelVisualItem--color-depth"><type>"color-depth"</type></link>
 * @set_color_depth: setter method for the abstract property <link linkend="RygelVisualItem--color-depth"><type>"color-depth"</type></link>
 * @get_thumbnails: getter method for the abstract property <link linkend="RygelVisualItem--thumbnails"><type>"thumbnails"</type></link>
 * @set_thumbnails: setter method for the abstract property <link linkend="RygelVisualItem--thumbnails"><type>"thumbnails"</type></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="RygelVisualItem"><type>RygelVisualItem</type></link> implementations.
 */
