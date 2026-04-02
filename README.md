# Cpp-File-Packer
여러 개의 파일을 하나의 바이너리 아카이브(`.dat`)로 병합할 수 있습니다.
## 원

본 프로젝트는 데이터를 읽고 쓸 때 [File Header] + [File Data]의 구조를 반복하여 쌓는 방식입니다

### File Header structure
```cpp
struct FileHeader {
    char fileName[256]; // 파일 이름 (최대 256자)
    long long fileSize;  // 파일 크기 (바이트 단위)
};
```
