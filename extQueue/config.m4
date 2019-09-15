dnl $Id$
dnl config.m4 for extension extQueue

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(extQueue, for extQueue support,
dnl Make sure that the comment is aligned:
dnl [  --with-extQueue             Include extQueue support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(extQueue, whether to enable extQueue support,
dnl Make sure that the comment is aligned:
[  --enable-extQueue           Enable extQueue support])

if test "$PHP_EXTQUEUE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-extQueue -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/extQueue.h"  # you most likely want to change this
  dnl if test -r $PHP_EXTQUEUE/$SEARCH_FOR; then # path given as parameter
  dnl   EXTQUEUE_DIR=$PHP_EXTQUEUE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for extQueue files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       EXTQUEUE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$EXTQUEUE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the extQueue distribution])
  dnl fi

  dnl # --with-extQueue -> add include path
  dnl PHP_ADD_INCLUDE($EXTQUEUE_DIR/include)

  dnl # --with-extQueue -> check for lib and symbol presence
  dnl LIBNAME=extQueue # you may want to change this
  dnl LIBSYMBOL=extQueue # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $EXTQUEUE_DIR/$PHP_LIBDIR, EXTQUEUE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_EXTQUEUELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong extQueue lib version or lib not found])
  dnl ],[
  dnl   -L$EXTQUEUE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(EXTQUEUE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(extQueue, extQueue.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
