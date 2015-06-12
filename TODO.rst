TODO
====

This file lists the future improvements that can be brought to POP-C++.


Serialization of parallel objects
---------------------------------
Parallel objects should always be serialized in input, never in output. At the current time we need to force this by using: 

.. code::

    MyMethod([in] my_object& obj);

Some changes must be made in the parser


Serialization of inherited classes
----------------------------------
When serializing a Child type the remote method should be able to create a Child object (dynamic type) and not Mother object (static type). 

This happens because the parser will always instanciate an object of the static type in the method and can cause serialization problems. This happens in the example **heritage3**

To fix this the POPBase class shoud contain a factory. All serializable objects must be registered in this factory. It would then be possible to pass the dynamic type to the factory (at deserialization) and instanciate an object of the dynamic type.


TODO: LW
- suppress jobmgrpublish
- suppress LocalExec ?
- clean unit test
