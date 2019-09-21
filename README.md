# php-study-extend
PHP扩展学习
---
#扩展开发说明
+ :如何构建初始化的文件
      在PHP的源代码的ext目录里有ext_skel文件帮助我们构建初始化的扩展相关文件。ext_skel有几个参数，其中，extname参数用来指定要创建的扩展名称，是一个全为小写字母的标识符，仅包含字母和下划线，需要在ext目录下保持唯一；proto用来指定函数原型（这一步可以省略，定义函数的出参入参，及返回类型）。
      在编译安装PHP的时候，会指定一些编译配置选项，有些是–with，有些是–enable，这里有什么区别呢？一般来说，enable表示某个内置功能是否开启，而with表示是否需要添加某个功能，通常需要指定依赖的外部库。我们生成的扩展不依赖外部组件，所以这里选择enable方式。修改config.m4，去掉PHP_ARG_ENABLE和enablewcl两行前面的dnl（在autoconf语法中，dnl表示注释）。

+ PHP扩展开发相关API
  + php无论是cli，还是fastcgi[php-fpm]都会建立如下的执行流程【而每次执行cli都会经历如下的几个流程】，而在常用的php-fpm模式，在fpm启动的时候也是会构建 模块初始化阶段，后期不在构建，而是对每一个请求都有构建 请求初始化和请求结束阶段。
      + 模块初始化阶段
            模块初始化阶段对应上边生成的*.c文件中的PHP_MINIT_FUNCTION宏内，一般在这里边最一些模块初始化的工作，如注册资源类型，或者在编写类扩展的时候在这里注册和初始化类的指针变量和类的一些属性等待
      + 请求初始化阶段
            请求初始化在这里对请求的一些处理。
      + 执行PHP脚本阶段
      + 请求结束阶段
            请求完毕的时候一些操作
      + 模块关闭阶段
            模块关闭阶段，可以一些资源回收的等待工作
---
#扩展开发的一些说明
  待补充

---
#链表队列扩展的说明
   本扩展是基于链表实现的一个队列，而且是单链表的一个例子，扩展使用注册PHP资源类型的方式来开发，初步了解资源类型在PHP扩展开发的使用，代码中有注释详解。
  开发概略说明：
     在开发资源类型的首先需要对资源类型有一个标示，一般使用生成的扩展文件中的
```
/* True global resources - no need for thread safety here */
static int le_*;//使用这个作为标示，而且这个变量只在文件中有作用域，防止扩展间的相同变量引起问题，static关键在变量定义前标明这个变量只在自身文件中有作用域
```
还需要给资源起一个名字，然后在PHP_MINIT_FUNCTION宏中注册资源类别。在创建的资源指针需要和这个资源类型ID绑定，这个操作一般在对外提供生成的资源操作函数实现，如fopen等待。随后可以使用PHP内核提供的操作资源类型的函数【zend_*_resource系列函数】，来操作资源类型。


***
#二叉堆扩展的说明

  本扩展是基于数组来实现的二叉堆的存储。二叉堆的结构说明及插入，删除操作在本目录下的[heap-data-staruct](https://github.com/lihongsheng/php-study-extend/heapQueue/heap-data-staruct.md)
   二叉堆队列扩展对应 heapQueue目录：(https://github.com/lihongsheng/php-study-extend/heapQueue) 
   
  ---
+ 内存的操作
  + 使用emalloc函数申请内存【emalloc对应着C的malloc，e*开头的内存操作函数是PHP内核提供的一种申请内存的函数做了一定封装，防止内存溢出等问题】
  + 使用efree [对应C的free]释放申请的内存，包括用来存储PHP的实际值的zval的结构体。
  + 使用 erealloc 【对应C的realloc】函数扩从内存或者缩减内存。
+ 内存动态扩充与缩减
   + 在插入的时候会判断当前存储的数据是否和数组大小一致，一致则使用erealloc翻倍扩充。
   + 在删除的操作中，会有一个判断，当为使用的数据组处于一般的时候，会缩减到目前数组大小的四分之三。
   + 缺点频繁操作内存，数据的拷贝和内存的申请会占用大量操作，后期可以加入定时器去检测缩减内存。
#使用例子
···
$obj = new heapQueue();
var_dump($obj->getVersion());
 $obj->push(10,'test1');
 var_dump($obj->pop());
 var_dump($obj->getNum());
 echo "--------------".PHP_EOL;
···