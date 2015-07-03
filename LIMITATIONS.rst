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

Classes and structures handled differently:
* classes (class keyword) needs to inherit from pop_base.
* structures (struct keyword) cannot inherit from anything. Each attribute must be marshallable.

Limitations of the POP-C++ core
=================================
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
