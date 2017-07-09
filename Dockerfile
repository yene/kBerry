# build with: docker build --tag yene/kberry .
# run with: docker run --rm yene/kberry
FROM golang:1.8

RUN mkdir -p /go/src/github.com/yene/kBerry
COPY . /go/src/github.com/yene/kBerry
COPY kdrive/lib/ubuntu_1404/libkdriveExpress.so /go/bin/
RUN go install github.com/yene/kBerry
#RUN ldd -v /go/bin/kBerry | grep libkdriveExpress
ENTRYPOINT ["/go/bin/kBerry"]
