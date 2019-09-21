<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('heapQueue')) {
	dl('heapQueue.' . PHP_SHLIB_SUFFIX);
}
$module = 'heapQueue';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
// if (extension_loaded($module)) {
// 	$str = $function($module);
// } else {
// 	$str = "Module $module is not compiled into PHP";
// }
echo "$str\n";


$obj = new heapQueue();
var_dump($obj->getVersion());
// $arr = 'test1';
 $obj->push(10,'test1');
 var_dump($obj->pop());
 var_dump($obj->getNum());
 echo "--------------".PHP_EOL;

$obj->push(10,10);
$obj->push(11,11);
$obj->push(12,12);
echo "--------------".PHP_EOL;
 var_dump($obj->pop());
 var_dump($obj->getNum());
 echo "--------------".PHP_EOL;
 var_dump($obj->pop());
 var_dump($obj->getNum());
 echo "--------------".PHP_EOL;
?>
