/**
 * SECTION:rygel-description-file
 * @short_description: Represents a device description document and offers methods for easy manipulation of those.
 */
/**
 * TYPE_DESCRIPTION_FILE:
 * 
 * The type for <link linkend="DescriptionFile"><type>DescriptionFile</type></link>.
 */
/**
 * description_file_set_device_type:
 * @self: the <link linkend="DescriptionFile"><type>DescriptionFile</type></link> instance
 * @device_type: (in): is the current content of serviceType. 
 * 
 * Change the type of a service.
 * 
 * <para>Usually used to modify the device version, e.g. default device type is &quot;MediaServer:2&quot; and device_type = &quot;MediaServer:1&quot;.</para>
 */
/**
 * description_file_set_model_name:
 * @self: the <link linkend="DescriptionFile"><type>DescriptionFile</type></link> instance
 * @model_name: (in): is the new model name. 
 * 
 * Modify the model name.
 * 
 * <para>Usually the name of the software implementing this device.</para>
 */
/**
 * description_file_set_model_number:
 * @self: the <link linkend="DescriptionFile"><type>DescriptionFile</type></link> instance
 * @model_number: (in): is the new model number. 
 * 
 * Modify the model number.
 * 
 * <para>Usually the version of the software implementing this device.</para>
 */
/**
 * description_file_set_friendly_name:
 * @self: the <link linkend="DescriptionFile"><type>DescriptionFile</type></link> instance
 * @friendly_name: (in): is the new friendly name of the device. 
 * 
 * Set the friendly name of the device.
 * 
 * <para>The friendly name is the one usually presented to the user in control points or DMPs</para>
 */
/**
 * description_file_get_friendly_name:
 * @self: the <link linkend="DescriptionFile"><type>DescriptionFile</type></link> instance
 * 
 * Get the current friendly name of the device.
 * 
 * Returns: The currenly set friendly name. 
 */
/**
 * description_file_modify_service_type:
 * @self: the <link linkend="DescriptionFile"><type>DescriptionFile</type></link> instance
 * @old_type: (in): is the current content of serviceType. 
 * @new_type: (in): is the content serviceType will be set to. 
 * 
 * Change the type of a service.
 * 
 * <para>Usually used to modify the service version, e.g. old_type = &quot;ContentDirectory:2&quot; and new_type = &quot;ContentDirectory:1&quot;.</para>
 */
/**
 * description_file_save:
 * @self: the <link linkend="DescriptionFile"><type>DescriptionFile</type></link> instance
 * @path: (in): is a path to a file. 
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Writes the current document to a file.
 * 
 * <para>It makes sure that the resulting file has the correct UTF-8 encoding and does not have any kind of newlines. This is necessary as some devices with broken XML parsers can&apos;t cope with UNIX newlines. If a file with the same name exists it will be overwritten.</para>
 * <para><link linkend="GError"><type>GError</type></link> will be returned in @error if anything fails while creating the XML dump. </para>
 */
/**
 * description_file_new:
 * @template: (in): the path to the description file. 
 * @error: location to store the error occuring, or %NULL to ignore
 * 
 * Constructor to load a description file from disk
 * 
 * <para><link linkend="GUPNP-XML-ERROR-PARSE"><type>GUPNP_XML_ERROR_PARSE</type></link> will be returned in @error if there was an error reading or parsing the file. </para>
 */
/**
 * description_file_new_from_xml_document:
 * @doc: (in): is the GUPnP.XMLDoc to wrap. 
 * 
 * Constructor which wraps an existing GUPnP.XMLDoc as a description file.
 */
/**
 * DescriptionFile:
 * 
 * Represents a device description document and offers methods for easy manipulation of those.
 */
/**
 * DescriptionFileClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="TYPE-DESCRIPTION-FILE:CAPS"><literal>TYPE_DESCRIPTION_FILE</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
