# Image-scrambling-with-pseudo-random-patterns-from-direct-sequence-generating
## 畢業專題
藉由Linear Feedback Shift Register產生的偽亂數來打亂影像，藉此降低連續錯誤的頻率。
這個程式只有利用1來取代錯誤，並未載入實際圖片做計算。

### 1.設定direct sequence
設定n階的direct sequence來產生週期為(2^n)-1的最大序列，也就是偽亂數。
這裡是利用[Primitive Polynomial List](https://www.partow.net/programming/polynomials/index.html) 來做設置。
