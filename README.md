# 2022_Kwangwoon_Univ_CE_DS_Project_1

> 2022년 광운대학교 데이터구조설계 과제 구현 내용입니다.

본 프로젝트에서는 C++ 언어를 기반으로 이진 탐색 트리와 연결리스트, 그리고 큐 자료구조를 이용하여 간단한 사진 파일 편집 프로그램을 구현합니다. 
 
이 프로그램은 특정 경로에 저장된 사진 파일에 대한 정보를 링크드 리스트(Linked List)로 저장한 후, 검색에 용이하게 트리 자료 구조로 저장합니다.
 
이진트리 탐색 알고리즘을 통해 사용자의 입력에 적합한 이미지 파일을 찾아내고, 해당 파일을 읽어옵니다. 이후 큐를 활용하여 각각의 이미지 파일을 읽어오고, 동일한 디렉토리의 command.txt에 입력된
명령어에 적합하게 이미지를 변형하는 기능을 추가하여 이미지 변형 프로그램을 구현합다. 

## 사용법

본 코드는 LINUX 환경에서 작성되었습니다.
`LINUX` 폴더에서 Result.h, main.cpp 파일을 '2021202039` 폴더의 main.cpp로 교체하고
`Dataset' 폴더의 이미지 파일을 활용해 테스트하세요.

자세한 요구사항은 master/2021202039_DS_project1 파일에서, 구현 로직은 '2021202039' 폴더의 보고서 pdf 파일에서 확인할 수 있습니다.
