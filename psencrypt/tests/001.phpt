--TEST--
Check if psencrypt is loaded
--EXTENSIONS--
psencrypt
--FILE--
<?php
echo 'The extension "psencrypt" is available';
?>
--EXPECT--
The extension "psencrypt" is available
