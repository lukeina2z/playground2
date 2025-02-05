
docker network create jaeger-network


docker run --rm \
    --name otel-collector \
    --network jaeger-network \
    -p 4317:4317 \
    -p 4318:4318 \
    -v ./collector-config.yaml:/etc/otelcol/config.yaml \
    otel/opentelemetry-collector


