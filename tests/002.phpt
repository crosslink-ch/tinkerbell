--TEST--
test1() Basic test
--EXTENSIONS--
tinkerbell
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension tinkerbell is loaded and working!
NULL
