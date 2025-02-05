
docker network create p5Network

docker run --rm \
    --network p5Network \
    --name zipkin \
    -e ZIPKIN_LOG_LEVEL=debug \
    -p 9411:9411 \
    openzipkin/zipkin:latest



