### 20194546윤경호 12장 6번 연습문제.


#### 다음의 정렬기법을 이용하여 다음의 정수 배열을 오름차순으로 정렬하라. 각 단계에서의 배열의 내용을 나타내어라.

![image](https://user-images.githubusercontent.com/94778099/173365140-fb7a815d-2ecf-41a2-b552-b9d864f3a98c.png)


  
  #### 퀵정렬
  
  53을 피벗으로 잡고, 맨 앞을 i 피벗 뒤를 j라고 하자.
  
 
  피벗 53/  i는 71 j는 72이다.
  
  71 72 둘다 피벗보다 크므로 교환하지 않고, j만 왼쪽으로 옮긴다.
  
  71 82 둘다 피벗보다 크므로 교환하지 않고, j만 왼쪽으로 옮긴다.
  
  71은 38보다 크므로 위치를 바꾸고, i를 오른쪽, j를 왼쪽으로 옮긴다. 38 49 92 55 71 82 72 53 (i는 49, j는 55에 위치)
  
  49는 55보다 작고 피벗보다 크므로 교환하지 않고 j를 왼쪽, i를 오른쪽으로 옮긴다. j,i 는 92에 위치.
  
  92는 53보다 크므로 피벗과 위치를 바꾼다. 38 49 53 55 71 82 72 92.
  
  왼쪽은 해봣자 마무리가 됫으므로, 오른쪽을 본다. 55 71 82 72 92 
  
  피벗 92로 잡고 제일왼쪽i, 피벗 왼쪽을 j로 잡는다.
  
  55는 72보다 작고 피벗보다 작으므로 i값을 올린다.
  
  71은 72보다 작고 피벗보다 작으므로 i값을 올린다.
  
  82는 72보다 크므로, 위치를 서로 바꾼다. 그리고 i j값을 하나씩 올린다. 55 71 72 82 92
  
  왼쪽 38 49 53/ 오른쪽 55 71 72 82 92 으로 퀵정렬이 완성되었다.
  
  
  #### 합병정렬
  
  
  71 | 49 | 92 | 55 | 38 | 82 | 72 | 53
  
  쪼갠다..
  
  71 | 49 | 92 | 55            38 | 82 | 72 | 53
  
  
  또 쪼갠다
  
  71 | 49      92 | 55          38 | 82           72 | 53
  
  
  또 쪼갠다...
  
  71  49         92    55         38   82         72  53 
  
  
  크키가 작은것을 앞으로 옮기고 붙인다.
  
  49 | 71         55 | 92       38 | 82        53 | 72
  
  
  한번 더 반복한다.
  
  
  49 | 55 | 71 | 92              38 | 53 | 72  | 82
  
  
  한번 더 반복한다.
  
  38 | 49 | 53 | 55 | 71 | 72 | 82 | 92
  
  완성.
  
  #### 히프 정렬
  
  
  
  ![데이터구조히프](https://user-images.githubusercontent.com/94778099/173372654-c6c4a818-4d59-440f-a09e-47e48c147573.jpg)

  사진이 작습니다..  따로 사진 파일도 올리겠습니다.
  
  트리에 다 나열 한 후,
  
  제일 말단에 있는 히프를 빼고, 제일 바깥쪽에 있는 히프를 올립니다.
  
  -> 92가 빠져나가고, 53이 올라감.
  
  53은 좌우중 더 큰 82보다 작으므로 위치가 바뀝니다.
  
  그리고 더 큰 72보다 작으므로 위치가 또 다시 바뀝니다.
 
  빠져나간 값 / / / / / / / 92
   
   현재 트리 상태
   ![image](https://user-images.githubusercontent.com/94778099/173374002-5406b842-25a7-4a25-9e03-c9564bf8a63d.png)

   82가 빠져나가고, 53이 말단위치에 간다.
   
   53은 55와 72중 더 큰 72와 바뀐다.
   
   53은 71과 바뀐다.
   
   빠져나간 값 / / / / / / 82 / 92

  트리상태
  ![image](https://user-images.githubusercontent.com/94778099/173374451-0e68051f-89cd-4c91-9a8d-4d40e6874170.png)

  72가 빠져나가고 그 위치에 53이 올라온다.
  
  53은 더 큰 71과 바뀐다.
  
  빠져나간 값 / / / / / / 72 82 92
  
  트리상태
  
  ![image](https://user-images.githubusercontent.com/94778099/173374768-27088810-7db1-414e-88a5-c3f62b1aed02.png)
  
  71이 빠지고 38이 올라온다.
  
  38은 더 큰 55랑 바뀐다.
  
  38은 49랑 바뀐다.
  
  빠져나간값 / / / / / / 71 72 82 92
  
  트리상태
  
  ![image](https://user-images.githubusercontent.com/94778099/173375015-2b7b059a-c823-4269-957a-4445d1d19daf.png)
  
  55가 빠지고 38이 올라온다.
  
  38은 더 큰 53과 바뀐다.
  
  빠져나간값 / / / / / 55 71 72 82 92
  
  트리상태
  
  ![image](https://user-images.githubusercontent.com/94778099/173375293-0298456d-d711-4ebd-8251-b1249a9ad3e4.png)
  
  53이 빠지고 38이 올라온다.
  
  38은 49와 바뀐다.
  
  빠져나간값 / / / / 53 55 71 72 82 92
  
  트리상태
  
  ![image](https://user-images.githubusercontent.com/94778099/173375511-9a7e4e57-de2e-4ba6-8adb-5983204a2816.png)
  
  그리고 49가 빠지고, 38이 빠진다.. 38 49 53 55 71 72 82 92
  
  히프 정렬 끝.

  


  
  
  
  
  
  
  
  
  
  
