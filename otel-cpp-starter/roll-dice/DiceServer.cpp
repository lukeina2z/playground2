#include <cstdlib>
#include <ctime>
#include <string>
#include <cassert>
#include <chrono>
#include <thread>

#include "DiceServer.h"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "opentelemetry/trace/provider.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"

#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/batch_span_processor_factory.h"
#include "opentelemetry/sdk/trace/batch_span_processor_options.h"
#include <opentelemetry/sdk/trace/multi_span_processor.h>
#include <opentelemetry/sdk/trace/simple_processor.h>
#include "opentelemetry/sdk/trace/simple_processor_factory.h"

#include "opentelemetry/sdk/trace/exporter.h"
#include <opentelemetry/exporters/otlp/otlp_http_exporter.h>
#include <opentelemetry/exporters/ostream/span_exporter.h>
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"

using namespace std;
namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;

namespace
{
    const std::string TracerName("my-app-tracer");
    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> GetTracer()
    {
        auto retVal = opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("my-app-tracer");
        return retVal;
    }

    void InitTracer(const opentelemetry::exporter::otlp::OtlpHttpExporterOptions &opts)
    {
        namespace trace_sdk = opentelemetry::sdk::trace;
        namespace otlp_exporter = opentelemetry::exporter::otlp;
        namespace ostream_exporter = opentelemetry::exporter::trace;

        // Create Console (OStream) Exporter
        auto console_exporter = std::make_unique<ostream_exporter::OStreamSpanExporter>();

        // Create OTLP HTTP Exporter
        auto otlp_http_exporter = std::make_unique<otlp_exporter::OtlpHttpExporter>(opts);

        // Create Span Processors
        auto console_processor = std::make_unique<trace_sdk::SimpleSpanProcessor>(std::move(console_exporter));
        auto otlp_http_processor = std::make_unique<trace_sdk::SimpleSpanProcessor>(std::move(otlp_http_exporter));

        // Use MultiSpanProcessor to combine both exporters
        std::vector<std::unique_ptr<trace_sdk::SpanProcessor>> processors;
        processors.emplace_back(std::move(console_processor));
        processors.emplace_back(std::move(otlp_http_processor));
        auto multi_processor = std::make_unique<trace_sdk::MultiSpanProcessor>(std::move(processors));

        std::shared_ptr<trace_api::TracerProvider> provider = std::make_shared<trace_sdk::TracerProvider>(std::move(multi_processor));
        opentelemetry::trace::Provider::SetTracerProvider(provider);
    }

    void CleanupTracer()
    {
        std::shared_ptr<opentelemetry::trace::TracerProvider> none;
        trace_api::Provider::SetTracerProvider(none);
    }

}

class GameHandler : public oatpp::web::server::HttpRequestHandler
{
public:
    shared_ptr<OutgoingResponse> handle(const shared_ptr<IncomingRequest> &request) override
    {
        auto tracer = GetTracer();
        auto span = tracer->StartSpan("RollDiceServer");
        int low = 100;
        int high = 700;
        int random = rand() % (high - low) + low;
        // Convert a std::string to oatpp::String
        const string response = to_string(random);
        span->End();
        return ResponseFactory::createResponse(Status::CODE_200, response.c_str());
    }
};

bool Within17Seconds(const std::chrono::time_point<std::chrono::system_clock> &inputTime)
{
    // Get the current time point
    auto currentTime = std::chrono::system_clock::now();

    // Calculate the difference in seconds
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - inputTime);

    // Check if the input time is at least 100 seconds earlier
    return duration.count() < 17;
}

void run()
{
    auto tracer = GetTracer();
    auto span = tracer->StartSpan("Run-Web-Server");
    auto router = oatpp::web::server::HttpRouter::createShared();
    router->route("GET", "/rolldice", std::make_shared<GameHandler>());
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8080, oatpp::network::Address::IP_4});
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("Dice Server", "Server running on port %s", static_cast<const char *>(connectionProvider->getProperty("port").getData()));

    auto startTime = std::chrono::system_clock::now();
    auto fn = [startTime]() -> bool
    {
        auto currentTime = std::chrono::system_clock::now();
        return Within17Seconds(startTime);
    };

    server.run();
    // server.run(fn);
    server.stop();
}

int mainDiceServer(const opentelemetry::exporter::otlp::OtlpHttpExporterOptions &opts)
{
    oatpp::base::Environment::init();
    InitTracer(opts);
    auto tracer = GetTracer();
    auto span = tracer->StartSpan("Main-Fn");
    srand((int)time(0));
    run();

    span->End();
    CleanupTracer();
    // oatpp::base::Environment::destroy();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
