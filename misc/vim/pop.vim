" Vim syntax file
" Language: POP-C++ 
" Maintainer: Valentin CLEMENT
" Latest Revision: 28th of February 2013

if exists("b:current_syntax")
  finish
endif

so <sfile>:p:h/cpp.vim

" Keywords
syn keyword popLanguageKeywords parclass sync async seq conc mutex
syn keyword popLanguageKeywords broadcast scatter gather reduce classuid

syn region popObjectDescription start='@{' end='}' 


let b:current_syntax = "pop"

hi def link popLanguageKeywords Identifier
hi def link popObjectDescription PreProc
