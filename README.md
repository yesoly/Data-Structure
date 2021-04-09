# Data-Structure
2019-1 CAUCSE Data-Structure

## Project_1 : Maze
> 1. 출구(EXIT) 대신 임의의 위치(row, col)를 목적지(destination)로 지정하여 입구에서 목적지까지의 path를 찾는다.
> 2. mark[][] 배열을 사용하지 않는다.
> 3. 어떤 위치로 처음 갔을 때 8 방향 이웃 위치 중에 목적지가 있으면 path 찾기가 종료되도록 한다.
> 4. path 찾기를 위해 이동할 방향의 결정은 매번 random하게 한다.

## Project_2 : Binary Tree
> 정수값을 element로 하는 행렬이 2차원 배열에 저장되어 주어졌다고 하자. binary search tree를 이용하여 행렬의 각 row 별로 정수값의 빈도를 count한 후, loser tree를 이용하여 행렬 전체적으로 빈도가(즉, count가) 가장 높은 정수값부터 내림순으로 정렬하여 출력하는 프로그램을 작성하시오.  
  
  
**< 요건 >**
1. 각 row 당 1개의 binary search tree를 생성.
2. 각 binary search tree는 linked representation으로 구현.
3. 각 row 별로 column 번호 증가 순으로 정수값을 하나씩 차례로 해당 binary search tree에 반영.
4. loser tree는 배열 representation으로 구현.
5. loser tree에서는 이미 생성된 binary search tree를 traverse하여 필요한 정보를 이용.
6. loser tree에서 tie breaking 규칙: count가 같으면 정수값 큰 것이 win. count와 정수값이 모두 같으면 row 번호 큰 것이 win.
7. 행렬의 row 및 column 갯수는 임의로 변경 설정할 수 있도록 아래 예시와 같이 define 문으로 정의. (단, row 개수는 power of 2 (2, 4, 8, 16, ...)가 아닌 값으로 한정)
8. 행렬의 정수값은 아래 예시와 같이 프로그램에서 2차원 배열에 직접 저장.
9. 정렬 결과 출력 양식: (row번호, 정수값, count)의 sequence
