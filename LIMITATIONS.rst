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

Limitations of the POP-C++ core
=================================
* It is dangerous to send an object to itself as a reference. The buffer is already busy. An error occurs if the parallel method
  returns a value. As seen in test/parobjbyref

