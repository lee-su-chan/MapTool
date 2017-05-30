# MapTool

## 조작키
W, A, S, D: 이동  
Q: 상승  
E: 하강  
마우스 우클릭후 드래그: 회전  
←, →, ↑, ↓: 회전  
F1; UI 끄기 켜기  
F2: Wireframe 모드 끄기 켜기  
F3: 상호작용 재생 끄기 켜기  
F4: CellLine 표시 끄기 켜기  
F5: 자유이동 끄기 켜기  

## 개발자 노트
### 2017-03-21
![1](https://cloud.githubusercontent.com/assets/13383741/24149895/65523ba2-0e87-11e7-8fdb-d8cd3a6a69eb.PNG)
1. 프로젝트 생성  
2. 분할 뷰 구현

### 2017-03-22
![1](https://cloud.githubusercontent.com/assets/13383741/24201478/795e088e-0f53-11e7-84a1-77ccb80507f3.PNG)
1. FormView와 DirectX 프레임워크 연결

### 2017-03-28
![1](https://cloud.githubusercontent.com/assets/13383741/24409360/f387d6d8-140a-11e7-978a-8cff1dfa3f6a.PNG)
1. 전체적인 해상도 조절
2. 화면 크기 조절 제거
3. 최소화, 최대화 제거
4. 분할 뷰 크기 조절 제거

### 2017-03-28
![default](https://cloud.githubusercontent.com/assets/13383741/24754747/a828f014-1b12-11e7-92f3-b33c76073cf8.PNG)
1. TerrainRendering 프로젝트 소스 추가

### 2017-04-11
!사진으로 표현할 수 없기 때문에 사진은 없습니다.  
1. 조작키 변경(마우스 시점 변환 구현 등)
2. DirectXView 클래스 삭제 후 MapToolView 클래스 사용

### 2017-04-27
![1](https://cloud.githubusercontent.com/assets/13383741/25487568/937649da-2b9f-11e7-9978-afd31b0a2fc8.PNG)
![2](https://cloud.githubusercontent.com/assets/13383741/25487569/93a05694-2b9f-11e7-879b-9c4b05fe2d2a.PNG)
1. 파일 생성 다이얼로그 UI 업데이트
2. Cell Size와 Tile Size를 선택하여 지형 생성 구현

### 2017-05-30
![1](https://cloud.githubusercontent.com/assets/13383741/26587353/089eb0e2-458d-11e7-9098-aed9a5f13fba.png)
1. 원하는 텍스쳐 파일 선택 후 맵핑 구현  
2. TextureClass 내부 변경  
  
기존에는 LoadTarga()라는 함수가 있었는데 알고보니 이 함수는 fread()함수를 통해  
이미지를 바이너리 형식으로 읽어 형식에 딱 맞는 구조체를 만들고 그 안에 이미지의  
메타데이터들을 담는 것이었다.  
  
하지만 tga 형식이 아닌 다른 형식의 이미지를 읽지는 못 하였기 때문에  
나는 jpg header의 구조를 가진 구조체를 구글링하여 만들었고 fread()함수를 사용해서  
jpg 파일을 읽었지만 이상하게도 정해진 구조에 알맞은 값들이 들어가지 않았다.  
그래서 간단히 D3DX함수를 사용하여 텍스쳐를 읽으려 했지만 나는 윈도우10에 내장된  
DirectX SDK를 사용하고 있고 D3DX함수는 성능상 좋지 않다고 해서 사용하지 않게 되었다.  
  
그렇게 구글링을 하다가 DirectXTex라는 공식 라이브러리를 찾았고 그 라이브러리를 통해  
파일 형식에 맞게 이미지를 읽을 수 있게 되었다.  
  
어떻게 보면 직접 구조체를 선언하여 데이터를 받아오는 것 보다 쉬운 방법일지도 모르지만  
사실 두 경우의 성능 차이가 얼마나 있는지는 자세히 모르기 때문에 어떤 것이  
더 좋다 라고 말하기는 어렵다. 나중에 다시 원래의 방법을 동작하게 해서 DirectXTex를  
사용한 것과 비교해봐야겠다.  
