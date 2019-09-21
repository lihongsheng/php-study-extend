<?php

$base =  base64_encode(file_get_contents("http://code.youquwei.net/img/08-07/f41c8b2d-e2ed-4d18-a1ea-b9a0f28931a9.png"));

$str = file_get_contents("head-data-struct.md");

$str = str_replace("http://code.youquwei.net/img/08-07/f41c8b2d-e2ed-4d18-a1ea-b9a0f28931a9.png",
$base,
$str
);
file_put_contents("head-data-struct.md", $str);

/*$br = (php_sapi_name() == "cli")? "":"<br>";

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
 echo "--------------".PHP_EOL;*/
?>
