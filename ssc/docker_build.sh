#!/bin/sh

docker build -f Dockerfile -t ssc .
docker run --rm -v $(pwd):/out ssc
