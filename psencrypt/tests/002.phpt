--TEST--
test1() Basic test
--EXTENSIONS--
psencrypt
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension psencrypt is loaded and working!
NULL
