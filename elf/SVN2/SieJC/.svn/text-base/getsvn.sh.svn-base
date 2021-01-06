#!/bin/sh
rm revision.h
svn up revision.h
echo -n "#define __SVN_REVISION__ `svnversion .``printf '\r\n'`" > revision.h
