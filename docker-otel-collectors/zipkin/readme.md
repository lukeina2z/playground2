
docker network create p5Network

docker run --rm \
    --network p5Network \
    --name zipkin \
    -p 9411:9411 \
    openzipkin/zipkin



