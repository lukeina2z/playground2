#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "opentelemetry-cpp::common" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::common APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::common PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_common.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::common )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::common "${_IMPORT_PREFIX}/lib/opentelemetry_common.lib" )

# Import target "opentelemetry-cpp::trace" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::trace APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::trace PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_trace.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::trace )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::trace "${_IMPORT_PREFIX}/lib/opentelemetry_trace.lib" )

# Import target "opentelemetry-cpp::metrics" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::metrics APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::metrics PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_metrics.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::metrics )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::metrics "${_IMPORT_PREFIX}/lib/opentelemetry_metrics.lib" )

# Import target "opentelemetry-cpp::logs" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::logs APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::logs PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_logs.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::logs )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::logs "${_IMPORT_PREFIX}/lib/opentelemetry_logs.lib" )

# Import target "opentelemetry-cpp::version" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::version APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::version PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_version.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::version )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::version "${_IMPORT_PREFIX}/lib/opentelemetry_version.lib" )

# Import target "opentelemetry-cpp::resources" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::resources APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::resources PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_resources.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::resources )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::resources "${_IMPORT_PREFIX}/lib/opentelemetry_resources.lib" )

# Import target "opentelemetry-cpp::ostream_span_exporter" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::ostream_span_exporter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::ostream_span_exporter PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_ostream_span.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::ostream_span_exporter )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::ostream_span_exporter "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_ostream_span.lib" )

# Import target "opentelemetry-cpp::ostream_metrics_exporter" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::ostream_metrics_exporter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::ostream_metrics_exporter PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_ostream_metrics.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::ostream_metrics_exporter )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::ostream_metrics_exporter "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_ostream_metrics.lib" )

# Import target "opentelemetry-cpp::ostream_log_record_exporter" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::ostream_log_record_exporter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::ostream_log_record_exporter PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_ostream_logs.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::ostream_log_record_exporter )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::ostream_log_record_exporter "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_ostream_logs.lib" )

# Import target "opentelemetry-cpp::in_memory_span_exporter" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::in_memory_span_exporter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::in_memory_span_exporter PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_in_memory.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::in_memory_span_exporter )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::in_memory_span_exporter "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_in_memory.lib" )

# Import target "opentelemetry-cpp::in_memory_metric_exporter" for configuration "Debug"
set_property(TARGET opentelemetry-cpp::in_memory_metric_exporter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opentelemetry-cpp::in_memory_metric_exporter PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_in_memory_metric.lib"
  )

list(APPEND _cmake_import_check_targets opentelemetry-cpp::in_memory_metric_exporter )
list(APPEND _cmake_import_check_files_for_opentelemetry-cpp::in_memory_metric_exporter "${_IMPORT_PREFIX}/lib/opentelemetry_exporter_in_memory_metric.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
