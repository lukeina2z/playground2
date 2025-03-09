#pragma once

#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"

int mainDiceServer(const opentelemetry::exporter::otlp::OtlpHttpExporterOptions& opts);