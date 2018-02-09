/**
 * SECTION:rygel-resource-info
 * @short_description: Holds information about a particular resource (device and service) implementation.
 */
/**
 * RYGEL_TYPE_RESOURCE_INFO:
 * 
 * The type for <link linkend="RygelResourceInfo"><type>RygelResourceInfo</type></link>.
 */
/**
 * rygel_resource_info_new:
 */
/**
 * RygelResourceInfo:
 * 
 * Holds information about a particular resource (device and service) implementation.
 */
/**
 * rygel_resource_info_ref:
 * @instance: a <link linkend="RygelResourceInfo"><type>RygelResourceInfo</type></link>.
 * 
 * Increases the reference count of @object.
 * 
 * Returns: the same @object
 */
/**
 * rygel_resource_info_unref:
 * @instance: a <link linkend="RygelResourceInfo"><type>RygelResourceInfo</type></link>.
 * 
 * Decreases the reference count of @object. When its reference count drops to 0, the object is finalized (i.e. its memory is freed).
 */
/**
 * rygel_param_spec_resource_info:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @object_type: <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived type of this property
 * @flags: flags for the property specified
 * 
 * Creates a new <link linkend="GParamSpecBoxed"><type>GParamSpecBoxed</type></link> instance specifying a <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived property.
 * 
 * See <link linkend="g-param-spec-internal"><function>g_param_spec_internal()</function></link> for details on property names.
 */
/**
 * rygel_value_set_resource_info:
 * @value: a valid <link linkend="GValue"><type>GValue</type></link> of <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived type
 * @v_object: object value to be set
 * 
 * Set the contents of a <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived <link linkend="GValue"><type>GValue</type></link> to @v_object.
 * 
 * <link linkend="rygel-value-set-resource-info"><function>rygel_value_set_resource_info()</function></link> increases the reference count of @v_object (the <link linkend="GValue"><type>GValue</type></link> holds a reference to @v_object). If you do not wish to increase the reference count of the object (i.e. you wish to pass your current reference to the <link linkend="GValue"><type>GValue</type></link> because you no longer need it), use <link linkend="rygel-value-take-resource-info"><function>rygel_value_take_resource_info()</function></link> instead.
 * 
 * It is important that your <link linkend="GValue"><type>GValue</type></link> holds a reference to @v_object (either its own, or one it has taken) to ensure that the object won't be destroyed while the <link linkend="GValue"><type>GValue</type></link> still exists).
 */
/**
 * rygel_value_get_resource_info:
 * @value: a valid <link linkend="GValue"><type>GValue</type></link> of <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived type
 * 
 * Get the contents of a <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived <link linkend="GValue"><type>GValue</type></link>.
 * 
 * Returns: object contents of @value
 */
/**
 * rygel_value_take_resource_info:
 * @value: a valid <link linkend="GValue"><type>GValue</type></link> of <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived type
 * @v_object: object value to be set
 * 
 * Sets the contents of a <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link> derived <link linkend="GValue"><type>GValue</type></link> to @v_object and takes over the ownership of the callers reference to @v_object; the caller doesn't have to unref it any more (i.e. the reference count of the object is not increased).
 * 
 * If you want the GValue to hold its own reference to @v_object, use <link linkend="rygel-value-set-resource-info"><function>rygel_value_set_resource_info()</function></link> instead.
 */
/**
 * RygelResourceInfoClass:
 * @parent_class: the parent class structure
 * 
 * The class structure for <link linkend="RYGEL-TYPE-RESOURCE-INFO:CAPS"><literal>RYGEL_TYPE_RESOURCE_INFO</literal></link>. All the fields in this structure are private and should never be accessed directly.
 */
