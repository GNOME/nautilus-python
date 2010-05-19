#!/bin/sh

PROJECT=nautilus-python
PKG_NAME=$PROJECT

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

topsrcdir=`dirname $0`
if test x$topsrcdir = x ; then
	topsrcdir=.
fi

(test -f $topsrcdir/configure.in \
  && test -f $topsrcdir/README \
  && test -d $topsrcdir/src) || {
    echo -n "**Error**: Directory "\`$topsrcdir\'" does not look like the"
    echo " top-level $PROJECT directory"
    exit 1
}

which gnome-autogen.sh || {
    echo "You need to install gnome-common from the GNOME Git"
    exit 1
}

. gnome-autogen.sh --enable-maintainer-mode "$@"
