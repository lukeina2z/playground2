#include "xtrace.h"

#include <opentelemetry/sdk/resource/resource.h>

namespace XTrace
{
    const std::string TracerName("my-app-tracer");
    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> GetTracer()
    {
        auto retVal = opentelemetry::trace::Provider::GetTracerProvider()->GetTracer(TracerName);
        return retVal;
    }

    void InitTracer(const opentelemetry::exporter::otlp::OtlpHttpExporterOptions &opts)
    {
        namespace trace_sdk = opentelemetry::sdk::trace;
        namespace otlp_exporter = opentelemetry::exporter::otlp;
        namespace ostream_exporter = opentelemetry::exporter::trace;

        auto console_exporter = std::make_unique<ostream_exporter::OStreamSpanExporter>();
        auto console_processor = std::make_unique<trace_sdk::SimpleSpanProcessor>(std::move(console_exporter));

        auto otlp_http_exporter = std::make_unique<otlp_exporter::OtlpHttpExporter>(opts);
        auto otlp_http_processor = std::make_unique<trace_sdk::SimpleSpanProcessor>(std::move(otlp_http_exporter));

        std::vector<std::unique_ptr<trace_sdk::SpanProcessor>> processors;
        processors.emplace_back(std::move(console_processor));
        processors.emplace_back(std::move(otlp_http_processor));
        auto multi_processor = std::make_unique<trace_sdk::MultiSpanProcessor>(std::move(processors));

        auto resource_attributes = opentelemetry::sdk::resource::Resource::Create({{"service.name", "Gaming-Service"}});
        std::shared_ptr<trace_api::TracerProvider> provider = std::make_shared<trace_sdk::TracerProvider>(std::move(multi_processor));
        opentelemetry::trace::Provider::SetTracerProvider(provider);
    }

    void CleanupTracer()
    {
        GetTracer()->ForceFlushWithMicroseconds(1000);
        GetTracer()->CloseWithMicroseconds(1000);

        std::shared_ptr<opentelemetry::trace::TracerProvider> none;
        trace_api::Provider::SetTracerProvider(none);
    }

}