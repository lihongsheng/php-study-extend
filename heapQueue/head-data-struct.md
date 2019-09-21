#二叉堆数据结构说明
>堆是解决优先级队列，topK问题的常见算法。
>二叉堆的结构性质：堆是一个完全被填满的二叉树，一颗高位h的二叉树有 2^h到2^h+1 - 1个节点。
>堆的性质：父节点的键值总是不大于它的孩子节点的键值（小顶堆）, 堆可以分为小顶堆和大顶堆。 以0开头的 数组中i处的左子节点为 2 * i + 1 右子节点在 2 * i + 2，子节点的父节点在 （i-1）/2处。
>二叉堆具有有序性，但是不是说对插入的值是完全按照 单调的顺序排序的。

![二叉堆的一个例子](http://code.youquwei.net/img/08-07/c5b78405-6523-4b41-af40-13448b431648.png "二叉堆的一个例子")
>可以看出看出位于数组下标三的左子节点和右子节点符合定义，在 2 * 3 + 1 = 7【数组下标】； 2 * 3 + 2 = 8【数组下标8】
>1:插入的操作
>>先插入到数组最后一个坐标下，如果可以放在最后一个坐标【符合二叉堆的性质】大于父节点【小顶堆】。如果不符合需要朝着父节点的方向一步一步上移。如上图插入14的过程
>>插入底部
![插入底部](http://code.youquwei.net/img/08-07/f41c8b2d-e2ed-4d18-a1ea-b9a0f28931a9.png "插入底部")
>>2:上移 14 与父节点互换值
![上移 14 与父节点互换值](http://code.youquwei.net/img/08-07/fef77d6f-6a19-478a-8268-ea7f6f5a2883.png "上移 14 与父节点互换值")

>>3:判断继续上移与父节点【21】互换值
![判断继续上移与父节点【21】互换值](http://code.youquwei.net/img/08-07/d09b977c-8f72-4536-ab8f-e194698dead6.png "判断继续上移与父节点【21】互换值")

>>到达条件退出上浮操作.

```
function insert(&$arr, $value) {
      $arr[] = $value;
      $len  = count($arr) - 1;
      $i = $len;
      while($i >= 0) {
             $j = ($i - 1)/2;//找到父节点
             if ($j >= 0 && $arr[$j] > $arr[$i]) {
                     $tmp = $arr[$i];
                     $arr[$i] = $arr[$j];
                     $arr[$j] = $tmp;
                     $i = $j;//往上上浮
              } else {
                    break;
             }
       }

}
```
>删除操作
>删除其实和插入类似，把数组第一个节点数据取出作为返回数据，把数组最后一个元素取出用于比较，重新比较让结构符合二叉堆的性质。其实删除的是最后一个数组节点，其他数据通过比较运算一个放到合适的节点。
>> 1:取出第一个数组的值 13 和最后一个值31

![取出第一个数组的值 13 和最后一个值31](http://code.youquwei.net/img/08-07/a0afaf79-7cd1-4918-9ccb-08683554ed02.png "取出第一个数组的值 13 和最后一个值31")

>>14 和 16比较 那个大小 决定往哪一个方向走，是往 14 左子树走，还是往16 的左子树走。然后用最后一个值【31】 与 当前走向的节点比较，如果最后一个值【31】如果大于当前节点继续往下进行。【代码实现：图中那些空的其实还保留着原来的值，随后会用新值替换原来的值】

![14上移替换跟节点的值](http://code.youquwei.net/img/08-07/cf29c3be-1f7d-44e0-a97e-903e66443c21.png "14上移替换跟节点的值")

14上移替换跟节点的值

![21上移替换跟14的值](http://code.youquwei.net/img/08-07/98d16f4f-2cc1-44ab-a048-be8e7cc36694.png "21上移替换跟14的值")

21上移替换跟14的值

![31上移替换跟21的值](http://code.youquwei.net/img/08-07/9640dfdc-cc2d-40b3-a3a1-347824df31c9.png "31上移替换跟21的值"）

31上移替换跟21的值

![image](http://code.youquwei.net/img/08-07/bf50d17f-e654-40b2-a687-9da633fae3a1.png "删除最后一个节点"）

删除最后一个节点

```
function del(&$arr) {
    $midValue = $arr[0]; //取得第一个元素
    $len = count($arr) - 1;//取得数组的长度
    $lastVal  = $arr[$len];//取得最后一个值
    $j = 0;//从头开始
    while (2 * $j <= $i) {//防止节点超出数组长度
           $left    =  2 * $j + 1;//左子节点
           $right  =  2 * $j + 2;//右子节点
           $t = $left;//走向，初始往左边走
           if ($arr[$right && $arr[$right] < $arr[$left]) {//决定往左子树走，还是右子树走
                $t = $right; //往右边走
            }
            if ($lastVal > $arr[$j]) {
                 $arr[$j] = $arr[$t];//把子节点上浮，继续往下走
                 $j = $t;//下次比较的数组下标
            } else {
                break;
           }
     }
    $arr[$j] = $lastVal;//重新放入最后一个节点，如上图的操作 最后 $j 的坐标值 是 10 但是下边的删除语句删除它了，保证此二叉堆还是一个满二叉堆且符合二叉堆性质
    $unset[$arr[$len]];//删除最后一个元素
    return $arr;//返回数组
}
```
-------
#完整代码例子
```
<?php
/**
 * Created by PhpStorm.
 * User: lhs
 * Date: 2019-06-18
 * Time: 10:38
 */

/**
 * Class heap
 * 二叉堆【优先级队列】
 * 二叉堆的定义是：父节点的键值总是不大于它的孩子节点的键值（小顶堆）, 堆可以分为小顶堆和大顶堆。
 *     在数组中i处的左子节点为 2 * i + 1 右子节点在 2 * i + 2，子节点的父节点在 （i-1）/2处
 */
class heap
{
    public $heapArr = [];
    protected $heapSize = -1;

    /**
     * @param $testArr
     *
     */
    public function init($testArr)
    {

    }

    /**
     * @param $val
     */
    public function insert($val)
    {
        $this->heapSize++;
        $this->heapArr[$this->heapSize] = $val;
        $i                              = (count($this->heapArr) - 1);
        while ($i >= 0) {
            $j = ($i - 1) / 2;
            if ($j >= 0 && $this->heapArr[$i] < $this->heapArr[$j]) {
                $tmp               = $this->heapArr[$i];
                $this->heapArr[$i] = $this->heapArr[$j];
                $this->heapArr[$j] = $tmp;
                $i                 = $j;
            } else {
                break;
            }
        }
    }

    /**
     *
     */
    public function delete()
    {
        $i       = (count($this->heapArr) - 1);
        $minVal  = $this->heapArr[0];
        $lastVal = $this->heapArr[$i];
        $j       = 0;
        while (2 * $j <= $i) {
            $left  = 2 * $j + 1;
            $right = 2 * $j + 2;
            $t     = $left;
            if ($this->heapArr[$left] && $this->heapArr[$right] && $this->heapArr[$right] < $this->heapArr[$left]) {
                $t = $right;
            }
            if ($lastVal > $this->heapArr[$j]) {
                $this->heapArr[$j] = $this->heapArr[$t];
                $j                 = $t;
            } else {
                break;
            }
        }
        $this->heapArr[$j] = $lastVal;
        unset($this->heapArr[$i]);
        $this->heapSize--;
        return $minVal;
    }


    /**
     * @param array $arr
     * @return array
     */
    public function sort(array $arr)
    {
        //构建二叉堆
        $length = count($arr);
        for ($i = ($length - 2) / 2; $i >= 0; $i--) {
            $arr = $this->down($arr, $i, $length);
        }
        var_dump($arr);
        //进行堆排序
        for ($i = $length - 1; $i >= 1; $i--) {
            //把堆顶的元素与最后一个元素交换
            $temp    = $arr[$i];
            $arr[$i] = $arr[0];
            $arr[0]  = $temp;
            //下沉调整
            $arr = $this->down($arr, 0, $i);
        }
        return $arr;
    }

    /**
     * @param array $arr
     * @param int $parent
     * @param int $length
     * @return array
     */
    public function down(array $arr, int $parent, int $length)
    {
        //临时保证要下沉的元素
        $temp = $arr[$parent];
        //定位左孩子节点位置
        $child = 2 * $parent + 1;
        //开始下沉
        while ($child < $length) {
            //如果右孩子节点比左孩子小，则定位到右孩子
            if ($child + 1 < $length && $arr[$child] > $arr[$child + 1]) {
                $child++;
            }
            //如果父节点比孩子节点小或等于，则下沉结束
            if ($temp <= $arr[$child]) {
                break;
            }
            //单向赋值
            $arr[$parent] = $arr[$child];
            $parent       = $child;
            $child        = 2 * $parent + 1;
        }
        $arr[$parent] = $temp;
        return $arr;
    }

}



$testArr = [
    31,
    21,
    19,
    68,
    26,
    65,
    19,
    14,
    13,
    16,
    32
];

$heap = new heap();

/*foreach ($testArr as $val) {
    $heap->insert($val);
}*/

//var_dump($heap->heapArr);

echo json_encode($heap->getTree($array,0));
//var_dump($heap->heapArr);
```
