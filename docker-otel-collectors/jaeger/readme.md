docker run --rm  -e COLLECTOR_ZIPKIN_HOST_PORT=:9411 \
    -p 16686:16686 \
    -p 4317:4317 \
    -p 4318:4318 \
    -p 9411:9411 \
    jaegertracing/all-in-one:latest





docker run --rm --name jaeger \
    --name jaeger \
    --network p5Network \
    -e COLLECTOR_ZIPKIN_HTTP_HTTP_PORT=9411 \
    -e JAEGER_LOG_LEVEL=debug \
    -p 9411:9411 \
    -p 16686:16686 \
    -p 14317:14317 \
    -p 14318:14318 \
    jaegertracing/all-in-one:latest \
    --collector.otlp.grpc.host-port=14317 \
    --collector.otlp.http.host-port=14318




