all: popfile.h popfile.cpp main.cpp popfile_metadata.h popfile_metadata.cpp
	g++ -o popf_test popfile.cpp main.cpp popfile.h tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp popfile_metadata.h popfile_metadata.cpp popfile_datathread.h popfile_datathread.cpp
	
clean:
	rm -f popf_test