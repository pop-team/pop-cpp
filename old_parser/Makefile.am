AUTOMAKE_OPTIONS=no-dependencies



YACC=@YACC@
LEX=@LEX@

bin_PROGRAMS = popcpp popcc

popcpp_SOURCES = parser.cc parser_common.cc parser_common.h codefile.cc othercode.cc classmember.cc class.cc packobject.cc \
 parser.tab.cc parser.yy.cc parser.h parser.tab.h parser_common.h type.h\
typearray.cc  type.cc  typeequal.cc  typeptr.cc  typestruct.cc typeseqclass.cc typeclassstruct.cc typetemplate.cc

nodist_popcpp_SOURCES= debug.cc  utils.cc 
popcpp_LDADD = @LEXLIB@
popcpp_CCFLAGS = -I../include
popcpp_CXXFLAGS = -I../include

nodist_popcc_SOURCES= popcc.cc utils.cc
popcc_CCFLAGS = -I../include -DYYERROR_VERBOSE
popcc_CXXFLAGS = -I../include -DYYERROR_VERBOSE

AM_CPPFLAGS = -DSVNREV="\"$(shell ./version.sh)\""

gen: parser.y  parser.lex
	$(YACC) -b parser -d parser.y
	mv  parser.tab.c parser.tab.cc
	$(LEX) -oparser.yy.cc parser.lex


