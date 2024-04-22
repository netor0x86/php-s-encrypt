dnl config.m4 for extension psencrypt

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([psencrypt],
dnl   [for psencrypt support],
dnl   [AS_HELP_STRING([--with-psencrypt],
dnl     [Include psencrypt support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([psencrypt],
  [whether to enable psencrypt support],
  [AS_HELP_STRING([--enable-psencrypt],
    [Enable psencrypt support])],
  [no])

if test "$PHP_PSENCRYPT" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, PSENCRYPT_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-psencrypt -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/psencrypt.h"  # you most likely want to change this
  dnl if test -r $PHP_PSENCRYPT/$SEARCH_FOR; then # path given as parameter
  dnl   PSENCRYPT_DIR=$PHP_PSENCRYPT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for psencrypt files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PSENCRYPT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PSENCRYPT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the psencrypt distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-psencrypt -> add include path
  dnl PHP_ADD_INCLUDE($PSENCRYPT_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-psencrypt -> check for lib and symbol presence
  dnl LIBNAME=PSENCRYPT # you may want to change this
  dnl LIBSYMBOL=PSENCRYPT # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_PSENCRYPT_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your psencrypt library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PSENCRYPT_DIR/$PHP_LIBDIR, PSENCRYPT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PSENCRYPT_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your psencrypt library.])
  dnl ],[
  dnl   -L$PSENCRYPT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PSENCRYPT_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_PSENCRYPT, 1, [ Have psencrypt support ])

  PHP_NEW_EXTENSION(psencrypt, psencrypt.c, $ext_shared)
fi
