#!/bin/bash

# Returns the svn version number of the current directory.
# Works in an svn working copy, or in a git svn clone of an svn repo.

if which svnversion>/dev/null; then
	SVNVERSION=`svnversion .`
fi

if [ "X${SVNVERSION:0:1}" = "Xe" -o "X$SVNVERSION" = "X" ]; then
	if which git>/dev/null; then
		GITREV=`git log -1 --pretty=format:%H 2>/dev/null`
		SVNVERSION=`git svn find-rev $GITREV 2>/dev/null`
		GITBRANCH=`git branch --no-color 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'`
	fi
fi

DATE=$(date +"%Y%m%d")
if [ "X$SVNVERSION" = "X" ]; then
	echo "$DATE"	
else
	echo "$DATE.r$SVNVERSION$GITBRANCH"
fi


