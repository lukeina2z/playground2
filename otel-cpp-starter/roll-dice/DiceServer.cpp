#include <cstdlib>
#include <ctime>
#include <string>
#include <cassert>
#include <chrono>
#include <thread>

#include "DiceServer.h"
#include "xtrace.h"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;

class GameHandler : public oatpp::web::server::HttpRequestHandler
{
public:
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override
    {
        auto tracer = XTrace::GetTracer();
        auto span = tracer->StartSpan("RollDiceServer");
        auto scope = tracer->WithActiveSpan(span);

        int low = 100;
        int high = 700;
        int random = rand() % (high - low) + low;
        // Convert a std::string to oatpp::String
        const std::string response = std::to_string(random);
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
    auto tracer = XTrace::GetTracer();
    auto span = tracer->StartSpan("Run-Web-Server");
    auto scope = tracer->WithActiveSpan(span);

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

    // server.run();
    server.run(fn);
    server.stop();
}

int mainDiceServer(const opentelemetry::exporter::otlp::OtlpHttpExporterOptions &opts)
{
    oatpp::base::Environment::init();
    auto tracer = XTrace::GetTracer();
    auto span = tracer->StartSpan("Main-DiceServer");
    auto scope = tracer->WithActiveSpan(span);

    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    srand((int)time(0));
    run();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    span->End();
    // oatpp::base::Environment::destroy();
    return 0;
}
