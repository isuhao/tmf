project(tmf)

include_directories(.)

add_subdirectory(dataflow)
add_subdirectory(parser)

add_subdirectory(server)
add_subdirectory(deploy)
add_subdirectory(analyse)

option(BUILD_RDF_MODULE "Build RDF module" OFF)

if (BUILD_RDF_MODULE)
	add_subdirectory(rdf)
endif()
