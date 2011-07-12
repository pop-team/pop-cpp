AUTOMAKE_OPTIONS=no-dependencies

YACC=@YACC@
LEX=@LEX@

bin_PROGRAMS = parocpp parocc

parocpp_SOURCES = parser.cc parser_common.cc parser_common.h codefile.cc othercode.cc classmember.cc class.cc packobject.cc \
 parser.tab.cc parser.yy.cc parser.h parser.tab.h parser_common.h type.h\
typearray.cc  type.cc  typeequal.cc  typeptr.cc  typestruct.cc typeseqclass.cc

nodist_parocpp_SOURCES= debug.cc  utils.cc 
parocpp_LDADD = @LEXLIB@
parocpp_CCFLAGS = -I../include
parocpp_CXXFLAGS = -I../include

nodist_parocc_SOURCES= parocc.cc utils.cc
parocc_CCFLAGS = -I../include
parocc_CXXFLAGS = -I../include



gen: parser.y  parser.lex
	$(YACC) -b parser -d parser.y
	mv  parser.tab.c parser.tab.cc
	$(LEX) -oparser.yy.cc parser.lex


