FROM dockcross/windows-static-x64:latest AS builder

WORKDIR /src
COPY . .

RUN x86_64-w64-mingw32.static-g++ -static -std=c++17 -O2 -o lab1.exe *.cpp

FROM scratch AS export
COPY --from=builder /src/lab1.exe /