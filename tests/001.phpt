--TEST--
Check if tinkerbell is loaded
--EXTENSIONS--
tinkerbell
--FILE--
<?php
echo 'The extension "tinkerbell" is available';
?>
--EXPECT--
The extension "tinkerbell" is available
