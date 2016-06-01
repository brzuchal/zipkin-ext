# Compile

phpize  
./configure --enable-zipkin  
make  

# Tutorial 1

http://devzone.zend.com/303/extension-writing-part-i-introduction-to-php-and-zend/

# Run

php -c php.ini -r "echo zipkin_world();"  
zipkin World

php -c php.ini -r "var_dump( zipkin_bool() );"  
bool(true)

php -c php.ini -r "echo zipkin_long();"  
42

php -c php.ini -r "echo zipkin_double();"  
3.1415926535

php -c php.ini -r "var_dump( zipkin_null() );"  
NULL


# Tutorial 2

http://devzone.zend.com/317/extension-writing-part-ii-parameters-arrays-and-zvals/
http://devzone.zend.com/318/extension-writing-part-ii-parameters-arrays-and-zvals-continued/

php -c php.ini -r "zipkin_greetme('Joe');"  
zipkin Joe

php -c php.ini -r "echo zipkin_add(2, 4.1);"  
6.1

php -c php.ini -r "echo zipkin_add(2, 4.1, true);"  
6

php -c php.ini -r "var_dump(zipkin_array());"  

    array(6) {
      [42]=>
      int(123)
      [43]=>
      string(33) "I should now be found at index 43"
      [44]=>
      string(10) "I'm at 44!"
      [45]=>
      string(10) "Forty Five"
      ["pi"]=>
      float(3.1415926535)
      ["subarray"]=>
      array(1) {
        [0]=>
        string(5) "zipkin"
      }
    }


Show zipkin_array_strings:  

    <?php
    $a = array('foo', 123);
    var_dump($a);
    zipkin_array_strings($a);
    var_dump($a);

Working with $GLOBALS:  

    <?php
    $GLOBALS['test'] = 'Joe';
    echo zipkin_get_global_var('test');
    echo zipkin_get_global_var('none');

Setting local variables:

    <?php
    zipkin_set_local_var('test', 'Greetings');
    echo "$test\n";


# Tutorial 3

http://devzone.zend.com/446/extension-writing-part-iii-resources/

Resources

    <?php

    $person = zipkin_person_new("Joseph", 31);
    var_dump($person);

    zipkin_person_greet($person);

