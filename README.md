# MTCNN C version
## resource 

## 작업 해야할 것
- ~~fc layer~~
- ~~fixed pointer~~
- ~~Pnet 검증~~
- ~~Quantizer~~
- ~~OverflowCheck~~
- ~~Print layer output & make functions~~
- ~~ 이미지 해상도 상수(ex. myPnet(weightBuffer, imageBuffer, 72, 144)) 입력 -> args 변경 필요 ~~
- ~~Resizing: ~~
  - ~~원본, 1/2, 2/3 스케일(자세한 방법은 엑셀 참조)~~
  - ~~파일저장x, 메모리 상에서 처리 ~~
- (좌표변환시 필요)이미지 입력받아 12x12 패치 묶음으로 리턴 **or** pnet 리턴에 인덱스 포함
- ~~ Pnet 리턴 Threshold 값 적용 ~~
- ~~ Bounding Box 좌표 판별(이미지 내에 들어오는 박스인가?) ~~
- ~~ Sorting: Pnet result 상위 32개 x3(스케일 3개) = 총 96개 리턴 ~~
  - 모듈 분리(기존 Pnet 내에서 sorting 적용 후 리턴 -> pnet 리턴된 값 인풋으로 sorting)
- Rnet 검증: 
  - weight 로드가 정상적으로 되는가? 
  - input value가 정상적으로 들어오는가? 
  - input x weight 연산이 정상적으로 수행되는가?
- 연산 내 변수들 비트수 체크
- ~~ 박스 to 원본 좌표로 치환(모듈) ~~
- NMS

## 구동법
1. main.c main() 함수 내 파일 경로 변경
2. $ cmake CMakeLists.txt
3. $ make
4. $ ./mtcnn  # Linux
5. 16_print_pnet.txt 파일에 pnet output 출력(헥사값)
