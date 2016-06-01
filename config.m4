PHP_ARG_ENABLE(zipkin, whether to enable Zipkin support, 
[ --enable-zipkin   Enable Zipkin support])

if test "$PHP_ZIPKIN" = "yes"; then
   AC_DEFINE(HAVE_ZIPKIN, 1, [Whether you have Zipkin])
   PHP_NEW_EXTENSION(zipkin, zipkin.c, $ext_shared)
fi
