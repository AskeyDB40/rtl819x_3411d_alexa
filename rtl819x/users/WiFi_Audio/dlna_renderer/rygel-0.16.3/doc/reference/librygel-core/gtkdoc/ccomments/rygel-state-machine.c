/**
 * SECTION:rygel-state-machine
 * @short_description: StateMachine interface.
 */
/**
 * rygel_state_machine_run:
 * @self: the <link linkend="RygelStateMachine"><type>RygelStateMachine</type></link> instance
 * @_callback_: (scope async): callback to call when the request is satisfied
 * @_user_data_: (closure): the data to pass to @_callback_ function
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-state-machine-run-finish"><function>rygel_state_machine_run_finish()</function></link>
 */
/**
 * rygel_state_machine_run_finish:
 * @self: the <link linkend="RygelStateMachine"><type>RygelStateMachine</type></link> instance
 * @_res_: a <link linkend="GAsyncResult"><type>GAsyncResult</type></link>
 * 
 * <emphasis>See also</emphasis>: <link linkend="rygel-state-machine-run"><function>rygel_state_machine_run()</function></link>
 */
/**
 * RygelStateMachine:cancellable:
 */
/**
 * rygel_state_machine_get_cancellable:
 * @self: the <link linkend="RygelStateMachine"><type>RygelStateMachine</type></link> instance to query
 * 
 * Get and return the current value of the <link linkend="RygelStateMachine--cancellable"><type>"cancellable"</type></link> property.
 * 
 * Returns: the value of the <link linkend="RygelStateMachine--cancellable"><type>"cancellable"</type></link> property
 */
/**
 * rygel_state_machine_set_cancellable:
 * @self: the <link linkend="RygelStateMachine"><type>RygelStateMachine</type></link> instance to modify
 * @value: the new value of the <link linkend="RygelStateMachine--cancellable"><type>"cancellable"</type></link> property
 * 
 * Set the value of the <link linkend="RygelStateMachine--cancellable"><type>"cancellable"</type></link> property to @value.
 */
/**
 * RygelStateMachine::completed:
 * @state_machine: the <link linkend="RygelStateMachine"><type>RygelStateMachine</type></link> instance that received the signal
 */
/**
 * RygelStateMachine:
 * 
 * StateMachine interface.
 */
/**
 * RygelStateMachineIface:
 * @run: virtual method called by <link linkend="rygel-state-machine-run"><function>rygel_state_machine_run()</function></link>
 * @run_finish: asynchronous finish function for <structfield>run</structfield>, called by <link linkend="rygel-state-machine-run"><function>rygel_state_machine_run()</function></link>
 * @get_cancellable: getter method for the abstract property <link linkend="RygelStateMachine--cancellable"><type>"cancellable"</type></link>
 * @set_cancellable: setter method for the abstract property <link linkend="RygelStateMachine--cancellable"><type>"cancellable"</type></link>
 * @parent_iface: the parent interface structure
 * 
 * Interface for creating <link linkend="RygelStateMachine"><type>RygelStateMachine</type></link> implementations.
 */
