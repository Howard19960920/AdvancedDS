
## Phone book hash practice
***
> 一個簡單的 hash 練習，透過 hash 來實做電話簿的查詢，以 name 當作 key，phone 當作 value。並觀察 hash table size 以及 hash base 對於 collision 的影響。

***

1. 編譯並執行 generator.c，輸入欲產生的資料比數 n，程式將產生
* * records 檔案：內含 n 筆資料，每一筆資料包含一長度為 5 - 15 字元的姓名以及一長度為10的電話號碼。
* * queries 檔案：內含約 n/2 筆資料，每一筆資料包含一長度為 5 - 10 字元的姓名。
![](https://i.imgur.com/GGGU7Yd.png)

***

2. 編譯並且執行 hash.c ，從 argv 輸入 record file 路徑、query file 路徑、hash base、hash size，程式將產出
* * Hash Load Factor
* * Hash Maximum Collision
* * Average Query times
![](https://i.imgur.com/wA7Lknp.png)



***
