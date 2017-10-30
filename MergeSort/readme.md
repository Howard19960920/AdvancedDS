## Merge Sort divide and conquer

***
> 以 C 實做 Merge Sort，並與 C++ std::sort 、 Multi-thread version merge sort 並用 time 函式做時間測量、比較。

***
### 說明


1. Compile generator.c 執行並產生 n 筆測試資料。<br>
![](https://i.imgur.com/vcBjZCr.png)
2. Compile mergeSort.c 執行並透過單線程完成排序 n 筆測試資料。
![](https://i.imgur.com/3FFKEVL.png)
3. Compile mergeSort.c 執行並透過雙線程完成排序 n/2 筆測試資料，最後在 merge 在一起。
![](https://i.imgur.com/nVHcH0U.png)
4. Compile stdsort.cpp 執行並透過 c++ std::sort() 完成排序 n 筆測試資料
![](https://i.imgur.com/jtFVwvB.png)


### 結論

單線程 merge sort 與 c++ std::sort 表現差不多，而雙線程的 merge sort在排序所花的時間幾乎為單線的一半，但是整體執行時間只有比單線快一些，原因是因為大多數時間都被 IO 吃掉了。


