Limitations of the POP-C++ Parser
=================================

The POP-C++ parser has several limitations:

* enum declaration inside a parclass: The declaration of a enum type inside a parclass is totally supported. However, this type
  could not be passed as a parameter in parclass method. For this purpose, the type of the parameter must be a int.
* struct declaration inside a parclass: Only simple struct declaration are allowed in parclass. Nested struct declaration is not
  supported yet.
* class declaration inside a parclass: Class declaration inside parclass is not currently supported.
* typedef declaration inside a parclass: typedef declaration with structure inside a parclass is not currently supported.
* No support for C++11 in the headers. C++11 can be used in the source files if the -cpp11 option is passed to popcc
* A par class cannot have const variable.
* Const member functions are not supported
* throw() declaration for member functions is not supported

Classes and structures handled differently:
* classes (class keyword) needs to inherit from pop_base.
* structures (struct keyword) cannot inherit from anything. Each attribute must be marshallable.

Limitations of the POP-C++ core
===============================

* It is dangerous to send an object to itself as a reference. The buffer is already busy. An error occurs if the parallel method
  returns a value. As seen in test/parobjbyref

Limitations of the async allocation scheme
==========================================

Asynchronous allocation of parallel objects is a feature allowing your objects to be allocated concurrently. If you have several
objects to create one after another and then use them, this can save a lot of time. However, this is not without limitation:

* Exceptions do not go out of the constructor. If you rely on exceptions in the constructor, this won't work.
* References and pointers passed to the constructor must be valid after the constructor call exited. This can complicated since
  passing a const char* to a constructor takig a std::string will create a temporary, if this temporary is captured by const reference
  a reference to a possibly-invalid temporary will be passed to the constructor thread and will result in undefined behaviour.

Other limitations
=================

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

