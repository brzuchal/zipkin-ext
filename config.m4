dnl $Id$
dnl config.m4 for extension zipkin

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(zipkin, for zipkin support,
dnl Make sure that the comment is aligned:
dnl [  --with-zipkin             Include zipkin support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(zipkin, whether to enable zipkin support,
dnl Make sure that the comment is aligned:
dnl [  --enable-zipkin           Enable zipkin support])

if test "$PHP_ZIPKIN" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-zipkin -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/zipkin.h"  # you most likely want to change this
  dnl if test -r $PHP_ZIPKIN/$SEARCH_FOR; then # path given as parameter
  dnl   ZIPKIN_DIR=$PHP_ZIPKIN
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for zipkin files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ZIPKIN_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ZIPKIN_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the zipkin distribution])
  dnl fi

  dnl # --with-zipkin -> add include path
  dnl PHP_ADD_INCLUDE($ZIPKIN_DIR/include)

  dnl # --with-zipkin -> check for lib and symbol presence
  dnl LIBNAME=zipkin # you may want to change this
  dnl LIBSYMBOL=zipkin # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ZIPKIN_DIR/$PHP_LIBDIR, ZIPKIN_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ZIPKINLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong zipkin lib version or lib not found])
  dnl ],[
  dnl   -L$ZIPKIN_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ZIPKIN_SHARED_LIBADD)

  PHP_NEW_EXTENSION(zipkin, zipkin.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
