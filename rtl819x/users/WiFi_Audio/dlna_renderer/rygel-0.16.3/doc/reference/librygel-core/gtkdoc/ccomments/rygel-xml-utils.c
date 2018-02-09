/**
 * SECTION:rygel-xml-utils
 * @short_description: XML utility API.
 */
/**
 * RYGEL_TYPE_XML_UTILS:
 * 
 * The type for <link linkend="RygelXMLUtils"><type>RygelXMLUtils</type></link>.
 */
/**
 * rygel_xml_utils_new:
 */
/**
 * rygel_xml_utils_get_element:
 */
/**
 * RygelXMLUtils:
 * 
 * XML utility API.
 */
/**
 * rygel_xml_utils_ref:
 * @instance: a <link linkend="RygelXMLUtils"><type>RygelXMLUtils</type></link>.
 * 
 * Increases the reference count of @object.
 * 
 * Returns: the same @object
 */
/**
 * rygel_xml_utils_unref:
 * @instance: a <link linkend="RygelXMLUtils"><type>RygelXMLUtils</type></link>.
 * 
 * Decreases the reference count of @object. When its reference count drops to 0, the object is finalized (i.e. its memory is freed).
 */
/**
 * rygel_param_spec_xml_utils:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @object_type: <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived type of this property
 * @flags: flags for the property specified
 * 
 * Creates a new <link linkend="GParamSpecBoxed"><type>GParamSpecBoxed</type></link> instance specifying a <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived property.
 * 
 * See <link linkend="g-param-spec-internal"><function>g_param_spec_internal()</function></link> for details on property names.
 */
/**
 * rygel_value_set_xml_utils:
 * @value: a valid <link linkend="GValue"><type>GValue</type></link> of <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived type
 * @v_object: object value to be set
 * 
 * Set the contents of a <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived <link linkend="GValue"><type>GValue</type></link> to @v_object.
 * 
 * <link linkend="rygel-value-set-xml-utils"><function>rygel_value_set_xml_utils()</function></link> increases the reference count of @v_object (the <link linkend="GValue"><type>GValue</type></link> holds a reference to @v_object). If you do not wish to increase the reference count of the object (i.e. you wish to pass your current reference to the <link linkend="GValue"><type>GValue</type></link> because you no longer need it), use <link linkend="rygel-value-take-xml-utils"><function>rygel_value_take_xml_utils()</function></link> instead.
 * 
 * It is important that your <link linkend="GValue"><type>GValue</type></link> holds a reference to @v_object (either its own, or one it has taken) to ensure that the object won't be destroyed while the <link linkend="GValue"><type>GValue</type></link> still exists).
 */
/**
 * rygel_value_get_xml_utils:
 * @value: a valid <link linkend="GValue"><type>GValue</type></link> of <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived type
 * 
 * Get the contents of a <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived <link linkend="GValue"><type>GValue</type></link>.
 * 
 * Returns: object contents of @value
 */
/**
 * rygel_value_take_xml_utils:
 * @value: a valid <link linkend="GValue"><type>GValue</type></link> of <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived type
 * @v_object: object value to be set
 * 
 * Sets the contents of a <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link> derived <link linkend="GValue"><type>GValue</type></link> to @v_object and takes over the ownership of the callers reference to @v_object; the caller doesn't have to unref it any more (i.e. the reference count of the object is not increased).
 * 
 * If you want the GValue to hold its own reference to @v_object, use <link linkend="rygel-value-set-xml-utils"><function>rygel_value_set_xml_utils()</function></link> instead.
 */
/**
 * RygelXMLUtilsClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-XML-UTILS:CAPS"><literal>RYGEL_TYPE_XML_UTILS</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
