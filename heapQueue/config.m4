dnl $Id$
dnl config.m4 for extension heapQueue

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(heapQueue, for heapQueue support,
dnl Make sure that the comment is aligned:
dnl [  --with-heapQueue             Include heapQueue support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(heapQueue, whether to enable heapQueue support,
dnl Make sure that the comment is aligned:
[  --enable-heapQueue           Enable heapQueue support])

if test "$PHP_HEAPQUEUE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-heapQueue -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/heapQueue.h"  # you most likely want to change this
  dnl if test -r $PHP_HEAPQUEUE/$SEARCH_FOR; then # path given as parameter
  dnl   HEAPQUEUE_DIR=$PHP_HEAPQUEUE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for heapQueue files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       HEAPQUEUE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$HEAPQUEUE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the heapQueue distribution])
  dnl fi

  dnl # --with-heapQueue -> add include path
  dnl PHP_ADD_INCLUDE($HEAPQUEUE_DIR/include)

  dnl # --with-heapQueue -> check for lib and symbol presence
  dnl LIBNAME=heapQueue # you may want to change this
  dnl LIBSYMBOL=heapQueue # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $HEAPQUEUE_DIR/$PHP_LIBDIR, HEAPQUEUE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_HEAPQUEUELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong heapQueue lib version or lib not found])
  dnl ],[
  dnl   -L$HEAPQUEUE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(HEAPQUEUE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(heapQueue, heapQueue.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
