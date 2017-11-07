## Quick Sort 快速排序

### pseudo code
![](https://i.imgur.com/z449Lta.png)


#### 合併排序(Merge Sort) 與 快速排序(Quick Sort)都是 Divide & Conquer的實做。


### 快速排序
* 平均時間複雜度 O(n * lg(n))
* Worst-case O(n^2)
* 空間複雜度 O(lgn) ~ O(n)

### 合併排序
* 平均時間複雜度 O(n * lg(n))
* Worst-case O(n * lg(n))
* 空間複雜度 O(n) 

#### 有許多語言的sorting函式底下都是用 Quick Sort實做，雖然 Worst-case 是 n^2

#### 不過透過一些演算法可以幾乎避免掉這些 worst-case，如 Median algorithm

### 程式執行說明
1. 編譯並執行 generator.c 程式將產生 n 個整數作為排序用資料。
2. 編譯 qsort.c `gcc qsort.c`
3. 把測資餵給執行檔 `time ./a.out < td`

### 單線程 Quick sort執行排序一千萬個整數的結果
![](https://i.imgur.com/GQ1qPFq.png)

### 單線程 Merge sort執行排序一千萬個整數的結果
![](https://i.imgur.com/FuHGiPB.png)


### 比較
> 兩者效率都不差，且都滿方便可以寫成多線程，但可能 Merge sort 所花記憶體較大

> 所以大部分實做還是以 quick sort 為主。

##### Note that the qsort() in stdlib is not re-entrant function, use qsort_r instead or write on your own
