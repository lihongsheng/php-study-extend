dnl $Id$
dnl config.m4 for extension demoFun

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(demoFun, for demoFun support,
dnl Make sure that the comment is aligned:
dnl [  --with-demoFun             Include demoFun support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(demoFun, whether to enable demoFun support,
dnl Make sure that the comment is aligned:
[  --enable-demoFun           Enable demoFun support])

if test "$PHP_DEMOFUN" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-demoFun -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/demoFun.h"  # you most likely want to change this
  dnl if test -r $PHP_DEMOFUN/$SEARCH_FOR; then # path given as parameter
  dnl   DEMOFUN_DIR=$PHP_DEMOFUN
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for demoFun files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DEMOFUN_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DEMOFUN_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the demoFun distribution])
  dnl fi

  dnl # --with-demoFun -> add include path
  dnl PHP_ADD_INCLUDE($DEMOFUN_DIR/include)

  dnl # --with-demoFun -> check for lib and symbol presence
  dnl LIBNAME=demoFun # you may want to change this
  dnl LIBSYMBOL=demoFun # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DEMOFUN_DIR/$PHP_LIBDIR, DEMOFUN_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DEMOFUNLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong demoFun lib version or lib not found])
  dnl ],[
  dnl   -L$DEMOFUN_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DEMOFUN_SHARED_LIBADD)

  PHP_NEW_EXTENSION(demoFun, demoFun.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
