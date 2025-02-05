
docker network create p5Network


docker run --rm \
    --name otel-collector \
    --network p5Network \
    -p 4317:4317 \
    -p 4318:4318 \
    -v ./collector-config.yaml:/etc/otelcol/config.yaml \
    otel/opentelemetry-collector


