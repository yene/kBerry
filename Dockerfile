# build with: docker build --tag yene/kberry .
# run with: docker run --rm yene/kberry
FROM golang:1.8

COPY . /go/src/github.com/yene/kBerry
# Copy the required library into searchpath.
COPY kdrive/lib/ubuntu_1404/libkdriveExpress.so /go/bin/
RUN go install github.com/yene/kBerry
ENTRYPOINT ["/go/bin/kBerry"]
